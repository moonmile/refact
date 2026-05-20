#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "qrcode_url.h"

/* --- hex_to_bin ---------------------------------------------------------- */

static void test_hex_to_bin_valid(void)
{
    uint8_t bin[16] = {0};
    int n = hex_to_bin("560DB2A64C2BBE61FBE6810AFCB25230", bin, 16);
    CU_ASSERT_EQUAL(n, 16);
    CU_ASSERT_EQUAL(bin[0], 0x56);
    CU_ASSERT_EQUAL(bin[1], 0x0D);
    CU_ASSERT_EQUAL(bin[2], 0xB2);
    CU_ASSERT_EQUAL(bin[15], 0x30);
}

static void test_hex_to_bin_lowercase(void)
{
    uint8_t bin[4] = {0};
    int n = hex_to_bin("deadbeef", bin, 4);
    CU_ASSERT_EQUAL(n, 4);
    CU_ASSERT_EQUAL(bin[0], 0xDE);
    CU_ASSERT_EQUAL(bin[1], 0xAD);
    CU_ASSERT_EQUAL(bin[2], 0xBE);
    CU_ASSERT_EQUAL(bin[3], 0xEF);
}

static void test_hex_to_bin_short(void)
{
    /* 32文字未満は16バイトに満たないのでエラー扱いになる */
    uint8_t bin[16] = {0};
    int n = hex_to_bin("1234", bin, 16);
    CU_ASSERT_EQUAL(n, 2);   /* 4文字 → 2バイトだけ変換 */
}

static void test_hex_to_bin_limit(void)
{
    /* bin_len より多くは書き込まない */
    uint8_t bin[2] = {0};
    int n = hex_to_bin("AABBCCDD", bin, 2);
    CU_ASSERT_EQUAL(n, 2);
    CU_ASSERT_EQUAL(bin[0], 0xAA);
    CU_ASSERT_EQUAL(bin[1], 0xBB);
}

/* --- base64_encode -------------------------------------------------------- */

static void test_base64_encode_hello(void)
{
    char dst[64] = {0};
    int n = base64_encode((const uint8_t *)"Hello", 5, dst, sizeof(dst));
    CU_ASSERT_EQUAL(n, 8);
    CU_ASSERT_STRING_EQUAL(dst, "SGVsbG8=");
}

static void test_base64_encode_three_bytes(void)
{
    char dst[64] = {0};
    int n = base64_encode((const uint8_t *)"abc", 3, dst, sizeof(dst));
    CU_ASSERT_EQUAL(n, 4);
    CU_ASSERT_STRING_EQUAL(dst, "YWJj");
}

static void test_base64_encode_zeros(void)
{
    const uint8_t src[3] = {0, 0, 0};
    char dst[64] = {0};
    int n = base64_encode(src, 3, dst, sizeof(dst));
    CU_ASSERT_EQUAL(n, 4);
    CU_ASSERT_STRING_EQUAL(dst, "AAAA");
}

/* --- url_encode ----------------------------------------------------------- */

static void test_url_encode_alnum(void)
{
    char dst[64] = {0};
    int n = url_encode("abc123", 6, dst, sizeof(dst));
    CU_ASSERT_EQUAL(n, 6);
    CU_ASSERT_STRING_EQUAL(dst, "abc123");
}

static void test_url_encode_space(void)
{
    char dst[64] = {0};
    int n = url_encode("hello world", 11, dst, sizeof(dst));
    CU_ASSERT_EQUAL(n, 11);
    CU_ASSERT_STRING_EQUAL(dst, "hello+world");
}

static void test_url_encode_equals(void)
{
    char dst[64] = {0};
    int n = url_encode("a==", 3, dst, sizeof(dst));
    CU_ASSERT_EQUAL(n, 7);
    CU_ASSERT_STRING_EQUAL(dst, "a%3D%3D");
}

static void test_url_encode_slash_plus(void)
{
    char dst[64] = {0};
    url_encode("/+", 2, dst, sizeof(dst));
    CU_ASSERT_STRING_EQUAL(dst, "%2F%2B");
}

/* --- str_to_time_t -------------------------------------------------------- */

static void test_str_to_time_t(void)
{
    /* mktime はローカル時刻として解釈する。
     * ここでは戻り値が time_t として有効な正値であることだけ確認する。 */
    time_t t = str_to_time_t("2024/12/31 23:59:00");
    CU_ASSERT(t > 0);
}

/* --- make_qrcode_url ------------------------------------------------------ */

static void test_make_qrcode_url_normal(void)
{
    char buf[256] = {0};
    const char *base_url    = "https://simple.com/qrcode?";
    const char *encrypt_key = "560DB2A64C2BBE61FBE6810AFCB25230";
    time_t t = str_to_time_t("2024/12/31 23:59:00");

    int n = make_qrcode_url(buf, sizeof(buf), 1, "XXXXX-01234567",
                            base_url, encrypt_key, t);

    /* URL が正常に生成されたことを確認する */
    CU_ASSERT(n > 0);
    CU_ASSERT_NSTRING_EQUAL(buf, base_url, strlen(base_url));
    /* ベース URL よりも長いこと（暗号文が付加されている） */
    CU_ASSERT((int)strlen(buf) > (int)strlen(base_url));
}

static void test_make_qrcode_url_invalid_key(void)
{
    char buf[256] = {0};
    time_t t = str_to_time_t("2024/12/31 23:59:00");

    int n = make_qrcode_url(buf, sizeof(buf), 1, "XXXXX-01234567",
                            "https://simple.com/qrcode?",
                            "1234" /* 短すぎる鍵 */, t);
    CU_ASSERT_EQUAL(n, -1);
}

static void test_make_qrcode_url_buf_too_small(void)
{
    char buf[10] = {0};   /* 明らかに小さすぎるバッファ */
    const char *encrypt_key = "560DB2A64C2BBE61FBE6810AFCB25230";
    time_t t = str_to_time_t("2024/12/31 23:59:00");

    int n = make_qrcode_url(buf, sizeof(buf), 1, "XXXXX-01234567",
                            "https://simple.com/qrcode?",
                            encrypt_key, t);
    CU_ASSERT_EQUAL(n, -2);
}

static void test_make_qrcode_url_diff_device(void)
{
    char buf[256] = {0};
    const char *base_url    = "https://example.com/qr?";
    const char *encrypt_key = "560DB2A64C2BBE61FBE6810AFCB25230";
    time_t t = str_to_time_t("2025/01/01 00:00:00");

    int n = make_qrcode_url(buf, sizeof(buf), 2, "DEV-99999999",
                            base_url, encrypt_key, t);
    CU_ASSERT(n > 0);
    CU_ASSERT_NSTRING_EQUAL(buf, base_url, strlen(base_url));
}

/* --- スイート登録 --------------------------------------------------------- */

void make_suite_qrcode(void)
{
    CU_pSuite s = CU_add_suite("qrcode_url", NULL, NULL);

    CU_add_test(s, "hex_to_bin: valid",     test_hex_to_bin_valid);
    CU_add_test(s, "hex_to_bin: lowercase", test_hex_to_bin_lowercase);
    CU_add_test(s, "hex_to_bin: short",     test_hex_to_bin_short);
    CU_add_test(s, "hex_to_bin: limit",     test_hex_to_bin_limit);

    CU_add_test(s, "base64: Hello",         test_base64_encode_hello);
    CU_add_test(s, "base64: three bytes",   test_base64_encode_three_bytes);
    CU_add_test(s, "base64: zeros",         test_base64_encode_zeros);

    CU_add_test(s, "url: alnum passthrough",test_url_encode_alnum);
    CU_add_test(s, "url: space -> +",       test_url_encode_space);
    CU_add_test(s, "url: = -> %3D",         test_url_encode_equals);
    CU_add_test(s, "url: / and + encoded",  test_url_encode_slash_plus);

    CU_add_test(s, "str_to_time_t",         test_str_to_time_t);

    CU_add_test(s, "make_qrcode_url: normal",     test_make_qrcode_url_normal);
    CU_add_test(s, "make_qrcode_url: bad key",    test_make_qrcode_url_invalid_key);
    CU_add_test(s, "make_qrcode_url: buf small",  test_make_qrcode_url_buf_too_small);
    CU_add_test(s, "make_qrcode_url: diff device",test_make_qrcode_url_diff_device);
}

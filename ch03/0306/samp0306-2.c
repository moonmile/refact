#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/rand.h>


#define ESLC_SETTING_NAME_LEN 31
#define ESLC_SETTING_QR_ENCRYPT_KEY_LEN  32          // QRコード暗号化キーの長さ
#define ESLC_SETTING_QR_URL_LEN          255         // QRコードURLの長さ

typedef struct flash_data_settings {
    // 設定データ関連
    uint8_t name[ESLC_SETTING_NAME_LEN+1];
    uint8_t qrEncyptKey[ESLC_SETTING_QR_ENCRYPT_KEY_LEN];
    uint32_t qrEncyptKey_end ;  // 未使用
    uint8_t qrUrl[ESLC_SETTING_QR_URL_LEN+1];
  
} flash_data_settings_t ;
  
extern flash_data_settings_t setting_data ;


extern time_t str_to_time_t( const char *fmt );
extern const char *make_qrcocde_url( 
    int type,
    const char *device_id,
    const char *url,
    const char *encypt_key,
    time_t t ) ;

// Test suite initialization function
static int init_suite(void) {
    return 0;
}

// Test suite cleanup function
static int clean_suite(void) {
    return 0;
}

static void test_make_qrcode_url_valid() {
    memset(&setting_data, 0, sizeof(setting_data));
    strcpy((char*)setting_data.name, "XXXXX-01234567");
    strcpy((char*)setting_data.qrEncyptKey, "560DB2A64C2BBE61FBE6810AFCB25230");
    strcpy((char*)setting_data.qrUrl, "https://simple.com/qrcode?");
    time_t t = str_to_time_t("2024/12/31 23:59:00");

    const char *url = make_qrcocde_url(
        1,
        (const char *)setting_data.name,
        (const char *)setting_data.qrUrl,
        (const char *)setting_data.qrEncyptKey,
        t
    );

    CU_ASSERT_STRING_EQUAL(url, "https://simple.com/qrcode?msWBgyUw2s99TZP1vdX3j6BMbnvB57WHpfn5eIM7w");
}

static void test_make_qrcode_url_invalid_key() {
    memset(&setting_data, 0, sizeof(setting_data));
    strcpy((char*)setting_data.name, "XXXXX-01234567");
    strcpy((char*)setting_data.qrEncyptKey, "INVALIDKEY1234567890");
    strcpy((char*)setting_data.qrUrl, "https://simple.com/qrcode?");
    time_t t = str_to_time_t("2024/12/31 23:59:00");

    const char *url = make_qrcocde_url(
        1,
        (const char *)setting_data.name,
        (const char *)setting_data.qrUrl,
        (const char *)setting_data.qrEncyptKey,
        t
    );

    CU_ASSERT_STRING_EQUAL(url, "error1");
}

static void test_make_qrcode_url_invalid_url() {
    memset(&setting_data, 0, sizeof(setting_data));
    strcpy((char*)setting_data.name, "XXXXX-01234567");
    strcpy((char*)setting_data.qrEncyptKey, "560DB2A64C2BBE61FBE6810AFCB25230");
    strcpy((char*)setting_data.qrUrl, ""); // Invalid URL
    time_t t = str_to_time_t("2024/12/31 23:59:00");

    const char *url = make_qrcocde_url(
        1,
        (const char *)setting_data.name,
        (const char *)setting_data.qrUrl,
        (const char *)setting_data.qrEncyptKey,
        t
    );

    CU_ASSERT_STRING_EQUAL(url, "error1");
}

void make_suite_test2(void) {
    CU_pSuite suite = CU_add_suite("Test Suite for make_qrcocde_url", init_suite, clean_suite);
    CU_add_test(suite, "Test valid QR code URL generation", test_make_qrcode_url_valid);
    CU_add_test(suite, "Test invalid encryption key", test_make_qrcode_url_invalid_key);
    CU_add_test(suite, "Test invalid URL", test_make_qrcode_url_invalid_url);
}

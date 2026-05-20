#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

#include <openssl/evp.h>
#include <openssl/aes.h>

#include "qrcode_url.h"

/* POSIX の strptime が Windows にないため独自実装 */
static int parse_datetime(const char *s, struct tm *tm)
{
    int year, month, day, hour, minute, second;
    if (sscanf(s, "%d/%d/%d %d:%d:%d",
               &year, &month, &day, &hour, &minute, &second) != 6) {
        return 0;
    }
    tm->tm_year  = year - 1900;
    tm->tm_mon   = month - 1;
    tm->tm_mday  = day;
    tm->tm_hour  = hour;
    tm->tm_min   = minute;
    tm->tm_sec   = second;
    tm->tm_isdst = -1;
    return 1;
}

time_t str_to_time_t(const char *fmt)
{
    struct tm tm = {0};
    parse_datetime(fmt, &tm);
    return mktime(&tm);
}

struct tm *localtime_jst(time_t *t)
{
    time_t t_jst = *t + 9 * 60 * 60;
    return gmtime(&t_jst);
}

int hex_to_bin(const char *hex, uint8_t *bin, int bin_len)
{
    int i = 0;
    int j = 0;
    while (hex[i] != '\0') {
        int hi = hex[i];
        int lo = hex[i + 1];
        if (lo == '\0') return j;

        if      (hi >= '0' && hi <= '9') hi = hi - '0';
        else if (hi >= 'A' && hi <= 'F') hi = hi - 'A' + 10;
        else if (hi >= 'a' && hi <= 'f') hi = hi - 'a' + 10;
        else                             hi = 0;

        if      (lo >= '0' && lo <= '9') lo = lo - '0';
        else if (lo >= 'A' && lo <= 'F') lo = lo - 'A' + 10;
        else if (lo >= 'a' && lo <= 'f') lo = lo - 'a' + 10;
        else                             lo = 0;

        bin[j] = (uint8_t)(hi * 16 + lo);
        i += 2;
        j++;
        if (j >= bin_len) return j;
    }
    return j;
}

int base64_encode(const uint8_t *src, int src_len, char *dst, int dst_len)
{
    static const char tbl[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int i = 0;
    int j = 0;
    while (i < src_len) {
        if (j + 4 >= dst_len) break;
        int b0 = src[i];
        int b1 = (i + 1 < src_len) ? src[i + 1] : 0;
        int b2 = (i + 2 < src_len) ? src[i + 2] : 0;
        dst[j++] = tbl[b0 >> 2];
        dst[j++] = tbl[((b0 & 0x03) << 4) | (b1 >> 4)];
        dst[j++] = (i + 1 < src_len) ? tbl[((b1 & 0x0f) << 2) | (b2 >> 6)] : '=';
        dst[j++] = (i + 2 < src_len) ? tbl[b2 & 0x3f]                       : '=';
        i += 3;
    }
    return j;
}

int url_encode(const char *src, int src_len, char *dst, int dst_len)
{
    int i = 0;
    int j = 0;
    while (i < src_len) {
        unsigned char c = (unsigned char)src[i];
        if (c == ' ') {
            if (j + 1 >= dst_len) break;
            dst[j++] = '+';
        } else if ((c >= 'A' && c <= 'Z') ||
                   (c >= 'a' && c <= 'z') ||
                   (c >= '0' && c <= '9') ||
                   c == '-' || c == '_' || c == '.') {
            if (j + 1 >= dst_len) break;
            dst[j++] = (char)c;
        } else {
            if (j + 3 >= dst_len) break;
            sprintf(dst + j, "%%%02X", c);
            j += 3;
        }
        i++;
    }
    dst[j] = '\0';
    return j;
}

int make_qrcode_url(char *buf, int buf_len,
    int type, const char *device_id,
    const char *url, const char *encrypt_key,
    time_t t)
{
    /* 鍵を16進数からバイト配列に変換 */
    uint8_t key[16] = {0};
    if (hex_to_bin(encrypt_key, key, 16) != 16) {
        return -1;
    }
    uint8_t iv[16] = {0};

    /* 平文を構築: "{type},{device_id},{YYYYMMDDHHMMSS}" */
    char data[128] = {0};
    struct tm *tm = localtime_jst(&t);
    snprintf(data, sizeof(data), "%d,%s,", type, device_id);
    strftime(data + strlen(data), sizeof(data) - strlen(data), "%Y%m%d%H%M%S", tm);
    int data_len = (int)strlen(data);

    /* AES-128-CBC 暗号化 */
    uint8_t ciphertext[128] = {0};
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    int update_len = 0;
    int final_len  = 0;
    EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv);
    EVP_EncryptUpdate(ctx, ciphertext, &update_len, (const uint8_t *)data, data_len);
    EVP_EncryptFinal_ex(ctx, ciphertext + update_len, &final_len);
    EVP_CIPHER_CTX_free(ctx);
    int ciphertext_len = update_len + final_len;

    /* Base64 エンコード */
    char b64[256] = {0};
    int  b64_len  = base64_encode(ciphertext, ciphertext_len, b64, (int)sizeof(b64));

    /* URL エンコード */
    char enc[512] = {0};
    url_encode(b64, b64_len, enc, (int)sizeof(enc));

    /* ベース URL + エンコード済み暗号文を結合 */
    int url_len = (int)strlen(url);
    int enc_len = (int)strlen(enc);
    if (url_len + enc_len + 1 > buf_len) {
        return -2;
    }
    memcpy(buf, url, url_len);
    memcpy(buf + url_len, enc, enc_len);
    buf[url_len + enc_len] = '\0';
    return url_len + enc_len;
}

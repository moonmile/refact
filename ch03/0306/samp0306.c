#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

static int strptime(const char *datetimeStr, const char *format, struct tm *tm) {
    int year, month, day, hour, minute, second;

    // 文字列を解析してそれぞれの値を取得
    if (sscanf(datetimeStr, "%d/%d/%d %d:%d:%d",
               &year, &month, &day, &hour, &minute, &second) != 6) {
        return 0;  // 解析エラー
    }

    // `struct tm` を設定
    tm->tm_year = year - 1900;  // `tm_year` は 1900 年からの年数を表す
    tm->tm_mon = month - 1;     // `tm_mon` は 0 (1月) から 11 (12月) を表す
    tm->tm_mday = day;
    tm->tm_hour = hour;
    tm->tm_min = minute;
    tm->tm_sec = second;
    tm->tm_isdst = -1;  // 夏時間情報を使用しない

    return 1;  // 成功
}


time_t str_to_time_t( const char *fmt ) {
    struct tm tm = {0};
    strptime(fmt, "%Y/%m/%d %H:%M:%S", &tm);
    return mktime(&tm) ;
}

struct tm *localtime_jst( time_t *t )
{
    time_t t2 = *t + 9*60*60;
    return gmtime( &t2 );
}

int hex_to_bin( const char *hex, uint8_t *bin, int bin_len ) 
{
    int i = 0;
    int j = 0;
    while ( hex[i] != 0 ) {
        int ch1 = hex[i];
        if ( ch1 == 0 ) return j;
        int ch2 = hex[i+1];
        if ( ch2 == 0 ) return j;
        
        if ( ch1 >= '0' && ch1 <= '9' ) {
            ch1 = ch1 - '0';
        } else if ( ch1 >= 'A' && ch1 <= 'F' ) {
            ch1 = ch1 - 'A' + 10;
        } else if ( ch1 >= 'a' && ch1 <= 'f' ) {
            ch1 = ch1 - 'a' + 10;
        } else {
            ch1 = 0;
        }
        if ( ch2 >= '0' && ch2 <= '9' ) {
            ch2 = ch2 - '0';
        } else if ( ch2 >= 'A' && ch2 <= 'F' ) {
            ch2 = ch2 - 'A' + 10;
        } else if ( ch2 >= 'a' && ch2 <= 'f' ) {
            ch2 = ch2 - 'a' + 10;
        } else {
            ch2 = 0;
        }
        bin[j] = ch1 * 16 + ch2;
        i += 2;
        j++;
        if ( j >= bin_len ) return j;
    }
    return j;
}
// base64 エンコード
int base64_encode(const uint8_t *src, int src_len, char *dst, int dst_len) 
{
    static const char base64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int i = 0;
    int j = 0;
    while (i < src_len) {
        int b0 = src[i];
        int b1 = (i + 1 < src_len) ? src[i+1] : 0;
        int b2 = (i + 2 < src_len) ? src[i+2] : 0;
        dst[j] = base64[b0 >> 2];
        j++;
        dst[j] = base64[((b0 & 0x03) << 4) | (b1 >> 4)];
        j++;
        dst[j] = (i + 1 < src_len) ? base64[((b1 & 0x0f) << 2) | (b2 >> 6)] : '=';
        j++;
        dst[j] = (i + 2 < src_len) ? base64[b2 & 0x3f] : '=';
        j++;
        i += 3;
    }
    return j;
}


int url_encode( const char *src, int src_len, char *dst, int dst_len ) 
{
    int i = 0;
    int j = 0;
    while ( i < src_len ) {
        if ( src[i] == ' ' ) {
            dst[j] = '+';
            j++;
        } else if ( (src[i] >= 'A' && src[i] <= 'Z') ||
                    (src[i] >= 'a' && src[i] <= 'z') ||
                    (src[i] >= '0' && src[i] <= '9') ||
                    src[i] == '-' || src[i] == '_' || src[i] == '.' ) {
            dst[j] = src[i];
            j++;
        } else {
            if ( j + 3 < dst_len ) {
                sprintf( dst+j, "%%%02X", src[i] );
                j += 3;
            }
        }
        i++;
    }
    return j;
}

/// 
char qrcocde_url[128];


const char *make_qrcocde_url( 
    int type,
    const char *device_id,
    const char *url,
    const char *encypt_key,
    time_t t ) 
{
    memset( qrcocde_url, 0x0, sizeof(qrcocde_url) );

    // 共通鍵を16進数からバイト配列に変換
    uint8_t key[16] = {0};
    int len = hex_to_bin( encypt_key, key, 16 );
    if ( len != 16 ) {
        return "error1";
    }
    uint8_t iv[16] = {0};

    // 暗号化するデータ
    static uint8_t data[128] = {0};
    struct tm *tm = localtime_jst(&t);
    sprintf( (char *)data, "%d,%s,", type, device_id );
    strftime((char *)data + strlen((char*)data), 
        sizeof(data) - strlen((char*)data), "%Y%m%d%H%M%S", tm );
    int data_len = strlen((char *)data); 

    uint8_t ciphertext[100] = {0};

    // OpenSSLのEVP APIを使用してAES-256-CBC暗号化を実行
    EVP_CIPHER_CTX *ctx;
    int ciphertext_len;    
    // コンテキストの作成
    ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv);
    // EVP_CIPHER_CTX_set_padding(ctx, 1);
    len = 0;
    EVP_EncryptUpdate(ctx, ciphertext, &len, data, data_len);
    ciphertext_len = len;
    int pad = 0;
    EVP_EncryptFinal_ex(ctx, ciphertext + len, &pad);
    ciphertext_len += len;
    EVP_CIPHER_CTX_free(ctx);

    char *base64 = (char *)malloc(128);
    char *enc_base64 = (char *)malloc(128);
    // BASE64エンコード
    int base64_len = base64_encode( ciphertext, ciphertext_len, base64, sizeof(base64) );
    // URLエンコード
    url_encode( base64, base64_len, enc_base64, sizeof(enc_base64) );

    memset( qrcocde_url, 0x0, sizeof(qrcocde_url) );
    strcat( qrcocde_url, url );
    strcat( qrcocde_url, enc_base64 );

    free(base64);
    free(enc_base64);
 
    return qrcocde_url;
}





// Test suite initialization function
static int init_suite(void) {
    return 0;
}

// Test suite cleanup function
static int clean_suite(void) {
    return 0;
}

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
  
flash_data_settings_t setting_data ;

static void test_qrcode_url() {
    
    memset(&setting_data, 0, sizeof(setting_data));
    strcpy((char*)setting_data.name, "XXXXX-01234567");
    strcpy((char*)setting_data.qrEncyptKey, "560DB2A64C2BBE61FBE6810AFCB25230");
    strcpy((char*)setting_data.qrUrl, "https://simple.com/qrcode?");
    time_t t = str_to_time_t("2024/12/31 23:59:00");    // 202412312359

    const char *url = make_qrcocde_url(
        1, 
        (const char *)setting_data.name, 
        (const char *)setting_data.qrUrl,
        (const char *)setting_data.qrEncyptKey,
        t );
    CU_ASSERT_STRING_EQUAL(url, "https://simple.com/qrcode?msWBgyUw2s99TZP1vdX3j6BMbnvB57WHpfn5eIM7w");
}

void make_suite_test1(void) {
    CU_pSuite suite = CU_add_suite("Test Suite", init_suite, clean_suite);
    CU_add_test(suite, "Test QR url", test_qrcode_url);
}

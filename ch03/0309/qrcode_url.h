#ifndef QRCODE_URL_H
#define QRCODE_URL_H

#include <stdint.h>
#include <time.h>

/* 文字列 "YYYY/MM/DD HH:MM:SS" を time_t に変換する */
time_t str_to_time_t(const char *fmt);

/* time_t を JST の struct tm に変換する */
struct tm *localtime_jst(time_t *t);

/* hex 文字列をバイト配列に変換する。戻り値は変換したバイト数 */
int hex_to_bin(const char *hex, uint8_t *bin, int bin_len);

/* バイト配列を Base64 文字列にエンコードする。戻り値は書き込んだ文字数 */
int base64_encode(const uint8_t *src, int src_len, char *dst, int dst_len);

/* URL エンコードを行う。戻り値は書き込んだ文字数 */
int url_encode(const char *src, int src_len, char *dst, int dst_len);

/* QRコード URL を生成する
 *   buf        : 結果を書き込むバッファ
 *   buf_len    : バッファのサイズ
 *   type       : QRコードのタイプ
 *   device_id  : デバイスID
 *   url        : ベースURL
 *   encrypt_key: AES-128 鍵（16進数文字列、32文字）
 *   t          : タイムスタンプ
 * 戻り値: 成功時は書き込んだバイト数、鍵エラーは -1、バッファ不足は -2
 */
int make_qrcode_url(char *buf, int buf_len,
    int type, const char *device_id,
    const char *url, const char *encrypt_key,
    time_t t);

#endif /* QRCODE_URL_H */

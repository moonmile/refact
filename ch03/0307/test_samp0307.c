#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <stdio.h>

// Forward declaration of the function to test
const char *make_qrcocde_url(
    int type,
    const char *device_id,
    const char *url,
    const char *encypt_key,
    time_t t
);

// Helper: convert string to time_t (copied from samp0307.c)
static int strptime(const char *datetimeStr, const char *format, struct tm *tm) {
    int year, month, day, hour, minute, second;
    if (sscanf(datetimeStr, "%d/%d/%d %d:%d:%d",
               &year, &month, &day, &hour, &minute, &second) != 6) {
        return 0;
    }
    tm->tm_year = year - 1900;
    tm->tm_mon = month - 1;
    tm->tm_mday = day;
    tm->tm_hour = hour;
    tm->tm_min = minute;
    tm->tm_sec = second;
    tm->tm_isdst = -1;
    return 1;
}
time_t str_to_time_t(const char *fmt) {
    struct tm tm = {0};
    strptime(fmt, "%Y/%m/%d %H:%M:%S", &tm);
    return mktime(&tm);
}

// Test: Normal case
void test_make_qrcocde_url_normal(void) {
    int type = 1;
    const char *device_id = "XXXXX-01234567";
    const char *url = "https://simple.com/qrcode?";
    const char *encypt_key = "560DB2A64C2BBE61FBE6810AFCB25230";
    time_t t = str_to_time_t("2024/12/31 23:59:00");

    const char *result = make_qrcocde_url(type, device_id, url, encypt_key, t);
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_STRING_EQUAL(result, "https://simple.com/qrcode?msWBgyUw2s99TZP1vdX3j6BMbnvB57WHpfn5eIM7w");
}

// Test: Invalid key length
void test_make_qrcocde_url_invalid_key(void) {
    int type = 1;
    const char *device_id = "XXXXX-01234567";
    const char *url = "https://simple.com/qrcode?";
    const char *encypt_key = "1234"; // too short
    time_t t = str_to_time_t("2024/12/31 23:59:00");

    const char *result = make_qrcocde_url(type, device_id, url, encypt_key, t);
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_STRING_EQUAL(result, "error1");
}

// Test: Different device ID
void test_make_qrcocde_url_diff_device(void) {
    int type = 2;
    const char *device_id = "DEV-99999999";
    const char *url = "https://example.com/qr?";
    const char *encypt_key = "560DB2A64C2BBE61FBE6810AFCB25230";
    time_t t = str_to_time_t("2025/01/01 00:00:00");

    const char *result = make_qrcocde_url(type, device_id, url, encypt_key, t);
    CU_ASSERT_PTR_NOT_NULL(result);
    // Just check prefix and that it's not "error1"
    CU_ASSERT_NSTRING_EQUAL(result, url, strlen(url));
    CU_ASSERT_NOT_EQUAL(strcmp(result, "error1"), 0);
}

// Test: Null device_id
void test_make_qrcocde_url_null_device(void) {
    int type = 1;
    const char *device_id = NULL;
    const char *url = "https://simple.com/qrcode?";
    const char *encypt_key = "560DB2A64C2BBE61FBE6810AFCB25230";
    time_t t = str_to_time_t("2024/12/31 23:59:00");

    // Should not crash, but may produce a URL with "null" or empty device id
    const char *result = make_qrcocde_url(type, device_id, url, encypt_key, t);
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_NOT_EQUAL(strcmp(result, "error1"), 0);
}

// Test: Null URL
void test_make_qrcocde_url_null_url(void) {
    int type = 1;
    const char *device_id = "XXXXX-01234567";
    const char *url = NULL;
    const char *encypt_key = "560DB2A64C2BBE61FBE6810AFCB25230";
    time_t t = str_to_time_t("2024/12/31 23:59:00");

    const char *result = make_qrcocde_url(type, device_id, url, encypt_key, t);
    CU_ASSERT_PTR_NOT_NULL(result);
    // Should not crash, but may produce a URL starting with "error1" or just the encoded part
}

// Register tests
int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("make_qrcocde_url Suite", NULL, NULL);
    CU_add_test(suite, "Normal case", test_make_qrcocde_url_normal);
    CU_add_test(suite, "Invalid key", test_make_qrcocde_url_invalid_key);
    CU_add_test(suite, "Different device", test_make_qrcocde_url_diff_device);
    CU_add_test(suite, "Null device_id", test_make_qrcocde_url_null_device);
    CU_add_test(suite, "Null url", test_make_qrcocde_url_null_url);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
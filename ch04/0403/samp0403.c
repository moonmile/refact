#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>


/**
 * 配列の平均値を計算する関数
 * 変数名を変更する前
 */
double calculateAverage0(int a[], int l) {
    int x = 0;
    for (int i = 0; i < l; i++) {
        x += a[i];
    }
    return (double)x / l;
}


/**
 * 配列の平均値を計算する関数
 * 変数名を変更した後
 */
double calculateAverage(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return (double)sum / size;
}

// Test suite initialization function
int init_suite(void) {
    return 0;
}

// Test suite cleanup function
int clean_suite(void) {
    return 0;
}


// Test case 1: Test average function 
void test_average(void) {

    int numbers[] = {1, 2, 3, 4, 5};
    int size = 5 ;
    double average = calculateAverage0(numbers, size);
    CU_ASSERT_EQUAL(average, 3.0);
}



// Test suite setup and registration
int main() {
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("Test Suite", init_suite, clean_suite);
    CU_add_test(suite, "Test average function", test_average);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}
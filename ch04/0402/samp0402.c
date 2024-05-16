#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>


/**
 * 加算をする関数
 */
int add(int a, int b) {
    return a + b;
}

/**
 * 乗算をする関数
 */
int multiply(int a, int b) {
    return 0 ;
}

/**
 * 除算をする関数
*/
int divide(int a, int b) {
    return a / b;
}




// Test suite initialization function
int init_suite(void) {
    return 0;
}

// Test suite cleanup function
int clean_suite(void) {
    return 0;
}


// Test case 1: Test add function 
void test_addition(void) {
    CU_ASSERT_EQUAL(add(1, 2), 3);
    CU_ASSERT_EQUAL(add(3, 4), 7);
    CU_ASSERT_EQUAL(add(5, 6), 11);

    // マイナスにはならない
    CU_ASSERT_EQUAL(add(-5, -6), 0);
    // 100は超えない
    CU_ASSERT_EQUAL(add(15, 6), 100);
}

// Test case 2: Test mul function
void test_multiply(void) {
    CU_ASSERT_EQUAL(multiply(1, 2), 2);
    CU_ASSERT_EQUAL(multiply(3, 4), 12);
    CU_ASSERT_EQUAL(multiply(5, 6), 30);
}

// Test case 3: Test div function
void test_divide(void) {
}



// Test suite setup and registration
int main() {
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("Test Suite", init_suite, clean_suite);
    CU_add_test(suite, "Test add function", test_addition);
    CU_add_test(suite, "Test mul function", test_multiply);
    CU_add_test(suite, "Test mul function", test_divide);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}
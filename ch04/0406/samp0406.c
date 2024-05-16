
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "sub.h"


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
}

// Test case 2: Test mul function
void test_multiply(void) {
    CU_ASSERT_EQUAL(mul(1, 2), 2);
    CU_ASSERT_EQUAL(mul(3, 4), 12);
    CU_ASSERT_EQUAL(mul(5, 6), 30);
}

// Test case 3: Test div function
void test_average(void) {
    int array[] = {1, 2, 3, 4, 5};
    int size = sizeof(array) / sizeof(array[0]);
    CU_ASSERT_EQUAL(average(array, size), 3);
}



// Test suite setup and registration
int main() {
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("Test Suite", init_suite, clean_suite);
    CU_add_test(suite, "Test add function", test_addition);
    CU_add_test(suite, "Test mul function", test_multiply);
    CU_add_test(suite, "Test average function", test_average);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>


/**
 * 長い関数を整理するためのサンプルコード
 */
typedef struct _DATA {
    int x;
    int y;
    int z;
    int result1 ;
    int result2 ;
} DATA;

/// @brief 長い関数のサンプル
/// @param a, b, c, d, e, f, g, h, i, j
/// @return DATA 構造体

DATA long_function(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j) {
    DATA data;
    
    // Code block 1
    // ...
    data.x = a + b ;

    // Code block 2
    // ...
    data.y = c * d ;

    // Code block 3
    // ...
    data.z = e * f / g ;

    // Code block 4
    // ...
    data.result1 = h + i + j ;

    // Code block 5
    // ...
    data.result2 = (h + i + j)/3 ;

    return data ;
}

/*
int block1(int a, int b) {
    return a + b;
}
int block2(int c, int d) {
    return c * d;
}
int block3(int e, int f, int g) {
    return e * f / g;
}
int block4(int h, int i, int j) {
    return h + i + j;
}
int block5(int h, int i, int j) {
    return (h + i + j) / 3;
}
DATA long_function(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j) {
    DATA data;
    data.y = block1(a, b);
    data.y = block2(c, d);
    data.z = block3(e, f, g);
    data.result1 = block4(h, i, j);
    data.result2 = block5(h, i, j);
    return data;
}
*/

// Test suite initialization function
int init_suite(void) {
    return 0;
}

// Test suite cleanup function
int clean_suite(void) {
    return 0;
}


// Test case 1: Test long_function
void test_addition(void) {
    DATA data = long_function(1, 1, 1, 1, 1, 1, 1, 1, 1, 1);

    CU_ASSERT_EQUAL(data.x, 2);
    CU_ASSERT_EQUAL(data.y, 1);
    CU_ASSERT_EQUAL(data.z, 1);
    CU_ASSERT_EQUAL(data.result1, 3);
    CU_ASSERT_EQUAL(data.result2, 1);
}

void test_addition2(void) {
    DATA data = long_function(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

    CU_ASSERT_EQUAL(data.x, 3);
    CU_ASSERT_EQUAL(data.y, 12);
    CU_ASSERT_EQUAL(data.z, 4);
    CU_ASSERT_EQUAL(data.result1, 27);
    CU_ASSERT_EQUAL(data.result2, 9);
}



// Test suite setup and registration
int main() {
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("Test Suite", init_suite, clean_suite);
    CU_add_test(suite, "Test long_function", test_addition);
    CU_add_test(suite, "Test long_function2", test_addition2);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}
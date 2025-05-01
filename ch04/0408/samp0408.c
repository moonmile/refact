#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include <stdio.h>
#include "color.h"

// Test suite initialization function
int init_suite(void) {
    return 0;
}

// Test suite cleanup function
int clean_suite(void) {
    return 0;
}

/**
 * 色の組み合わせテスト
 */
void test_color_combinations(void) {
    color_init() ;
    set_red( 1 ) ;
    set_green( 1 ) ;
    set_blue( 1 ) ;

    CU_ASSERT_EQUAL(get_red(), 1);
    CU_ASSERT_EQUAL(get_green(), 1);
    CU_ASSERT_EQUAL(get_blue(), 1);
    CU_ASSERT_EQUAL(get_status_red_or_green(), 1);
    CU_ASSERT_EQUAL(get_status_white(), 1);
    CU_ASSERT_EQUAL(get_status_black(), 0);

    color_clear() ;
    CU_ASSERT_EQUAL(get_red(), 0);
}

void test_color_red(void) {
    color_init() ;
    set_red( 1 ) ;
    CU_ASSERT_EQUAL(get_red(), 1);
    CU_ASSERT_EQUAL(get_green(), 0);
    CU_ASSERT_EQUAL(get_blue(), 0);
    CU_ASSERT_EQUAL(get_status_black(), 0);
    CU_ASSERT_EQUAL(get_status_white(), 0);
}

void test_color_yellow(void) {
    color_init() ;
    set_red( 1 ) ;
    set_green( 1 ) ;
    CU_ASSERT_EQUAL(get_status_yellow(), 1);
    CU_ASSERT_EQUAL(get_status_cyan(), 0);
    CU_ASSERT_EQUAL(get_status_magenta(), 0);

    set_green( 0 ) ;
    CU_ASSERT_EQUAL(get_status_yellow(), 0);
}

void test_color_or(void) {
    color_init() ;
    set_red( 0 ) ;
    set_green( 1 ) ;
    set_blue( 1 ) ;

    CU_ASSERT_EQUAL(get_status_red_or_green(), 1);
    CU_ASSERT_EQUAL(get_status_green_or_blue(), 1);

    CU_ASSERT_EQUAL(get_status_yellow(), 0);
    CU_ASSERT_EQUAL(get_status_cyan(), 1);
    CU_ASSERT_EQUAL(get_status_magenta(), 0);

    set_blue( 0 ) ;
    CU_ASSERT_EQUAL(get_status_green_or_blue(), 0);
    CU_ASSERT_EQUAL(get_status_cyan(), 0);
    CU_ASSERT_EQUAL(get_status_magenta(), 0);
    CU_ASSERT_EQUAL(get_status_black(), 0);
    CU_ASSERT_EQUAL(get_status_white(), 0);
    CU_ASSERT_EQUAL(get_status_red_or_green(), 1);
}

int main() 
{
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("Test Suite", init_suite, clean_suite);

    CU_add_test(suite, "Test Color Combinations", test_color_combinations);
    CU_add_test(suite, "Test Color Red", test_color_red);
    CU_add_test(suite, "Test Color Yellow", test_color_yellow);
    CU_add_test(suite, "Test Color OR", test_color_or);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}
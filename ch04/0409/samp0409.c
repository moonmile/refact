#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sleep_demo.h"

// Test suite initialization function
int init_suite(void) {
    return 0;
}

// Test suite cleanup function
int clean_suite(void) {
    return 0;
}

/**
 * 実行時間のテスト
 */
void test_sleep_seconds(void) {
    sleep_init() ;

    time_t t_start = time( NULL ) ;
    sleep_seconds( 5 ) ;
    time_t t_end = time( NULL ) ;
    double elapsed = difftime( t_end, t_start ) ;
    printf( "Elapsed time: %.2f seconds\n", elapsed ) ;
    CU_ASSERT( elapsed >= 5.0 ) ;
}

/**
 * ランダムな時間のテスト
 */
void test_sleep_random(void) {
    sleep_init() ;

    time_t t_start = time( NULL ) ;
    sleep_random( 5 ) ;
    time_t t_end = time( NULL ) ;
    double elapsed = difftime( t_end, t_start ) ;
    printf( "Elapsed time: %.2f seconds\n", elapsed ) ;
    CU_ASSERT( elapsed >= 1.0 && elapsed <= 5.0 ) ;
}

/**
 * ランダムな範囲の時間のテスト
 */
void test_sleep_random_range(void) {
    sleep_init() ;

    time_t t_start = time( NULL ) ;
    sleep_random_range( 5, 10 ) ;
    time_t t_end = time( NULL ) ;
    double elapsed = difftime( t_end, t_start ) ;
    printf( "Elapsed time: %.2f seconds\n", elapsed ) ;
    CU_ASSERT( elapsed >= 5.0 && elapsed <= 10.0 ) ;
}

/** 
 * 時間超過のテスト
 */
void test_sleep_longtime(void) {
    sleep_init() ;

    // 10回繰り返す
    for ( int i = 0 ; i < 10 ; i++ ) {
        time_t t_start = time( NULL ) ;
        sleep_random_range( 5, 10 ) ;
        time_t t_end = time( NULL ) ;
        double elapsed = difftime( t_end, t_start ) ;
        printf( "Elapsed time: %.2f seconds\n", elapsed ) ;
        CU_ASSERT( elapsed >= 7.0 ) ;
    }
}

int main() 
{
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("Test Suite", init_suite, clean_suite);
    CU_add_test(suite, "test_sleep_seconds", test_sleep_seconds);
    CU_add_test(suite, "test_sleep_random", test_sleep_random);
    CU_add_test(suite, "test_sleep_random_range", test_sleep_random_range);
    CU_add_test(suite, "test_sleep_longtime", test_sleep_longtime);


    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}
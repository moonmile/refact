#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "ring_buffer.h"

// Test suite initialization function
int init_suite(void) {
    return 0;
}

// Test suite cleanup function
int clean_suite(void) {
    return 0;
}

/**
 * ring_buffer_push
 * ring_buffer_pop
 * ring_buffer_shift
 * 
 * のシーケンステストを行う
 * 各関数を順番に呼出して、期待される値が得られるかを確認する
 */



/**
 * 通常のテストケース
 */
void test_ring_buffer(void) {
    ring_buffer_init() ;
    ring_buffer_push( 1 ) ;
    ring_buffer_push( 2 ) ;
    ring_buffer_push( 3 ) ;

    CU_ASSERT_EQUAL(ring_buffer_get(0), 1);
    CU_ASSERT_EQUAL(ring_buffer_get(1), 2);
    CU_ASSERT_EQUAL(ring_buffer_get(2), 3);

    ring_buffer_pop() ;
    CU_ASSERT_EQUAL(ring_buffer_get(0), 1);
    CU_ASSERT_EQUAL(ring_buffer_get(1), 2); 

    ring_buffer_clear() ;
    CU_ASSERT_EQUAL(ring_buffer_get(0), 0);
}

/**
 * バッファ最大サイズを越える場合
 */
void test_ring_buffer_overflow(void) {
    ring_buffer_init() ;
    for (int i = 0; i < 15; i++) {
        ring_buffer_push(i);
    }
    CU_ASSERT_EQUAL(ring_buffer_get(0), 10); 
    CU_ASSERT_EQUAL(ring_buffer_get(1), 11); 
    CU_ASSERT_EQUAL(ring_buffer_get(2), 12); 

    ring_buffer_clear() ;
    CU_ASSERT_EQUAL(ring_buffer_get(0), 0);
}

/**
 * ring_buffer_pop の正常系
 */
void test_ring_buffer_pop(void) 
{
    ring_buffer_init() ;
    ring_buffer_push( 1 ) ;
    ring_buffer_push( 2 ) ;
    ring_buffer_push( 3 ) ;

    CU_ASSERT_EQUAL(ring_buffer_pop(), 3);  
    CU_ASSERT_EQUAL(ring_buffer_get(0), 1); 
    CU_ASSERT_EQUAL(ring_buffer_get(1), 2); 

    ring_buffer_clear() ;
    CU_ASSERT_EQUAL(ring_buffer_get(0), 0);
}

/**
 * ring_buffer_pop の異常系
 */
void test_ring_buffer_pop_overflow(void) 
{
    ring_buffer_init() ;
    ring_buffer_push( 1 ) ;
    ring_buffer_push( 2 ) ;
    ring_buffer_push( 3 ) ;

    CU_ASSERT_EQUAL(ring_buffer_pop(), 3); 
    CU_ASSERT_EQUAL(ring_buffer_pop(), 2); 
    CU_ASSERT_EQUAL(ring_buffer_pop(), 1); 

    CU_ASSERT_EQUAL(ring_buffer_pop(), 0); 

    ring_buffer_clear() ;
    CU_ASSERT_EQUAL(ring_buffer_get(0), 0);

}

/**
 * ring_buffer_shift の正常系
 */
void test_ring_buffer_shift(void)
{
    ring_buffer_init() ;
    ring_buffer_push( 1 ) ;
    ring_buffer_push( 2 ) ;
    ring_buffer_push( 3 ) ;

    CU_ASSERT_EQUAL(ring_buffer_shift(), 1);  
    CU_ASSERT_EQUAL(ring_buffer_get(0), 2); 
    CU_ASSERT_EQUAL(ring_buffer_get(1), 3); 

    ring_buffer_clear() ;
    CU_ASSERT_EQUAL(ring_buffer_get(0), 0);
}

/**
 * ring_buffer_shift の異常系
 */
void test_ring_buffer_shift_overflow(void)
{
    ring_buffer_init() ;
    ring_buffer_push( 1 ) ;
    ring_buffer_push( 2 ) ;
    ring_buffer_push( 3 ) ;

    CU_ASSERT_EQUAL(ring_buffer_shift(), 1); 
    CU_ASSERT_EQUAL(ring_buffer_shift(), 2); 
    CU_ASSERT_EQUAL(ring_buffer_shift(), 3); 

    CU_ASSERT_EQUAL(ring_buffer_shift(), 0); 

    ring_buffer_clear() ;
    CU_ASSERT_EQUAL(ring_buffer_get(0), 0);
}


int main() 
{
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("Test Suite", init_suite, clean_suite);

    CU_add_test(suite, "Test ring buffer", test_ring_buffer);
    CU_add_test(suite, "Test ring buffer overflow", test_ring_buffer_overflow);
    CU_add_test(suite, "Test ring buffer pop", test_ring_buffer_pop);
    CU_add_test(suite, "Test ring buffer pop overflow", test_ring_buffer_pop_overflow);
    CU_add_test(suite, "Test ring buffer shift", test_ring_buffer_shift);
    CU_add_test(suite, "Test ring buffer shift overflow", test_ring_buffer_shift_overflow);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}
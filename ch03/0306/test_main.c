#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

// Test suite setup and registration
void make_suite_test1(void) ;
void make_suite_test2(void) ;

int main() {
    CU_initialize_registry();

    make_suite_test1();
    make_suite_test2() ;

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}

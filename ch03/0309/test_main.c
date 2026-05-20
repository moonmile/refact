#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void make_suite_qrcode(void);

int main(void)
{
    CU_initialize_registry();

    make_suite_qrcode();

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}

#include "pch.h"
#include "unitst.h"
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"

#include "lstree_list.h"
#include "lstree_bst.h"

#define CLEAN_CUNIT_EXIT() \
    CU_cleanup_registry();\
    return CU_get_error();

#define ADD_TEST(suite, msg, foo) \
    if (CU_add_test(suite, msg, foo) == nullptr)\
    {\
        CLEAN_CUNIT_EXIT();\
    }

int foo_suite() { return 0; }

void foo_test_1() { CU_ASSERT(1 == 4); }
void foo_test_2() {}
void foo_test_3() {}
void foo_test_4() { CU_ASSERT(1 == 2); }
void foo_test_5() { CU_ASSERT(2 == 1); }

int unitst()
{
    if (CU_initialize_registry() != CUE_SUCCESS)
    {
        return CU_get_error();
    }

    CU_pSuite lsuite = CU_add_suite(GC"List_structure"ZC, foo_suite, foo_suite);
    if (lsuite == nullptr) {
        CLEAN_CUNIT_EXIT();
    }

    ADD_TEST(lsuite, BBC"1"ZC, foo_test_1);
    ADD_TEST(lsuite, BBC"2"ZC, foo_test_2);
    ADD_TEST(lsuite, BBC"3"ZC, foo_test_3);

    // CU_basic_run_tests(); 

    CU_pSuite bsuite = CU_add_suite(GC"Tree_structure"ZC, foo_suite, foo_suite);
    if (bsuite == nullptr)
    {
        CLEAN_CUNIT_EXIT();
    }

    ADD_TEST(bsuite, BBC"4"ZC, foo_test_4);
    ADD_TEST(bsuite, BBC"5"ZC, foo_test_5);

    CU_basic_run_tests(); // run all the tests set before into current suite
    CLEAN_CUNIT_EXIT(); // clean CUnit registry and return errors
}
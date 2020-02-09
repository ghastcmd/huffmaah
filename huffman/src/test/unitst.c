#include "pch.h"
#include "unitst.h"
#include "defines.h"
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"

#include "lstree_list.h"
#include "lstree_bst.h"
#include "huffman.h"

#define CLEAN_CUNIT_EXIT() \
    CU_cleanup_registry();\
    return CU_get_error();

#define ADD_TEST(suite, msg, foo) \
    if (CU_add_test(suite, BBC msg ZC, foo) == nullptr)\
    {\
        CLEAN_CUNIT_EXIT();\
    }

int foo_suite() { return 0; }

void list_value_test()
{
    lstree* head = nullptr;
    CU_ASSERT_PTR_NULL(head);
    lstree_add_val(&head, 'C', 3);
    lstree_add_val(&head, 'D', 4);
    lstree_add_val(&head, 'A', 1);
    lstree_add_val(&head, 'B', 2);

    CU_ASSERT_PTR_NOT_NULL(head->next);
    CU_ASSERT_PTR_NOT_NULL(head->next->next);
    CU_ASSERT_PTR_NOT_NULL(head->next->next->next);

    CU_ASSERT_EQUAL(*(int64_t*)head->val, (int64_t)'A');
    CU_ASSERT_EQUAL(head->freq, 1);
    CU_ASSERT_EQUAL(*(int64_t*)head->next->val, (int64_t)'B');
    CU_ASSERT_EQUAL(head->next->freq, 2);
    CU_ASSERT_EQUAL(*(int64_t*)head->next->next->val, (int64_t)'C');
    CU_ASSERT_EQUAL(head->next->next->freq, 3);
    CU_ASSERT_EQUAL(*(int64_t*)head->next->next->next->val, (int64_t)'D');
    CU_ASSERT_EQUAL(head->next->next->next->freq, 4);

    CU_ASSERT_PTR_NULL(head->next->next->next->next);

    CU_ASSERT_PTR_NULL(head->left);
    CU_ASSERT_PTR_NULL(head->right);
    CU_ASSERT_PTR_NULL(head->next->left);
    CU_ASSERT_PTR_NULL(head->next->right);
    CU_ASSERT_PTR_NULL(head->next->next->left);
    CU_ASSERT_PTR_NULL(head->next->next->right);
    CU_ASSERT_PTR_NULL(head->next->next->next->left);
    CU_ASSERT_PTR_NULL(head->next->next->next->right);

    void* ptr = lstree_pop(&head);
    CU_ASSERT_PTR_NOT_NULL(ptr);
    CU_ASSERT_EQUAL(((lstree*)ptr)->freq, 1);
    CU_ASSERT_EQUAL(*(int64_t*)((lstree*)ptr)->val, (int64_t)'A');
    CU_ASSERT_PTR_NULL(((lstree*)ptr)->next);
    CU_ASSERT_PTR_NULL(((lstree*)ptr)->left);
    CU_ASSERT_PTR_NULL(((lstree*)ptr)->right);

    ptr = lstree_pop(&head);
    CU_ASSERT_PTR_NOT_NULL(ptr);
    CU_ASSERT_EQUAL(((lstree*)ptr)->freq, 2);
    CU_ASSERT_EQUAL(*(int64_t*)((lstree*)ptr)->val, (int64_t)'B');
    CU_ASSERT_PTR_NULL(((lstree*)ptr)->next);
    CU_ASSERT_PTR_NULL(((lstree*)ptr)->left);
    CU_ASSERT_PTR_NULL(((lstree*)ptr)->right);

    ptr = lstree_pop(&head);
    CU_ASSERT_PTR_NOT_NULL(ptr);
    CU_ASSERT_EQUAL(((lstree*)ptr)->freq, 3);
    CU_ASSERT_EQUAL(*(int64_t*)((lstree*)ptr)->val, (int64_t)'C');
    CU_ASSERT_PTR_NULL(((lstree*)ptr)->next);
    CU_ASSERT_PTR_NULL(((lstree*)ptr)->left);
    CU_ASSERT_PTR_NULL(((lstree*)ptr)->right);

    ptr = lstree_pop(&head);
    CU_ASSERT_PTR_NOT_NULL(ptr);
    CU_ASSERT_EQUAL(((lstree*)ptr)->freq, 4);
    CU_ASSERT_EQUAL(*(int64_t*)((lstree*)ptr)->val, (int64_t)'D');
    CU_ASSERT_PTR_NULL(((lstree*)ptr)->next);
    CU_ASSERT_PTR_NULL(((lstree*)ptr)->left);
    CU_ASSERT_PTR_NULL(((lstree*)ptr)->right);

    CU_ASSERT_PTR_NULL(head);

    ptr = lstree_pop(&head);
    CU_ASSERT_PTR_NULL(ptr);

    lstree_add_val(&head, 'A', 20);
    lstree_add_val(&head, 'D', 17);

    lstree* node_add = nullptr;

    ptr = lstree_pop(&head);
    lstree_add_node(&node_add, ptr);

    ptr = lstree_pop(&head);
    lstree_add_node(&node_add, ptr);

    CU_ASSERT_EQUAL(*(int64_t*)node_add->val, (int64_t)'D');
    CU_ASSERT_EQUAL(node_add->freq, 17);
    CU_ASSERT_EQUAL(*(int64_t*)node_add->next->val, (int64_t)'A');
    CU_ASSERT_EQUAL(node_add->next->freq, 20);

    lstree_clean_list(&node_add);

    CU_ASSERT_PTR_NULL(node_add);
}

void list_morph_test()
{
    lstree* head = nullptr;

    lstree_add_val(&head, 'A', 1);
    lstree_add_val(&head, 'B', 2);
    lstree_add_val(&head, 'C', 3);
    lstree_add_val(&head, 'D', 4);

    lstree_bst_treeify(&head);

    CU_ASSERT_PTR_NULL(head->next);
    CU_ASSERT_PTR_NOT_NULL(head->left);
    CU_ASSERT_PTR_NOT_NULL(head->right);
    CU_ASSERT_EQUAL(head->freq, 10);
    CU_ASSERT_EQUAL(*(int64_t*)head->val, FLAG);

    CU_ASSERT_PTR_NULL(head->left->next);
    CU_ASSERT_PTR_NULL(head->left->left);
    CU_ASSERT_PTR_NULL(head->left->right);
    CU_ASSERT_EQUAL(head->left->freq, 4);
    CU_ASSERT_EQUAL(*(int64_t*)head->left->val, (int64_t)'D');

    CU_ASSERT_PTR_NULL(head->right->next);
    CU_ASSERT_PTR_NOT_NULL(head->right->left);
    CU_ASSERT_PTR_NOT_NULL(head->right->right);
    CU_ASSERT_EQUAL(head->right->freq, 6);
    CU_ASSERT_EQUAL(*(int64_t*)head->right->val, FLAG);

    CU_ASSERT_PTR_NULL(head->right->right->next);
    CU_ASSERT_PTR_NULL(head->right->right->left);
    CU_ASSERT_PTR_NULL(head->right->right->right);
    CU_ASSERT_EQUAL(head->right->right->freq, 3);
    CU_ASSERT_EQUAL(*(int64_t*)head->right->right->val, (int64_t)'C');

    CU_ASSERT_PTR_NULL(head->right->left->next);
    CU_ASSERT_PTR_NOT_NULL(head->right->left->left);
    CU_ASSERT_PTR_NOT_NULL(head->right->left->right);
    CU_ASSERT_EQUAL(head->right->left->freq, 3);
    CU_ASSERT_EQUAL(*(int64_t*)head->right->left->val, FLAG);

    CU_ASSERT_PTR_NULL(head->right->left->left->next);
    CU_ASSERT_PTR_NULL(head->right->left->left->left);
    CU_ASSERT_PTR_NULL(head->right->left->left->right);
    CU_ASSERT_EQUAL(head->right->left->left->freq, 1);
    CU_ASSERT_EQUAL(*(int64_t*)head->right->left->left->val, (int64_t)'A');

    CU_ASSERT_PTR_NULL(head->right->left->right->next);
    CU_ASSERT_PTR_NULL(head->right->left->right->left);
    CU_ASSERT_PTR_NULL(head->right->left->right->right);
    CU_ASSERT_EQUAL(head->right->left->right->freq, 2);
    CU_ASSERT_EQUAL(*(int64_t*)head->right->left->right->val, (int64_t)'B');

    lstree_clean_tree(&head);
    CU_ASSERT_PTR_NULL(head);
}

void inters_list_test()
{
    inters* ine = lstree_lst_get_inters();

    lstree* head = nullptr;
    lstree_add_val(&head, 'A', 1);
    lstree_add_val(&head, 'B', 2);
    lstree_add_val(&head, 'C', 2);

    void* first = lstree_pop(&head);
    void* secnd = lstree_pop(&head);
    void* third = lstree_pop(&head);

    CU_ASSERT_PTR_NULL(head);
    CU_ASSERT_PTR_NOT_NULL(first);
    CU_ASSERT_PTR_NOT_NULL(secnd);
    CU_ASSERT_PTR_NOT_NULL(third);
    CU_ASSERT(ine->compar(first, secnd) < 0);
    CU_ASSERT(ine->compar(secnd, first) > 0);
    CU_ASSERT(ine->compar(first, third) < 0);
    CU_ASSERT(ine->compar(third, first) > 0);
    CU_ASSERT(ine->compar(secnd, third) < 0);
    CU_ASSERT(ine->compar(third, secnd) > 0);
    CU_ASSERT(ine->compar(first, first) == 0);
    CU_ASSERT(ine->compar(secnd, secnd) == 0);
    CU_ASSERT(ine->compar(third, third) == 0);

    lstree_add_node(&head, (lstree*)first);
    lstree_add_node(&head, (lstree*)secnd);
    lstree_add_node(&head, (lstree*)third);
    CU_ASSERT_PTR_NOT_NULL(head);

    CU_ASSERT_PTR_NOT_NULL(ine->nextp(head));
    CU_ASSERT_PTR_NOT_NULL(ine->nextp(head->next));
    CU_ASSERT_PTR_NULL(ine->nextp(head->next->next));

    CU_ASSERT_PTR_EQUAL(ine->nextp(head), head->next);
    CU_ASSERT_PTR_EQUAL(ine->nextp(head->next), head->next->next);

    CU_ASSERT_PTR_EQUAL(ine->nextp(head), *ine->nextptr(head));
    CU_ASSERT_PTR_EQUAL(ine->nextp(head->next), *ine->nextptr(head->next));
    CU_ASSERT_PTR_EQUAL(ine->nextp(head->next->next), *ine->nextptr(head->next->next));

    lstree_clean_list(&head);
    CU_ASSERT_PTR_NULL(head);
}

void make_tree_test()
{
    const char* desired_fmt = "*A*\\\\*E\\*";
    lstree* head = nullptr;

    lstree_add_val(&head, 'A' , 6);
    lstree_add_val(&head, '\\', 4);
    lstree_add_val(&head, '*' , 3);
    lstree_add_val(&head, 'E' , 2);

    lstree_bst_treeify(&head);

    int tree_len = bytelen_lstree(head);
    CU_ASSERT_EQUAL(tree_len, strlen(desired_fmt));
    char* str_fmt = (char*)calloc(tree_len, sizeof(char));
    {
        int i = 0;
        parse_lstree_string(head, str_fmt, &i);
        const char* test_str = str_fmt;
        CU_ASSERT_STRING_EQUAL(test_str, desired_fmt);
    }

    lstree* sec_head = lstree_bst_make_tree(str_fmt, tree_len);
    int sec_tree_len = bytelen_lstree(head);
    char* sec_str_fmt = (char*)calloc(sec_tree_len, sizeof(char));
    {
        int i = 0;
        parse_lstree_string(sec_head, sec_str_fmt, &i);
        const char* sec_test_str = sec_str_fmt;
        CU_ASSERT_STRING_EQUAL(sec_test_str, desired_fmt);
    }

    CU_ASSERT_EQUAL(*(int64_t*)head->val, *(int64_t*)sec_head->val);
    CU_ASSERT_PTR_NULL(sec_head->next);
    CU_ASSERT_PTR_NOT_NULL(sec_head->left);
    CU_ASSERT_PTR_NOT_NULL(sec_head->right);

    CU_ASSERT_EQUAL(*(int64_t*)head->left->val, *(int64_t*)sec_head->left->val);
    CU_ASSERT_PTR_NULL(sec_head->left->next);
    CU_ASSERT_PTR_NULL(sec_head->left->left);
    CU_ASSERT_PTR_NULL(sec_head->left->right);

    CU_ASSERT_EQUAL(*(int64_t*)head->right->val, *(int64_t*)sec_head->right->val);
    CU_ASSERT_PTR_NULL(sec_head->right->next);
    CU_ASSERT_PTR_NOT_NULL(sec_head->right->left);
    CU_ASSERT_PTR_NOT_NULL(sec_head->right->right);

    CU_ASSERT_EQUAL(*(int64_t*)head->right->left->val, *(int64_t*)sec_head->right->left->val);
    CU_ASSERT_PTR_NULL(sec_head->right->left->next);
    CU_ASSERT_PTR_NULL(sec_head->right->left->left);
    CU_ASSERT_PTR_NULL(sec_head->right->left->right);

    CU_ASSERT_EQUAL(*(int64_t*)head->right->right->val, *(int64_t*)sec_head->right->right->val);
    CU_ASSERT_PTR_NULL(sec_head->right->right->next);
    CU_ASSERT_PTR_NOT_NULL(sec_head->right->right->left);
    CU_ASSERT_PTR_NOT_NULL(sec_head->right->right->right);

    CU_ASSERT_EQUAL(*(int64_t*)head->right->right->left->val, *(int64_t*)sec_head->right->right->left->val);
    CU_ASSERT_PTR_NULL(sec_head->right->right->left->next);
    CU_ASSERT_PTR_NULL(sec_head->right->right->left->left);
    CU_ASSERT_PTR_NULL(sec_head->right->right->left->right);

    CU_ASSERT_EQUAL(*(int64_t*)head->right->right->right->val, *(int64_t*)sec_head->right->right->right->val);
    CU_ASSERT_PTR_NULL(sec_head->right->right->right->next);
    CU_ASSERT_PTR_NULL(sec_head->right->right->right->left);
    CU_ASSERT_PTR_NULL(sec_head->right->right->right->right);

    lstree_clean_tree(&head);
    lstree_clean_tree(&sec_head);

    CU_ASSERT_PTR_NULL(head);
    CU_ASSERT_PTR_NULL(sec_head);

    free(sec_str_fmt);
    free(str_fmt);
}

void inters_bst_test()
{
    inters_bst* ine = lstree_bst_get_inters();

    tuple* val1 = (tuple*)calloc(1, sizeof(tuple));
    *val1 = (tuple)
    {
        .st0 = 'A',
        .st1 = 2
    };

    tuple* val2 = (tuple*)calloc(1, sizeof(tuple));
    *val2 = (tuple)
    {
        .st0 = 'C',
        .st1 = 10
    };

    lstree* node1 = (lstree*)ine->create((void*)val1);
    lstree* node2 = (lstree*)ine->create((void*)val2);

    CU_ASSERT_PTR_NOT_NULL(node1);
    CU_ASSERT_PTR_NOT_NULL(node2);

    CU_ASSERT_EQUAL(*(int64_t*)node1->val, val1->st0);
    CU_ASSERT_EQUAL(node1->freq, val1->st1);
    CU_ASSERT_EQUAL(*(int64_t*)node2->val, val2->st0);
    CU_ASSERT_EQUAL(node2->freq, val2->st1);

    free(val1);
    free(val2);
    val1 = val2 = nullptr;

    tuple* values = (tuple*)ine->merge(node1, node2);

    CU_ASSERT_PTR_NOT_NULL(values);
    CU_ASSERT_EQUAL(values->st0, FLAG);
    CU_ASSERT_EQUAL(values->st1, 12);
    CU_ASSERT_EQUAL(values->st1, node1->freq + node2->freq);

    CU_ASSERT_EQUAL(*(int64_t*)node1->val, ine->get_val(node1));
    CU_ASSERT_EQUAL(*(int64_t*)node2->val, ine->get_val(node2));

    lstree* tree_ptr = (lstree*)ine->create(values);

    CU_ASSERT_PTR_NOT_NULL(tree_ptr);
    CU_ASSERT_EQUAL(*(int64_t*)tree_ptr->val, FLAG);
    CU_ASSERT_EQUAL(tree_ptr->freq, node1->freq + node2->freq);
    CU_ASSERT_EQUAL(*(int64_t*)tree_ptr->val, ine->get_val(tree_ptr));

    void** leftptr = ine->leftptr(tree_ptr);
    CU_ASSERT_PTR_NOT_NULL(leftptr);
    CU_ASSERT_PTR_EQUAL(ine->leftp(tree_ptr), tree_ptr->left);
    CU_ASSERT_PTR_EQUAL(*leftptr, tree_ptr->left);

    void** rightptr = ine->rightptr(tree_ptr);
    CU_ASSERT_PTR_NOT_NULL(rightptr);
    CU_ASSERT_PTR_EQUAL(ine->leftp(tree_ptr), tree_ptr->right);
    CU_ASSERT_PTR_EQUAL(*rightptr, tree_ptr->right);

    *leftptr = node1;
    *rightptr = node2;

    CU_ASSERT_EQUAL(*(int64_t*)tree_ptr->left->val, 'A');
    CU_ASSERT_EQUAL(*(int64_t*)tree_ptr->right->val, 'C');

    CU_ASSERT_EQUAL(ine->get_val(ine->leftp(tree_ptr)), 'A');
    CU_ASSERT_EQUAL(ine->get_val(ine->rightp(tree_ptr)), 'C');

    lstree_clean_tree(&tree_ptr);
    CU_ASSERT_PTR_NULL(tree_ptr);
}

int main()
{
    if (CU_initialize_registry() != CUE_SUCCESS)
    {
        return CU_get_error();
    }

    CU_pSuite lsuite = CU_add_suite(GC"List_structure"ZC, foo_suite, foo_suite);
    if (lsuite == nullptr) {
        CLEAN_CUNIT_EXIT();
    }

    ADD_TEST(lsuite, "linked list values", list_value_test);
    ADD_TEST(lsuite, "linked list morphing functions", list_morph_test);
    ADD_TEST(lsuite, "linked list interfaces", inters_list_test);

    CU_pSuite bsuite = CU_add_suite(GC"Tree_structure"ZC, foo_suite, foo_suite);
    if (bsuite == nullptr)
    {
        CLEAN_CUNIT_EXIT();
    }

    ADD_TEST(bsuite, "binary tree values", make_tree_test);
    ADD_TEST(bsuite, "binary tree interfaces", inters_bst_test);

    CU_basic_run_tests(); // run all the tests set before into current suite

    CLEAN_CUNIT_EXIT(); // clean CUnit registry and return errors
}
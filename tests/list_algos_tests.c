#include "minunit.h"
#include <lcthw/list_algos.h>
#include <assert.h>
#include <string.h>

char *values[] = { "XXXX", "1234", "abcd", "xjvef", "NDSS"};

//char *values[] = { "test0", "test1", "test2", "test3" "test4", "test5", "test6", "test7", "test8", "test9"};

#define NUM_VALUES 5
//#define NUM_VALUES 10

List *create_words()
{
    int i = 0;
    List *words = List_create();

    for (i = 0; i < NUM_VALUES; i++) {
        List_push(words, values[i]);
    }

    return words;
}

int is_sorted(List * words)
{
    LIST_FOREACH(words, first, next, cur) {
        if (cur->next && strcmp(cur->value, cur->next->value) > 0) {
            printf("%s %s\n", (char *)cur->value,\
                (char *)cur->next->value);
            return 0;
        }
    }

    return 1;
}

char *test_bubble_sort()
{
    List *words = create_words();
    
    // should work on a list that needs sorting
    int rc = List_bubble_sort(words, (List_compare) strcmp);
    mu_assert(rc == 0, "Bubble sort failed 1.");
    mu_assert(is_sorted(words),"Bubble sort failed.");
    
   
    // should work on an already sorted list
    rc = List_bubble_sort(words, (List_compare) strcmp);
    mu_assert(rc == 0, "Bubble sort failed 2.");
    mu_assert(is_sorted(words), "Bubble sort failed.");

    List_destroy(words);

    // should work on an empty list
    words = List_create(words);
    rc = List_bubble_sort(words, (List_compare) strcmp);
    mu_assert(rc == 0, "Bubble sort failed on empty list.");
    mu_assert(is_sorted(words), "Words should be sorted if empty.");
    
    List_destroy(words);

    return NULL;
}

char *test_merge_sort()
{
    List *words = create_words();
    

    // should work on a list that needs sorting
    List *res = List_merge_sort(words, (List_compare) strcmp);
    mu_assert(is_sorted(res), "Words are not sorted after merge sort.");
    
    // should work on a list that does not need sorting
    List *res2 = List_merge_sort(res, (List_compare) strcmp);
    mu_assert(is_sorted(res),"Merge sort failed.");
    List_destroy(res2);
    List_destroy(res);

    List_destroy(words);
    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_bubble_sort);
    mu_run_test(test_merge_sort);

    return NULL;
}

RUN_TESTS(all_tests);

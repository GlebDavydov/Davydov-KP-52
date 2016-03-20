#include <stdlib.h>  // !
#include <stdarg.h>  // !
#include <stddef.h>  // !
#include <setjmp.h>  // !

#include <cmocka.h>

#include "text.h"

static void sentWordNum_hwiaut_six(void **state){
    int errcheck = 0;
    int *ERR = &errcheck;
    assert_int_equal(sentence_word_number("hello world i am unit test", ERR), 6);
}

static void newText_void_emtyTrue(void **state){
    int errcheck = 0;
    int *ERR = &errcheck;
    text_t *aText = text_new(ERR);
    assert_int_equal(text_isempty(aText, ERR), 1);
    text_free(aText);
}

static void add_oneIndex_emptyFalse(void **state){ //3
    int errcheck = 0;
    int *ERR = &errcheck;
    text_t *aText = text_new(ERR);
    sentence_create(aText, 0, "some test sentence", ERR);
    assert_int_equal(text_isempty(aText, ERR), 0);
    text_free(aText);
}

static void newText_void_countZero(void **state){ //4
    int errcheck = 0;
    int *ERR = &errcheck;
    text_t *aText = text_new(ERR);
    assert_int_equal(text_count(aText, ERR), 0);
    text_free(aText);
}

static void add_twoIndex_countTwo(void **state){ //5
    int errcheck = 0;
    int *ERR = &errcheck;
    text_t *aText = text_new(ERR);
    sentence_create(aText, 0, "some test sentence", ERR);
    sentence_create(aText, 1, "some test sentence", ERR);
    assert_int_equal(text_count(aText, ERR), 2);
    text_free(aText);
}

static void print_NULL_errorTrue(void **state){
    int errcheck = 0;
    int *ERR = &errcheck;
    text_print(NULL, ERR);
    assert_int_equal(*ERR, NULL_POINTER);
}

static void add_oneBeginning_wordNumberTree(void **state){
    int errcheck = 0;
    int *ERR = &errcheck;
    text_t *aText = text_new(ERR);
    sentence_create_beginning(aText, "some test sentence", ERR);
    assert_int_equal(text_word_number(aText, ERR), 3);
    text_free(aText);
}

static void add_threeEnd_countThree(void **state){
    int errcheck = 0;
    int *ERR = &errcheck;
    text_t *aText = text_new(ERR);
    sentence_create_end(aText, "some test sentence", ERR);
    sentence_create_end(aText, "some test sentence", ERR);
    sentence_create_end(aText, "some test sentence", ERR);
    assert_int_equal(text_count(aText, ERR), 3);
    text_free(aText);
}


static void add_oneIndex_wordNumberThree(void **state){
    int errcheck = 0;
    int *ERR = &errcheck;
    text_t *aText = text_new(ERR);
    sentence_create(aText, 0, "some test sentence", ERR);
    assert_int_equal(text_word_number(aText, ERR), 3);
    text_free(aText);
}

static void dot_noDot_strlenIncreasedByOne(void **state){
    int errcheck = 0;
    int *ERR = &errcheck;
    assert_int_equal(strlen(sentence_dot("five", ERR)), 5);
}

static void add_twoEnd_deleteOneBeginningCountOne(void **state){
    int errcheck = 0;
    int *ERR = &errcheck;
    text_t *aText = text_new(ERR);
    sentence_create_end(aText, "some test sentence", ERR);
    sentence_create_end(aText, "another test sentence", ERR);
    sentence_delete_beginning(aText, ERR);
    assert_int_equal(text_count(aText, ERR), 1);
    text_free(aText);
}

static void add_oneBeginning_deleteEndErrorFalse(void **state){
    int errcheck = 0;
    int *ERR = &errcheck;
    text_t *aText = text_new(ERR);
    sentence_create_beginning(aText, "some test sentence", ERR);
    sentence_delete_end(aText, ERR);
    assert_int_equal(*ERR, CORRECT);
    text_free(aText);
}

static void deleteByIndex_empty_errorTrue(void **state){
    int errcheck = 0;
    int *ERR = &errcheck;
    text_t *aText = text_new(ERR);
    sentence_delete(aText, 0, ERR);
    assert_int_equal(*ERR, EMPTY_DELETION);
    text_free(aText);
}

int main(void) {
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(sentWordNum_hwiaut_six),
        cmocka_unit_test(newText_void_emtyTrue),
        cmocka_unit_test(add_oneIndex_emptyFalse),
        cmocka_unit_test(newText_void_countZero),
        cmocka_unit_test(add_twoIndex_countTwo),
        cmocka_unit_test(print_NULL_errorTrue),
        cmocka_unit_test(add_oneBeginning_wordNumberTree),
        cmocka_unit_test(add_threeEnd_countThree),
        cmocka_unit_test(add_oneIndex_wordNumberThree),
        cmocka_unit_test(dot_noDot_strlenIncreasedByOne),
        cmocka_unit_test(add_twoEnd_deleteOneBeginningCountOne),
        cmocka_unit_test(add_oneBeginning_deleteEndErrorFalse),
        cmocka_unit_test(deleteByIndex_empty_errorTrue),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}

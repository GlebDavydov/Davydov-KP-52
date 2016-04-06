#include <stdlib.h>  // !
#include <stdarg.h>  // !
#include <stddef.h>  // !
#include <setjmp.h>  // !

#include <cmocka.h>

#include "lab1.h"

static void new_void_emptyTrue(void **state){
    int errcheck = 0;
    int *ERR = &errcheck;
    section_t *psec = section_new(ERR);
    assert_int_equal(section_isempty(psec, ERR), 1);
    section_free(psec, ERR);
}

static void add_auditory_countOne(void **state){
    int errcheck = 0;
    int *ERR = &errcheck;
    section_t *psec = section_new(ERR);
    section_auditory_add(psec, 10, 10, ERR);
    assert_int_equal(section_count(psec, ERR), 1);
    section_free(psec, ERR);
}

static void new_audThreePlaces_placesThree(void **state){
    int errcheck = 0;
    int *ERR = &errcheck;
    section_t *psec = section_new(ERR);
    aud_t *paud = section_auditory_add(psec, 1, 3, ERR);
    assert_int_equal(auditory_places(paud, ERR), 3);
    section_free(psec, ERR);
}

static void add_twoAudsFivePlaces_placesTen(void **state){
    int errcheck = 0;
    int *ERR = &errcheck;
    section_t *psec = section_new(ERR);
    section_auditory_add(psec, 1, 5, ERR);
    section_auditory_add(psec, 2, 5, ERR);
    assert_int_equal(section_total_places(psec, ERR), 10);
    section_free(psec, ERR);
}

static void addThree_deleteOne_countTwo(void **state){
    int errcheck = 0;
    int *ERR = &errcheck;
    section_t *psec = section_new(ERR);
    section_auditory_add(psec, 1, 5, ERR);
    section_auditory_add(psec, 2, 5, ERR);
    section_auditory_add(psec, 3, 5, ERR);
    section_auditory_remove(psec, 3, ERR);
    assert_int_equal(section_count(psec, ERR), 2);
    section_free(psec, ERR);
}

static void print_empty_errorTrue(void **state){
    int errcheck = 0;
    int *ERR = &errcheck;
    section_print_auditories(NULL, ERR);
    assert_int_equal(*ERR, NULL_POINTER);
}

static void addThreeAuds_findByNumber_numberSeven(void **state){
    int errcheck = 0;
    int *ERR = &errcheck;
    section_t *psec = section_new(ERR);
    section_auditory_add(psec, 7, 5, ERR);
    section_auditory_add(psec, 110, 5, ERR);
    section_auditory_add(psec, 111, 5, ERR);
    aud_t *paud = section_auditory_find(psec, 7, ERR);
    assert_int_equal(auditory_saynumber(paud, ERR), 7);
    section_free(psec, ERR);
}

static void addAud_usedNumber_errorInvalidNumber(void **state){
    int errcheck = 0;
    int *ERR = &errcheck;
    section_t *psec = section_new(ERR);
    section_auditory_add(psec, 1, 4, ERR);
    section_auditory_add(psec, 1, 3, ERR);
    assert_int_equal(*ERR, INCORRECT_NUMBER);
    section_free(psec, ERR);
}

static void addAud_incorrectPlaces_defaultFiftyPlaces(void **state){
    int errcheck = 0;
    int *ERR = &errcheck;
    section_t *psec = section_new(ERR);
    section_auditory_add(psec, 1, 1024, ERR);
    aud_t *paud = section_auditory_find(psec, 1, ERR);
    assert_int_equal(auditory_places(paud, ERR), 50);
    section_free(psec, ERR);
}

static void aud_occupieHadyniak_occupiedHadyniak(void **state){
    int errcheck = 0;
    int *ERR = &errcheck;
    section_t *psec = section_new(ERR);
    section_auditory_add(psec, 1, 1, ERR);
    char *name = "Ruslan Hadyniak";
    auditory_occupy(psec, 1, name, ERR);
    assert_string_equal(auditory_isoccupied(psec, 1, ERR), name);
    section_free(psec, ERR);
}

static void aud_unoccupied_deoccupyFalse(void **state){
    int errcheck = 0;
    int *ERR = &errcheck;
    section_t *psec = section_new(ERR);
    section_auditory_add(psec, 1, 1, ERR);
    assert_false(auditory_deoccupy(psec, 1, ERR));
    section_free(psec, ERR);
}

int my_test(void){
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(new_void_emptyTrue),
        cmocka_unit_test(add_auditory_countOne),
        cmocka_unit_test(new_audThreePlaces_placesThree),
        cmocka_unit_test(add_twoAudsFivePlaces_placesTen),
        cmocka_unit_test(addThree_deleteOne_countTwo),
        cmocka_unit_test(print_empty_errorTrue),
        cmocka_unit_test(addThreeAuds_findByNumber_numberSeven),
        cmocka_unit_test(addAud_usedNumber_errorInvalidNumber),
        cmocka_unit_test(addAud_incorrectPlaces_defaultFiftyPlaces),
        cmocka_unit_test(aud_occupieHadyniak_occupiedHadyniak),
        cmocka_unit_test(aud_unoccupied_deoccupyFalse),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}

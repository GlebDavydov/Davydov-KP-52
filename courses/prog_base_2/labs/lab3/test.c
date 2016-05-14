#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "earthquake.h"

void calm(listener_t *self, callback_args args);

static message_callback cb = calm;

static void newSeismo_void_countZero(void **state){
    seismometer_t *self = ssm_new("Explorer");
    assert_int_equal(ssm_get_count(self), 0);
    ssm_delete(self);
};//1

static void seismoAddListener_one_countOne(void**state){
    seismometer_t *self = ssm_new("Explorer");
    listener_t *me = listener_new("Me");
    ssm_add_listener(self, me, cb);
    assert_int_equal(ssm_get_count(self), 1);
    listener_delete(me);
    ssm_delete(self);
};//2

static void seismoAddTwoListeners_sameName_False(void**state){
    seismometer_t *self = ssm_new("Explorer");
    listener_t *me1 = listener_new("Me");
    listener_t *me2 = listener_new("Me");
    ssm_add_listener(self, me2, cb);
    assert_false(ssm_add_listener(self, me1, cb));
    listener_delete(me1);
    listener_delete(me2);
    ssm_delete(self);
};//4

static void seismoAddThreeListeners_deleteLast_countTwo(void**state){
    seismometer_t *self = ssm_new("Explorer");
    listener_t *me1 = listener_new("Hello");
    listener_t *me2 = listener_new("earthquake");
    listener_t *me3 = listener_new("hide");
    ssm_add_listener(self, me1, cb);
    ssm_add_listener(self, me2, cb);
    ssm_add_listener(self, me3, cb);
    ssm_remove_listener(self, me2);
    assert_int_equal(ssm_get_count(self), 2);
    listener_delete(me1);
    listener_delete(me2);
    listener_delete(me3);
    ssm_delete(self);
};//5

static void seismoAddListener_remove_removedName(void **state){
    seismometer_t *self = ssm_new("Explorer");
    char *name = "Name";
    listener_t *me = listener_new(name);
    ssm_add_listener(self, me, cb);
    assert_string_equal(listener_get_name(me), name);
    listener_delete(me);
    ssm_delete(self);
};//6

static void newSeismo_switchOn_statusON(void**state){
    seismometer_t *self = ssm_new("Explorer");
    ssm_turn_on(self);
    assert_int_equal(ssm_get_status(self), ON);
    ssm_delete(self);
};//7

int unit_test_run(void) {
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(newSeismo_void_countZero),
        cmocka_unit_test(seismoAddListener_one_countOne),
        cmocka_unit_test(seismoAddTwoListeners_sameName_False),
        cmocka_unit_test(seismoAddThreeListeners_deleteLast_countTwo),
        cmocka_unit_test(seismoAddListener_remove_removedName),
        cmocka_unit_test(newSeismo_switchOn_statusON),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}

#ifndef EARTHQUAKE_H_INCLUDED
#define EARTHQUAKE_H_INCLUDED

#define ERR_INDEX 257
#define OFF 0
#define ON 1
#define ESCAPE 27

enum ssm_status{CLEAR, HIGHS};

typedef char* callback_args;

typedef struct event_s event_t;


typedef struct listener_s listener_t;
typedef struct seismometer_s seismometer_t;
typedef void (*message_callback)(listener_t *self, callback_args); //contained in seismometer.c
typedef void (*ssm_mode)(double val); // contained in main.c

//listener.c
listener_t *listener_new(char *name);
void listener_delete(listener_t * self);
char *listener_get_name(listener_t *self);
//void listener_react_event(listener_t *self, message_callback cb, callback_args args);

//seismometer.c
seismometer_t *ssm_new(char *name);
void ssm_delete(seismometer_t *self);
int ssm_add_listener(seismometer_t *base, listener_t *self, message_callback cb);
listener_t *ssm_remove_listener(seismometer_t *self, listener_t *lis);
//void ssm_send_event(seismometer_t *self);
void ssm_cycle(seismometer_t *self, ssm_mode cb);
void ssm_turn_on(seismometer_t *self);
void ssm_turn_off(seismometer_t *self);
int ssm_get_status(seismometer_t *self);
int ssm_get_count(seismometer_t *self);
char *ssm_get_name(seismometer_t *self);

int unit_test_run(void);

#endif // EARTHQUAKE_H_INCLUDED

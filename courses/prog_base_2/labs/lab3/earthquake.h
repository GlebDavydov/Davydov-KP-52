#ifndef EARTHQUAKE_H_INCLUDED
#define EARTHQUAKE_H_INCLUDED

#define ERR_INDEX 257

typedef struct listener_s listener_t;
typedef struct seismometer_s seismometer_t;
typedef void (*message_callback)(void); //contained in seismometer.c
typedef void (*ssm_mode)(double val); // contained in main.c


//listener.c
listener_t *listener_new(char *name);
void listener_delete(listener_t * self);
seismometer_t *listener_get_ssm(listener_t * self);
void listenet_set_ssm(listener_t *self, seismometer_t *ssm);
char *listener_get_name(listener_t *self);
void listener_react_event(listener_t *self, message_callback cb);
int get_event_status(listener_t *self);

//seismometer.c
seismometer_t *ssm_new(void);
void ssm_delete(seismometer_t *self);
int ssm_add_listener(seismometer_t *base, listener_t *self);
void ssm_send_event(seismometer_t *self);
int ssm_get_listener_index(seismometer_t * self, char * name);
listener_t *ssm_remove_listener(seismometer_t *self, int index);
void ssm_send_event(seismometer_t *self);
void ssm_cycle(seismometer_t *self, ssm_mode cb);
void ssm_turn_on(seismometer_t *self);
void ssm_turn_off(seismometer_t *self);
int ssm_get_status(seismometer_t *self);
int ssm_get_count(seismometer_t *self);

int unit_test_run(void);

#endif // EARTHQUAKE_H_INCLUDED

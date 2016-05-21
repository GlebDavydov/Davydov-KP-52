#ifndef MODULE_H_INCLUDED
#define MODULE_H_INCLUDED

#incldue<stdio.h>
#include<stdlib.h>

#include"list.h"

typedef struct os_s *os_t;
typedef struct prog_s *prog_t;
typedef struct user_s *user_t;
typedef struct event_s *event_t;


typedef void (*message_callback)(user_t *self, prog_t *prog);

typedef enum STATUS{OFF, ON}state;

os_t *os_new(void);
void os_shutdown(os_t *self);
void os_user_login(os_t *self, user_t *activator);
state os_get_status(os_t *self);
int os_get_users(os_t *self);
int os_get_programs(os_t *self);
int os_get_programs_active(os_t *self);
void os_program_add(os_t *base, prog_t*self);
prog_t *os_program_remove(os_t *base, int index);
user_t *os_user_logout(os_t *base, int index);
void os_user_signup(os_t *base, event_t *event);
event_t *os_user_signout(os_t *base, int index);
void os_free(os_t *self);
int os_get_listeners(os_t *base);

prog_t *prog_new(char *name);
void prog_free(prog_t *prog);
char *prog_get_name(prog_t *prog);

user_t *user_new(char *name);
void user_free(user_t *user);
char *user_get_name(user_t *user);
void prog_user_launchProgram(user_t *user, prog_t *prog);
user_t *prog_user_exitProgram(prog_t *prog);
//void event_f

event_t *event_new(user_t *user, message_callback cb);

#endif // MODULE_H_INCLUDED

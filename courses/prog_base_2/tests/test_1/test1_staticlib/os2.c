#include "module.h"

struct event_s{
    user_t *user;
    message_callback cb;
};

struct os_s{
    state status;
    list_t *progs;
    list_t *activeUsers;
    list_t *events;
};

struct prog_s{
    state status;
    char *name;
    user_t *user;
};

os_t *os_new(void){
    os_t *newOs = malloc(sizeof(struct os_s));
    newOs->state = OFF;
    newOS->progs = list_new();
    newOs->activeUsers = list_new();
    newOs->events = list_new();
}

void os_shutdown(os_t *self){
    while(os_get_users(self)){
        free(os_user_signout(self, 0));
        user_free(os_user_logout(self, 0));
    }
    os_status = OFF;
}

void os_user_login(os_t *self, user_t *activator){
    self->state = ON;
    list_add(self->activeUsers, (void*)activator, list_size(self->activeUsers));
}

state os_get_status(os_t *self){
    return self->state;
}

int os_get_users(os_t *self){
    return list_size(self->progs);
}

int os_get_programs(os_t *self){
    return list_size(self->activeUsers);
}

int os_get_programs_active(os_t *self){
    int c = 0;
    for(int i = 0; i < os_get_programs(self); i++){
        if((prog_t*)list_get(self, i)->state == ON)
            c++;
    }
    return c;
}

void os_program_add(os_t *base, prog_t*self){
    self->user = NULL;
    self->state = OFF;
    list_add(base->progs, (void*)self, list_size(base->progs));
}

prog_t *os_program_remove(os_t *base, int index){
    return (prog_t*)list_del(base->progs, index);
}

user_t *os_user_logout(os_t *base, int index){
    user_t *curr = (user_t*)list_del(base->activeUsers, index);
    for(int i = 0; i < os_get_programs(base); i++){
        prog_t* currProg = (prog_t*)list_get(base->progs, i);
        if(currProg->user == curr){
            currProg->user = NULL;
            currProg->state = OFF;
        }
    }
    return curr;
}

void os_user_signup(os_t *base, event_t *event){
    list_add(base->events, (void *)event, os_get_listeners(base));
}

event_t *os_user_signout(os_t *base, int index){
    return (event_t*)list_del(base->events, index);
}

void os_free(os_t *self){
    list_free(self->progs);
    list_free(self->activeUsers);
    list_free(self->events);
    free(self);
}

int os_get_listeners(os_t *base){
    return list_size(base->events);
}

prog_t *prog_new(char *name){
    prog_t *p = malloc(sizeof(struct prog_s));
    p->name = name;
    p->state = OFF;
    p->users = NULL;
    return p;
}

void prog_free(prog_t *prog){
    free(prog);
}

char *prog_get_name(prog_t *prog){
    return prog->name;
}

void prog_user_launchProgram(os_t *base, user_t *user, prog_t *prog){
    if(prog->state == ON){
        return;
    }
    else{
        prog->state = ON;
        prog->user = user;
        for(int i = 0; i < os_get_listeners(base); i++){
            (event_t*)list_get(base->events, i)->cb(user, prog);
        }
    }
}

user_t *prog_user_exitProgram(prog_t *prog){
    user_t *user = NULL;
}

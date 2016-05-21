#include "module.h"

struct event_s{
    user_t *user;
    message_callback cb;
};


event_t *event_new(user_t *user, message_callback cb){
    event_t *newEvent = malloc(sizeof(struct event_s));
    newEvent->user = user;
    newEvent->cb = cb;
    return newEvent;
}

/*user_new(char *name){
    user_t* us = malloc(sizeof(struct user_s));

}*/

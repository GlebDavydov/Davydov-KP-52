#include "module.h"

struct event_s{
    user_t *user;
    message_callback cb;
};

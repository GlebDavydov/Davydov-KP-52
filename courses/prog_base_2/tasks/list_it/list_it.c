#include <stdlib.h>
#include "list_it.h"
#include "list.h"

#define SIZE 100
#define TRUE 1
#define FALSE 0

struct list_it_s{
    int curr;
    int count;
    list_t *elems;
};

list_it_elem_t * list_it_next(list_it_t * self){
    if(self->count == 0)
        return NULL;
    list_it_elem_t *next = list_get(self->elems, self->curr);
    self->curr = (self->curr + 1) % self->count;
    return next;
}

void list_it_free(list_it_t * self){
    list_free(self->elems);
    free(self);
}

list_it_t *list_it_new(void){
    list_it_t *it_list = malloc(sizeof(struct list_it_s));
    it_list->elems = list_new_deallocDefault();
    it_list->count = 0;
    it_list->curr = 0;
    return it_list;
}

/**
*   @brief Calls callback on for each element in array
*/
void list_forEach(list_t * self, iteration_fn callback, void * ctx) {
    if (NULL == callback) {
        return;
    }
    const int size = list_getSize(self);
    for (int index = 0; index < size; index++) {
        callback(list_get(self, index), index, self, ctx);
    }
}

/**
*   @return new list_it_t object that contains the key\value pair for each index in the list
*
*   do list_it_free() after usage of list_t pointer
*/

//!"do list_it_free() after usage of list_t pointer"
//!I guess it means "do list_free()", or should I free the pointer which I return?
list_it_t * list_entries(list_t * self){
    if(list_getSize(self) > SIZE)
        return NULL;
    list_it_t *it_list = list_it_new();
    for(int i = 0; i < list_getSize(self); i++){
        list_it_elem_t* element = malloc(sizeof(struct list_it_elem_s));
        element->done = 0;
        element->entry = malloc(sizeof(struct list_entry_s));
        element->entry->index = i;
        element->entry->value = list_get(self, i);
        list_insert(it_list->elems, i, (void*)element);
        it_list->count++;
    }
    list_free(self);
    return it_list;
}

/**
*   @return true if at least one element in this array
*   satisfies the provided testing callback function
*
*   Stops iterating when testing function returns first true value
*/
int list_some(list_t * self, predicate_fn callback, void * context){
    for(int i = 0; i < list_getSize(self); i++){
        if(TRUE == callback(list_get(self, i), i, self, context))
            return TRUE;
    }
    return FALSE;
}

/**
*   @return new list with the results of calling a provided
*   function on every element in this array
*/
list_t * list_map(list_t * self, map_fn callback, void * context){
    list_t *newList = list_new_deallocDefault();
    for(int i = 0; i < list_getSize(self); i++){
        void *value = list_get(self, i);
        list_insert(newList, i, callback(value, i, self, context));
    }
    return newList;
}

/**
*   @brief  Apply a callback function against an accumulator and each
*   value of the list (from right-to-left) as to reduce it to a single value
*   @param initial - initial accumulator value
*   @return accumulated value
*/
void * list_reduceRight(list_t * self, reduce_fn callback, void * context, void * initial){
    void *value = callback(initial, list_get(self, 0), 0, self, context);
    for(int i = list_getSize(self) - 1; i >= 0; i++){
        value = callback(value, list_get(self, i), i, self, context);
    }
    return value;
}

/**
*   @return the found index in the list, if an element in the list satisfies
*   the provided testing callback function or -1 if not found
*/
int list_it_findIndex(list_t * self, predicate_fn callback, void * context){
    for(int i = 0; i < list_getSize(self); i++){
        void *val = list_get(self, i);
        if(TRUE == callback(val, i, self, context))
            return i;
    }
    return -1;
}

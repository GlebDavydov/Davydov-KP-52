#include"threads.h"
//#include"thread.h"
#include"mutex.h"

int main(void){
    shared_t *shared = new_shared();
    char *str = "Hello, my beloved world";
    change_symbol(shared, '0');
    change_string(shared, str);
    thread_t * reader1 = readerThread(shared);
    thread_t * reader2 = readerThread(shared);
    thread_t * reader3 = readerThread(shared);
    thread_t * writer = writerThread(shared);
    thread_join(writer);
    thread_free(reader1);
    thread_free(reader2);
    thread_free(reader3);
    thread_free(writer);
    free_shared(shared);
}

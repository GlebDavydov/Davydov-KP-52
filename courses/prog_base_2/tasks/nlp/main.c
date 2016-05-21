#include "nlp.h"

int main(void){
    text_t *Alice = read_text("Sourse.txt");
    text_insertion_sort(Alice);
    if(Alice){
        write_text("Destination.txt", Alice);
        text_free(Alice);
    }
}

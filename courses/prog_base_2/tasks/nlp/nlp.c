#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "nlp.h"

struct text_s{
    int count;
    sent_t *first;
    sent_t *last;
};

struct sent_s{
    int count;
    word_t *fword;
    sent_t *prev;
    sent_t *next;
};

struct word_s{
    char *contents;
    word_t *next;
};

text_t *text_new_empty(void){
    text_t *nt = malloc(sizeof(struct text_s));
    nt->first = malloc(sizeof(struct sent_s));
    nt->last = malloc(sizeof(struct sent_s));
    nt->count = 0;
    nt->first->count = 0;
    nt->first->fword = NULL;
    nt->first->prev = NULL;
    nt->first->next = nt->last;
    nt->last->count = 0;
    nt->last->fword = NULL;
    nt->last->prev = nt->first;
    nt->last->next = NULL;
    return nt;
}

text_t *read_text(char *filename){
    char line[100];
    char text[1000000] = "";
    FILE * fr = fopen(filename, "r");
    if(!fr)
        return NULL;
    while(fgets(line, 100, fr)){
    strcat(text, line);
    };
    fclose(fr);
    text_t *thetext = text_new_empty();
    for(int i = 0; i < strlen(text) && text[i] != '/0'; i++){
        char sentense_contents[1000] = {0};
        for(int j = 0; text[i] != '!' && text[i] != '.' && text[i] != '?'; i++, j++){
            sentense_contents[j] = text[i];
        }
        text_sentense_add(thetext, sentense_new(sentense_contents), text_sentenses(thetext));
    }
    return thetext;
}

void write_text(char *filename, text_t *self){
    FILE *fp = fopen(filename, "w");
    sent_t *sent = self->first;
    for(int i = 0; i < self->count; i++){
        sent = sent->next;
        char buff[1000] = {"\0"};
        print_sentense(buff, sent);
        char tmp[100] = {"\0"};
        sprintf(tmp, "Sentence%d, contains %d words:", i, sentense_words(sent));
        fputs(tmp, fp);
        fputs(buff, fp);
    }
    fclose(fp);
}

sent_t *sentense_new(char *contents){
    sent_t *asent = malloc(sizeof(struct sent_s));
    asent->prev = NULL;
    asent->next = NULL;
    asent->count = 0;
    asent->fword = word_new(" ");
    contents = clear_odd(contents, strlen(contents));
    char *p;
    p = strtok(contents, " ");
    if(!p)
        return asent;
    word_t *nword = word_new(p);
    asent->fword->next = nword;
    asent->count++;
    while(p){
        p = strtok(NULL, " ");
        if(p){
            nword->next = word_new(p);
            nword = nword->next;
            asent->count++;
        }
    }
    return asent;
}

char *print_sentense(char *buff, sent_t *self){
    word_t *curr = self->fword;
    for(int i = 0; i < self->count && curr->next!=NULL; i++){
        curr = curr->next;
        if(!i){
            sprintf(buff, "%s", curr->contents);
        }else
            sprintf(buff, "%s, %s", buff, curr->contents);
    }
    sprintf(buff, "%s\n", buff);
    return buff;
}

void sentense_free(sent_t *self){
    while(sentense_words(self)){
        word_t *curr = self->fword->next;
        self->fword->next = curr->next;
        free(curr);
        self->count--;
    }
    free(self);
}

void text_sentense_add(text_t *text, sent_t *self, int index){
    sent_t *curr = text->first;
    if (text->count < index)
        index = text->count;
    for (int i = 0; i < index; i++)
    {
        curr = curr->next;
    }
    self->prev = curr;
    self->next = curr->next;
    curr->next->prev = self;
    curr->next = self;
    text->count++;
}

sent_t *text_sentense_delete(text_t *text, int index){
    sent_t *self;
    sent_t *curr = text->first->next;
    if (text->last == curr)
        return NULL;
    if (index >= text->count )
    {
        index = text->count - 1;
    }
    for (int i = 0; i < index; i++)
        curr = curr->next;
    self = curr;
    self->prev->next = curr->next;
    self->next->prev = curr->prev;
    text->count--;
    self->next = NULL;
    self->prev = NULL;
    return self;
}

word_t *word_new(char *contents){
    word_t *neword = malloc(sizeof(struct word_s)+strlen(contents)*sizeof(char));
    neword->contents = malloc(strlen(contents));
    strcpy(neword->contents, contents);
    neword->next = NULL;
    return neword;
}

sent_t *text_get_sent(text_t *text, int index){
    sent_t *curr = text->first->next;
    if (text->count < index)
        index = text->count-1;
    for (int i = 0; i < index; i++){
        curr =curr->next;
    }
    return curr;
}

void swap(text_t *text, int i, int j){
    sent_t *s1 = text_get_sent(text, i);
    sent_t *s2 = text_get_sent(text, j);
    s2->next->prev = s1;
    s1->next = s2->next;
    s2->next = s1;
    s2->prev = s1->prev;
    s1->prev->next = s2;
    s1->prev = s2;
}

void text_insertion_sort(text_t *self){
    for(int i = 0; i < text_sentenses(self);i++){
        int j = i;
        while(j > 0 && text_get_sent(self, j)->count < text_get_sent(self, j-1)->count){
        swap(self, j-1, j);
        j--;
        }
    }
}

char* clear_odd(char *stuff, size_t length){
    for(int i = 0; i < length; i++){
        if(!isalpha(stuff[i]) && !isspace(stuff[i])){
            for(int j = i; j < length; j++){
                stuff[j] = stuff[j+1];
            }
            length--;
        }
    }
    char *newstr = malloc(sizeof(char)*(length + 1));
    strcpy(newstr, stuff);
    return newstr;
}

int text_sentenses(text_t *self){
    return self->count;
}

int sentense_words(sent_t *self){
    return self->count;
}

void text_free(text_t *text){
    while(text->count){
        sentense_free(text_sentense_delete(text, 0));
    }
    free(text->first);
    free(text->last);
    free(text);
}

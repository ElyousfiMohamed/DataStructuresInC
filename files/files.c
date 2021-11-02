#include <stdio.h>
#include <stdlib.h>

typedef struct element {
    int data;
    struct element *next;
}Element;

typedef struct {
    Element *first;
    Element *last;
}File;

int isEmpty(File *file) {
    if(file->first == NULL && file->last == NULL)
        return 1;
    else
        return 0;
}

File* createFile() {
    File *f = (File*)malloc(sizeof(File));
    f->first = NULL;
    f->last = NULL;
    return f;
}

Element* createElement(int data) {
    Element *e = (Element*)malloc(sizeof(Element));
    e->data = data;
    e->next = NULL;
    return e;
}

void enFiler(int data,File *file) {
    Element *e = createElement(data);
    if(isEmpty(file)) {
        file->first = e;
        file->last = e;
    }else {
        file->last->next = e;
        file->last = e;
    }
}

int getFirst(File *file){
    if(file->first == NULL)
        return -1;
    else
        return file->first->data;
}

void deFilier(File *file) {
    File *tmp;
    if(isEmpty(file)) {
        printf("la file est vide\n");

    }else if(file->first == file->last) {
        tmp = file->first;
        file->first = NULL;
        file->last = NULL;
        free(tmp);

    }else {
        tmp = file->first;
        file->first = file->first->next;
        free(tmp);
    }
}

int main()
{
    File *queue;
    queue=createFile();

    enFiler(1,queue);
    enFiler(3,queue);
    enFiler(5,queue);
    enFiler(6,queue);
    enFiler(9,queue);

    printf("\n%d\n",getFirst(queue));
    deFilier(queue);

    printf("\n%d\n",getFirst(queue));
    deFilier(queue);

    printf("\n%d\n",getFirst(queue));
    deFilier(queue);

    printf("\n%d\n",getFirst(queue));
    deFilier(queue);

    printf("\n%d\n",getFirst(queue));
    deFilier(queue);

    printf("\n%d\n",getFirst(queue));
    deFilier(queue);
    return 0;
}

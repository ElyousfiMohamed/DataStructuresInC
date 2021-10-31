#include <stdio.h>
#include <stdlib.h>

typedef struct element {
    int data;
    struct element *left;
    struct element *right;
}Element;

Element* createElement(int data) {
    Element *T = (Element*)malloc(sizeof(Element));
    T->left = NULL;
    T->right = NULL;
    T->data = data;
    return T;
}

/* file pour affichage par largeur */
typedef struct file{
    struct element *node;
    struct file *next;
}File;

typedef struct {
    File *first;
    File *last;
}FileFL;

int isEmpty(FileFL *file) {
    if(file->first == NULL && file->last == NULL)
        return 1;
    else
        return 0;
}

FileFL* createFileFL() {
    FileFL *f = (FileFL*)malloc(sizeof(FileFL));
    f->first = NULL;
    f->last = NULL;
    return f;
}

File* createFile(Element* node) {
    File *e = (File*)malloc(sizeof(File));
    e->node = node;
    e->next = NULL;
    return e;
}

void enFiler(Element* node,FileFL *file) {
    File *e = createFile(node);
    if(isEmpty(file)) {
        file->first = e;
        file->last = e;
    }else {
        file->last->next = e;
        file->last = e;
    }
}

int getFirst(FileFL *file){
    if(file->first == NULL)
        return -1;
    else
        return file->first->node;
}

void deFilier(FileFL *file) {
    FileFL *tmp;
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

void affichageParLargeur(Element *T) {
    Element *tmp = T;
    FileFL *FL = createFileFL();
    enFiler(tmp,FL);
    do{
        tmp = getFirst(FL);
        printf("%d ",tmp->data);
        deFilier(FL);

        if(tmp -> left != NULL)
            enFiler(tmp -> left,FL);

        if(tmp -> right != NULL)
            enFiler(tmp -> right,FL);
    }while(!isEmpty(FL));
}

void insert(Element *T,int data){
    Element *tmp = T;

    if(data < tmp->data && tmp -> left != NULL)
        insert(tmp->left,data);

    if(data > tmp->data && tmp -> right != NULL)
        insert(tmp->right,data);


    Element *e = createElement(data);

    if(data < tmp->data && tmp -> left == NULL)
        tmp -> left = e;

    if(data > tmp->data && tmp -> right == NULL)
        tmp -> right = e;
}


void displayPreRec(Element *T) {
    if(T != NULL) {
        printf("%d ",T->data);
        displayPreRec(T->left);
        displayPreRec(T->right);
    }
}

int main()
{
    Element *T = createElement(1);

    insert(T,2);
    insert(T,0);
    insert(T,3);
    insert(T,-1);
    insert(T,4);
    displayPreRec(T);
    printf("\n");
    affichageParLargeur(T);

    return 0;
}


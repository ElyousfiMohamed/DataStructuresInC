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

void displayInRec(Element *T) {
    if(T != NULL) {
        displayInRec(T->left);
        printf("%d ",T->data);
        displayInRec(T->right);
    }
}

/* pile pour methode iterative */
typedef struct pile {
    struct element *node;
    struct pile *next;
}Pile;

Pile* createElemPile(Element *node) {
    Pile *p = (Pile*)malloc(sizeof(Pile));
    p->node = node;
    p->next = NULL;
    return p;
}

void push(Pile **head,Element *node) {
    Pile *p = createElemPile(node);
    p->next = *head;
    *head = p;
}

Element* peek(Pile *head) {
    if(head == NULL)
        printf("La pile est vide");
    else
        return head->node;
}

void pop(Pile **head) {
    if(head == NULL) {
        printf("La pile est vide");
        return;
    }

    Pile *tmp = *head;
    *head=(*head)->next;
    free(tmp);
}

void displayInItera(Element *T) {
    Element *tmp = T;
    Pile *P = NULL;
    do{
        if(tmp != NULL){
            push(&P,tmp);
            tmp = tmp->left;
        }

        if(tmp == NULL){
            tmp = peek(P);
            printf("%d ",tmp->data);
            pop(&P);
            tmp = tmp->right;
        }
    }while(P != NULL || tmp != NULL);
}


int main()
{
    Element *T;
    Element *e1,*e2,*e3,*e4,*e5,*e6,*e7,*e8,*e9,*e10;

    e1 = createElement(1);
    e2 = createElement(2);
    e3 = createElement(3);
    e4 = createElement(4);
    e5 = createElement(5);
    e6 = createElement(6);
    e7 = createElement(7);
    e8 = createElement(8);
    e9 = createElement(9);
    e10 = createElement(10);

    T = e1;
    e1->left = e2;
    e1->right = e3;
    e2->left = e4;
    e2->right = e5;
    e3->left = e6;
    e3->right = e7;
    e5->left = e8;
    e7->left = e9;
    e7->right = e10;

    displayInRec(T);
    printf("\n");
    displayInItera(T);

    return 0;
}



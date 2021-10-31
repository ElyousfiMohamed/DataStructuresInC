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

void displayPostRec(Element *T) {
    if(T != NULL) {
        displayPostRec(T->left);
        displayPostRec(T->right);
        printf("%d ",T->data);
    }
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

    displayPostRec(T);
    printf("\n");

    return 0;
}




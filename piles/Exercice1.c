#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pile {
    int data;
    struct pile *next;
}Pile;

Pile* createElemPile(int data) {
    Pile *p = (Pile*)malloc(sizeof(Pile));
    p->data = data;
    p->next = NULL;
    return p;
}

int isEmpty (Pile *head) {
    if(head == NULL)
        return 1;
    else
        return 0;
}

void push(Pile **head,int data) {
    Pile *p = createElemPile(data);
    p->next = *head;
    *head = p;
}

int peek(Pile *head) {
    if(head == NULL)
        printf("La pile est vide");
    else
        return head->data;
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

int evaluer (char *T,int taille) {
    Pile *head = NULL;
    int helper,result;
    for(int i=0;i<taille;i++) {
        helper = T[i]-48;
        if( helper >= 0 && helper <= 9)
            push(&head,helper);
        else {
            switch(T[i]) {
            case '+' :
                result = peek(head);
                pop(&head);
                result += peek(head);
                pop(&head);
                push(&head,result);
                break;
            case '-' :
                result = peek(head);
                pop(&head);
                result -= peek(head);
                pop(&head);
                push(&head,result);
                break;

            case '*' :
                result = peek(head);
                pop(&head);
                result *= peek(head);
                pop(&head);
                push(&head,result);
                break;

            case '/' :
                result = peek(head);
                pop(&head);
                result /= peek(head);
                pop(&head);
                push(&head,result);
                break;
            }
        }
    }
    pop(&head);
    return result;
}

int main()
{
    //variables
    char *TMP = (char*)malloc(50),*T;
    int i;

    //saisie de l'expression arithmethique
    printf("entrez une expression arithmetique en postfixe : ");
    scanf("%s",TMP);

    //calcule de la taille d'expression
    for(i=0;TMP[i]!='\0';i++);

    T = (char*)malloc(i);
    strcpy(T,TMP);
    free(TMP);

    printf("\n%d\n",evaluer(T,i));
    return 0;
}

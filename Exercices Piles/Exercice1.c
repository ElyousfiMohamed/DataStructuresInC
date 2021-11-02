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

int evaluer (char *T) {
    Pile *head = NULL;
    int helper,result,tmp;
    for(int i=0;i<strlen(T);i++) {
        helper = T[i]-48;
        if( helper >= 0 && helper <= 9)
            push(&head,helper);
        else {
            switch(T[i]) {
            case '+' :
                tmp = peek(head);
                pop(&head);
                result = peek(head) + tmp;
                pop(&head);
                push(&head,result);
                break;
            case '-' :
                tmp = peek(head);
                pop(&head);
                result = peek(head) - tmp;
                pop(&head);
                push(&head,result);
                break;

            case '*' :
                tmp = peek(head);
                pop(&head);
                result = peek(head) * tmp;
                pop(&head);
                push(&head,result);
                break;

            case '/' :
                tmp = peek(head);
                pop(&head);
                result = peek(head) / tmp;
                pop(&head);
                push(&head,result);
                break;
            }
        }
    }
    pop(&head);
    return result;
}

int verifier_si_postfixe(char *T) {
    int flag = 0;
    for(int i=0;i<strlen(T);i++) {
        if(T[i] >= '0' && T[i] <= '9')
            flag++;

        if(T[i] >= '*' && T[i] <= '/')
            flag--;
    }
    if(flag == 1                           //on verifie si le nombre d'operandes plus que nombre d'operateurs par 1
       && (T[0] >= '0' && T[0] <= '9')         //et que les deux premiers caracteres sont des nombres
       && (T[1] >= '0' && T[1] <= '9')
       && (T[strlen(T)-1] >= '*' && T[strlen(T)-1] <= '/')) //et que le dernier caractere est un operateur
        return 1;
    else
        return 0;
}

int main()
{
    char *TMP = (char*)malloc(50),*T;
    int i;

    printf("entrez une expression arithmetique en postfixe : ");
    scanf("%s",TMP);

    T = (char*)malloc(strlen(TMP));
    strcpy(T,TMP);
    free(TMP);

    if(verifier_si_postfixe(T))
        printf("\n%d\n",evaluer(T));
    else
        printf("\nl'expression n'est pas en postfixe\n");

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pile{
    char data;
    struct pile *next;
}Pile;

Pile* createElemPile(char data) {
    Pile *p = (Pile*)malloc(sizeof(Pile));
    p->data = data;
    p->next = NULL;
    return p;
}

char peek(Pile *head) {
    if(head == NULL)
        printf("La Pile est vide");
    else
        return head->data;
}

int isEmpty (Pile *head) {
    if(head == NULL)
        return 1;
    else
        return 0;
}

void push(Pile **head,char data) {
    Pile *p = createElemPile(data);
    p->next = *head;
    *head = p;
}

void pop(Pile **head) {
    if(head == NULL) {
        printf("La Pile est vide");
        return;
    }

    Pile *tmp = *head;
    *head=(*head)->next;
    free(tmp);
}

int est_bien_parentheses (char *T) {
    Pile *head = NULL;
    for(int i=0;i<strlen(T);i++) {

        if(T[i] != '(' && T[i] != ')' )
        continue;

        if(T[i] == ')' && isEmpty(head) )
            return 0;

        switch(T[i]){
        case '(' :
               push(&head,'(');
                break;

        case ')' :
               pop(&head);
                break;
        }
    }
    return isEmpty(head);
}

void convert_infixe_postfixe(char *T) {
    Pile *head = NULL;
    int helper,i = 0;
    while(i < strlen(T) ) {
        helper = T[i] - 48;
        if(T[i] == '(')
            push(&head,'(');

        if(helper >= 0 && helper <= 9){
            printf("%c",T[i]);
        }

        if(helper >= -6 && helper <= -1){
            while(isEmpty(head) == 0) {
                if(peek(head) == '(')
                    pop(&head);
            }
            push(&head,T[i]);
        }

        if(T[i] == ')') {
            while(isEmpty(head) == 0) {
                printf("%c",peek(head));
                pop(&head);
            }
        }
        i++;
    }
    while(isEmpty(head) == 0) {
        printf("%c",peek(head));
        pop(&head);
    }
}


/*//partie evaluer
typedef struct pileE {
    int data;
    struct pileE *next;
}PileE;

PileE* createElemPileE(int data) {
    PileE *p = (PileE*)malloc(sizeof(PileE));
    p->data = data;
    p->next = NULL;
    return p;
}

int isEmptyE (PileE *head) {
    if(head == NULL)
        return 1;
    else
        return 0;
}

void pushE(PileE **head,int data) {
    PileE *p = createElemPileE(data);
    p->next = *head;
    *head = p;
}

int peekE(PileE *head) {
    if(head == NULL)
        printf("La pile est vide");
    else
        return head->data;
}

void popE(PileE **head) {
    if(head == NULL) {
        printf("La pile est vide");
        return;
    }

    PileE *tmp = *head;
    *head=(*head)->next;
    free(tmp);
}

int evaluer (char *T) {
    PileE *head = NULL;
    int helper,result;

    for(int i=0;i<strlen(T);i++) {
        helper = T[i]-48;
        if( helper >= 0 && helper <= 9)
            pushE(&head,helper);

        else {
            switch(T[i]) {
            case '+' :
                result = peekE(head);
                popE(&head);
                result += peekE(head);
                popE(&head);
                pushE(&head,result);
                break;
            case '-' :
                result = peekE(head);
                popE(&head);
                result -= peekE(head);
                popE(&head);
                pushE(&head,result);
                break;

            case '*' :
                result = peekE(head);
                popE(&head);
                result *= peekE(head);
                popE(&head);
                pushE(&head,result);
                break;

            case '/' :
                result = peekE(head);
                popE(&head);
                result = result / peekE(head);
                popE(&head);
                pushE(&head,result);
                break;
            }
        }
    }
    popE(&head);
    return result;
}*/
int main()
{
    char *TMP = (char*)malloc(50),*T;
    int i;

    printf("entrez une expression : ");
    scanf("%s",TMP);

    //calcule de la taille d'expression
    for(i=0;TMP[i]!='\0';i++);

    T = (char*)malloc(i);
    strcpy(T,TMP);
    free(TMP);

    if(est_bien_parentheses(T)) {
        convert_infixe_postfixe (T);
    }
    else
        printf("\nexpression mal parenthesee\n");

    /*printf("\n%d\n",evaluer(expr));*/
    return 0;
}

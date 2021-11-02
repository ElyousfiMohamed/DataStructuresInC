#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//pile de verification parethesee et conversion infix -> postfixe
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

//pile d'evaluation
typedef struct pileEval {
    int data;
    struct pileEval *next;
}PileEval;

PileEval* createElemPileEval(int data) {
    PileEval *p = (PileEval*)malloc(sizeof(PileEval));
    p->data = data;
    p->next = NULL;
    return p;
}

int isEmptyEval (PileEval *head) {
    if(head == NULL)
        return 1;
    else
        return 0;
}

void pushEval(PileEval **head,int data) {
    PileEval *p = createElemPileEval(data);
    p->next = *head;
    *head = p;
}

int peekEval(PileEval *head) {
    if(head == NULL)
        printf("La pile est vide");
    else
        return head->data;
}

void popEval(PileEval **head) {
    if(head == NULL) {
        printf("La pile est vide");
        return;
    }

    PileEval *tmp = *head;
    *head=(*head)->next;
    free(tmp);
}

//fonctions principales
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

char* convert_infixe_postfixe(char *T) {
    Pile *head = NULL;
    int i,j = 0;
    for(i=0;i<strlen(T);i++){
        if(T[i] == '(' || T[i] == ')')
            j++;
    }

    char *result = (char*)malloc(strlen(T)-j);
    i = 0;
    j = 0;

    while(i < strlen(T) ) {
        if(T[i] >= '0' && T[i] <= '9'){
            result[j] = T[i];
            j++;
        }

        if(T[i] >= '*' && T[i] <= '/')
            push(&head,T[i]);

        if(T[i] == ')') {
            while(isEmpty(head) == 0) {
                result[j] = peek(head);
                pop(&head);
                j++;
            }
        }
        i++;
    }
    while(isEmpty(head) == 0) {
        result[j] = peek(head);
        pop(&head);
        j++;
    }
    return result;
}

int evaluer (char *T) {
    PileEval *head = NULL;
    int helper,result,tmp;
    for(int i=0;i<strlen(T);i++) {
        helper = T[i]-48;
        if( helper >= 0 && helper <= 9)
            pushEval(&head,helper);
        else {
            switch(T[i]) {
            case '+' :
                tmp = peekEval(head);
                popEval(&head);
                result = peekEval(head) + tmp;
                popEval(&head);
                pushEval(&head,result);
                break;
            case '-' :
                tmp = peekEval(head);
                popEval(&head);
                result = peekEval(head) - tmp;
                popEval(&head);
                pushEval(&head,result);
                break;

            case '*' :
                tmp = peekEval(head);
                popEval(&head);
                result = peekEval(head) * tmp;
                popEval(&head);
                pushEval(&head,result);
                break;

            case '/' :
                tmp = peekEval(head);
                popEval(&head);
                result = peekEval(head) / tmp;
                popEval(&head);
                pushEval(&head,result);
                break;
            }
        }
    }
    popEval(&head);
    return result;
}

int main () {
    char *TMP = (char*)malloc(50),*T;
    int i;

    printf("entrez une expression arithmetique : ");
    scanf("%s",TMP);

    T = (char*)malloc(strlen(TMP));
    strcpy(T,TMP);
    free(TMP);

    if(est_bien_parentheses(T)) {
        printf("\nBien parentheresee\n");
        printf("Expression en postfixe : %s\n",convert_infixe_postfixe(T));
        printf("Valeur de l'expression : %d\n",evaluer(convert_infixe_postfixe(T)));
    }

    else
        printf("\nMal parentheresee\n");

    return 0;
}

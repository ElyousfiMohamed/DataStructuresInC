#include <stdio.h>
#include <stdlib.h>

typedef struct pile{
    char data;
    struct expr *next;
}Pile;

Pile* createElemPile(char data) {
    Pile *p = (Pile*)malloc(sizeof(Pile));
    p->data = data;
    p->next = NULL;
    return p;
}

char peek(Pile *head) {
    if(head == NULL)
        printf("La pile est vide");
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
        printf("La pile est vide");
        return;
    }

    Pile *tmp = *head;
    *head=(*head)->next;
    free(tmp);
}

int est_bien_parentheses (char *T,int taille,Pile **head) {
    for(int i=0;i<taille;i++) {

        if(T[i] != '(' && T[i] != ')' )
        continue;

        if(T[i] == ')' && isEmpty(*head) )
            return 0;
        switch(T[i]){
        case '(' :
               push(head,'(');
                break;

        case ')' :
               pop(head);
                break;
        }
    }

    return isEmpty(*head);

}

char* convert_infixe_postfixe(char *T,int taille,Pile **head) {
    char *result = (char*)malloc(taille);
    int helper;
    for(int i=0,j=0;i<taille;i++) {
        helper = T[i] - 48;
        if(helper >= 0 && helper <= 9){
            result[j] = T[i];
            j++;
        }

        if(helper >= -6 && helper <= -1){
            push(head,T[i]);
        }

        if(T[i] == ')') {
            result[j] = peek(*head);
            pop(head);
            j++;
        }
    }
    return result;
}
int main()
{
    //variables
    Pile *head = NULL;
    char *TMP = (char*)malloc(50),*T;
    int i;

    //saisie de l'expression arithmethique
    printf("entrez une expression : ");
    scanf("%s",TMP);

    //calcule de la taille d'expression
    for(i=0;TMP[i]!='\0';i++);

    T = (char*)malloc(i);
    strcpy(T,TMP);
    free(TMP);

    if(est_bien_parentheses(T,i,&head)) {
        char *expr = convert_infixe_postfixe (T,i,&head);
        printf("\n%s\n",expr);
    }
    else
        printf("\nexpression mal parenthesee\n");


    return 0;
}

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

int est_bien_structuree (char *T) {
    Pile *head = NULL;
    for(int i=0;i<strlen(T);i++) {
        if(T[i] == '<' && T[i+1] != '/')
            push(&head,'<');

        if(T[i] == '<' && T[i+1] == '/' && isEmpty(head))
            return 0;

        if(T[i] == '<' && T[i+1] == '/' && !isEmpty(head))
            pop(&head);
    }

    return isEmpty(head);
}


int main()
{
    char *TMP = (char*)malloc(50),*T;
    int i;

    printf("entrez un code html :\n");
    gets(TMP);

    T = (char*)malloc(strlen(TMP));
    strcpy(T,TMP);
    free(TMP);

    if(est_bien_structuree(T))
        printf("\nBien structuree\n");
    else
        printf("\nMal structuree\n");

    return 0;
}

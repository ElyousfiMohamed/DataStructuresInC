#include <stdio.h>
#include <stdlib.h>

typedef struct piles{
    int data;
    struct piles *next;
}pile;

pile* createElement(int data) {
    pile *p = (pile*)malloc(sizeof(pile));
    p->data = data;
    p->next = NULL;
    return p;
}

int isEmpty(pile **S) {
    if(*S == NULL)
        return 1;
    else
        return 0;
}

void push(int data,pile **S) {
    pile *p = createElement(data);
    p->next = *S;
    *S = p;
}

int peek(pile *S) {
    if(S == NULL)
        return -1;
    else
        return S->data;
}

void pop(pile **S){
    if(*S == NULL)
        return;

    pile *tmp = *S;
    *S = (*S)->next;
    free(tmp);
}

int main()
{
    pile *S = NULL;
    printf("peek = %d\n",peek(S));
    push(5,&S);
    push(4,&S);
    push(3,&S);
    push(2,&S);
    push(1,&S);
    printf("peek = %d\n",peek(S));
    pop(&S);
    printf("peek = %d\n",peek(S));
    pop(&S);
    printf("peek = %d\n",peek(S));
    pop(&S);
    printf("peek = %d\n",peek(S));
    pop(&S);
    printf("peek = %d\n",peek(S));
    pop(&S);
    printf("peek = %d\n",peek(S));
    return 0;
}

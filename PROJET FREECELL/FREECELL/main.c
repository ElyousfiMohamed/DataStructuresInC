#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char enseigne; /*S : Spade = Pique, C : Club = Trèfle, H : Heart = Coeur, D : Diamond = Carreau*/
    char* valeur; // As, Roi, Dame, Valet, 10, 9, 8, 7, 6, 5, 4, 3, 2.
}Carte;

typedef struct col {  //les colonnes(cases) sont au forme des piles
    Carte *c;
    struct col *next;
}Col;

Carte *cartes[52]; // tableau des cartes
Col *Zone1[8]; //zone1 contient 8 colonnes
Col *Zone2[4]; //zone2 contient 4 colonnes
Col *Zone3[4]; //zone3 contient 4 colonnes

void push(Col **head,Carte *c) {
    Col *cl = (Col*)malloc(sizeof(Col));
    cl->c = c;
    cl->next = *head;
    *head = cl;
}

Carte* peek(Col *head) {
    if(head == NULL)
        printf("colonne vide");
    else
        return head->c;
}

void pop(Col **head) {
    if(head == NULL) {
        printf("colonne vide");
        return;
    }

    Col *tmp = *head;
    *head=(*head)->next;
    free(tmp);
}

void swap(int b, int c) {
    Carte *temp = cartes[b];
    cartes[b] = cartes[c];
    cartes[c] = temp;
}

void displayCol(Col *c) {
    Col *tmp = c;
        while(tmp != NULL) {
            printf("%c|%s ",tmp->c->enseigne,tmp->c->valeur);
            tmp = tmp -> next;
        }
}

void displayZones() {
    Col *tmp;
    printf("**********Zone1**********\n");
    for(int i=0;i<8;i++) {
        printf("col %d : ",i);
        displayCol(Zone1[i]);
        printf("\n");
    }
    printf("\n\n");
    printf("**********Zone2**********\n");
    for(int i=0;i<4;i++) {
        printf("col %d : ",i);
        displayCol(Zone2[i]);
        printf("\n");
    }
    printf("\n\n");
    printf("**********Zone3**********\n");
    for(int i=0;i<4;i++) {
        printf("col %d : ",i);
        displayCol(Zone3[i]);
        printf("\n");
    }
    printf("\n");
}

void InitialiserJeux() {
    char enseignes[4] = {'S','C','H','D'};/*S : Spade = Pique, C : Club = Trèfle,
                                            H : Heart = Coeur, D : Diamond = Carreau*/
    char* valeurs[13] = {"As", "Roi", "Dame", "Valet", "10","9", "8", "7", "6", "5", "4", "3", "2"};
    int k = 0,tmp;

    for (int i=0;i<8;i++) {
        Zone1[i] = NULL;
    }

    for (int i=0;i<4;i++) {
        Zone2[i] = NULL;
        Zone3[i] = NULL;
    }

    for(int i=0;i<4;i++){
        for(int j=0;j<13;j++){
            cartes[k] = (Carte*)malloc(sizeof(Carte));
            cartes[k]->enseigne = enseignes[i];
            cartes[k]->valeur = valeurs[j];
            k++;
        }
    }

    k++;
    for (int i=0;i<4;i++) {    // les 4 premiers colonnes contient 7 cartes
        for (int j=0;j<7;j++) {
            k--;
            tmp = rand()%k;
            push(&Zone1[i],cartes[tmp]);
            swap(tmp,k-1);
        }
    }

    for (int i=4;i<8;i++) {  //les 4 derniers colonnes contient 6 cartes
        for (int j=0;j<6;j++) {
            k--;
            tmp = rand()%k;
            push(&Zone1[i],cartes[tmp]);
            swap(tmp,k-1);
        }
    }
}

void deplaceZone1(int colSrc,int colDest) {
        push(&Zone1[colDest],peek(Zone2[colSrc]));
        pop(&Zone2[colSrc]);
}

void deplaceZone2(int colSrc,int colDest) {
        push(&Zone2[colDest],peek(Zone1[colSrc]));
        pop(&Zone1[colSrc]);
}

void deplaceZone3(int colSrc,int colDest) {
        push(&Zone3[colDest],peek(Zone1[colSrc]));
        pop(&Zone1[colSrc]);
}

int main()
{
    int colSrc,colDest;
    char choice;
    InitialiserJeux();

    while(1) {
        system("cls");
        printf("**********Menu**********\n");
        printf("1 pour deplacer du zone1 au zone2\n");
        printf("2 pour deplacer du zone2 au zone1\n");
        printf("3 pour deplacer du zone1 au zone3\n");
        printf("R pour reinitialiser le jeux\n");
        printf("Q pour quitter\n");
        printf("************************\n\n");
        displayZones();
        scanf("%c",&choice);
        switch(choice) {
            case '1' :
                printf("colonne source(zone1) : ");scanf("%d",&colSrc);
                printf("colonne destination(zone2) : ");scanf("%d",&colDest);
                deplaceZone2(colSrc,colDest);
                break;

            case '2' :
                printf("colonne source(zone2) : ");scanf("%d",&colSrc);
                printf("colonne destination(zone1) : ");scanf("%d",&colDest);
                deplaceZone1(colSrc,colDest);
                break;

            case '3' :
                printf("colonne source(zone1) : ");scanf("%d",&colSrc);
                printf("colonne destination(zone3) : ");scanf("%d",&colDest);
                deplaceZone3(colSrc,colDest);
                break;

            case 'R' :
                InitialiserJeux();
                break;

            case 'Q' :
                goto end;
                break;
        }
    }
    end : return 0;
}

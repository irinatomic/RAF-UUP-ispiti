#include <stdio.h>
#include <string.h>

char opcijeStr[] = "[0]Prekid programa \n[1]Ucitavanje podataka \n[2]Broj ocena po predmetu \n[3]Dodavanje ocene za ucenika na predmetu \nOpcija: ";

typedef struct{

    int broj;
    char predmet[3];
    int ocene[5];
    struct Ucenik* next;

}Ucenik;

Ucenik* createUcenik(char str[]){

    Ucenik* newUcenik = (Ucenik*) malloc(sizeof(Ucenik));

    char* token = strtok(str, " ");
    newUcenik->broj = atoi(token);

    token = strtok(NULL, " ");
    strcpy(newUcenik->predmet, token);

    int oceneIndex = 0;
    token = strtok(NULL, " ");
    while(token){
        newUcenik->ocene[oceneIndex++] = atoi(token);
        token = strtok(NULL, " ");
    }

    for(oceneIndex; oceneIndex < 5; oceneIndex++)
        newUcenik->ocene[oceneIndex] = NULL;

    newUcenik->next = NULL;
    return newUcenik;
}

Ucenik* addUcenik(Ucenik* head, Ucenik* newUcenik){

    if(head == NULL)                                                //ako je lista prazna
        return newUcenik;

    if(newUcenik->broj < head->broj || (newUcenik->broj == head->broj && strcmp(newUcenik->predmet, head->predmet) < 0)){                               //ako dodajemo na pocetak
        newUcenik->next = head;
        return newUcenik;
    }

    Ucenik* prev = NULL;
    Ucenik* tmp = head;
    while(tmp != NULL && newUcenik->broj > tmp->broj){
        prev = tmp;
        tmp = tmp->next;
    }

    while(tmp != NULL && (newUcenik->broj == tmp->broj) && strcmp(newUcenik->predmet, tmp->predmet) > 0){
        prev = tmp;
        tmp = tmp->next;
    }

    if(tmp == NULL){
        prev->next = newUcenik;
        return head;
    }

    newUcenik->next = tmp;
    prev->next = newUcenik;
    return head;
}

int prebrojUNizu(int min, int max, char niz[]){

    int brojac = 0;
    for(int i = 0; i < 5; i++){
        brojac = (niz[i] >= min && niz[i] <= max)? brojac+1: brojac;
    }
    return brojac;
}

int brojOcenaURasponuIter(Ucenik* head, char predmet[], int min, int max){

    int brojac = 0;
    while(head != NULL){
        if(strcmp(head->predmet, predmet) == 0){
            brojac += prebrojUNizu(min, max, head->ocene);
        }
        head = head->next;
    }
    return brojac;
}

int brojOcenaURasponuRek(Ucenik* head, char predmet[], int min, int max, int* brojac){

    if(head == NULL)
        return *brojac;

    if(strcmp(head->predmet, predmet) == 0)
            (*brojac) += prebrojUNizu(min, max, head->ocene);

    brojOcenaURasponuRek(head->next, predmet, min, max, brojac);
}

void dodajOcenuUceniku(Ucenik* head, int broj, int ocena, char predmet[]){

    Ucenik* headCopy = head;
    while(head != NULL){
        if(head->broj == broj && !strcmp(head->predmet, predmet)){
            int dodato = 0;
            for(int i = 0; i < 5; i++){
                if(head->ocene[i] == 0){
                    head->ocene[i] = ocena;
                    dodato = 1;
                    break;
                }
            }
            if(!dodato){
                printf("Ucenik vec ima 5 ocena \n");
                return;
            }
            else break;
        }
        head = head->next;
    }

    ispisiListu(headCopy);
    return;
}

void ispisiOcene(int niz[]){

    for(int i = 0; i < 5; i++){
        if(niz[i] != 0)
            printf("%d ", niz[i]);
    }
    printf("\n");
    return;
}

void ispisiListu(Ucenik* head){

    while(head){
        printf("%d %s", head->broj, head->predmet);
        ispisiOcene(head->ocene);
        head = head->next;
    }
    printf("\n");
    return;
}

void izbrisiListu(Ucenik* head){

    while(head != NULL){
        Ucenik* tmp = head;
        head = head->next;
        free(tmp);
    }
    return;
}

Ucenik* ucitajFajl(Ucenik* head, char fileName[]){

    FILE* fp = fopen(fileName, "r");

    if(fp == NULL){
        printf("Greska pri ucitavanju \n");
        fclose(fp);
        return NULL;
    }

    char linijaFajla[100];
    while(!feof(fp)){
        fgets(linijaFajla, sizeof(linijaFajla), fp);
        linijaFajla[strlen(linijaFajla)-1] = '\0';
        Ucenik* newUcenik = createUcenik(linijaFajla);
        head = addUcenik(head, newUcenik);
    }
    fclose(fp);
    return head;
}

int main(){

    Ucenik* head = NULL;
    int n;
    do{
        printf("%s", opcijeStr);
        scanf("%d", &n);

        if(n == 1){
            char imeFajla[] = "ocene1.txt";
            //printf("Unesite ime fajla: ");
            //scanf("%s", imeFajla);
            head = ucitajFajl(head, imeFajla);
            ispisiListu(head);
        }
        else if(n == 2){
            char predmet[3];
            printf("Unesite ime predmeta: ");
            scanf("%s", predmet);
            int min, max;
            printf("Unesite raspon: ");
            scanf("%d%d", &min, &max);
            int brojac = 0;
            printf("iterativno %d \n", brojOcenaURasponuIter(head, predmet, min, max));
            printf("rekurzivno %d \n", brojOcenaURasponuRek(head, predmet, min, max, &brojac));
        }
        else if(n == 3){
            int broj, ocena;
            char predmet[5];
            printf("Unsite redni broj ucenika, ocenu i predmet: ");
            scanf("%d%d%s", &broj, &ocena, predmet);
            dodajOcenuUceniku(head, broj, ocena, predmet);
        }

        else continue;

    }while(n != 0);

    izbrisiListu(head);
    head = NULL;
    printf("Kraj programa");
    return 0;
}

#include <stdio.h>
#include <string.h>

char opcijeStr[] = "[0]Kraj programa \n[1]Ucitavanje podataka \n[2]Broj ocena na predmetu \n[3]Dodavanje ocene za ucenika na predmetu \nOpcija: ";

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

    if(head == NULL)
        return newUcenik;

    if(newUcenik->broj < head->broj || (newUcenik->broj == head->broj && strcmp(newUcenik->predmet, head->predmet) < 0)){
        newUcenik->next = head;
        return newUcenik;
    }

    Ucenik* prev = NULL;
    Ucenik* tmp = head;
    while(tmp && newUcenik->broj > tmp->broj){
        prev = tmp;
        tmp = tmp->next;
    }

    while(tmp && newUcenik->broj == tmp->broj && strcmp(newUcenik->predmet, tmp->predmet) > 0){
        prev = tmp;
        tmp = tmp->next;
    }

    if(tmp == NULL){
        prev->next = newUcenik;
        return head;
    }

    prev->next = newUcenik;
    newUcenik->next = tmp;
    return head;
}

void ispisiOcene(int nizOcena[]){

    for(int i = 0; i < 5; i++){
        if(nizOcena[i] != 0)
            printf("%d ", nizOcena[i]);
    }
    printf("\n");
    return;
}

void ispisiListu(Ucenik* head){

    while(head != NULL){
        printf("%s %d ", head->predmet, head->broj);
        ispisiOcene(head->ocene);
        head = head->next;
    }
    printf("\n");
    return;
}

int brojOcenaPoPredmetuIter(Ucenik* head, char predmet[], int min, int max){

    int brojac = 0;
    while(head != NULL){
        if(strcmp(head->predmet, predmet) == 0){
            for(int i = 0; i < 5; i++)
                brojac = (head->ocene[i] >= min && head->ocene[i] <= max)? brojac+1: brojac;
        }
        head = head->next;
    }
    return brojac;
}

int brojOcenaPoPredmetuRek(Ucenik* head, char predmet[], int min, int max, int* brojac){

    if(head == NULL)
        return *brojac;

    if(strcmp(head->predmet, predmet) == 0){
            for(int i = 0; i < 5; i++)
                *brojac = (head->ocene[i] >= min && head->ocene[i] <= max)? (*brojac)+1: (*brojac);
        }

    brojOcenaPoPredmetuRek(head->next, predmet, min, max, brojac);
}

void dodajOcenuUceniku(Ucenik* head, int broj, char predmet[], int ocena){

    Ucenik* headCopy = head;
    while(head){
        if(head->broj == broj && strcmp(head->predmet, predmet) == 0){
            int upisano = 0;
            for(int i = 0; i < 5; i++){
                if(head->ocene[i] == 0){
                    head->ocene[i] = ocena;
                    upisano = 1;
                    break;
                }
            }
            if(!upisano){
                printf("Ucenik ima vec 5 ocena \n");
                return;
            }
            else
                break;
        }
        head = head->next;
    }

    ispisiListu(headCopy);
    return;
}

Ucenik* ucitajFajl(Ucenik* head, char fileName[]){

    FILE* fp = fopen(fileName, "r");

    if(fp == NULL){
        printf("Greska pri ucitavanju fajla \n");
        fclose(fp);
        return NULL;
    }

    char fileLine[50];
    while(!feof(fp)){
        fgets(fileLine, sizeof(fileLine), fp);
        fileLine[strlen(fileLine)-1] = '\0';
        Ucenik* newUcenik = createUcenik(fileLine);
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
            char fileName[] = "oceneRN.txt";
            head = ucitajFajl(head, fileName);
            ispisiListu(head);
        }
        else if(n == 2){
            char predmet[3];
            int min, max;
            printf("Unesite predmet i raspon ocena: ");
            scanf("%s%d%d", predmet, &min, &max);
            int brojac = 0;
            printf("iterativno %d \n", brojOcenaPoPredmetuIter(head, predmet, min, max));
            printf("rekurzivno %d \n", brojOcenaPoPredmetuRek(head, predmet, min, max, &brojac));
        }
        else if(n == 3){
            int broj, ocena;
            char predmet[20];
            printf("Unesite broj i ocenu: ");
            scanf("%d%d", &broj, &ocena);
            fflush(stdin);
            printf("Unesite predmet: ");
            fgets(predmet, sizeof(predmet), stdin);
            predmet[strlen(predmet)-1] = '\0';
            dodajOcenuUceniku(head, broj, predmet, ocena);
        }
        else continue;

    }while(n != 0);

    izbrisiListu(head);
    head = NULL;
    printf("Kraj programa");
    return 0;
}

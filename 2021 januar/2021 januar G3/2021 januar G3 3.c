#include <stdio.h>
#include <string.h>

char opcijeStr[] = "[0]Kraj programa \n[1]Ucitavanje podataka \n[2]Ispis ocena za ucenika \n[3]Predmet sa najvise ocena \nOpcija: ";

typedef struct{

    int broj;
    char predmet[3];
    int ocene[5];
    struct Ucenik* next;

}Ucenik;

Ucenik* createUcenik(int broj, char predmet[], int ocena){

    Ucenik* newUcenik = (Ucenik*) malloc(sizeof(Ucenik));
    newUcenik->broj = broj;
    strcpy(newUcenik->predmet, predmet);
    newUcenik->ocene[0] = ocena;

    for(int i = 1; i < 5; i++)
        newUcenik->ocene[i] = 0;

    newUcenik->next = NULL;
    return newUcenik;
}

Ucenik* addUcenik(Ucenik* head, int broj, char predmet[], int ocena){

    Ucenik* newUcenik = createUcenik(broj, predmet, ocena);

    if(head == NULL){
        return newUcenik;
    }

    if(strcmp(newUcenik->predmet, head->predmet) < 0 || (strcmp(newUcenik->predmet, head->predmet) == 0 && newUcenik->broj < head->broj)){
        newUcenik->next = head;
        return newUcenik;
    }

    Ucenik* tmp = head;
    Ucenik* prev = NULL;
    while(tmp != NULL && strcmp(newUcenik->predmet, tmp->predmet) > 0){
        prev = tmp;
        tmp = tmp->next;
    }

    if(tmp == NULL){                                            //ako smo na kraju liste
        prev->next = newUcenik;
        return head;
    }

    while(tmp != NULL && strcmp(newUcenik->predmet, tmp->predmet) == 0 && newUcenik->broj > tmp->broj){
        prev = tmp;
        tmp = tmp->next;
    }

    if(tmp != NULL && strcmp(newUcenik->predmet, tmp->predmet) == 0 && newUcenik->broj == tmp->broj){
        int i = 0;
        for(i; i < 5; i++){
            if(tmp->ocene[i] == 0)
                break;
        }
        tmp->ocene[i] = newUcenik->ocene[0];
        free(newUcenik);
        return head;
    }

    if(tmp == NULL){                                            //ako smo na kraju liste
        prev->next = newUcenik;
        return head;
    }

    newUcenik->next = tmp;
    prev->next = newUcenik;
    return head;
}

void ispisiOcene(int nizOcena[]){

    for(int i = 0; i < 5; i++){
        if(nizOcena[i] != 0)
            printf("%d ", nizOcena[i]);
    }
    return;
}

void ispisiListu(Ucenik* head){

    while(head != NULL){
        printf("%s %d ", head->predmet, head->broj);
        ispisiOcene(head->ocene);
        printf("\n");
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

void ispisOcenaZaUcenikaIter(Ucenik* head, int broj){

    while(head != NULL){
        if(head->broj == broj){
            printf("%s ", head->predmet);
            ispisiOcene(head->ocene);
            printf("\n");
        }
        head = head->next;
    }
    printf("\n");
    return;
}

void ispisOcenaZaUcenikaRek(Ucenik* head, int broj){

    if(head == NULL)
        return;

    if(head->broj == broj){
        printf("%s ", head->predmet);
        ispisiOcene(head->ocene);
        printf("\n");
    }

    ispisOcenaZaUcenikaRek(head->next, broj);
}

int brojOcena(int niz[]){

    int brojac = 0;
    for(int i = 0; i < 5; i++){
        brojac = (niz[i] != 0)? brojac+1: brojac;
    }
    return brojac;
}

void predmetSaNajviseOcena(Ucenik* head, char max[]){

    int tmpBrojOcena = 0, maxBrojOcena = 0;
    char tmpStr[5];
    strcpy(tmpStr, head->predmet);
    while(head != NULL){
        if(strcmp(tmpStr, head->predmet) != 0){
            if(tmpBrojOcena > maxBrojOcena){
                maxBrojOcena = tmpBrojOcena;
                strcpy(max, tmpStr);
            }
            tmpBrojOcena = brojOcena(head->ocene);
            strcpy(tmpStr, head->predmet);
        }

        tmpBrojOcena += brojOcena(head->ocene);
        head = head->next;
    }
    return;
}

Ucenik* ucitajFajl(Ucenik* head, char fileName[]){

    FILE* fp = fopen(fileName, "r");

    if(fp == NULL){
        printf("Greska pri ucitavanju fajla \n");
        fclose(fp);
        return NULL;
    }

    int broj, ocena;
    char predmet[3];
    char fileLine[50];
    while(!feof(fp)){
        fgets(fileLine, sizeof(fileLine), fp);
        fileLine[strlen(fileLine)-1] = '\0';
        char* token = strtok(fileLine, " ");
        broj = atoi(token);
        token = strtok(NULL, " ");
        token[strlen(token)-1] = '\0';                                      //♦♣♥☻
        strcpy(predmet, token);
        token = strtok(NULL, " ");
        ocena = atoi(token);
        head = addUcenik(head, broj, predmet, ocena);
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
            char imeFajla[] = "ocene3.txt";
            head = ucitajFajl(head, imeFajla);
            ispisiListu(head);
        }
        else if(n == 2){
            int broj;
            printf("Unesite redni broj ucenika: ");
            scanf("%d", &broj);
            printf("iterativno: \n"); ispisOcenaZaUcenikaIter(head, broj); printf("\n");
            printf("rekurzivno: \n"); ispisOcenaZaUcenikaRek(head, broj); printf("\n");
        }
        else if(n == 3){
            char predmet[3];
            predmetSaNajviseOcena(head, &predmet);
            puts(predmet);
        }
        else continue;

    }while(n != 0);

    izbrisiListu(head);
    head = NULL;
    printf("Kraj programa");
    return 0;
}

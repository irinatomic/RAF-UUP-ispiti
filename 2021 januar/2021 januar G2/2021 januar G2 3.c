#include <stdio.h>
#include <string.h>

//POD TRI NIJE URADJENO

char opcijeStr[] = "[0]Prekid programa \n[1]Ucitavanje podataka \n[2]Brisanje svih ocena za datum \n[3]Zakljucivanje ocena \nOcpija: ";

typedef struct{

    int broj;
    char predmet[3];
    int ocena;
    int god, mesec, dan;
    struct Ucenik* next;

}Ucenik;

typedef struct{

    int broj;
    char mat[30], srp[30], eng[30], pid[30], lik[30];
    struct oceneZaUcenika* next;

}oceneZaUcenika;

Ucenik* createUcenik(char str[]){

    Ucenik* newUcenik = (Ucenik*) malloc(sizeof(Ucenik));

    char* token = strtok(str, " ");
    newUcenik->broj = atoi(token);

    token = strtok(NULL, " ");
    strcpy(newUcenik->predmet, token);

    token = strtok(NULL, " ");
    newUcenik->ocena = atoi(token);

    token = strtok(NULL, " ");
    char* token2 = strtok(token, "-");
    newUcenik->god = atoi(token2);
    token2 = strtok(NULL, "-");
    newUcenik->mesec = atoi(token2);
    token2 = strtok(NULL, "-");
    newUcenik->dan = atoi(token2);
    newUcenik->next = NULL;
    return newUcenik;
}

Ucenik* addUcenik(Ucenik* head, Ucenik* newUcenik){

    if(head == NULL)
        return newUcenik;

    if(newUcenik->broj < head->broj || (newUcenik->broj == head->broj && newUcenik->mesec > head->mesec) ||
       (newUcenik->broj == head->broj && newUcenik->mesec == head->mesec && newUcenik->dan > head->dan)){
        newUcenik->next = head;
        return newUcenik;
    }

    Ucenik* prev = NULL;
    Ucenik* tmp = head;
    while(tmp != NULL && newUcenik->broj > tmp->broj){
        prev = tmp;
        tmp = tmp->next;
    }

    while(tmp != NULL && (newUcenik->broj == tmp->broj) && newUcenik->mesec < tmp->mesec){
        prev = tmp;
        tmp = tmp->next;
    }

    while(tmp != NULL && (newUcenik->broj == tmp->broj) && (newUcenik->mesec == tmp->mesec) && (newUcenik->dan < tmp->dan)){
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

void ispisiListu(Ucenik* head){

    while(head){
        printf("%d %s %d %d-%d-%d \n", head->broj, head->predmet, head->ocena, head->god, head->mesec, head->dan);
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

void izbrisiOceneZaDatum(Ucenik* head, int dan, int mesec, int god){

    while(head != NULL){
        if(head->god == god && head->mesec == mesec && head->dan == dan){
            head->ocena = NULL;
        }
        head = head->next;
    }
    return;
}

Ucenik* ucitajFajl(Ucenik* head, char imeFajla[]){

    FILE* fp = fopen(imeFajla, "r");

    if(fp == NULL){
        printf("Greska pri ucitavanju \n");
        fclose(fp);
        return NULL;
    }

    char linijaFajla[50];
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
            char imeFajla[] = "ocene2.txt";
//            printf("Unesite ime fajla: ");
//            scanf("%s", imeFajla);
            head = ucitajFajl(head, imeFajla);
            ispisiListu(head);
        }
        else if(n == 2){
            printf("Unesite dan, mesec i godinu: ");
            int dan, mesec, god;
            scanf("%d%d%d", &dan, &mesec, &god);
            izbrisiOceneZaDatum(head, dan, mesec, god);
            ispisiListu(head);
        }
        else if(n == 3){
            //oceneProsek(head);
        }
        else continue;

    }while(n != 0);

    izbrisiListu(head);
    head = NULL;
    printf("Kraj programa");
    return 0;
}

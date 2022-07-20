#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//pitanja.txt
//Nesto se cudno desava sa prezimenima u kreiranju Node-a ali nzm sta

char opcijeStr[] = "[0]Kraj programa \n[1]Ucitavanje podataka \n[2]Ukupan br poena za raspon \n[3]Ispis sortirano po indexu \nOpcija: ";

typedef struct{

    char ime;
    char prezime[50];
    int index;
    int god;
    char smer[2];
    int poeni;
    struct Node* next;
}Node;

Node* createNode(char str[]){

    char ime = str[0];

    char prezime[30];
    int prezimeIndex = 0;
    int i = 1;

    for(i = 1; str[i] >= 'a' && str[i] <= 'z'; i++){
        prezime[i-1] = str[i];
    }
    prezime[i] = '\0';

    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->ime = ime;
    strcpy(newNode->prezime, prezime);

    char podstr[6];                                                 //br indexa + godina upisa + smer
    int podstrIndex = 0;
    for(i; str[i] != '@'; i++)
        podstr[podstrIndex++] = str[i];
    podstr[podstrIndex] = '\0';

    char str1[3];                                                                   //broj indexa
    int str1Index = 0;
    for(int i = 0; i < podstrIndex-4; i++)
        str1[str1Index++] = podstr[i];
    str1[str1Index] = '\0';
    char str2[] = {podstr[podstrIndex-4], podstr[podstrIndex-3], '\0'};             //broj upisa
    char str3[] = {podstr[podstrIndex-2], podstr[podstrIndex-1], '\0'};             //smer

    int poeni = 0;
    int k = 1;
    for(int i = strlen(str) - 1; str[i] != ','; i--){
        poeni = k * (str[i] - '0');
        k *= 10;
    }

    newNode->index = atoi(str1);
    newNode->god = atoi(str2);
    strcpy(newNode->smer, str3);
    newNode->poeni = poeni;
    newNode->next = NULL;
    return newNode;
}

Node* addNode(Node* head, Node* newNode){

    if(head == NULL)                                        //ako je lista prazna
        return newNode;

    if(newNode->poeni > head->poeni){                       //ako stavljamo na pocetak
        newNode->next = head;
        return newNode;
    }

    Node* prev = NULL;
    Node* tmp = head;
    while(tmp != NULL && newNode->poeni <= tmp->poeni){
        prev = tmp;
        tmp = tmp->next;
    }
    newNode->next = tmp;
    prev->next = newNode;
    return head;
}

void ispisiListu(Node* head){

    while(head != NULL){
        printf("%c %s %d %d %s %d \n", head->ime, head->prezime, head->index, head->god, head->smer, head->poeni);
        head = head->next;
    }
    printf("\n");
    return;
}

int brojPoenaStudenataURasponuIter(Node* head, int a, int b){

    int zbir = 0;
    while(head != NULL){
        if(head->index > a && head->index < b)
            zbir += head->poeni;
        head = head->next;
    }
    return zbir;
}

void brojPoenaStudenataURasponuRek(Node* head, int a, int b, int* zbir){

    if(head == NULL)
        return;

    if(head->index > a && head->index < b)
        *zbir += head->poeni;

    brojPoenaStudenataURasponuRek(head->next, a, b, zbir);
}

void izbrisiListu(Node* head){

    while(head != NULL){
        Node* tmp = head;
        head = head->next;
        free(tmp);
    }
    return;
}

void swap(Node* a, Node* b){

    char tmpC = a->ime;
    a->ime = b->ime;
    b->ime = tmpC;

    int tmp = a->god;
    a->god = b->god;
    b->god = tmp;

    tmp = a->index;
    a->index = b->index;
    b->index = tmp;

    tmp = a->poeni;
    a->poeni = b->poeni;
    b->poeni = tmp;

    char tmpS[50];
    strcpy(tmpS, a->prezime);
    strcpy(a->prezime, b->prezime);
    strcpy(b->prezime, tmpS);

    strcpy(tmpS, a->smer);
    strcpy(a->smer, b->smer);
    strcpy(b->smer, tmpS);
    return;
}

void sortirajListu(Node* head){

    Node* NodeI = head;
    while(NodeI->next != NULL){
        Node* NodeJ = NodeI->next;
        while(NodeJ != NULL){

            if(strcmp(NodeI->smer, NodeJ->smer) < 0)
                swap(NodeI, NodeJ);
            else if(strcmp(NodeI->smer, NodeJ->smer) == 0){
                if(NodeI->god < NodeJ->god)
                    swap(NodeI, NodeJ);
                else if(NodeI->god == NodeJ->god){
                    if(NodeI->index < NodeJ->index)
                       swap(NodeI, NodeJ);
                }
            }
            NodeJ = NodeJ->next;
        }
        NodeI = NodeI->next;
    }
    return;
}

void ispisiListuNakonSortiranja(Node* head){

    while(head != NULL){
        printf("%s %d %d %d \n", head->smer, head->god, head->index, head->poeni);
        head = head->next;
    }
    printf("\n");
    return;
}

Node* ucitajFajl(Node* head, char imeFajla[]){

    FILE* fp = fopen(imeFajla, "r");

    if(fp == NULL){
        printf("Greska pri ucitavanju");
        fclose(fp);
        return NULL;
    }

    char str[100];
    while(!feof(fp)){
        fgets(str, sizeof(str), fp);
        str[strlen(str)-1] = '\0';
        Node* newNode = createNode(str);
        //printf("%c %s %d %d %s %d \n", newNode->ime, newNode->prezime, newNode->index, newNode->god, newNode->smer, newNode->poeni);
        head = addNode(head, newNode);
    }

    fclose(fp);
    return head;
}

int main(){

    Node* head = NULL;
    int n;

    do{
        printf("%s", opcijeStr);
        scanf("%d", &n);

        if(n == 1){
            char imeFajla[30];
            printf("Unesite ime fajla: ");
            scanf("%s", imeFajla);
            head = ucitajFajl(head, imeFajla);
            ispisiListu(head);
        }
        else if(n == 2){
            int a, b, zbir = 0;
            printf("Unesite raspon indexa: ");
            scanf("%d%d", &a, &b);
            printf("Zbir iterativno: %d \n", brojPoenaStudenataURasponuIter(head, a, b));
            brojPoenaStudenataURasponuRek(head, a, b, &zbir);
            printf("Zbir rekurzivno %d \n", zbir);
            printf("\n");
        }
        else if(n == 3){
            sortirajListu(head);
            ispisiListuNakonSortiranja(head);
        }
        else continue;

    }while(n != 0);

    izbrisiListu(head);
    head = NULL;
    printf("Kraj programa");
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min(int a, int b){
    return (a < b)? a: b;
}

typedef struct{
    int god, mesec, dan;
}Datum;

typedef struct{

    Datum* datum;
    int sat1, sat2, sat3;
    int zag1, zag2, zag3;
    struct Node* next;
}Node;

Datum* kreirajDatum(char* str){

    Datum* noviDatum = (Datum*) malloc(sizeof(Datum));
    char str1[] = {str[0], str[1], str[2], str[3], '\0'};
    char str2[] = {str[4], str[5], '\0'};
    char str3[] = {str[6], str[7], '\0'};

    noviDatum->god = atoi(str1);
    noviDatum->mesec = atoi(str2);
    noviDatum->dan = atoi(str3);
    return noviDatum;
}

Node* addNode(Node* head, Node* newNode){

    if(head == NULL)                                              //ako je lista prazna
        return newNode;

    int minNew = min(newNode->zag1, min(newNode->zag2, newNode->zag3));

    if(minNew < min(head->zag1, min(head->zag2, head->zag3))){                                           //ako treba da stavimo na pocetak
        newNode->next = head;
        return newNode;
    }

    Node* prev = NULL;
    Node* tmp = head;
    while(tmp != NULL && minNew > min(tmp->zag1, min(tmp->zag2, tmp->zag3))){
        prev = tmp;
        tmp = tmp->next;
    }
    newNode->next = tmp;
    prev->next = newNode;
    return head;
}

Node* ucitajFajl(Node* head, char* naziv){

    FILE *fp = fopen(naziv, "r");
    char datum[10];
    int sat1, sat2, sat3;
    int zag1, zag2, zag3;

    if(fp == NULL){
        printf("Greska pri ucitavanju\n");
        fclose(fp);
        return NULL;
    }

    while(!feof(fp)){
        fscanf(fp, "%s%d%d%d%d%d%d", datum, &sat1, &zag1, &sat2, &zag2, &sat3, &zag3);
        Datum* noviDatum = kreirajDatum(datum);
        Node* newNode = (Node*) malloc(sizeof(Node));
        newNode->datum = noviDatum;
        newNode->sat1 = sat1;
        newNode->zag1 = zag1;
        newNode->sat2 = sat2;
        newNode->zag2 = zag2;
        newNode->sat3 = sat3;
        newNode->zag3 = zag3;
        newNode->next = NULL;
        head = addNode(head, newNode);
    }

    fclose(fp);
    return head;
}

void ispisiListu(Node* head){

    while(head!= NULL){
        printf("%d.%d.%d %dh %d %dh %d %dh %d \n", head->datum->dan, head->datum->mesec, head->datum->god, head->sat1, head->zag1, head->sat2, head->zag2, head->sat3, head->zag3);
        head = head->next;
    }
    return;
}

void izbrisiListu(Node* head){

    while(head != NULL){
        Node* tmp = head;
        head = head->next;
        free(tmp);
    }
    return;
}

void zagadjenostNdanaIter(int n, Node* head){

    double zagadjenost = 0;
    while(head != NULL){
        if(head->datum->dan <= n){
            if(head->sat1 == 9)
                    zagadjenost += head->zag1;
            else if(head->sat2 == 9)
                zagadjenost += head->zag2;
            else
                zagadjenost += head->zag3;
        }
        head = head->next;
    }

    printf("Prosecna zagadjenost u prvih %d dana svakog meseca u celoj godini: %lf \n", n, zagadjenost/(n*12));
}

void zagadjenostNdanaRek(int n, Node* head, double* zagadjenost){

    if(head == NULL){
        printf("Prosecna zagadjenost u prvih %d dana svakog meseca u celoj godini: %lf \n", n, *zagadjenost/(n*12));
        return;
    }

    if(head->datum->dan <= n){
        if(head->sat1 == 9)
            *zagadjenost += head->zag1;
        else if(head->sat2 == 9)
            *zagadjenost += head->zag2;
        else
            *zagadjenost += head->zag3;
    }

    zagadjenostNdanaRek(n, head->next, zagadjenost);
}

void sortPoDatumu(Node* head){

    Node* prevI = NULL;
    Node* NodeI = head;

    while(NodeI->next != NULL){
        Node* prevJ = NodeI;
        Node* NodeJ = NodeI->next;
        while(NodeJ != NULL){

            if(NodeI->datum->mesec == NodeJ->datum->mesec && NodeI->datum->dan > NodeJ->datum->dan){
                //swap;
            }

            if(NodeI->datum->mesec > NodeJ->datum->mesec){
                prevI->next = NodeJ;
                prevJ->next = NodeI;
                Node* tmp = NodeI->next;
                NodeI->next = NodeJ->next;
                NodeJ->next = tmp;
            }

            prevJ = NodeJ;
            NodeJ = NodeJ->next;
        }

        prevI = NodeI;
        NodeI = NodeI->next;
    }

    return;
}

void zagadjenostPoMesecima(Node* head){

    for(int god = 2019; god <= 2020; god++){
        for(int i = 0; i <= 12; i++){
            double zag = 0;
            int brDana = 0;
            Node* tmp = head;
            while(tmp!= NULL){
                if(tmp->datum->mesec == i && tmp->datum->god == god){
                    if(tmp->sat1 == 12)
                        zag += tmp->zag1;
                    else if(tmp->sat2 == 12)
                        zag += tmp->zag2;
                    else
                        zag += tmp->zag3;
                    brDana++;
                }
                tmp = tmp->next;
            }
            if(zag != 0)
                printf("%d-%d %lf \n", god, i, zag/brDana);
        }
    }
    return;
}

int main(){

    int n;
    char str[100];
    Node* head = NULL;

    do{
        printf("[0]Prekid programa \n[1]Ucitavanje podataka \n[2]Zagadjenost u prvim danima meseca \n[3]Zagadjenost po mesecima \nOpcija: ");
        scanf("%d", &n);
        fflush(stdin);

        if(n == 1){
            printf("Unesite ime fajla: ");
            fgets(str, sizeof(str), stdin);
            str[strlen(str)-1] = '\0';
            head = ucitajFajl(head, str);
            ispisiListu(head);
            printf("\n");
        }

        if(n == 2){
            printf("Unesite broj dana: ");
            int broj;
            scanf("%d", &broj);
            fflush(stdin);
            zagadjenostNdanaIter(broj, head);
            double zagadjenost = 0;
            zagadjenostNdanaRek(broj, head, &zagadjenost);
        }

        if(n == 3){
            zagadjenostPoMesecima(head);
        }

    }while(n != 0);

    printf("Kraj programa");
    izbrisiListu(head);
    head = NULL;
    return 0;
}

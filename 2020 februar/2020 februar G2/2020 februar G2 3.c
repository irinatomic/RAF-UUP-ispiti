#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b, int c){

    if(a > b && a > c)
        return a;
    if(b > a &&  b > c)
        return b;
    return c;
}

typedef struct{

    int dan;
    int mesec;
    int godina;
}Datum;

typedef struct{

    Datum* datum;
    int sat1, lok1;
    int sat2, lok2;
    int sat3, lok3;
    struct Node* next;

}Node;

Datum* createDatum(char* str){

    Datum* newDatum = (Datum*) malloc(sizeof(Datum));
    char str1[] = {str[0], str[1], str[2], str[3], '\0'};
    char str2[] = {str[4], str[5], '\0'};
    char str3[] = {str[6], str[7], '\0'};

    newDatum->godina = atoi(str1);
    newDatum->mesec = atoi(str2);
    newDatum->dan = atoi(str3);
    return newDatum;
}

Node* addNode(Node* head, Node* newNode){

    if(head == NULL)
        return newNode;

    int newMax = max(newNode->lok1, newNode->lok2, newNode->lok3);

    if(newMax > max(head->lok1, head->lok2, head->lok3)){                   //ako dodajemo na pocetak
        newNode->next = head;
        return newNode;
    }

    Node* prev = NULL;
    Node* tmp = head;
    while(tmp != NULL && newMax < max(tmp->lok1, tmp->lok2, tmp->lok3)){
        prev = tmp;
        tmp = tmp->next;
    }
    newNode->next = tmp;
    prev->next = newNode;
    return head;
}

void ispisiListu(Node* head){

    while(head != NULL){
        printf("%d.%d.%d. %dh %d %dh %d %dh %d \n", head->datum->dan, head->datum->mesec, head->datum->godina, head->sat1, head->lok1, head->sat2, head->lok2, head->sat3, head->lok3);
        head = head->next;
    }
    return;
}

Node* ucitajFajl(Node* head, char* naziv){

    FILE* fp = fopen(naziv, "r");
    char str[100];
    char datum[20];
    int sat1, lok1, sat2, lok2, sat3, lok3;

    if(fp == NULL){
        printf("Greska pri ucitavanju \n");
        fclose(fp);
        return NULL;
    }

    while(!feof(fp)){
        fscanf(fp, "%s%d%d%d%d%d%d", datum, &sat1, &lok1, &sat2, &lok2, &sat3, &lok3);
        Node* newNode = (Node*) malloc(sizeof(Node));
        Datum* newDatum = createDatum(datum);
        newNode->datum = newDatum;
        newNode->sat1 = sat1;
        newNode->lok1 = lok1;
        newNode->sat2 = sat2;
        newNode->lok2 = lok2;
        newNode->sat3 = sat3;
        newNode->lok3 = lok3;
        newNode->next = NULL;
        head = addNode(head, newNode);
    }

    fclose(fp);
    return head;
}

void ispisiMesecIter(Node* head, int mesec, int granica){

    while(head != NULL){
        if(mesec == head->datum->mesec && (head->sat1 == 9 && head->lok1 > granica || head->sat2 == 9 && head->lok2 > granica || head->sat3 == 9 && head->lok3 > granica))
            printf("%d.%d.%d. %dh %d %dh %d %dh %d \n", head->datum->dan, head->datum->mesec, head->datum->godina, head->sat1, head->lok1, head->sat2, head->lok2, head->sat3, head->lok3);

        head = head->next;
    }
    return;
}

void ispisiMesecRek(Node* head, int mesec, int granica){

    if(head == NULL)
        return;

    if(mesec == head->datum->mesec && (head->sat1 == 9 && head->lok1 > granica || head->sat2 == 9 && head->lok2 > granica || head->sat3 == 9 && head->lok3 > granica))
        printf("%d.%d.%d. %dh %d %dh %d %dh %d \n", head->datum->dan, head->datum->mesec, head->datum->godina, head->sat1, head->lok1, head->sat2, head->lok2, head->sat3, head->lok3);

    ispisiMesecRek(head->next, mesec, granica);
}

void sortirajPoDatumu(Node* head){

    Node* NodeI = head;
    while(NodeI->next != NULL){
        Node* NodeJ = NodeI->next;
        while(NodeJ != NULL){

            if(NodeI->datum->mesec == NodeJ->datum->mesec){
                if(NodeI->datum->dan > NodeJ->datum->dan){
                    Datum* tmpDatum = NodeI->datum; NodeI->datum = NodeJ->datum; NodeJ->datum = tmpDatum;                           //nadji funkciju za ovo sr!!!!!
                    int tmpSat1 = NodeI->sat1; NodeI->sat1 = NodeJ->sat1; NodeJ->sat1 = tmpSat1;
                    int tmpLok1 = NodeI->lok1; NodeI->lok1 = NodeJ->lok1; NodeJ->lok1 = tmpLok1;
                    int tmpSat2 = NodeI->sat2; NodeI->sat2 = NodeJ->sat2; NodeJ->sat2 = tmpSat2;
                    int tmpLok2 = NodeI->lok2; NodeI->lok2 = NodeJ->lok2; NodeJ->lok2 = tmpLok2;
                    int tmpSat3 = NodeI->sat3; NodeI->sat3 = NodeJ->sat3; NodeJ->sat3 = tmpSat3;
                    int tmpLok3 = NodeI->lok3; NodeI->lok3 = NodeJ->lok3; NodeJ->lok3 = tmpLok3;
                }
            }

            if(NodeI->datum->mesec > NodeJ->datum->mesec){
                Datum* tmpDatum = NodeI->datum; NodeI->datum = NodeJ->datum; NodeJ->datum = tmpDatum;
                int tmpSat1 = NodeI->sat1; NodeI->sat1 = NodeJ->sat1; NodeJ->sat1 = tmpSat1;
                int tmpLok1 = NodeI->lok1; NodeI->lok1 = NodeJ->lok1; NodeJ->lok1 = tmpLok1;
                int tmpSat2 = NodeI->sat2; NodeI->sat2 = NodeJ->sat2; NodeJ->sat2 = tmpSat2;
                int tmpLok2 = NodeI->lok2; NodeI->lok2 = NodeJ->lok2; NodeJ->lok2 = tmpLok2;
                int tmpSat3 = NodeI->sat3; NodeI->sat3 = NodeJ->sat3; NodeJ->sat3 = tmpSat3;
                int tmpLok3 = NodeI->lok3; NodeI->lok3 = NodeJ->lok3; NodeJ->lok3 = tmpLok3;
            }

            NodeJ = NodeJ->next;
        }
        NodeI = NodeI->next;
    }
}

void ispisi5dana()

int main(){

    int n = 1;
    char naziv[50], str[50];
    Node* head = NULL;

    while(n != 0){
        printf("[0] Kraj programa \n[1] Ucitavanje podataka \n[2]Zagadjenost za mesec \n[3]Zagadjenost za 5 uzastopnih dana \nOpcija: ");
        fgets(str, sizeof(str), stdin);
        str[strlen(str)-1] = '\0';
        n = atoi(str);

        if(n == 1){
            printf("Unesite ime fajla: ");
            fgets(naziv, sizeof(naziv), stdin);
            naziv[strlen(naziv)-1] = '\0';
            head = ucitajFajl(head, naziv);
            ispisiListu(head);
            printf("\n");
        }

        if(n == 2){
            int mesec, granica;
            printf("Unesite mesec i granicu: ");
            fgets(str, sizeof(str), stdin);
            str[strlen(str)-1] = '\0';
            char* token = strtok(str, " \n");
            mesec = atoi(token);
            token = strtok(NULL, " \n");
            granica = atoi(token);

            //ispisiMesecIter(head, mesec, granica);
            ispisiMesecRek(head, mesec, granica);
            printf("\n");
        }

        if(n == 3){
            sortirajPoDatumu(head);
            ispisi5dana(head);
            printf("\n");
        }
    }

    printf("Kraj programa");
    return 0;
}

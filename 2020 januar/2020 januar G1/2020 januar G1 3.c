#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int dan;
    int mesec;
    int godina;
}Datum;

Datum* kreirajDatum(char* str){

    char str1[] = {str[0], str[1], str[2], str[3], '\0'};
    char str2[] = {str[4], str[5], '\0'};
    char str3[] = {str[6], str[7], '\0'};
    Datum* noviDatum = (Datum*) malloc(sizeof(Datum));

    noviDatum->godina = atoi(str1);
    noviDatum->mesec = atoi(str2);
    noviDatum->dan = atoi(str3);
    return noviDatum;
}

typedef struct{
    Datum* datum;
    int sat;
    int lok1;
    int lok2;
    int lok3;
    struct Node* next;
}Node;

Node* addNode(Node* head, Node* newNode){

    if(head == NULL)
        return newNode;

    if(head->next == NULL){
        head->next = newNode;
        return head;
    }

    if(head->datum->dan >= newNode->datum->dan){                        //dodajemo na pocetak
        newNode->next = head;
        return newNode;
    }

    Node* tmp = head;
    Node* prev = NULL;
    while(tmp != NULL && (tmp->datum->dan <= newNode->datum->dan)){
        prev = tmp;
        tmp = tmp->next;
    }

    if(tmp == NULL){
        prev->next = newNode;
        return head;
    }

    else{
        newNode->next = tmp;
        prev->next = newNode;
        return head;
    }
}

void sortirajPoSatima(Node* head){

    while(head->next != NULL){

        Node* tmp = head->next;
        while(tmp != NULL && (head->datum->dan == tmp->datum->dan)){
            if(tmp->sat < head->sat){

                int temp = tmp->sat;
                tmp->sat = head->sat;
                head->sat = temp;

                temp = tmp->lok1;
                tmp->lok1 = head->lok1;
                head->lok1 = temp;

                temp = tmp->lok2;
                tmp->lok2 = head->lok2;
                head->lok2 = temp;

                temp = tmp->lok3;
                tmp->lok3 = head->lok3;
                head->lok3 = temp;
            }
            tmp = tmp->next;
        }
        head = head->next;
    }
    return;
}

void ispisiListu(Node* head){

    while(head != NULL){
        printf("%d.%d.%d %dh %d %d %d \n", head->datum->dan, head->datum->mesec, head->datum->godina, head->sat, head->lok1, head->lok2, head->lok3);
        head = head->next;
    }
    return;
}

Node* ucitajFajl(char* naziv){

    FILE *fp;
    char str[100];
    Node* glava = NULL;

    if(fp = fopen(naziv, "r")){
        while(fgets(str, sizeof(str), fp)){

          Node* newNode = (Node*) malloc(sizeof(Node));
          Datum* newDatum = (Datum*) malloc(sizeof(Datum));

          char* token = strtok(str, " ");
          newDatum = kreirajDatum(token);
          newNode->datum = newDatum;

          token = strtok(NULL, " ");
          newNode->sat = atoi(token);
          token = strtok(NULL, " ");
          newNode->lok1 = atoi(token);
          token = strtok(NULL, " ");
          newNode->lok2 = atoi(token);
          token = strtok(NULL, " \n");
          newNode->lok3 = atoi(token);
          newNode->next = NULL;
          glava = addNode(glava, newNode);
        }
        fclose(fp);
    }
    else{
        printf("Fajl nije uspesno ucitan");
        fclose(fp);
        return NULL;
    }
    return glava;
}

int daniuRasponuIter(Node* head, int a, int b){

    int brojac = 0;
    while(head != NULL){
        if(head->sat == 9){
            float prosek = (head->lok1 + head->lok2 + head->lok3) / 3;
            brojac = (prosek >= a && prosek <= b)? brojac + 1: brojac;
        }
        head = head->next;
    }
    return brojac;
}

int daniuRasponuRek(Node* head, int a, int b, int dani){

    if(head == NULL)
        return dani;

    float prosek = 0;
    if(head->sat == 9)
        prosek = (head->lok1 + head->lok2 + head->lok3) / 3;

    if(prosek >= a && prosek <= b)
        dani++;

    daniuRasponuRek(head->next, a, b, dani);
}

void izbrisiListu(Node* head){

    while(head != NULL){
        Node* tmp = head;
        head = head->next;
        free(tmp);
    }
    return;
}

int main(){

    int n = 1;
    char str[5], naziv[20];
    Node* head = NULL;

    while(n == 1 || n == 2 || n == 3){
        printf("Izaberite:\n [0] Kraj\n [1] Unos podataka\n [2] Broj dana zagadjenosti u rasponu\n [3] Sortiran ispis zagadjenosti po danu\n Opcija: ");
        fgets(str, sizeof(str), stdin);
        str[strlen(str)-1] = '\0';
        n = atoi(str);

        if(n == 1){
            printf("Unesite ime fajla: ");
            fgets(naziv, sizeof(naziv), stdin);
            naziv[strlen(naziv)-1] = '\0';
            head = ucitajFajl(naziv);
            sortirajPoSatima(head);
            ispisiListu(head);
        }

        if(n == 2){
            int a, b;
            printf("Unesite raspon: ");
            scanf("%d %d", &a, &b);
            fflush(stdin);
            printf("Iterativno: %d\n", daniuRasponuIter(head, a, b));
            printf("Rekurzivno: %d\n", daniuRasponuRek(head, a, b, 0));
        }

        if(n == 3){

        }
    }

    izbrisiListu(head);
    head = NULL;
    printf("Zavrsetak programa");
    return 0;
}

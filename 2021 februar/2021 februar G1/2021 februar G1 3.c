#include <stdio.h>
#include <string.h>

char opcijeStr[] = "[0]Kraj programa \n[1]Ucitavanje podataka \n[2]Redni broj na trci za igraca \n[3]Generisanje ukupnih rezultata \nOpcija: ";

typedef struct{

    int trka;
    char trkac;
    float vreme;
    struct Node* next;

}Node;

typedef struct{

    char trkac;
    int brPoena;
    struct Node2* next;

}Node2;

int redniBrojTrkacaNaTrciIter(Node* head, int trka, char trkac){

    int brojac = 0;
    while(head != NULL){
        if(head->trka == trka){
            brojac++;
            if(head->trkac == trkac)
                return brojac;
        }
        head = head->next;
    }
    return NULL;
}

int redniBrojTrkacaNaTrciRek(Node* head, int trka, char trkac, int* brojac){

    if(head == NULL)
        return NULL;

    if(head->trka == trka){
        (*brojac)++;
        if(head->trkac == trkac)
            return *brojac;
    }

    redniBrojTrkacaNaTrciRek(head->next, trka, trkac, brojac);
}

Node2* createNode2(Node* head, Node* headCopy){

    Node2* newNode2 = (Node2*) malloc(sizeof(Node2));
    newNode2->trkac = head->trkac;
    newNode2->brPoena = 0;
    newNode2->next = NULL;

    while(head != NULL){
        if(head->trkac == newNode2->trkac){
            int poeni = 20 - redniBrojTrkacaNaTrciIter(headCopy, head->trka, newNode2->trkac);
            newNode2->brPoena += poeni;
        }
        head = head->next;
    }
    return newNode2;
}

Node2* addNode2(Node2* head2, Node2* newNode2){

    if(head2 == NULL)
        return newNode2;

    if(newNode2->brPoena < head2->brPoena){
        newNode2->next = head2;
        return newNode2;
    }

    Node2* prev2 = NULL;
    Node2* tmp2 = head2;
    while(tmp2 && newNode2->brPoena > tmp2->brPoena){
        prev2 = tmp2;
        tmp2 = tmp2->next;
    }

    if(tmp2 == NULL){
        prev2->next = newNode2;
        return head2;
    }

    newNode2->next = tmp2;
    prev2->next = newNode2;
    return head2;
}

void ispisiDruguListu(Node2* head){

    while(head){
        printf("%c %d \n", head->trkac, head->brPoena);
        head = head->next;
    }
    printf("\n");
    return;
}

Node2* popuniDruguStrukturu(Node* head2, Node* head, Node* headCopy){

    int broj = head->trka;
    Node* NodeI = head;

    while(NodeI->trka == broj){
        Node2* newNode2 = createNode2(NodeI, head);
        head2 = addNode2(head2, newNode2);
        NodeI = NodeI->next;
    }
    return head2;
}

Node* createNode(char str[]){

    Node* newNode = (Node*) malloc(sizeof(Node));

    char * token = strtok(str, " ");
    int broj = atoi(token);
    token = strtok(NULL, " ");
    char trkac = token[0];
    token = strtok(NULL, " ");

    int vreme = 0;
    for(int i = 0; i < strlen(token); i++){
        if(token[i] != '.' && token[i] != '\n')
            vreme = vreme*10 + (token[i] - '0');
    }

    newNode->trka = broj;
    newNode->trkac = trkac;
    newNode->vreme = (float)vreme/100;
    newNode->next = NULL;
    return newNode;
}

Node* addNode(Node* head, Node* newNode){

    if(head == NULL)
        return newNode;

    if(newNode->trka < head->trka || (newNode->trka == head->trka && newNode->vreme > head->vreme)){        //ako dodajemo na pocetak
        newNode->next = head;
        return newNode;
    }

    Node* prev = NULL;
    Node* tmp = head;
    while(tmp && newNode->trka > tmp->trka){
        prev = tmp;
        tmp = tmp->next;
    }

    while(tmp && newNode->trka == tmp->trka && newNode->vreme < tmp->vreme){
        prev = tmp;
        tmp = tmp->next;
    }

    if(tmp == NULL){                                                                //ako smo na kraju liste
        prev->next = newNode;
        return head;
    }

    newNode->next = tmp;
    prev->next = newNode;
    return head;
}

void ispisiListu(Node* head){

    while(head){
        printf("%d %c %.2f \n", head->trka, head->trkac, head->vreme);
        head = head->next;
    }
    printf("\n");
    return;
}

void izbrisiListu(Node* head){

    while(head){
        Node* tmp = head;
        head = head->next;
        free(tmp);
    }
    return;
}

Node* ucitajFajl(Node* head, char fileName[]){

    FILE* fp = fopen(fileName, "r");

    if(fp == NULL){
        printf("Greska pri ucitavanju fajla \n");
        fclose(fp);
        return NULL;
    }

    char fileLine[50];
    while(!feof(fp)){
        fgets(fileLine, sizeof(fileLine), fp);
        fileLine[strlen(fileLine)] = '\0';
        Node* newNode = createNode(fileLine);
        head = addNode(head, newNode);
        //printf("%d %c %f \n", newNode->trka, newNode->trkac, newNode->vreme);

    }
    fclose(fp);
    return head;
}

int main(){

    Node* head = NULL;
    Node2* head2 = NULL;
    int n;

    do{
        printf("%s", opcijeStr);
        scanf("%d", &n);
        if(n == 1){
            char fileName[] = "trke.txt";
            head = ucitajFajl(head, fileName);
            ispisiListu(head);
        }
        else if(n == 2){
            int trka;
            char trkac;
            printf("Unesite redni broj trke: ");
            scanf("%d", &trka);
            fflush(stdin);
            printf("Unesite trkaca: ");
            scanf("%c", &trkac);
            fflush(stdin);                                                                                  //ovde pamti vrednosti i vrti petlju beskonacno puta tkd moram fflush
            int redniBroj = 0;
            printf("iterativno %d \n", redniBrojTrkacaNaTrciIter(head, trka, trkac));
            printf("rekurzivno %d \n", redniBrojTrkacaNaTrciRek(head, trka, trkac, &redniBroj));
        }
        else if(n == 3){
            head2 = popuniDruguStrukturu(head2, head, head);
            ispisiDruguListu(head2);
        }
        else continue;

    }while(n != 0);

    izbrisiListu(head);
    head = NULL;
    printf("Kraj programa");
    return 0;
}

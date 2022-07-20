#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char opcijeStr[] = "[0]Kraj programa \n[1]Ucitavanje podataka \n[2]Broj rodjenih beba u godini \n[3]Ispis rodjenih beba sortirano \nOpcija: ";

typedef struct{
    int dan;
    int mesec;
    int god;
    int broj;
    struct Node* next;

}Node;

Node* addNode(Node* head, Node* newNode){

    if(head == NULL)                                        //u slucaju da je lista prazna
        return newNode;

    if(newNode->broj >= head->broj){
        newNode->next = head;
        return newNode;
    }

    Node* prev = NULL;
    Node* tmp = head;
    while(tmp != NULL && newNode->broj < tmp->broj){
        prev = tmp;
        tmp = tmp->next;
    }
    prev->next = newNode;
    newNode->next = tmp;
    return head;
}

void ispisiListu(Node* head){

    while(head != NULL){
        printf("%d.%d.%d %d \n", head->dan, head->mesec, head->god, head->broj);
        head = head->next;
    }
    return;
}

int brojBebaUGodiniIter(Node* head, int n){

    int brBeba = 0;
    while(head != NULL){
        brBeba = (head->god == n)? brBeba + head->broj: brBeba;
        head = head->next;
    }
    return brBeba;
}

int brojBebaUGodiniRek(Node* head, int n, int brBeba){

    if(head == NULL)
        return brBeba;

    if(head->god == n)
        return brojBebaUGodiniRek(head->next, n, brBeba + head->broj);
    return brojBebaUGodiniRek(head->next, n, brBeba);
}

void swapNodes(Node* Node1, Node* Node2){

    int tmp = Node1->broj;
    Node1->broj = Node2->broj;
    Node2->broj = tmp;

    tmp = Node1->dan;
    Node1->dan = Node2->dan;
    Node2->dan = tmp;

    tmp = Node1->mesec;
    Node1->mesec = Node2->mesec;
    Node2->mesec = tmp;

    tmp = Node1->god;
    Node1->god = Node2->god;
    Node2->god = tmp;
}

Node* napraviKopijuListe(Node* head){

    Node* newHead = head;
    Node* prev = newHead;
    head = head->next;
    while(head != NULL){
        Node* newNode = head;
        prev->next = newNode;
        prev = newNode;
        head = head->next;
    }
    return newHead;
}

void soritrajListuRastuceAndIspisiPoMesecu(Node* head){

    Node* newHead = napraviKopijuListe(head);
    Node* NodeI = newHead;
    while(NodeI->next != NULL){
        Node* NodeJ = NodeI->next;
        while(NodeJ != NULL){

            if(NodeI->god > NodeJ->god)
                swapNodes(NodeI, NodeJ);

            else if(NodeI->god == NodeJ->god && NodeI->mesec > NodeJ->mesec)
                swapNodes(NodeI, NodeJ);

            NodeJ = NodeJ->next;
        }
        NodeI = NodeI->next;
    }

    int brBeba = 0;
    int prosliMesec = newHead->mesec;
    int proslaGod = newHead->god;

    while(newHead != NULL){
        if(newHead->mesec == prosliMesec)
            brBeba += newHead->broj;
        else{
            printf("%d %d %d \n", proslaGod, prosliMesec, brBeba);
            prosliMesec = newHead->mesec;
            proslaGod = newHead->god;
            brBeba = newHead->broj;
        }
        newHead = newHead->next;
    }
    printf("%d %d %d \n", proslaGod, prosliMesec, brBeba);
    izbrisiListu(newHead);
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

Node* ucitajFajl(Node* head, char* imeFajla){

    FILE* fp = fopen(imeFajla, "r");

    if(fp == NULL){
        printf("Greska pri ucitavanju \n");
        fclose(fp);
        return NULL;
    }

    int dan, mesec, god, broj;
    while(!feof(fp)){
        fscanf(fp, "%d%d%d%d", &dan, &mesec, &god, &broj);
        Node* newNode = (Node*) malloc(sizeof(Node));
        newNode->dan = dan;
        newNode->mesec = mesec;
        newNode->god = god;
        newNode->broj = broj;
        newNode->next = NULL;
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
        fflush(stdin);

        if(n == 1){
            printf("Unesite ime fajla: ");
            char imeFajla[50];
            scanf("%s", imeFajla);
            head = ucitajFajl(head, imeFajla);
            ispisiListu(head);
            printf("\n");
        }

        if(n == 2){
            printf("Unesite godinu: ");
            int godina;
            scanf("%d", &godina);
            printf("iterativno: %d \n", brojBebaUGodiniIter(head, godina));
            printf("rekurzivno: %d \n", brojBebaUGodiniRek(head, godina, 0));
            printf("\n");
        }

        if(n == 3){
            soritrajListuRastuceAndIspisiPoMesecu(head);
            printf("\n");
        }

    }while(n != 0);

    printf("Kraj programa");
    izbrisiListu(head);
    head = NULL;
    return 0;
}

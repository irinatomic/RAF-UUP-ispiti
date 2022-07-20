#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char opcijeStr[] = "[0]Kraj programa \n[1]Ucitavanje podataka \n[2]Broj meseci u kojima je rodjeno vise od n dece \n[3]Ispis po godini sortiran po uk broju rodjenih \nOpcija: ";

typedef struct{

    int mesec;
    int god;
    int mus;
    int zen;
    struct Node* next;

}Node;

typedef struct{

    int godina;
    int brBeba;
    int mus, zen;

}brBebaPoGod;

Node* addNode(Node* head, Node* newNode){

    if(head == NULL)                                //ako je lista prazna
        return newNode;

    if(newNode->god > head->god || (newNode->god == head->god && newNode->mesec > head->mesec)){           //ako dodajemo na pocetak
        newNode->next = head;
        return newNode;
    }

    Node* prev = NULL;
    Node* tmp = head;
    while(tmp != NULL && newNode->god < tmp->god){
        prev = tmp;
        tmp = tmp->next;
    }

    if(tmp == NULL){                    //ako dodajemo na kraj liste
        prev->next = newNode;
        return head;
    }

    if(newNode->god == tmp->god){
        while(tmp != NULL && newNode->god == tmp->god && newNode->mesec < tmp->mesec){
            prev = tmp;
            tmp = tmp->next;
        }
        prev->next = newNode;
        newNode->next = tmp;
        return head;
    }

    prev->next = newNode;
    newNode->next = tmp;
    return head;
}

void ispisiListu(Node* head){

    while(head != NULL){
        printf("%d %d %d %d \n", head->mesec, head->god, head->mus, head->zen);
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

int brMeseciViseOdXDeceIter(Node* head, int granica){

    int brojac = 0;
    while(head != NULL){
        brojac = (head->mus + head->zen > granica)? brojac+1: brojac;
        head = head->next;
    }
    return brojac;
}

int brMeseciViseOdXDeceRek(Node* head, int granica, int brojac){

    if(head == NULL)
        return brojac;

    if(head->mus + head->zen > granica)
        return brMeseciViseOdXDeceRek(head->next, granica, brojac+1);
    return brMeseciViseOdXDeceRek(head->next, granica, brojac);
}

void swapNiz(brBebaPoGod* X, brBebaPoGod* Y){

    int tmp = X->brBeba;
    X->brBeba = Y->brBeba;
    Y->brBeba = tmp;

    tmp = X->mus;
    X->mus = Y->mus;
    Y->mus = tmp;

    tmp = X->zen;
    X->zen = Y->zen;
    Y->zen = tmp;

    tmp = X->godina;
    X->godina = Y->godina;
    Y->godina = tmp;

    return;
}

void ispisSoritranoPoBrBeba(Node* head){

    brBebaPoGod niz[30];
    int nizIndex = 0;
    niz[nizIndex].godina = head->god;
    niz[nizIndex].mus = 0, niz[nizIndex].zen = 0, niz[nizIndex].brBeba = 0;

    while(head != NULL){                                                        //ovo mozemo jer je lista sortirana po god pa mesecu (nerastuce)
        if(head->god != niz[nizIndex].godina){
            nizIndex++;
            niz[nizIndex].godina = head->god;
            niz[nizIndex].mus = 0, niz[nizIndex].zen = 0, niz[nizIndex].brBeba = 0;
        }

        niz[nizIndex].brBeba += head->mus + head->zen;
        niz[nizIndex].mus += head->mus;
        niz[nizIndex].zen += head->zen;
        head = head->next;
    }

    for(int i = 0; i < nizIndex; i++){              //soritramo niz opadajuce po brBeba
        for(int j = i+1; j <= nizIndex; j++){
            if(niz[i].brBeba < niz[j].brBeba){
                swapNiz(&niz[i], &niz[j]);
            }
        }
    }

    for(int i = 0; i <= nizIndex; i++)                                              //ispisujemo niz
        printf("%d %d %d\n", niz[i].godina, niz[i].mus, niz[i].zen);

    return;
}

Node* ucitajFajl(Node* head, char* imeFajla){

    FILE* fp = fopen(imeFajla, "r");

    if(fp == NULL){
        printf("Greska pri ucitavanju \n");
        fclose(fp);
        return NULL;
    }

    int mesec, god, mus, zen;
    while(!feof(fp)){
        fscanf(fp, "%d%d%d%d", &mesec, &god, &mus, &zen);
        Node* newNode = (Node*) malloc(sizeof(Node));
        newNode->mesec = mesec;
        newNode->god = god;
        newNode->mus = mus;
        newNode->zen = zen;
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
        if(n == 1){
            printf("Unesite ime fajla: ");
            char imeFajla[50];
            scanf("%s", imeFajla);
            head = ucitajFajl(head, imeFajla);
            ispisiListu(head);
        }
        else if(n == 2){
            printf("Unesite broj dece: ");
            int x;
            scanf("%d", &x);
            printf("iterativno %d \n", brMeseciViseOdXDeceIter(head, x));
            printf("rekurzivno %d \n", brMeseciViseOdXDeceRek(head, x, 0));
        }
        else if(n == 3){
            ispisSoritranoPoBrBeba(head);
        }

    }while(n != 0);

    printf("Kraj programa");
    izbrisiListu(head);
    head = NULL;
    return 0;
}

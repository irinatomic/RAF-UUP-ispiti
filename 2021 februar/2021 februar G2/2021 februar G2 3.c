#include <stdio.h>
#include <string.h>
#include <math.h>

char opcijeStr[] = "[0]Prekid programa \n[1]Ucitavanje podataka \n[2]Broj golova odredjenog tima \n[3]Obracun poena i generisanje tabele \nOpcija: ";

typedef struct{

    int god, mesec, dan;
    char tim1, tim2;
    int gol1, gol2;
    struct Node* next;

}Node;

typedef struct{

    char tim;
    int bodovi, datiGol, primljenGol;
    struct Node2* next;

}Node2;

int brojGolovaTimaIter(Node* head, char tim){

    int brojac = 0;
    while(head){
        if(head->tim1 == tim)
            brojac += head->gol1;
        else if(head->tim2 == tim)
            brojac += head->gol2;

        head = head->next;
    }
    return brojac;
}

int brojGolovaTimaRek(Node* head, char tim, int* brojac){

    if(head == NULL)
        return *brojac;

    if(head->tim1 == tim)
        *brojac += head->gol1;
    else if(head->tim2 == tim)
        *brojac += head->gol2;

    brojGolovaTimaRek(head->next, tim, brojac);
}

Node2* createNode2(Node* head, char tim){

    Node* headCopy = head;
    while(headCopy){                                                        //prvo cemo da proverimo postoji li uopste taj tim
        if(headCopy->tim1 == tim || headCopy->tim2 == tim)
            break;
        headCopy = headCopy->next;
    }

    if(headCopy == NULL)                                                    //ako tim ne postoji stigli smo do kraja liste i vraticemo NULL
        return NULL;

    Node2* newNode2 = (Node2*) malloc(sizeof(Node2));
    newNode2->tim = tim;
    newNode2->bodovi = 0;
    newNode2->datiGol = 0;
    newNode2->primljenGol = 0;
    while(head){
        if(head->tim1 == tim){
            if(head->gol1 > head->gol2)
                newNode2->bodovi += 3;
            else if(head->gol1 == head->gol2)
                newNode2->bodovi += 1;
            else
                newNode2->bodovi += 0;

            newNode2->primljenGol += head->gol2;
            newNode2->datiGol += head->gol1;
        }

        else if(head->tim2 == tim){
            if(head->gol2 > head->gol1)
                newNode2->bodovi += 3;
            else if(head->gol2 == head->gol1)
                newNode2->bodovi += 1;
            else
                newNode2->bodovi += 0;

            newNode2->primljenGol += head->gol1;
            newNode2->datiGol += head->gol2;
        }
        head = head->next;
    }
    newNode2->next = NULL;
    return newNode2;
}

Node2* addNode2(Node2* head2, Node2* newNode2){

    if(head2 == NULL)
        return newNode2;

    int razlikaNew = abs(newNode2->primljenGol - newNode2->datiGol);

    if(newNode2->bodovi > head2->bodovi || (newNode2->bodovi == head2->bodovi && razlikaNew > abs(head2->primljenGol - head2->datiGol))){
        newNode2->next = head2;
        return newNode2;
    }

    Node2* prev = NULL;
    Node2* tmp = head2;
    while(tmp && newNode2->bodovi < tmp->bodovi){
        prev = tmp;
        tmp = tmp->next;
    }

    while(tmp && newNode2->bodovi == tmp->bodovi && razlikaNew < abs(tmp->datiGol - tmp->primljenGol)){
        prev = tmp;
        tmp = tmp->next;
    }

    if(tmp == NULL){
        prev->next = newNode2;
        return head2;
    }

    newNode2->next = tmp;
    prev->next = newNode2;
    return head2;
}

void ispisiListu2(Node2* head2){

    while(head2){
        printf("%c %d %d %d \n", head2->tim, head2->bodovi, head2->datiGol, head2->primljenGol);
        head2 = head2->next;
    }
    printf("\n");
    return;
}

Node2* createList2(Node* head, Node2* head2){

    char tim = 'a';
    for(tim; tim != 'z'; tim++){
        Node2* newNode2 = createNode2(head, tim);
        if(newNode2 != NULL)
            head2 = addNode2(head2, newNode2);
    }
    return head2;
}

Node* createNode(char str[]){

    Node* newNode = (Node*) malloc(sizeof(Node));

    char* token = strtok(str, " ");
    int god = 0;
    int i = 0;
    for(i; token[i] != '-'; i++)
        god = god*10 + (token[i] - '0');

    i++;
    int mesec = 0;
    for(i; token[i] != '-'; i++)
        mesec = mesec*10 + (token[i] - '0');

    i++;
    int dan = 0;
    for(i; token[i] != '\0'; i++)
        dan = dan*10 + (token[i] - '0');

    newNode->god = god;
    newNode->mesec = mesec;
    newNode->dan = dan;

    token = strtok(NULL, " ");
    newNode->tim1 = token[0];
    token = strtok(NULL, " ");
    newNode->tim2 = token[0];
    token = strtok(NULL, " ");
    newNode->gol1 = atoi(token);
    token = strtok(NULL, " ");
    newNode->gol2 = atoi(token);
    newNode->next = NULL;
    return newNode;
}

Node* addNode(Node* head, Node* newNode){

    if(head == NULL)
        return newNode;

    if(newNode->mesec < head->mesec || (newNode->mesec == head->mesec && newNode->dan < head->dan)){        //ako dodajemo na pocetak
        newNode->next = head;
        return newNode;
    }

    Node* prev = NULL;
    Node* tmp = head;
    while(tmp && newNode->mesec > tmp->mesec){
        prev = tmp;
        tmp = tmp->next;
    }

    while(tmp && newNode->mesec == tmp->mesec && newNode->dan > tmp->dan){
        prev = tmp;
        tmp = tmp->next;
    }

    if(tmp == NULL){                                                                    //ako smo na kraju liste
        prev->next = newNode;
        return head;
    }

    newNode->next = tmp;
    prev->next = newNode;
    return head;
}

void ispisiListu(Node* head){

    Node* tmp = head;
    while(tmp){
        printf("%d %d %d %c %c %d %d \n", tmp->god, tmp->mesec, tmp->dan, tmp->tim1, tmp->tim2, tmp->gol1, tmp->gol2);
        tmp = tmp->next;
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
        printf("Greska pri ucitavanju \n");
        fclose(fp);
        return NULL;
    }

    char fileLine[100];
    while(!feof(fp)){
        fgets(fileLine, sizeof(fileLine), fp);
        fileLine[strlen(fileLine)] = '\0';
        Node* newNode = createNode(fileLine);
        //printf("%d %d %d %c %c %d %d \n", tmp->god, tmp->mesec, tmp->dan, tmp->tim1, tmp->tim2, tmp->gol1, tmp->gol2);
        head = addNode(head, newNode);
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
        fflush(stdin);
        if(n == 1){
            char fileName[] = "utakmice.txt";
            head = ucitajFajl(head, fileName);
            ispisiListu(head);
        }
        else if(n == 2){
            char tim;
            printf("Unesite oznaku tima: ");
            scanf("%c", &tim);
            fflush(stdin);
            int brGolova = 0;
            printf("iterativno: %d \n", brojGolovaTimaIter(head, tim));
            printf("rekurzivno: %d \n", brojGolovaTimaRek(head, tim, &brGolova));
        }
        else if(n == 3){
            head2 = createList2(head, head2);
            ispisiListu2(head2);
        }

    }while(n != 0);

    izbrisiListu(head);
    izbrisiListu(head2);
    head = NULL;
    head2 = NULL;
    printf("Kraj programa \n");
    return 0;
}

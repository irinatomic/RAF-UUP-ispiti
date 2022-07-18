#include <stdio.h>
#include <string.h>
#include <math.h>

char opcijeStr[] = "[0]Kraj programa + snimanje u fajl \n[1]Ucitavanje podataka \n[2]Regioni sa vecom razlikom \n[3]Dodavanje osobe po diplomiranju \nOpcija: ";

typedef struct{

    int region, muskiU, zenskiU, muskiD, zenskiD;
    char studije[5];
    char status;
    struct Node* next;

}Node;

Node* addNode(Node* head, Node* newNode){

    if(head == NULL)
        return newNode;

    int nadjeno = 0;                                        //proveravano da li je vec upisano za taj region i smer
    Node* headCopy = head;
    while(headCopy){
        if(strcmp(headCopy->studije, newNode->studije) == 0 && headCopy->region == newNode->region){
            nadjeno = 1;
            break;
        }
        headCopy = headCopy->next;
    }

    Node* prev = NULL;
    Node* tmp = head;

    if(nadjeno){
        while(tmp){
            if(strcmp(tmp->studije, newNode->studije) == 0 && tmp->region == newNode->region){
                if(tmp->status == 'u'){
                    tmp->muskiD = newNode->muskiD;
                    tmp->zenskiD = newNode->zenskiD;
                } else{
                    tmp->muskiU = newNode->muskiU;
                    tmp->zenskiU = newNode->zenskiU;
                }
                free(newNode);
                return head;
            }
            tmp = tmp->next;
        }
    }

    else{
        if(strcmp(newNode->studije, head->studije) < 0 || (strcmp(newNode->studije, head->studije) == 0 && (newNode->muskiU + newNode->zenskiU) < (head->muskiU + head->zenskiU))){         //ako
            newNode->next = head;                                                                                                                                                           //dodajemo na pocetak
            return newNode;
        }
        while(tmp && strcmp(newNode->studije, tmp->studije) > 0){
            prev = tmp;
            tmp = tmp->next;
        }
        while(tmp && strcmp(newNode->studije, tmp->studije) == 0 && (newNode->muskiU + newNode->zenskiU) > (tmp->muskiU + tmp->zenskiU)){
            prev = tmp;
            tmp = tmp->next;
        }
        if(tmp == NULL){                        //ako dodajemo na kraj
            prev->next = newNode;
            return head;
        }
        newNode->next = tmp;
        prev->next = newNode;
        return head;
    }
}

void regioniSaVecomRazlikom(Node* head, char studije[], int granica){

    while(head != NULL){
        if(strcmp(head->studije, studije) == 0 && abs((head->muskiD + head->zenskiD) - (head->muskiU + head->zenskiU)) > granica)
            printf("%d \n", head->region);
        head = head->next;
    }
    return;
}

void dodajOsobuPosleDiplomiranja(Node* head, int region, char pol, char studije[]){

    while(head){
        if(strcmp(head->studije, studije) == 0 && head->region == region){
            if(pol == 'm')
                head->muskiD += 1;
            else
                head->zenskiD += 1;
        }
        head = head->next;
    }
    return;
}

void ispisiListu(Node* head){

    while(head){
        printf("%s %d MU %d ZU %d MD %d ZD %d \n", head->studije, head->region, head->muskiU, head->zenskiU, head->muskiD, head->zenskiD);
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

void ispisiListuUFajl(Node* head){

    FILE* fpO = fopen("ispis.txt", "w");
    while(head){
        fprintf(fpO, "%s %d MU %d ZU %d MD %d ZD %d \n", head->studije, head->region, head->muskiU, head->zenskiU, head->muskiD, head->zenskiD);
        head = head->next;
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

    char str[100];
    while(fgets(str, sizeof(str), fp)){
        //str[strlen(str)-1] = '\0';

        Node* newNode = (Node*) malloc(sizeof(Node));
        char status = str[strlen(str)-2];
        char* token = strtok(str, " ");
        newNode->region = atoi(token);
        if(status == 'u'){
            token = strtok(NULL, " ");
            newNode->muskiU = atoi(token);
            token = strtok(NULL, " ");
            newNode->zenskiU = atoi(token);
        } else{
            token = strtok(NULL, " ");
            newNode->muskiD = atoi(token);
            token = strtok(NULL, " ");
            newNode->zenskiD = atoi(token);
        }
        token = strtok(NULL, " ");
        strcpy(newNode->studije, token);
        newNode->status = status;
        newNode->next = NULL;
        head = addNode(head, newNode);
    }
    fclose(fp);
    return head;
}

int main(){

    int n;
    Node* head = NULL;

    do{
        printf("%s", opcijeStr);
        scanf("%d", &n);
        fflush(stdin);
        if(n == 1){
            char fileName[] = "brojStudenata.txt";
            head = ucitajFajl(head, fileName);
            ispisiListu(head);
        }
        else if(n == 2){
            printf("Unesite vrstu studija: ");
            char studije[5];    scanf("%s", studije);   fflush(stdin);
            printf("Unesite broj: ");
            int granica;    scanf("%d", &granica);   fflush(stdin);
            regioniSaVecomRazlikom(head, studije, granica);
        }
        else if(n == 3){
            int region;
            char polStr[1], studije[3];
            printf("Pol: ");
            scanf("%s", polStr);
            char pol = polStr[0];
            printf("Region: ");
            scanf("%d", &region);
            printf("Studije: ");
            scanf("%s", studije);
            dodajOsobuPosleDiplomiranja(head, region, pol, studije);
            //ispisiListu(head);
        }
        else continue;
    }while(n != 0);

    ispisiListuUFajl(head);
    izbrisiListu(head);
    head = NULL;
    printf("Kraj programa \n");
    return 0;
}

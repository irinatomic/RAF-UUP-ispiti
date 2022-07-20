#include <stdio.h>
#include <string.h>

//NIJE URADJENO SINONIMI ITER

char opcijeStr[] = "[0]Kraj programa \n[1]Ucitavanje sinonima \n[2]Ispis sinonima jedne reci \n[3]Rec sa najvise sinonima \nOpcija: ";

typedef struct{

    char prvaRec[30];
    char drugaRec[30];
    struct Node* left;
    struct Node* right;

}Node;

Node* createNode(char str[]){

    int koord = strchr(str, '-') - str;
    char prvaRec[30], drugaRec[30];

    int j = 0;
    for(int i = 0; i < koord; i++)
        prvaRec[j++] = str[i];
    prvaRec[j] = '\0';

    j = 0;
    for(int i = koord+1; i < strlen(str); i++)
        drugaRec[j++] = str[i];
    drugaRec[j] = '\0';

    Node* newNode = (Node*) malloc(sizeof(Node));
    strcpy(newNode->prvaRec, prvaRec);
    strcpy(newNode->drugaRec, drugaRec);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* addNodeRek(Node* root, Node* newNode){

    if(root == NULL)
        return newNode;

    if(strcmp(newNode->prvaRec, root->prvaRec) <= 0)
        root->left = addNodeRek(root->left, newNode);
    else
        root->right = addNodeRek(root->right, newNode);
    return root;
}

Node* addNodeIter(Node* root, Node* newNode){

    if(root == NULL)
        return newNode;

    Node* tmp = root;
    while(1){
        if(strcmp(newNode->prvaRec, tmp->prvaRec) <= 0){
            if(tmp->left == NULL){
                tmp->left = newNode;
                return root;
            }
            tmp = tmp->left;
        } else{
            if(tmp->right == NULL){
                tmp->right = newNode;
                return root;
            }
            tmp = tmp->right;
        }
    }
}

void ispisiStablo(Node* root){

    if(root == NULL)
        return;

    ispisiStablo(root->left);
    printf("%s %s \n", root->prvaRec, root->drugaRec);
    ispisiStablo(root->right);
    return;
}

void sinonimiRek(Node* root, char rec[]){

    if(root == NULL)
        return;

    sinonimiRek(root->left, rec);
    if(!strcmp(rec, root->prvaRec))
        printf("%s ", root->drugaRec);
    else if(!strcmp(rec, root->drugaRec))
        printf("%s ", root->prvaRec);
    sinonimiRek(root->right, rec);
    return;
}

void sinonimiIter(Node* root, char rec[]){

    Node* rootCopy = root;
    while(1){                                            //pretrazujemo prvu rec
        if(root == NULL)
            break;
        if(!strcmp(rec, root->prvaRec))
            printf("%s ", root->drugaRec);
        if(!strcmp(rec, rootCopy->drugaRec))
            printf("%s ", rootCopy->prvaRec);

        if(strcmp(rec, root->prvaRec) <= 0)
            root = root->left;
        else
            root = root->right;
    }

    while(1){                                           //pretrazujemo drugu rec
        if(rootCopy == NULL)
            break;
        if(!strcmp(rec, rootCopy->drugaRec))
            printf("%s ", rootCopy->prvaRec);

        if(strcmp(rec, rootCopy->drugaRec) <= 0)
            rootCopy = rootCopy->left;
        else
            rootCopy = rootCopy->right;
    }
    return;
}

Node* ucitajFajl(Node* root, char imeFajla[]){

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
        Node* newNode = createNode(linijaFajla);
        //root = addNodeRek(root, newNode);
        root = addNodeIter(root, newNode);
    }

    fclose(fp);
    return root;
}

void brojPonavljanjaReci(Node* root, char rec[], int* brojac){

    if(root == NULL)
        return;

    if(!strcmp(root->prvaRec, rec) || !strcmp(root->drugaRec, rec))
        (*brojac)++;

    brojPonavljanjaReci(root->left, rec, brojac);
    brojPonavljanjaReci(root->right, rec, brojac);
    return;
}

void recSaNajviseSinonima(Node* root, Node* rootCopy, char rec[], int* maxPon){

    if(root == NULL)
        return;

    int brojac = 0;                                                     //za svaki Node proveravamo brPonavljanja prve i druge reci u celom stablu
    brojPonavljanjaReci(rootCopy, root->prvaRec, &brojac);
    if(brojac > *maxPon){
        *maxPon = brojac;
        strcpy(rec, root->prvaRec);
    }
    brojac = 0;
    brojPonavljanjaReci(rootCopy, root->drugaRec, &brojac);
    if(brojac > *maxPon){
        *maxPon = brojac;
        strcpy(rec, root->drugaRec);
    }

    recSaNajviseSinonima(root->left, rootCopy, rec, maxPon);
    recSaNajviseSinonima(root->right, rootCopy, rec, maxPon);
    return;
}

void izbrisiStablo(Node* root){

    if(root == NULL){
        return;
    }

    izbrisiStablo(root->left);
    izbrisiStablo(root->right);
    free(root);
}

int main(){

    Node* root = NULL;
    int n;
    do{
        printf("%s", opcijeStr);
        scanf("%d", &n);

        if(n == 1){
            char imeFajla[30];
            printf("Unesite ime fajla: ");
            scanf("%s", imeFajla);
            root = ucitajFajl(root, imeFajla);
            ispisiStablo(root);
        }
        else if(n == 2){
            char rec[30];
            printf("Unesite rec: ");
            scanf("%s ", rec);
            sinonimiRek(root, rec);
            //sinonimiIter(root, rec);
            printf("\n");
        }
        else if(n == 3){
            char rec[30];
            int maxPon = 0;
            recSaNajviseSinonima(root, root, rec, &maxPon);
            printf("%s %d \n", rec, maxPon);
        }
        else continue;

    }while(n != 0);

    izbrisiStablo(root);
    root = NULL;
    printf("Kraj programa");
    return 0;
}

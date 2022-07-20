#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char opcijeStr[] = "[0]Kraj programa \n[1]Ucitavanje podataka \n[2]Ispis stabla \n[3]Najveca razlika \n[4]Prosecna temp za jutarnju \nOpcija: ";

typedef struct{

    char grad[30];
    int jutroT;
    int danT;
    struct Node* left;
    struct Node* right;

}Node;

Node* addNodeIter(Node* root, Node* newNode){

    if(root == NULL)
        return newNode;

    Node* rootCopy = root;
    while(1){
        if(strcmp(newNode->grad, root->grad) < 0){
            if(root->left == NULL){
                root->left = newNode;
                return rootCopy;
            }
            root = root->left;
        }
        else{
            if(root->right == NULL){
                root->right = newNode;
                return rootCopy;
            }
            root = root->right;
        }
    }
}

Node* addNodeRek(Node* root, Node* newNode){

    if(root == NULL)
        return newNode;

    if(strcmp(newNode->grad, root->grad) < 0)
        root->left = addNodeRek(root->left, newNode);
    else
        root->right = addNodeRek(root->right, newNode);

    return root;                                                //mozemo samo root (ne rootCopy) jer svaki rekurzivni poziv pravi svoju promenljivu
}                                                               //tkd kad zavrsimo sa svime i vratimo se na pocetak stabla, root je nas originalni koren koji se cuvao u steku tog poziva funkcije sve vreme

void ispisiStablo(Node* root){

    if(root == NULL)
        return;

    ispisiStablo(root->left);
    printf("%s %d %d \n", root->grad, root->jutroT, root->danT);
    ispisiStablo(root->right);
    return;
}

void najvecaRazlika(Node* root, int* max, char* maxGrad){

    if(root == NULL)
        return;

    if(abs(root->jutroT - root->danT) > *max){
        *max = abs(root->jutroT - root->danT);
        strcpy(maxGrad, root->grad);
    }

    najvecaRazlika(root->left, max, maxGrad);
    najvecaRazlika(root->right, max, maxGrad);
    return;
}

void prosecnaTempZaJutarnju(Node* root, int granica, int* suma, int* brGradova){

    if(root == NULL)
        return;

    if(root->jutroT <= granica){
        *suma += root->danT;
        (*brGradova)++;
    }

    prosecnaTempZaJutarnju(root->left, granica, suma, brGradova);
    prosecnaTempZaJutarnju(root->right, granica, suma, brGradova);
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

Node* ucitajFajl(Node* root, char imeFajla[]){

    FILE* fp = fopen(imeFajla, "r");

    if(fp == NULL){
        printf("Greska pri ucitavanju");
        fclose(fp);
        return NULL;
    }

    char grad[30];
    int jutroT, danT;
    while(!feof(fp)){
        fscanf(fp, "%s%d%d", grad, &jutroT, &danT);
        Node* newNode = (Node*) malloc(sizeof(Node));
        strcpy(newNode->grad, grad);
        newNode->jutroT = jutroT;
        newNode->danT = danT;
        newNode->left = NULL;
        newNode->right = NULL;
        //root = addNodeIter(root, newNode);
        root = addNodeRek(root, newNode);
    }

    fclose(fp);
    return root;
}

int main(){

    Node* root = NULL;
    int n;

    do{
        printf("%s", opcijeStr);
        scanf("%d", &n);

        if(n == 1){
            char naziv[30];
            printf("Unesite ime fajla: ");
            scanf("%s", naziv);
            root = ucitajFajl(root, naziv);
        }

        else if(n == 2) ispisiStablo(root);

        else if(n == 3){
            int maxRazlika = 0;
            char maxGrad[30];
            najvecaRazlika(root, &maxRazlika, maxGrad);
            printf("maxRazlika: %s %d \n", maxGrad, maxRazlika);
        }

        else if(n == 4){
            int tempJutro;
            printf("Unesite granicnu jutarnju temp: ");
            scanf("%d", &tempJutro);
            int suma = 0, brGradova = 0;
            prosecnaTempZaJutarnju(root, tempJutro, &suma, &brGradova);
            printf("Prosek je %lf \n", (double)suma/brGradova);
        }

        else continue;

    }while(n != 0);

    izbrisiStablo(root);
    root = NULL;
    printf("Kraj programa");
    return 0;
}

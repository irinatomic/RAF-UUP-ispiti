#include <stdio.h>
#include <string.h>

char opcijeStr[] = "[0]Kraj progama \n[1]Ucitavanje podataka \n[2]Ispis svih sinonima jedne reci \n[3]Rec sa najvise sinonima \nOpcija: ";

typedef struct{

    char rec1[30], rec2[30];
    struct Node* left;
    struct Node* right;

}Node;

Node* addNodeIter(Node* root, Node* newNode){

    if(root == NULL)
        return newNode;

    Node* tmp = root;
    while(1){
        if(strcmp(newNode->rec1, tmp->rec1) <= 0){
            if(tmp->left == NULL){
                tmp->left = newNode;
                return root;
            }
            tmp = tmp->left;
        }
        else{
            if(tmp->right == NULL){
                tmp->right = newNode;
                return root;
            }
            tmp = tmp->right;
        }
    }
}

Node* addNodeRek(Node* root, Node* rootCopy, Node* newNode){

    if(root == NULL)
        return newNode;

    if(strcmp(newNode->rec1, root->rec1) <= 0)
        root->left = addNodeRek(root->left, rootCopy, newNode);
    else
        root->right = addNodeRek(root->right, rootCopy, newNode);
}

void brPonavljanjaReci(Node* root, char trazenaRec[], int* brojac){

    if(root == NULL)
        return;

    *brojac = (strcmp(root->rec1, trazenaRec) == 0 || strcmp(root->rec2, trazenaRec) == 0)? (*brojac)+1: *brojac;
    brPonavljanjaReci(root->left, trazenaRec, brojac);
    brPonavljanjaReci(root->right, trazenaRec, brojac);
    return;
}

void recSaNajviseSinonima(Node* root, Node* rootCopy, char rec[], int* maxPon){

    if(root == NULL)
        return;

    int brojac = 0;
    brPonavljanjaReci(rootCopy, root->rec1, &brojac);
    if(brojac > *maxPon){
        *maxPon = brojac;
        strcpy(rec, root->rec1);
    }

    brojac = 0;
    brPonavljanjaReci(rootCopy, root->rec2, &brojac);
    if(brojac > *maxPon){
        *maxPon = brojac;
        strcpy(rec, root->rec2);
    }

    recSaNajviseSinonima(root->left, rootCopy, rec, maxPon);
    recSaNajviseSinonima(root->right, rootCopy, rec, maxPon);
}

void sviSinonimiRek(Node* root, char rec[]){

    if(root == NULL)
        return;

    if(strcmp(root->rec1, rec) == 0) printf("%s ", root->rec2);
    else if(strcmp(root->rec2, rec) == 0) printf("%s ", root->rec1);

    sviSinonimiRek(root->left, rec);
    sviSinonimiRek(root->right, rec);
}

void sviSinonimiIter(Node* root, char rec[]){

    if(root == NULL)                                                //u slucaju da je lista prazna
        return;

    Node* tmp = root;
    Node* tmp2 = root;              //da ide "suprotno"

    while(1){
        if(strcmp(tmp->rec1, rec) == 0) printf("%s ", tmp->rec2);
        else if(strcmp(tmp->rec2, rec) == 0) printf("%s ", tmp->rec1);
        else if(strcmp(tmp2->rec2, rec) == 0) printf("%s ", tmp2->rec1);
        else if(strcmp(tmp2->rec1, rec) == 0) printf("%s ", tmp2->rec2);


        if(strcmp(rec, tmp->rec1) <= 0){
            if(tmp->left == NULL) break;
            if(tmp2->right == NULL) break;
            tmp = tmp->left;
            tmp2 = tmp2->right;
        }

        else{
            if(tmp->right == NULL) break;
            if(tmp2->left == NULL) break;
            tmp = tmp->right;
            tmp2 = tmp2->left;
        }
    }
}

void ispisiStablo(Node* root){

    if(root == NULL)
        return;

    ispisiStablo(root->left);
    printf("%s %s \n", root->rec1, root->rec2);
    ispisiStablo(root->right);
}

void izbrisiStablo(Node* root){

    if(root == NULL)
        return;

    izbrisiStablo(root->left);
    izbrisiStablo(root->right);
    free(root);
}

Node* ucitajFajl(Node* root, char fileName[]){

    FILE* fp = fopen(fileName, "r");

    if(fp == NULL){
        printf("Greska pri ucitavanju \n");
        fclose(fp);
        return NULL;
    }

    char str[100];
    while(fgets(str, sizeof(str), fp)){
        Node* newNode = (Node*) malloc(sizeof(Node));
        char* token = strtok(str, "-");
        strcpy(newNode->rec1, token);
        token = strtok(NULL, "\n");
        strcpy(newNode->rec2, token);
        newNode->left = NULL;
        newNode->right = NULL;
        //root = addNodeIter(root, newNode);
        root = addNodeRek(root, root, newNode);
    }
    fclose(fp);
    return root;
}

int main(){

    int n;
    Node* root = NULL;
    do{
        printf("%s", opcijeStr);
        scanf("%d", &n);
        if(n == 1){
            char fileName[] = "sinonimi.txt";
            root = ucitajFajl(root, fileName);
            ispisiStablo(root);
            printf("\n");
        }
        if(n == 2){
            char rec[30];
            printf("Unesite rec: ");
            scanf("%s", rec);
            sviSinonimiRek(root, rec);
            //sviSinonimiIter(root, rec);       IDK
            printf("\n");
        }
        else if(n == 3){
            char rec[30];
            int maxPon = 0;
            recSaNajviseSinonima(root, root, rec, &maxPon);
            printf("To je rec: %s \n", rec);
        }
        else continue;

    }while(n != 0);

    izbrisiStablo(root);
    root = NULL;
    printf("Kraj programa \n");
    return 0;
}

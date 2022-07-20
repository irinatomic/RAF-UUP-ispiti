#include <stdio.h>
#include <string.h>

char opcijeStr[] = "[0]Kraj programa \n[1]Uciitavanje podataka \n[2]Ispis elemenata \n[3]Najhladniji grad \nOpcija: ";

typedef struct{

    char drzava[30], grad[30];
    int temp;
    struct Node* left;
    struct Node* right;

}Node;

Node* addNodeIter(Node* root, Node* newNode){

    if(root == NULL)
        return newNode;

    Node* tmp = root;
    while(1){
        if(strcmp(newNode->grad, tmp->grad) <= 0){
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

    if(strcmp(newNode->grad, root->grad) <= 0)
        root->left = addNodeRek(root->left, rootCopy, newNode);
    else
        root->right = addNodeRek(root->right, rootCopy, newNode);
}

void najhladnijiGrad(Node* root, char drzava[], char grad[], int* tempMin){

    if(root == NULL)
        return;

    if(root->temp < *tempMin){
        *tempMin = root->temp;
        strcpy(drzava, root->drzava);
        strcpy(grad, root->grad);
    }

    najhladnijiGrad(root->left, drzava, grad, tempMin);
    najhladnijiGrad(root->right, drzava, grad, tempMin);
    return;
}

void ispisiStablo(Node* root){

    if(root == NULL)
        return;

    ispisiStablo(root->left);
    printf("%s %s %d \n", root->drzava, root->grad, root->temp);
    ispisiStablo(root->right);
    return;
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

        char* token = strtok(str, " ");
        strcpy(newNode->drzava, token);
        token = strtok(NULL, " ");
        strcpy(newNode->grad, token);
        token = strtok(NULL, " \n");
        newNode->temp = atoi(token);
        newNode->left = NULL;
        newNode->right = NULL;
        //root = addNodeIter(root, newNode);
        root = addNodeRek(root, root, newNode);
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
            char fileName[] = "grupa1.txt";
            root = ucitajFajl(root, fileName);
        }
        else if(n == 2){
            ispisiStablo(root);
            printf("\n");
        }
        else if(n == 3){
            char drzava[30], grad[30];
            int temp = 100;
            najhladnijiGrad(root, drzava, grad, &temp);
            printf("Najhladnije: %s %s %d \n\n", drzava, grad, temp);
        }

    }while(n != 0);

    izbrisiStablo(root);
    root = NULL;
    printf("Kraj programa");
    return 0;
}

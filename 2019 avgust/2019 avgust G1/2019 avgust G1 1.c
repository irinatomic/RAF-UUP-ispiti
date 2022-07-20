#include <stdio.h>

/**
broj: 3453
matrica:
3 1 9 1
4 3 5 4
2 3 3 5
7 4 1 7
ispis: 2
**/

int brojCifara(int n){

    int brojac = 0;
    while(n){
        brojac++;
        n /= 10;
    }
    return brojac;
}

int main(){

    int broj;
    printf("Unesite broj: ");
    scanf("%d", &broj);

    int brCifara = brojCifara(broj);
    int cifre[brCifara];
    for(int i = brCifara-1; i >= 0; i--){
        cifre[i] = broj%10;
        broj /= 10;
    }

    int n;
    printf("Unesite dim matrice: ");
    scanf("%d", &n);

    int mat[n][n];
    printf("Unesite matricu: \n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", &mat[i][j]);
        }
    }

    int niz[n*n], indexNiz = 0;                                         //pravimo niz od elemenata matrice
    for(int i = 0; i < n; i++){                                         //kroz koji cemo ici da proveravamo postojanje cifara broja
        for(int j = n-1; j >= 0; j--){
            niz[indexNiz++] = mat[i][j];
        }
    }

    int brojac = 0;
    for(int i = 0; i < n*n; i++){
        int indexCifre = 0;
        if(niz[i] == cifre[0]){
            for(int j = i; j < n*n-i; j++){
                if(niz[j] == cifre[indexCifre]){
                    indexCifre++;
                }
            }
            brojac = (indexCifre == brCifara)? brojac+1: brojac;
        }
    }

    printf("Broj ponavljanja: %d", brojac);
    return 0;
}

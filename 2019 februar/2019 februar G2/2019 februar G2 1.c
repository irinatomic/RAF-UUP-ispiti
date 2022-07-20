#include <stdio.h>

/**
broj: 447
matrica:
1 4 9 1
4 7 1 4
2 3 4 2
7 4 1 4

ispis:
vrste 1 3
kolone 1
**/

int brojCifara(int n){

    int brojac = 0;
    while(n){
        brojac++;
        n /= 10;
    }
    return brojac;
}

void proveriVrstu(int ii, int n, int niz[], int brCifara, int cifre[]){

    int brojac = 0;
    for(int i = 0; i < brCifara; i++){
        for(int j = 0; j < n; j++){
            if(cifre[i] == niz[j]){
                brojac++;
                niz[j] = -1;                    //ako pronadjemo stavljamo -1 u niz jer je on tmp, ne zelimo da menjamo niz cifara broja
            }
        }
    }

    if(brojac == brCifara)
        printf("%d ", ii);
    return;
}

void proveriKolonu(int jj, int n, int niz[], int brCifara, int cifre[]){

    int brojac = 0;
    for(int i = 0; i < brCifara; i++){
        for(int j = 0; j < n; j++){
            if(cifre[i] == niz[j]){
                brojac++;
                niz[j] = -1;
            }
        }
    }

    if(brojac == brCifara)
        printf("%d ", jj);
    return;
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

    int tmp[n];
    printf("vrste: ");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            tmp[j] = mat[i][j];
        }
        proveriVrstu(i, n, tmp, brCifara, cifre);
    }

    printf("\n");
    printf("kolone: ");
    for(int j = 0; j < n; j++){
        for(int i = 0; i < n; i++){
            tmp[i] = mat[i][j];
        }
        proveriKolonu(j, n, tmp, brCifara, cifre);
    }

    return 0;
}

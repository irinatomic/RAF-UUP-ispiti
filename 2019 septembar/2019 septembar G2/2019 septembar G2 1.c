#include <stdio.h>

/**
n = 3453
3 5 9 1
4 3 5 4
2 4 3 5
7 4 1 6
ispis: 2
**/

int proveriPodmtatricu(int ii, int jj, int mat[][4], int cifre[]){

    int k = 0;
    for(int j = jj; j < jj+2; j++){
        for(int i = ii; i < ii+2; i++){
            if(mat[i][j] != cifre[k++])
                return 0;
        }
    }
    return 1;
}

int main(){

    int broj;
    printf("Unesite cetvorocifreni broj: ");
    scanf("%d", &broj);

    int cifre[4];
    for(int i = 3; i >= 0; i--){
        cifre[i] = broj%10;
        broj /= 10;
    }

    int mat[4][4];
    printf("Unesite matrici 4x4: \n");
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            scanf("%d", &mat[i][j]);
        }
    }

    int brojac = 0;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            brojac = (proveriPodmtatricu(i, j, mat, cifre))? brojac+1: brojac;
        }
    }

    printf("%d", brojac);
    return 0;
}

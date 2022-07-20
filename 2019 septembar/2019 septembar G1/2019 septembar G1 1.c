#include <stdio.h>

/**
n = 3453
matrica:
3 4 9 1
5 3 4 4
2 5 3 5
7 4 1 6
ispis: 2
**/

int proveriPodmatricu(int ii, int jj, int n, int cifre[], int mat[][n]){

    int index = 0;
    for(int i = ii; i < ii+2; i++){
        for(int j = jj; j < jj+2; j++){
            if(mat[i][j] != cifre[index++])
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

    int n;
    printf("Unesite dimenziju matrice: ");
    scanf("%d", &n);

    int mat[n][n];
    printf("Unesite matricu: \n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", &mat[i][j]);
        }
    }

    int brojac = 0;
    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < n-1; j++){
            brojac = proveriPodmatricu(i, j, n, cifre, mat)? brojac+1: brojac;
        }
    }

    printf("%d \n", brojac);
    return 0;
}

#include <stdio.h>

/**
broj = 23561
n = 4, m = 6
3 8 3 6 7 3
2 9 2 5 5 6
1 9 3 1 6 8
7 6 1 6 6 9

teme:(1,2) dim:3X3
**/

int brojCifara(int n){
    int brojac = 0;
    while(n){
        brojac++;
        n /= 10;
    }
    return brojac;
}

int sadrziSeUNizu(int niz[], int duzinaNiza, int n){
    for(int i = 0; i < duzinaNiza; i++){
        if(niz[i] == n)
            return 1;
    }
    return 0;
}

int min(int a, int b){
    return (a < b)? a: b;
}

int proveriPodmatricu(int ii, int jj, int dim, int n, int m, int mat[n][m], int cifre[], int brCifara){

    for(int i = ii; i < ii+dim; i++){
        for(int j = jj; j < jj+dim; j++){
            if(!sadrziSeUNizu(cifre, brCifara, mat[i][j]))
                return 0;
        }
    }
    return dim;
}
int main(){

    int broj;
    printf("Unesite broj: ");
    scanf("%d", &broj);

    int brCifara = brojCifara(broj);
    int cifre[brCifara];
    for(int i = 0; i < brCifara; i++){
        cifre[i] = broj%10;
        broj /= 10;
    }

    int n, m;
    printf("Unesite dim matrice: ");
    scanf("%d%d", &n, &m);

    int mat[n][m];
    printf("Unesite matricu: \n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            scanf("%d", &mat[i][j]);
        }
    }

    int maxDim = 0;
    int koordX, koordY;
    for(int i = 0; i <= n-2; i++){
        for(int j = 0; j <= m-2; j++){
            for(int dim = 2; dim <= min(n-i, m-j); dim++){
                int tmpDim = proveriPodmatricu(i, j, dim, n, m, mat, cifre, brCifara);
                if(tmpDim > maxDim){
                    maxDim = tmpDim;
                    koordX = i;
                    koordY = j;
                }
            }
        }
    }

    if(maxDim == 0)
        printf("Nema trazenih podmatrica \n");
    else
        printf("teme: (%d,%d) dim: %dx%d \n", koordX, koordY, maxDim, maxDim);
    return 0;
}

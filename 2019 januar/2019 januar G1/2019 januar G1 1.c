#include <stdio.h>

/**
prva matrica:
1 1 9 7
1 5 9 1
1 9 7 9
1 15 6 9

druga matrica:
1 9
7 9

ispis:
vrsta 0
vrsta 2
kolona 3
**/

void proveriPostojanjeVrste(int ii, int n, int mat1[][n*n], int mat2[][n]){

    int nadjeno = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int j1 = 0; j1 < n*n; j1++){
                if(mat1[ii][j1] == mat2[i][j]){
                    nadjeno++;
                    break;
                }
            }
        }
    }

    if(nadjeno == n*n)
        printf("vrsta: %d \n", ii);
    return;
}

void proveriPostojanjeKolone(int jj, int n, int mat1[][n*n], int mat2[][n]){

    int nadjeno = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int i1 = 0; i1 < n*n; i1++){
                if(mat1[i1][jj] == mat2[i][j]){
                    nadjeno++;
                    break;
                }
            }
        }
    }

    if(nadjeno == n*n)
        printf("kolona: %d \n", jj);
    return;
}

int main(){

    int n;
    scanf("%d", &n);

    printf("Unesite matricu dimenzije n*n: \n");
    int mat1[n*n][n*n];
    for(int i = 0; i < n*n; i++){
        for(int j = 0; j < n*n; j++){
            scanf("%d", &mat1[i][j]);
        }
    }

    printf("Unesite matricu dimenzije n: \n");
    int mat2[n][n];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", &mat2[i][j]);
        }
    }

    for(int i = 0; i < n*n; i++)
        proveriPostojanjeVrste(i, n, mat1, mat2);

    for(int j = 0; j < n*n; j++)
        proveriPostojanjeKolone(j, n, mat1, mat2);

    return 0;
}

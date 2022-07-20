#include <stdio.h>

/**
Primer:
1. matrica  2. matrica
1 1 9 7     1 9 7 9
1 5 9 1     7 9 7 1
1 9 7 9     5 1 8 8
1 15 6 9    5 7 8 6

Ispis:
vrste 0 0
vrste 0 1
vrste 2 0
vrste 2 1
kolone 3 1
*/

void proveriVrstu(int ii, int n, int mat1[][n], int mat2[][n]){

    for(int i2 = 0; i2 < n; i2++){
        int brojac = 0;
        for(int j2 = 0; j2 < n; j2++){
            for(int j1 = 0; j1 < n; j1++){
                if(mat1[ii][j1] == mat2[i2][j2]){
                    brojac++;
                    break;
                }
            }
        }
        if(brojac >= n)
            printf("vrste: %d %d \n", ii, i2);
    }
    return;
}

void proveriKolonu(int jj, int n, int mat1[][n], int mat2[][n]){

    for(int j2 = 0; j2 < n; j2++){
        int brojac = 0;
        for(int i2 = 0; i2 < n; i2++){
            for(int i1 = 0; i1 < n; i1++){
                if(mat1[i1][jj] == mat2[i2][j2]){
                    brojac++;
                    break;
                }
            }
        }
        if(brojac >= n)
            printf("kolone: %d %d \n", jj, j2);
    }
    return;
}

int main(){

    int n;
    scanf("%d", &n);

    printf("Unesite prvu matricu: \n");
    int mat1[n][n];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", &mat1[i][j]);
        }
    }

    printf("Unesite drugu matricu: \n");
    int mat2[n][n];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", &mat2[i][j]);
        }
    }

    for(int i = 0; i < n; i++){                     //idemo krzo vrste 2. i proveravamo vrstu prve na kojoj smo
        proveriVrstu(i, n, mat1, mat2);
    }

    for(int j = 0; j < n; j++){                     //idemo kroz kolone 2. i proveravamo kolonu prve na kojoj smo
        proveriKolonu(j, n, mat1, mat2);
    }

    return 0;
}

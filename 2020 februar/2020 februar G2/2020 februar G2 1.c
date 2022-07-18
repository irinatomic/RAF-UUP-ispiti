#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Ulaz:
1 3 5 6 7 5
2 3 4 5 1 6
9 1 1 3 4 8
5 6 7 8 7 9
1 2 3 4 5 0
3 4 1 2 6 4

Izlaz:
1 3 5 6 7 5
5 3 4 5 1 1
3 3 1 3 1 1
8 8 7 8 7 7
5 2 3 4 5 2
3 4 1 2 6 4
*/

void ispisiMatricu(int n, int mat[][n]){

    for(int i = 0; i < n; i++){
        for(int j = 0; j <  n; j++){
            printf("%2d", mat[i][j]);
        }
        printf("\n");
    }
}

int main(){

    int n;
    scanf("%d", &n);
    int mat[n][n];

    for(int i = 0; i < n; i++){                                                 //ucitavamo matricu
        for(int j = 0; j < n; j++){
            scanf("%d", &mat[i][j]);
        }
    }

    int leva = 0, desna = n-1;                                                  //granice
    int minReda, maxReda;

    for(int i = 0; i < n; i++){
        minReda = INT_MAX; maxReda = INT_MIN;
        for(int j = leva; j <= desna; j++){                                     //pre ulaska u svaki red prolazimo kroz "ostatak elemanata"
            minReda = (mat[i][j] < minReda)? mat[i][j]: minReda;                //i odredjujemo min i max od preostalih
            maxReda = (mat[i][j] > maxReda)? mat[i][j]: maxReda;
        }

        for(int j = 0; j < n; j++){
            if(j < leva)
                mat[i][j] = maxReda;
            if(j > desna)
                mat[i][j] = minReda;
        }
        if(n%2 == 0 && i == n/2-1)                                              //pomeramo granice
            continue;
        if(i < n/2){
            leva++;
            desna--;
        } else{
            leva--;
            desna++;
        }
    }

    printf("Nova matrica: \n");
    ispisiMatricu(n, mat);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void ispisiMatricu(int n, int mat[][n]){

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%2d", mat[i][j]);
        }
        printf("\n");
    }
}

int main(){

    int n;
    scanf("%d", &n);

    int mat[n][n];
    int maxKolona[n];
    int minKolona[n];

    for(int i = 0; i < n; i++){
        maxKolona[i] = 0;
        minKolona[i] = INT_MAX;
    }

    for(int i = 0; i < n; i++){                                                     //ucitavamo matricu
        for(int j = 0; j < n; j++){
            scanf("%d", &mat[i][j]);
        }
    }

    int leva = n/2 - !(n%2);                                                        //granice romba
    int desna = n/2;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(j >= leva && j <= desna){
                maxKolona[j] = (mat[i][j] > maxKolona[j])? mat[i][j]: maxKolona[j];
                minKolona[j] = (mat[i][j] < minKolona[j])? mat[i][j]: minKolona[j];
            }
            else
                mat[i][j] = -1;                                                     //elemente koje "odesacmo" pisemo u -1
        }
        if(n%2 == 0 && i == n/2 - !(n%2))                                           //menjamo granice
            continue;
        if(i < n/2 - !(n%2)){
            leva--;
            desna++;
        } else{
            leva++;
            desna--;
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(mat[i][j] == -1){                                                    //popunjavamo "odsecene" delove
                if(i < n/2) mat[i][j] = maxKolona[j];
                else mat[i][j] = minKolona[j];
            }
        }
    }

    printf("Nova matrica: \n");
    ispisiMatricu(n, mat);
    return 0;
}

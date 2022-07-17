#include <stdio.h>

/**
n = 6;
3 4 3 4 7 5
2 4 2 5 5 4
1 3 4 1 6 1
1 2 3 1 5 2
2 3 1 4 5 5
1 4 5 1 2 3
**/

void ispisiMatricu(int n, int mat[][n]){

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%2d", mat[i][j]);
        }
        printf("\n");
    }
    return;
}

int main(){

    int n;
    scanf("%d", &n);

    int mat[n][n];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", &mat[i][j]);
        }
    }

    int maxPrstenova[n/2];
    int nizIndex = 0;

    int ii = 0, jj = 0;                                             //gornja i leva granica
    int lastRow = n-1, lastColumn = n-1;                            //donja i desna granica

    int brPrstenova = 0;
    while(brPrstenova < n/2){
        int max = 0;
        for(int j = jj; j < lastColumn; j++)
            max = (mat[ii][j] > max)? mat[ii][j]: max;
        for(int i = ii; i < lastRow; i++)
            max = (mat[i][lastColumn] > max)? mat[i][lastColumn]: max;
        for(int j = lastColumn; j > jj; j--)
            max = (mat[lastRow][j] > max)? mat[lastRow][j]: max;
        for(int i = lastRow; i > ii; i--)
            max = (mat[i][jj] > max)? mat[i][jj]: max;

        maxPrstenova[nizIndex++] = max;
        jj++;
        ii++;
        lastColumn--;
        lastRow--;
        brPrstenova++;
    }

    ii = 0, jj = 0;                                             //gornja i leva granica
    lastRow = n-1, lastColumn = n-1;                            //donja i desna granica
    nizIndex = 0;

    brPrstenova = 0;
    while(brPrstenova < n/2){
        for(int j = jj; j < lastColumn; j++)
            mat[ii][j] = maxPrstenova[nizIndex];
        for(int i = ii; i < lastRow; i++)
            mat[i][lastColumn] = maxPrstenova[nizIndex];
        for(int j = lastColumn; j > jj; j--)
            mat[lastRow][j] = maxPrstenova[nizIndex];
        for(int i = lastRow; i > ii; i--)
            mat[i][jj] = maxPrstenova[nizIndex];

        jj++;
        ii++;
        lastColumn--;
        lastRow--;
        brPrstenova++;
        nizIndex++;
    }

    printf("\n");
    ispisiMatricu(n, mat);
    return 0;
}

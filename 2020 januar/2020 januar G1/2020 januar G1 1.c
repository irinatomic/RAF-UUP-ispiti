#include <stdio.h>

/**
1 1 1 0 1 0
1 0 0 0 1 1
1 1 1 1 0 1
0 1 1 1 0 1
1 1 1 1 0 1
1 1 1 0 0 1

ispis: dimenzija:3X3, gornji levi ugao: 2,1
**/

int proveriPodmatricu(int i, int j, int k, int n, int mat[][n]){

    int prev = mat[i][j];

    for(int ii = i; ii <= i+k; ii++){
        for(int jj = j; jj <= j+k; jj++){
            if(prev != mat[ii][jj])
                return 0;
            prev = mat[ii][jj];
        }
    }
    return k+1;
}

int main(){

    int n;
    scanf("%d", &n);

    int mat[n][n];
    int maxDim = 0, koordX, koordY;
    int tmpDim;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", &mat[i][j]);
        }
    }

    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < n-1; j++){
            for(int k = 1; k < n-i; k++){                             //k = dim podmatrice
                tmpDim = proveriPodmatricu(i, j, k, n, mat);
                if(tmpDim > maxDim){
                    maxDim = tmpDim;
                    koordX = i;
                    koordY = j;
                }
            }
        }
    }

    printf("Dimenzija %dx%d \n", maxDim, maxDim);
    printf("Gornji levi ugao: %d, %d", koordX, koordY);
    return 0;
}

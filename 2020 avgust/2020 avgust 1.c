#include <stdio.h>

int proveriPodmatricu(int ii, int jj, int dim, int m, int mat[][m], int n){

    for(int i = ii; i < ii+dim; i++){
        for(int j = jj; j < jj+dim; j++){
            if(i == ii || i == ii+dim-1 || j == jj || j == jj+dim-1){
                if(mat[i][j] > n)
                    return 0;
            }
        }
    }
    return dim;
}

int main(){

    int n, m;
    scanf("%d %d", &n, &m);

    int mat[m][m];
    for(int i = 0; i < m; i++){
        for(int j = 0; j < m; j++){
            scanf("%d", &mat[i][j]);
        }
    }

    int maxDim = 0, tmpDim;
    int KoordX, KoordY;

    for(int dim = 2; dim <= m; dim++){
        for(int i = 0; i <= m-dim+1; i++){
            for(int j = 0; j <= m-dim+1; j++){
                tmpDim = proveriPodmatricu(i, j, dim, m, mat, n);
                if(tmpDim > maxDim){
                    maxDim = tmpDim;
                    KoordX = i;
                    KoordY = j;
                }
            }
        }
    }

    printf("dimenzija %dx%d gornji levi ugao (%d,%d) \n", maxDim, maxDim, KoordX, KoordY);
    return 0;
}

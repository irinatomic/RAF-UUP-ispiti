#include <stdio.h>

/**
n = 5,m = 6
1 3 1 1 1 1
2 1 3 1 9 1
1 4 7 1 2 1
2 8 7 1 1 1
2 3 4 5 1 2

(1,0) dim 4x4
(0,3) dim 3x3
**/

void proveriPodmtatricu(int ii, int jj, int dim, int n, int m, int mat[n][m]){

    int zbirIvice = 0, zbirUnutra = 0;

    for(int i = ii; i < ii+dim; i++){
        for(int j = jj; j < jj+dim; j++){
            if(i == ii || i == ii+dim-1 || j == jj || j == jj+dim-1)
                zbirIvice += mat[i][j];
            else
                zbirUnutra += mat[i][j];
        }
    }

    if(zbirIvice == zbirUnutra)
        printf("(%d,%d) dim %dx%d \n", ii, jj, dim, dim);
    return;
}

int min(int a, int b){
    return (a < b)? a: b;
}

int main(){

    int n, m;
    scanf("%d%d", &n, &m);

    int mat[n][m];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            scanf("%d", &mat[i][j]);
        }
    }

    for(int i = 0; i <= n-2; i++){
        for(int j = 0; j <= m-2; j++){
            for(int dim = 2; dim <= min(n-i, m-j); dim++)
                proveriPodmtatricu(i, j, dim, n, m, mat);
        }
    }

    return 0;
}

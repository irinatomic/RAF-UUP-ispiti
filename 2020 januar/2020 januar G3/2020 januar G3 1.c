#include <stdio.h>

/**
n=2
2 1 3 4 5
6 1 9 3 1
2 1 1 1 1
2 2 2 2 6
3 1 2 4 8
ispis: broj podmatrica: 6 (0,1) (1,1) (1,2) (1,3) (3,2) (3,3)
**/

int neparnost(int x){
    return (x%2)? 1: 0;
}

int proveriPodmatricu(int ii, int jj, int a, int n, int mat[][a]){

    int neparan = neparnost(mat[ii][jj]);
    for(int i = ii; i < ii+n; i++){
        for(int j = jj; j < jj+n; j++){
            if(neparnost(mat[i][j]) != neparan)
                return 0;
        }
    }
    return 1;
}

int main(){

    int a, n;
    printf("Dimenzija matrice i podmatrice: ");
    scanf("%d %d", &a, &n);

    int mat[a][a];
    printf("Unesite matricu: \n");
    for(int i = 0; i < a; i++){
        for(int j = 0; j < a; j++){
            scanf("%d", &mat[i][j]);
        }
    }

    int brojac = 0;
    for(int i = 0; i <= a-n; i++){
        for(int j = 0; j <= a-n; j++){
            if(proveriPodmatricu(i, j, a, n, mat))
                brojac++;
        }
    }
    printf("Broj podmatrica: %d  ", brojac);

    for(int i = 0; i <= a-n; i++){
        for(int j = 0; j <= a-n; j++){
            if(proveriPodmatricu(i, j, a, n, mat))
                printf("(%d,%d) ", i, j);
        }
    }
    return 0;
}

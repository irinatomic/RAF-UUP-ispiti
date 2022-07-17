#include <stdio.h>

/**
n = 5, m = 6
1 3 1 4 3 1
2 1 3 4 9 7
1 4 7 4 2 1
2 7 7 1 1 1
2 3 4 5 1 2

Ispis:
(2,0) - 2
(4,0) - 2
(4,0) - 4
(2,3) - 3
(1,3) - 2
(2,3) - 2
**/

int min(int a, int b){
    return (a < b)? a: b;
}

int brojElemenata(int n){

    int zbir = 0;
    while(n){
        zbir += n;
        n--;
    }
    return zbir;
}

void proveriPodmtatricu(int ii, int jj, int dim, int n, int m, int mat[n][m]){

    int brElemenata = brojElemenata(dim)/2;
    int brParnih = 0;
    int hipot = jj+dim-1;                                                                    //hipotenuza kao desna granica

    for(int i = ii; i >= ii-dim+1; i--){
        for(int j = jj; j <= jj+dim-1; j++){
            if(j <= hipot)
                brParnih = (mat[i][j]%2 == 0)? brParnih+1: brParnih;
        }
        hipot--;
    }

    if(brParnih > brElemenata)
        printf("(%d,%d) %d \n", ii, jj, dim);
    return;
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

    for(int i = 1; i < n; i++){
        for(int j = 0; j < m-1; j++){
            for(int dim = 2; dim <= min(i+1, m-j); dim++)
                proveriPodmtatricu(i, j, dim, n, m, mat);
        }
    }

    return 0;
}

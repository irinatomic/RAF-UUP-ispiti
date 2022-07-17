#include <stdio.h>

/**
n = 5, m = 6
1 3 1 4 3 1
2 1 3 4 9 7
1 4 7 1 2 1
2 7 7 1 1 1
2 3 4 5 1 2

(4,0) - 2
(4,0) - 3
(4,0) - 4
(3,0) - 3
(1,3) - 2
**/

int min(int a, int b){
    return (a < b)? a: b;
}

int brojElemenata(int n){

    int brojac = 0;
    while(n){
        brojac += n;
        n--;
    }
    return brojac;
}

void proveriPodmtatricu(int ii, int jj, int dim, int n, int m, int mat[n][m]){

    int hipot = jj+dim-1;
    int brElemenata = brojElemenata(dim)/2;
    int brojac = 0;

    for(int i = ii; i >= ii-dim+1; i--){
        for(int j = jj; j < jj+dim; j++){
            if(j <= hipot)
                brojac = (mat[i][j]%2 == 0)? brojac+1: brojac;
        }
        hipot--;
    }

    if(brojac > brElemenata)
       printf("(%d,%d) - %d \n", ii, jj, dim);
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
        for(int j = 0; j <= m-2; j++){
            for(int dim = 2; dim <= min(i+1, m-j); dim++)
                proveriPodmtatricu(i, j, dim, n, m, mat);
        }
    }

    return 0;
}

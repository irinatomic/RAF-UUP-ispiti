#include <stdio.h>
#include <stdlib.h>

/**
n = 3, m = 2
1 1 1 0 1 0
1 0 0 0 1 1
1 1 1 1 0 1
0 1 1 1 0 0
1 1 1 1 0 0
1 1 1 0 0 0
ispis: broj podmatrica 4, (2,1) (2,2) (3,1) (3,4)
**/

int proveriPodmatricu(int ii, int jj, int a, int n, int m, int mat[][a]){

    int broj = mat[ii][jj];
    for(int i = ii; i < ii+n; i++){
        for(int j = jj; j < jj+m; j++){
            if(mat[i][j] != broj)
                return 0;
        }
    }
    return 1;
}

int main(){

    int a, n, m;
    printf("Dimenzija matrice i visina(n) i sirina(m) podmatrice: ");
    scanf("%d %d %d", &a, &n, &m);

    int mat[a][a];
    char koord[a*a];
    int koordIndex = 0;
    int brojac = 0;

    printf("Unesite matricu: \n");
    for(int i = 0; i < a; i++){
        for(int j = 0; j < a; j++){
            scanf("%d", &mat[i][j]);
        }
    }

    for(int i = 0; i <= a-n; i++){
        for(int j = 0; j <= a-m; j++){
            if(proveriPodmatricu(i, j, a, n, m, mat)){
                brojac++;
                koord[koordIndex++] = i + '0';
                koord[koordIndex++] = j + '0';
            }
        }
    }

    koord[koordIndex] = '\0';
    printf("Broj podmatrica: %d, ", brojac);

    int lenKoord = strlen(koord);
    for(int i = 0; i < lenKoord; i++){
        printf("(%c,%c) ", koord[i], koord[i+1]);
        i++;
    }

    return 0;
}

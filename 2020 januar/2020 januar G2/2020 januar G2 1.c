#include <stdio.h>

/**
2 1 3 4 5
6 1 9 3 1
2 1 1 1 1
2 2 2 2 6
3 1 2 4 1

ispis: dimenzija:4X2, gornji levi ugao: 1,1
**/

int neparnost(int a){
    return (a%2 == 1)? 1: 0;
}

int proveriPravougaonik(int sirina, int visina, int n, int ii, int jj, int mat[][n]){

    int neparan = neparnost(mat[ii][jj]);
    for(int i = ii; i <= ii+visina; i++){
        for(int j = jj; j <= jj+sirina; j++){
            if(neparnost(mat[i][j]) != neparan)
                return 0;
        }
    }
    return 1;
}

int main(){

    int n;
    scanf("%d", &n);

    int mat[n][n];
    int maxP = 0, koordX, koordY;
    int maxSirina, maxVisina;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", &mat[i][j]);
        }
    }
    printf("\n");

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int sirina = 1; sirina <= n-1-j; sirina++){
                for(int visina = 1; visina <= n-1-i; visina++){
                    if(proveriPravougaonik(sirina, visina, n, i, j, mat)){
                        if((sirina+1)*(visina+1) > maxP){
                            maxSirina = sirina+1;
                            maxVisina = visina+1;
                            koordX = i;
                            koordY = j;
                            maxP = (sirina+1)*(visina+1);
                        }
                    }
                }
            }
        }
    }

    printf("Dimenzija %dx%d, gornji levi ugao: %d,%d \n", maxSirina, maxVisina, koordX, koordY);
    return 0;
}

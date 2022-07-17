#include <stdio.h>

/**
broj = 97884
n = 4, m = 6
3 8 3 1 2 3
2 9 2 9 5 6
1 9 3 1 6 8
7 6 1 6 6 9

teme: (0,2) dim:3X4
**/

int brojCifara(int n){
    int brojac = 0;
    while(n){
        brojac++;
        n /= 10;
    }
    return brojac;
}

int sadrziSeUNizu(int niz[], int duzinaNiza, int n){
    for(int i = 0; i < duzinaNiza; i++){
        if(niz[i] == n)
            return 1;
    }
    return 0;
}

int proveriPodmatricu(int ii, int jj, int sirina, int visina, int n, int m, int mat[n][m], int cifre[], int brCifara){

    for(int i = ii; i < ii+visina; i++){
        for(int j = jj; j < jj+sirina; j++){
            if(i == ii || j == jj || i == ii+visina-1 || j == jj+sirina-1){                //ako smo na obodima matrice
                if(sadrziSeUNizu(cifre, brCifara, mat[i][j]))
                    return 0;
            }
        }
    }
    return 1;
}

int main(){

    int broj;
    printf("Unesite broj: ");
    scanf("%d", &broj);

    int brCifara = brojCifara(broj);
    int cifre[brCifara];
    for(int i = 0; i < brCifara; i++){
        cifre[i] = broj%10;
        broj /= 10;
    }

    int n, m;
    printf("Unesite dim matrice: ");
    scanf("%d%d", &n, &m);

    int mat[n][m];
    printf("Unesite matricu: \n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            scanf("%d", &mat[i][j]);
        }
    }

    int maxSirina = 0, maxVisina = 0;
    int KoordX, KoordY;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            for(int sirina = 2; sirina <= m-j; sirina++){
                for(int visina = 2; visina <= n-i; visina++){
                    if(proveriPodmatricu(i, j, sirina, visina, n, m, mat, cifre, brCifara)){
                        if(sirina >= maxSirina && visina >= maxVisina){
                            maxSirina = sirina;
                            maxVisina = visina;
                            KoordX = i;
                            KoordY = j;
                        }
                    }
                }
            }
        }
    }

    if(maxSirina != 0 && maxVisina != 0)
        printf("(%d,%d) %dx%d \n", KoordX, KoordY, maxSirina, maxVisina);
    else
        printf("Ne postoji trazena podmatrica(pravougaonik) \n");
    return 0;
}

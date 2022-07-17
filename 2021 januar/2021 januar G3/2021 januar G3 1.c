#include <stdio.h>

/**
x = 33124
n = 5, m =6
mat:
1 3 1 4 3 1
2 1 3 4 9 7
1 4 2 4 2 1
2 7 7 1 1 1
2 3 4 5 1 2
**/

int brojCifara(int n){

    int brojac = 0;
    while(n){
        brojac++;
        n /= 10;
    }
    return brojac;
}

int sadrziSeUNizu(int n, int brCifara, int nizCifara[]){

    for(int i = 0; i < brCifara; i++){
        if(n == nizCifara[i])
            return 1;
    }
    return 0;
}

int main(){

    int x;
    scanf("%d", &x);

    int brCifara = brojCifara(x);
    int nizCifara[brCifara];
    for(int i = brCifara-1; i >= 0; i--){
        nizCifara[i] = x%10;
        x /= 10;
    }

    int n, m;
    printf("Unesite dimenzije matrice: ");
    scanf("%d%d", &n, &m);

    int mat[n][m];
    printf("Unesite matricu: \n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            scanf("%d", &mat[i][j]);
        }
    }

    int koordXVrste, koordYVrste;
    int koordXVrsteMax, koordYVrsteMax;
    int maxLenVrste = 0, tmpLen = 0;

    for(int i = 0; i < n; i++){                                 //prvo cemo da proveravamo vrste
        for(int j = 0; j < m; j++){
            if(sadrziSeUNizu(mat[i][j], brCifara, nizCifara) && tmpLen == 0){
                koordXVrste = i;
                koordYVrste = j;
                tmpLen++;
            }
            else if(sadrziSeUNizu(mat[i][j], brCifara, nizCifara) && tmpLen != 0)
                tmpLen++;
            else if(!sadrziSeUNizu(mat[i][j], brCifara, nizCifara) && tmpLen != 0){
                if(tmpLen > maxLenVrste){
                    maxLenVrste = tmpLen;
                    koordXVrsteMax = koordXVrste;
                    koordYVrsteMax = koordYVrste;
                    tmpLen = 0;
                }
            }
            else tmpLen = 0;
        }
        i++;
        for(int j = m-1; j >= 0; j--){
            if(sadrziSeUNizu(mat[i][j], brCifara, nizCifara) && tmpLen == 0){
                koordXVrste = i;
                koordYVrste = j;
                tmpLen++;
            }
            else if(sadrziSeUNizu(mat[i][j], brCifara, nizCifara) && tmpLen != 0)
                tmpLen++;
            else if(!sadrziSeUNizu(mat[i][j], brCifara, nizCifara) && tmpLen != 0){
                if(tmpLen > maxLenVrste){
                    maxLenVrste = tmpLen;
                    koordXVrsteMax = koordXVrste;
                    koordYVrsteMax = koordYVrste;
                    tmpLen = 0;
                }
            }
            else tmpLen = 0;
        }
    }


    int koordXKolone, koordYKolone;
    int koordXKoloneMax, koordYKoloneMax;
    int maxLenKolone = 0;
    tmpLen = 0;

    for(int j = 0; j < m; j++){                                 //zatim proveravamo kolone
        for(int i = 0; i < n; i++){
            if(sadrziSeUNizu(mat[i][j], brCifara, nizCifara) && tmpLen == 0){
                koordXKolone = i;
                koordYKolone = j;
                tmpLen++;
            }
            else if(sadrziSeUNizu(mat[i][j], brCifara, nizCifara) && tmpLen != 0)
                tmpLen++;
            else if(!sadrziSeUNizu(mat[i][j], brCifara, nizCifara) && tmpLen != 0){
                if(tmpLen > maxLenKolone){
                    maxLenKolone = tmpLen;
                    koordXKoloneMax = koordXKolone;
                    koordYKoloneMax = koordYKolone;
                    tmpLen = 0;
                }
            }
            else tmpLen = 0;
        }
        j++;
        for(int i = n-1; i >= 0; i--){
            if(sadrziSeUNizu(mat[i][j], brCifara, nizCifara) && tmpLen == 0){
                koordXKolone = i;
                koordYKolone = j;
                tmpLen++;
            }
            else if(sadrziSeUNizu(mat[i][j], brCifara, nizCifara) && tmpLen != 0)
                tmpLen++;
            else if(!sadrziSeUNizu(mat[i][j], brCifara, nizCifara) && tmpLen != 0){
                if(tmpLen > maxLenKolone){
                    maxLenKolone = tmpLen;
                    koordXKoloneMax = koordXKolone;
                    koordYKoloneMax = koordYKolone;
                    tmpLen = 0;
                }
            }
            else tmpLen = 0;
        }
    }

    if(maxLenKolone > maxLenVrste){
        printf("duzina: %d (%d,%d) zmija po kolonama\n", maxLenKolone, koordXKoloneMax, koordYKoloneMax);
    }
    else
        printf("duzina: %d (%d,%d) zmija po vrstama\n", maxLenVrste, koordXVrsteMax, koordYVrsteMax);
    return 0;
}

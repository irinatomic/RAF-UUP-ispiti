#include <stdio.h>

/**
broj: 477
matrica:
1 1 9 1
2 7 4 4
2 3 4 2
7 4 1 7
ispis: glavna
**/

//idemo kroz niz i ako nadjemo tu cifru na dijagonali stavaljamo -1 na mesto u matrici
//edge case: ako imamo vise ponavljivannja iste cifre na dijagonali nego u broju

void proveriDijagonale(int n, int brCifara, int cifre[], int mat[][n]){

    int brojacGlavna = 0, brojacSporedna = 0;

    for(int i = 0; i < brCifara; i++){          //proveravamo glavnu dijagonalu
        for(int j = 0; j < n; j++){
            if(cifre[i] == mat[j][j]){
                if(j == n-j-1){                 //da ne bi izgubili onaj na preklapanju glavne i sporedne dijagonale
                    brojacGlavna++;
                    break;
                }
                mat[j][j] = -1;
                brojacGlavna++;
                break;
            }
        }
    }

    for(int i = 0; i < n; i++){                 //ako se cifra ponavlja vise puta na (glavnoj) dijagonali nego u broju ne treba da ispisemo
        for(int j = 0; j < brCifara; j++){
            if(mat[i][i] == cifre[j]){
                brojacGlavna = 0;
                break;
            }
        }
    }

    for(int i = 0; i < brCifara; i++){          //proveravamo sporednu dijagonalu
        for(int j = 0; j < n; j++){
            if(cifre[i] == mat[j][n-j-1]){
                mat[j][n-j-1] = -1;
                brojacSporedna++;
                break;
            }
        }
    }

    for(int i = 0; i < n; i++){                 //ako se cifra ponavlja vise puta na (sporednoj) dijagonali nego u broju ne treba da ispisemo
        for(int j = 0; j < brCifara; j++){
            if(mat[i][n-i-1] == cifre[j]){
                brojacSporedna = 0;
                break;
            }
        }
    }

    if(brojacGlavna == brCifara)
        printf("glavna \n");
    if(brojacSporedna == brCifara)
        printf("sporedna \n");
    return;
}

int brCifara(int n){

    int brojac = 0;
    while(n){
        brojac++;
        n /= 10;
    }
    return brojac;
}

int main(){

    int broj;
    printf("Unesite broj: ");
    scanf("%d", &broj);

    int brojCifara = brCifara(broj);
    int cifre[brojCifara];
    for(int i = 0; i < brojCifara; i++){
        cifre[i] = broj%10;
        broj /= 10;
    }

    int n;
    printf("Unesite dim matrice: ");
    scanf("%d", &n);

    printf("Unesite matricu: \n");
    int mat[n][n];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", &mat[i][j]);
        }
    }

    proveriDijagonale(n, brojCifara, cifre, mat);
    return 0;
}

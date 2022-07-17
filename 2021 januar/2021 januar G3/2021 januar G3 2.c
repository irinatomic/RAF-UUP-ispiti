#include <stdio.h>
#include <string.h>

//proci cemo kroz manji string (S) i u njemu ostaviti samo slova koja se nalaze i u duzem (P)
//potom idemo kroz duzi (P) i ako se slovo nalazi u oba, redom stavljamo slova iz modifkiovanog kraceg (S)

/**
Unos: P: aefughckl S: cdea
Ispis: cefughakl
**/

int main(){

    char P[100], S[50];
    fgets(P, sizeof(P), stdin);
    P[strlen(P)-1] = '\0';

    fgets(S, sizeof(S), stdin);
    S[strlen(S)-1] = '\0';

    int indexS = 0;
    for(int i = 0; i < strlen(S); i++){                         //modifikujemo kraci (S)
        if(strchr(P, S[i]))
            S[indexS++] = S[i];
    }
    S[indexS] = '\0';

    indexS = 0;
    for(int i = 0; i < strlen(P); i++){                         //idemo kroz duzi (P) i menjamo slova redom slovima iz kraceg (S)
        if(strchr(S, P[i]))
            P[i] = S[indexS++];
    }

    puts(P);
    return 0;
}

#include <stdio.h>
#include <string.h>

/**
Unos: P: fcghtdcbacvbbbffa S: dcba
Ispis: cvbbbffa
**/

int proveriPodstring(int ii, int jj, char P[], char S[]){

    int koord = strchr(S, P[ii]) - S;

    for(int k = ii; k <= jj; k++){
        if(strchr(S, P[k])){
            if(strchr(S, P[k]) - S == koord)
                continue;
            else if(strchr(S, P[k]) - S == koord+1)
                koord++;
            else
                return 0;
        }
    }
    return jj-ii+1;
}

int main(){

    char P[300], S[50];
    fgets(P, sizeof(P), stdin);
    P[strlen(P)-1] = '\0';

    fgets(S, sizeof(S), stdin);
    S[strlen(S)-1] = '\0';

    int tmpDim, maxDim = 0;
    int koord1, koord2;

    for(int i = 0; i < strlen(P)-1; i++){
        for(int j = i+1; j < strlen(P); j++){
            if(strchr(S, P[i]) && strchr(S, P[j])){
                tmpDim = proveriPodstring(i, j, P, S);
                if(tmpDim > maxDim){
                    maxDim = tmpDim;
                    koord1 = i;
                    koord2 = j;
                }
            }
        }
    }

    for(int i = koord1; i <= koord2; i++)
        printf("%c", P[i]);
    return 0;
}

#include <stdio.h>
#include <string.h>

/**
Unos: P: (dfhhj)fg(adbjbdnc)agh(haj)gh(akjh) S: dhj
Ispis: dfhhj haj
**/

int validan(char zagrada[], char S[]){

    int brojac = 0;
    int i;
    int index;

    for(i = 0; i < strlen(zagrada); i++){
        if(strchr(S, zagrada[i])){
            index = strchr(S, zagrada[i]) - S;
            brojac++;
            break;
        }
    }

    for(i; i < strlen(zagrada); i++){
        if(strchr(S, zagrada[i])-S == index+1){
            index++;
            brojac++;
        }
    }

    if(brojac >= 2)
        return 1;
    return 0;
}

int main(){

    char P[300], S[100], novi[300];
    fgets(P, sizeof(P), stdin);
    P[strlen(P)-1] = '\0';

    fgets(S, sizeof(S), stdin);
    S[strlen(S)-1] = '\0';

    char zagrada[50];
    int zagradaIndex = 0;
    int zagradaFlag = 0;
    novi[0] = '\0';

    for(int i = 0; i < strlen(P); i++){
        if(P[i] == ')'){
            zagradaFlag = 0;
            zagrada[zagradaIndex] = '\0';
            zagradaIndex = 0;
            if(validan(zagrada, S)){
                strcat(novi, zagrada);
                strcat(novi, " ");
            }
        }
        if(P[i] == '('){
            zagradaFlag = 1;
            continue;
        }
        if(zagradaFlag)
            zagrada[zagradaIndex++] = P[i];
    }

    novi[strlen(novi)-1] = '\0';
    puts(novi);
    return 0;
}

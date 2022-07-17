#include <stdio.h>
#include <string.h>

/**
Unos: jghcba ba vcba jvcba
Ispis: vcba jvcba
**/

void pronadjiMaxPozadi(char nasaRec[], char str[], char maxPozadi[]){

    char strCopy[100];
    strcpy(strCopy, str);

    char tmpPozadi[30];
    int tmpPozadiIndex = 0;

    char* token = strtok(strCopy , " ");
    while(token){

        if(strcmp(nasaRec, token) == 0){                                             //da ne bi poredili rec sa samom sobom
            token = strtok(NULL, " ");
            continue;
        }

        tmpPozadiIndex = 0;
        int tokenIndex = strlen(token) - 1;
        for(int i = strlen(nasaRec)-1; i >= 0; i--){
            if(nasaRec[i] == token[tokenIndex--])
                tmpPozadi[tmpPozadiIndex++] = nasaRec[i];
            else{
                tmpPozadi[tmpPozadiIndex] = '\0';
                tmpPozadiIndex = 0;
                if(strlen(tmpPozadi) > strlen(maxPozadi))
                    strcpy(maxPozadi, tmpPozadi);
                break;
            }
        }

        token = strtok(NULL, " ");
    }

    return;
}

int main(){

    char str[100], rec[30], maxPozadi[30];
    fgets(str, sizeof(str), stdin);
    str[strlen(str)-1] = '\0';
    maxPozadi[0] = '\0';

    int recIndex = 0;
    for(int i = 0; i < strlen(str)+1; i++){
        if(str[i] == ' ' || str[i] == '\0'){
            rec[recIndex] = '\0';
            recIndex = 0;
            pronadjiMaxPozadi(rec, str, maxPozadi);
        }
        else
            rec[recIndex++] = str[i];
    }

    char* token = strtok(str, " ");
    while(token){
        int maxPozadiIndex = 0;
        for(int i = strlen(token)-1; i >= 0; i--){
            if(token[i] == maxPozadi[maxPozadiIndex++])
                continue;
            else break;
        }

        if(maxPozadiIndex == strlen(maxPozadi))
            puts(token);

        token = strtok(NULL, " ");
    }

    return 0;
}

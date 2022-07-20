#include <stdio.h>
#include <string.h>

/**
Unos: obla(ci) m)e(sec su(nce) polj)e
Ispis: obla(ic) su(ecn)
**/

int proveri(char str[]){

    int nivo = 0;
    for(int i = 0; i < strlen(str); i++){
        if(str[i] == '('){
            nivo = 1;
            continue;
           }

        if(nivo == 0 && str[i] == ')' || nivo == 1 && str[i] == '(')
            return 0;

        if(str[i] == ')')
            nivo = 0;
    }
    return 1;
}

int main(){

    char str[100], novi[100];
    fgets(str, sizeof(str), stdin);
    str[strlen(str)-1] = '\0';
    novi[0] = '\0';

    char* token = strtok(str, " ");
    while(token){

        if(proveri(token) > 0){
            strcat(novi, token);
            strcat(novi, " ");
        }
        token = strtok(NULL, " ");
    }

    novi[strlen(novi)-1] = '\0';
    puts(novi);
    return 0;
}

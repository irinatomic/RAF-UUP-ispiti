#include <stdio.h>
#include <string.h>

/**
Unos: acdj"knaan"nhn"prcf"ak"dfffs"j
Ispis: acdj"naan"nhn""ak"fff"j
**/

int brPojavljivanja(char str[], char slovo, int pocetniIndex){

    int brojac = 0;
    for(int i = pocetniIndex; str[i] != '\"'; i++)
        brojac = (str[i] == slovo)? brojac+1: brojac;
    return brojac;
}

int main(){

    char str[100], novi[100];
    fgets(str, sizeof(str), stdin);
    str[strlen(str)-1] = '\0';

    int noviIndex = 0;
    int navodniciIndex = 0;
    int navodniciFlag = 0;
    int slovo1Index;

    for(int i = 0; i < strlen(str); i++){

        if(str[i] == '\"'){
            novi[noviIndex++] = str[i];
            navodniciFlag = (navodniciFlag+1)%2;
            navodniciIndex = (navodniciFlag)? i+1: -1;
            continue;
        }

        if(navodniciFlag){
            if(brPojavljivanja(str, str[i], navodniciIndex) > 1)
                novi[noviIndex++] = str[i];
        }
        else novi[noviIndex++] = str[i];
    }

    novi[noviIndex] = '\0';
    puts(novi);
    return 0;
}

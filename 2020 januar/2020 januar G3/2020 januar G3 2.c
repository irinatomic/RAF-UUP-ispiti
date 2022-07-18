#include <stdio.h>

/**
Unos: a:dfg b:drt a:ght g:ase g:zua
Ispis: a:dfght b:drt g:asezu
**/

int dodatKljuc(char* novi, char ch){

    for(int i = 0; i < strlen(novi); i++){
        if(novi[i] == ch && novi[i+1] == ':')
            return 1;
    }
    return 0;
}

void izbaciDuplikate(char* str){

    int len = strlen(str);
    int strIndex = 2;
    for(int i = 2; i < len; i++){
        if(strchr(str + i + 1, str[i]) == NULL)
            str[strIndex++] = str[i];
    }
    str[strIndex] = '\0';
}

int main(){

    char str[100], novi[100];
    fgets(str, sizeof(str), stdin);
    str[strlen(str)-1] = '\0';

    int noviIndex = 0;
    novi[0] = '\0';
    int len = strlen(str);
    char kljuc;

    for(int i = 0; i < len; i++){
        if(str[i+1] == ':')
            kljuc = str[i];

        if(!dodatKljuc(novi, kljuc)){
            novi[noviIndex++] = kljuc;
            novi[noviIndex++] = ':';
            for(int j = i; j < len; j++){
                if(str[j] == kljuc && str[j+1] == ':'){
                    for(int k = j+2; str[k] != ' ' && str[k] != '\0'; k++)
                        novi[noviIndex++] = str[k];
                }
            }
            novi[noviIndex++] = ' ';
        }

    }

    novi[noviIndex] = '\0';
    str[0] = '\0';

    char* token = strtok(novi, " ");
    while(token){
        izbaciDuplikate(token);
        strcat(str, token);
        strcat(str, " ");
        token = strtok(NULL, " ");
    }

    str[strlen(str)-1] = '\0';
    puts(str);
    return 0;
}

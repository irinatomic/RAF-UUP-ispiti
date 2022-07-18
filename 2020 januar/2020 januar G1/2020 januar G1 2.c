#include <stdio.h>
#include <string.h>

/**
Unos: 2:adfh 1:ijjk 4:op 2:fghi 1:jk
Ispis: 2:adffghhi 1:ijjjkk 4:op
**/

int cifra(char c){
    return (c >= '0' && c <= '9')? 1: 0;
}

void sortiraj(char* str){

    int len = strlen(str);
    for(int i = 2; i < len-1; i++){
        for(int j = i+1; j < len; j++){
            if(str[j] < str[i]){
                char tmp = str[j];
                str[j] = str[i];
                str[i] = tmp;
            }
        }
    }
}

int main(){

    char str[100];
    char novi[100];
    int noviIndex;
    gets(str);
    strcat(str, " ");

    int len = strlen(str);
    char kljuc;

    for(int i = 0; i < len; i++){
        if(cifra(str[i]) && (strchr(novi, str[i]) == NULL)){
            kljuc = str[i];
            novi[noviIndex++] = kljuc;
            novi[noviIndex++] = ':';
            for(int j = i; j < len; j++){
                if(str[j] == kljuc){
                    for(int k = j+2; str[k] != ' '; k++)
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
        sortiraj(token);
        strcat(str, token);
        strcat(str, " ");
        token = strtok(NULL, " ");
    }

    puts(str);
    return 0;
}

#include <stdio.h>
#include <string.h>

/*
Unos: abccghj ujh hkllm weertz
Ispis: abccba jhgccghj hkllkh mllm weew ztreertz
*/

void proveriPreslikaj(char* token, char* novi, int* noviIndex){

    int preslikaj = 0;
    int len = strlen(token);
    int koordPreseka = 0;

    for(int i = 0; i < len-1; i++){
        if(token[i] == token[i+1]){
            preslikaj = 1;
            koordPreseka = i;
            break;
        }
    }

    if(preslikaj){
        for(int i = 0; i <= koordPreseka+1; i++)
            novi[(*noviIndex)++] = token[i];
        for(int i = koordPreseka-1; i >= 0; i--)
            novi[(*noviIndex)++] = token[i];

        novi[(*noviIndex)++] = ' ';

        for(int i = len-1; i>= koordPreseka; i--)
            novi[(*noviIndex)++] = token[i];
        for(int i = koordPreseka+2; i < len; i++)
            novi[(*noviIndex)++] = token[i];

        novi[(*noviIndex)++] = ' ';
    }
    return;
}

int main(){

    char str[100], novi[200];
    int noviIndex = 0;
    fgets(str, sizeof(str), stdin);
    str[strlen(str)-1] = '\0';

    char* token = strtok(str, " ");
    while(token){
        proveriPreslikaj(token, novi, &noviIndex);
        token = strtok(NULL, " ");
    }

    novi[noviIndex] = '\0';
    puts(novi);
    return 0;
}

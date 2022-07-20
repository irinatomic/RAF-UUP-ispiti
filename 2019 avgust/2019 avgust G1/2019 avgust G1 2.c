#include <stdio.h>
#include <string.h>

/**
unos: obla!ci mesec su!nce
ispis: ci!obla nce!su
**/

void modifikuj(char* str){

    if(strchr(str, '!') == NULL){
        str[0] = '\0';
        return;
    }

    int koord = strchr(str, '!') - str;
    char pre[30], posle[30];

    int j = 0;
    for(int i = 0; i < koord; i++)
        pre[j++] = str[i];

    pre[j] = '\0';
    j = 0;
    for(int i = koord+1; i < strlen(str); i++)
        posle[j++] = str[i];

    posle[j] = '\0';
    int noviIndex = 0;
    for(int i = 0; i < strlen(posle); i++)
        str[noviIndex++] = posle[i];

    str[noviIndex++] = '!';
    for(int i = 0; i < strlen(pre); i++)
        str[noviIndex++] = pre[i];

    str[noviIndex] = '\0';
    return;
}

int main(){

    char str[100], novi[100];
    fgets(str, sizeof(str), stdin);
    str[strlen(str)-1] = '\0';
    novi[0] = '\0';

    char* token = strtok(str, " ");
    while(token){
        modifikuj(token);
        strcat(novi, token);
        strcat(novi, " ");
        token = strtok(NULL, " ");
    }

    novi[strlen(novi)-1] = '\0';                            //-1 je poslednje mesto sto je ' '
    puts(novi);
    return 0;
}

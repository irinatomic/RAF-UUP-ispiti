#include <stdio.h>
#include <string.h>

/**
unos: obla!ci mesec su!nc!e polj!e!
ispis: obla!ci sue polj
**/

void modifikuj(char str[]){

    int brojac = 0;                                                    //broj uzvicnika
    int index1 = -1, index2;
    for(int i = 0; i < strlen(str); i++){
        if(str[i] == '!'){
            brojac++;
            if(index1 != -1) index2 = i;
            else index1 = i;
        }
    }

    int noviIndex = 0;
    if(brojac == 0){
        str[0] = '\0';
        return;
    }
    else if(brojac == 1) return;
    else{
        for(int i = 0; i < strlen(str); i++){
            if(i >= index1 && i <= index2) continue;
            else str[noviIndex++] = str[i];
        }
    }

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
        if(strlen(token) > 0){
            strcat(novi, token);
            strcat(novi, " ");
        }
        token = strtok(NULL, " ");
    }

    novi[strlen(novi)-1] = '\0';
    puts(novi);
    return 0;
}

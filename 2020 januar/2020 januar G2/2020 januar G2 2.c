#include <stdio.h>
#include <string.h>

/**
Unos: [adf] {bmno} {mm} {nm} (jkl) [dv]
Ispis: [addfv] {bmmmno} (jkl)
**/

void modifikuj(char* str){

    int len = strlen(str) - 1;
    for(int i = 1; i < len-1; i++){
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

    char str[100], novi[100];
    fgets(str, sizeof(str), stdin);
    str[strlen(str)-1] = '\0';
    strcat(str, " ");

    int noviIndex = 0;
    int len = strlen(str);

    for(int i = 0; i < len; i++){
        if((str[i] == '(' || str[i] == '[' || str[i] == '{') && strchr(novi, str[i]) == NULL){

            novi[noviIndex++] = str[i];
            for(int j = i; j < len; j++){
                if(str[j] == str[i]){
                    for(int k = j+1; str[k+1] != ' '; k++)
                        novi[noviIndex++] = str[k];
                }
            }
            if(str[i] == '(')
                novi[noviIndex++] = ')';
            else if(str[i] == '[')
                novi[noviIndex++] = ']';
            else
                novi[noviIndex++] = '}';
            novi[noviIndex++] = ' ';
        }
    }

    novi[noviIndex] = '\0';
    str[0] = '\0';

    char* token = strtok(novi, " ");
    while(token){

        modifikuj(token);
        strcat(str, token);
        strcat(str, " ");
        token = strtok(NULL, " ");
    }

    puts(str);
    return 0;
}

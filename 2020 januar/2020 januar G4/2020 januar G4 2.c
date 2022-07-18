#include <stdio.h>
#include <string.h>

/**
Unos: [adf] {dfg} {fgh} {nm} (jkl) [df]
Ispis: [adf] {dfghnm} (jkl)
**/

int main(){

    char str[100], novi[100];
    fgets(str, sizeof(str), stdin);
    str[strlen(str)-1] = '\0';
    int len = strlen(str);

    novi[0] = '\0';
    int noviIndex = 0;
    int zagradaIndex;

    for(int i = 0; i < len; i++){
        if((str[i] == '(' || str[i] == '[' || str[i] == '{') && strchr(novi, str[i]) == NULL){

            zagradaIndex = noviIndex;
            novi[noviIndex++] = str[i];

            for(int j = i; j < len; j++){
                if(str[j] == str[i]){
                    for(int k = j+1; str[k+1] != ' ' && str[k+1] != '\0'; k++){
                        if(strchr(novi + zagradaIndex, str[k]) == NULL)
                            novi[noviIndex++] = str[k];
                    }
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
    puts(novi);
    return 0;
}

#include <stdio.h>
#include <string.h>

/**
Unos: [a,b,c] [34,up,uup,34] [1,2] [1,2,1,4]
Ipsis: [a,b,c] [1,2]
**/

int razlicitiElementi(char* zagrada){

    char elem1[10], elem2[10];
    int elem1Index = 0, elem2Index = 0;

    for(int i = 1; i < strlen(zagrada)-1; i++){
        if(zagrada[i] == ','){
            elem1[elem1Index] = '\0';
            elem1Index = 0;
            for(int j = i+1; j < strlen(zagrada); j++){
                if(zagrada[j] == ',' || zagrada[j] == ']'){
                    elem2[elem2Index] = '\0';
                    elem2Index = 0;
                    if(strcmp(elem1, elem2) == 0)
                        return 0;
                }
                else elem2[elem2Index++] = zagrada[j];
            }
        }

        else elem1[elem1Index++] = zagrada[i];
    }
    return 1;
}

int main(){

    char str[100];
    fgets(str, sizeof(str), stdin);
    str[strlen(str)-1] = '\0';
    int len = strlen(str);

    char zagrada[50];
    int zagradaIndex = 0;

    for(int i = 0; i < len; i++){
        if(str[i] == ']'){
            zagrada[zagradaIndex++] = str[i];
            zagrada[zagradaIndex] = '\0';
            zagradaIndex = 0;
            if(razlicitiElementi(zagrada))
                puts(zagrada);
            i++;
            continue;
        }
        zagrada[zagradaIndex++] = str[i];
    }

    return 0;
}

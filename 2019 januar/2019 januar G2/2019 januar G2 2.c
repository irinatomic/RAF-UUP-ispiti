#include <stdio.h>
#include <string.h>

/**
Primer:
Unos: {a,b,c} {34,up, df} {1,2,1} {a,a}
Ispis:{1,2,1}
      {a,a}
 */

void proveriSkup(char* skup){

    char elem1[20], elem2[20];
    int elem1Index = 0, elem2Index = 0;
    int istiSu = 0;

    for(int i = 1; i < strlen(skup)-1; i++){
        if(skup[i] == ','){
            elem1[elem1Index] = '\0';
            elem1Index = 0;
            for(int j = i+1; j < strlen(skup); j++){
                if(skup[j] == ',' || skup[j] == '}'){
                    elem2[elem2Index] = '\0';
                    elem2Index = 0;
                    if(strcmp(elem1, elem2) == 0){
                        istiSu = 1;
                        break;
                    }
                }
                else elem2[elem2Index++] = skup[j];
            }
            if(istiSu) break;
        }
        else elem1[elem1Index++] = skup[i];
    }

    if(istiSu)
        puts(skup);
    return;
}

int main(){

    char str[100], skup[50];
    fgets(str, sizeof(str), stdin);
    str[strlen(str)-1] = '\0';

    int skupIndex = 0;
    int lenS = strlen(str);

    for(int i = 0; i < lenS; i++){
        if(str[i] == '}'){
            skup[skupIndex++] = str[i];
            skup[skupIndex] = '\0';
            skupIndex = 0;
            proveriSkup(skup);
            i++;                                //preskacemo space izmedju skupova
        }
        else
            skup[skupIndex++] = str[i];
    }

    return 0;
}

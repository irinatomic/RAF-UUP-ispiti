#include <stdio.h>
#include <string.h>

/**
Unos: acdj(knaan)nhn(prcf)ak(sdfffs)j
Ispis: acdj(kna)nhn(prcf)ak(sdf)j
**/

int main(){

    char str[100];
    fgets(str, sizeof(str), stdin);
    str[strlen(str)-1] = '\0';

    int strIndex = 0;
    int zagradeFlag = 0;
    int zagradeIndex;

    for(int i = 0; i < strlen(str); i++){

        if(str[i] == '('){
            zagradeIndex = i+1;                         //index 1. elementa u zagradi
            str[strIndex++] = str[i];
            zagradeFlag = 1;
            continue;
        }
        else if(str[i] == ')'){
            str[strIndex++] = str[i];
            zagradeFlag = 0;
            continue;
        }
        else if(zagradeFlag){
            //printf("%c %d %d \n", str[i], strchr(str + zagradeIndex, str[i]) - str - zagradeIndex, i - zagradeIndex);
            if(strchr(str + zagradeIndex, str[i])-str == i)
                str[strIndex++] = str[i];
            else continue;
        }
        else
            str[strIndex++] = str[i];
    }

    str[strIndex] = '\0';
    puts(str);
    return 0;
}

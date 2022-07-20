#include <stdio.h>
#include <string.h>

/**
Unos: obla(ci) m)e(sec su(n)ce polj)e
Ispis: (ci)obla ce(n)su
**/

int validan(char str[]){

    int nivo = 0;
    for(int i = 0; i < strlen(str); i++){

        if(nivo == 0 && str[i] == '('){
            nivo = 1;
            continue;
        }

        if(nivo == 1 && str[i] == ')'){
            nivo = 0;
            continue;
        }

        if((nivo == 1 && str[i] == '(') || (nivo == 0 && str[i] == ')'))
            return 0;
    }
    if(nivo == 0)
        return 1;
    else
        return 0;
}

void modifikuj(char str[]){

    int index1, index2;
    for(int i = 0; i < strlen(str); i++){
        if(str[i] == '(')
            index1 = i;
        if(str[i] == ')')
            index2 = i;
    }

    char pre[30], posle[30], unutar[30];
    pre[0] = '\0';
    posle[0] = '\0';
    int j = 0;

    for(int i = 0; i < index1; i++)
        pre[j++] = str[i];
    pre[j] = '\0';

    j = 0;
    for(int i = index2+1; i < strlen(str); i++)
        posle[j++] = str[i];
    posle[j] = '\0';

    j = 0;
    for(int i = index1; i <= index2; i++)
        unutar[j++] = str[i];
    unutar[j] = 0;

    j = 0;
    for(int i = 0; i < strlen(posle); i++)
        str[j++] = posle[i];
    for(int i = 0;i < strlen(unutar); i++)
        str[j++] = unutar[i];
    for(int i = 0; i < strlen(pre); i++)
        str[j++] = pre[i];
    str[j] = '\0';
    return;
}

int main(){

    char str[100];
    fgets(str, sizeof(str), stdin);
    str[strlen(str)-1] = '\0';
    int strIndex = 0;

    char* token = strtok(str, " ");
    while(token){

        if(validan(token)){
            modifikuj(token);
            for(int i = strIndex; i < strIndex + strlen(token); i++)
                str[i] = token[i - strIndex];
            strIndex += strlen(token);
            str[strIndex++] = ' ';
        }
        token = strtok(NULL, " ");
    }

    str[strIndex] = '\0';
    puts(str);
    return 0;
}

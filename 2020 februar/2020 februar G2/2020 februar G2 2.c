#include <stdio.h>
#include <string.h>

/*
Unos: nmXabcdefg zhj acXbbbbb sXcccccc
Ispis: abncdmefng bbabbcb ccsccscc
*/

void modifikuj(char* token){

    char novi[50], levaSlova[50];
    int noviIndex = 0, levaSlovaIndex = 0;
    int lenT = strlen(token);

    for(int i = 0; i < strchr(token, 'X') - token; i++)                                 //pravimo niz slova levo od X
        levaSlova[levaSlovaIndex++] = token[i];
    levaSlova[levaSlovaIndex] = '\0';
    int mod = strlen(levaSlova);

    int brojac = 0;                                                                     //brojac i mod za loop kroz niz levih slova
    for(int i = strchr(token, 'X') - token + 1; i < lenT; i++){
        novi[noviIndex++] = token[i++];
        novi[noviIndex++] = token[i];
        if(i+1 != lenT)                                                                 //jer ne moze levi karakter da bude na kraju modifikovane reci
            novi[noviIndex++] = levaSlova[brojac++ % mod];
    }

    novi[noviIndex] = '\0';
    strcpy(token, novi);
}

int main(){

    char str[100], novi[100];
    fgets(str, sizeof(str), stdin);
    str[strlen(str)-1] = '\0';
    novi[0] = '\0';

    char* token = strtok(str, " ");
    while(token){

        if(strchr(token, 'X')){
            modifikuj(token);
            strcat(novi, token);
            strcat(novi, " ");
        }
        token = strtok(NULL, " ");
    }

    novi[strlen(novi)-1] = '\0';
    puts(novi);
    return 0;
}

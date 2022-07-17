#include <stdio.h>
#include <string.h>

/**
Unos: abc nkj amng nrp cbf ak
Ispis: abcmngk nkjrp cbf
**/

int dodatKljuc(char str[], char ch){

    if(str[0] == ch)                                            //ako je pocetni karakter stringa jer ne mozemo posle da ga proverimo jer idemo od j-1 == ' '
        return 1;

    for(int i = 0; i < strlen(str); i++){
        if(str[i] == ' ' && str[i+1] == ch)
            return 1;
    }
    return 0;
}

int main(){

    char str[100], novi[100];
    fgets(str, sizeof(str), stdin);
    str[strlen(str)-1] = '\0';
    novi[0] = '\0';
    int noviIndex = 0;

    for(int i = 0; i < strlen(str); i++){

        if(i == 0 || str[i-1] == ' '){
            if(!dodatKljuc(novi, str[i])){                                              //provera da li je prvo slovo reci vec dodato kao kljuc

                int j = i;
                for(j; str[j] != ' '; j++)                                              //dodajemo u novi prvu rec sa kljucem
                    novi[noviIndex++] = str[j];

                for(j; j < strlen(str); j++){
                    if(str[j-1] == ' ' && str[j] == str[i]){
                        for(int k = j+1; str[k] != ' ' && str[k] != '\0'; k++)
                            novi[noviIndex++] = str[k];
                    }
                }

                novi[noviIndex++] = ' ';
            }
        }
    }

    novi[noviIndex] = '\0';
    puts(novi);
    return 0;
}

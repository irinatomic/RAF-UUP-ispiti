#include <stdio.h>
#include <string.h>

/**
prvi: Danas pada sneg u Beogradu
drugi: da
ispis: sneg u Beogradu
**/

char maloSlovo(char ch){
    return (ch >= 'A' && ch <= 'Z')? ch + 'a' - 'A': ch;
}

int main(){

    char str[300], kraci[50];
    fgets(str, sizeof(str), stdin);
    str[strlen(str)-1] = '\0';
    int len = strlen(str);

    fgets(kraci, sizeof(kraci), stdin);
    str[strlen(kraci)-1] = '\0';
    int lenK = strlen(kraci) - 1;

    int noviIndex = 0;
    int pocetak = 0, kraj;

    for(int i = 0; i < len + 1; i++){
        if((str[i] == ' ' || str[i] == '\0') && i != 2){
            kraj = i-1;

            int pocetakFlag = 1, krajFlag = 1;                              //flagujemo ako se poklapaju
            int j = 0;                                                      //sa j idemo kroz kraci
            if(maloSlovo(str[pocetak]) == maloSlovo(kraci[j])){
                for(j; j < lenK; j++){
                    if(maloSlovo(str[pocetak + j]) != maloSlovo(kraci[j])){
                        pocetakFlag = 0;
                        break;
                    }
                }
            }
            else
                pocetakFlag = 0;

            j = 0;
            if(maloSlovo(str[kraj - lenK + 1]) == maloSlovo(kraci[j])){
                for(j; j < lenK; j++){
                    if(maloSlovo(str[kraj-lenK + 1 + j]) != maloSlovo(kraci[j])){
                        krajFlag = 0;
                        break;
                    }
                }
            }
            else
                krajFlag = 0;

            if(!pocetakFlag && !krajFlag){
                for(int k = 0; k < kraj-pocetak+1; k++)
                    str[noviIndex++] = str[pocetak+k];
                str[noviIndex++] = ' ';
            }

            pocetak = i+1;
        }
    }

    str[noviIndex] = '\0';
    puts(str);
    return 0;
}

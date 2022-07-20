#include <stdio.h>
#include <string.h>

/**
prvi: Jaja pojavljivanja boja jabuka
drugi: ja
ispis: boja jabuka
*/

char maloSlovo(char ch){
    return (ch >= 'A' && ch <= 'Z')? ch + 'a' - 'A': ch;
}

int main(){

    char duzi[100], kraci[20];
    fgets(duzi, sizeof(duzi), stdin);
    duzi[strlen(duzi)-1] = '\0';

    fgets(kraci, sizeof(kraci), stdin);
    kraci[strlen(kraci)-1] = '\0';

    int kraciIndex = 0;
    int noviIndex = 0;
    int brPojavljivanja = 0;
    int pocetak = 0, kraj;                          //pocetak i kraj reci

    for(int i = 0; i < strlen(duzi)+1; i++){
        if(duzi[i] == ' ' || duzi[i] == '\0'){
            kraj = i-1;
            if(brPojavljivanja < 2){
                for(int j = pocetak; j <= kraj; j++)
                    duzi[noviIndex++] = duzi[j];
                duzi[noviIndex++] = ' ';
            }
            brPojavljivanja = 0;
            pocetak = i+1;
        }

        else{
            if(maloSlovo(duzi[i]) == maloSlovo(kraci[kraciIndex]))
                kraciIndex++;
            else
                kraciIndex = 0;

            if(kraciIndex == strlen(kraci)){
                brPojavljivanja++;
                kraciIndex = 0;
            }
        }
    }

    duzi[noviIndex-1] = '\0';
    puts(duzi);
    return 0;
}

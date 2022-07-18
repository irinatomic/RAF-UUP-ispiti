#include <stdio.h>
#include <string.h>

void modifikuj(char* str){

    char desno[10];
    int desnoIndex = 0;
    for(int i = strchr(str, 'X') - str + 1; i < strlen(str); i++){              //pravimo niz sa slovima desno od X
        desno[desnoIndex++] = str[i];
    }
    desno[desnoIndex] = '\0';
    int mod = strlen(desno);                                                    //pravicemo "loop" kroz niz desnih slova sa modom koji je duzina tog niza

    char novi[100];
    int noviIndex = 0, brojac = 0;
    for(int i = 0; str[i] != 'X'; i++){                                         //u novi niz naizmenicno dodajemo levi karakter pa desni
        novi[noviIndex++] = str[i];
        novi[noviIndex++] = desno[(brojac++)%mod];
    }
    novi[noviIndex-1] = '\0';                                                   //-1 jer zelimo da se zavrsi sa levim karakterom
    strcpy(str, novi);
}

int main(){

    char str[100], novi[100];
    fgets(str, sizeof(str), stdin);                                             //necemo brisati '\n' iz fgets jer mi pravi neku gresku

    char rec[50];
    rec[0] = '\0';
    novi[0] = '\0';
    int recIndex = 0;
    int len = strlen(str);

    for(int i = 0; i < len; i++){
        rec[recIndex++] = str[i];
        if(str[i] == ' ' || str[i] == '\n'){
            rec[recIndex-1] = '\0';
            recIndex = 0;
            if(strchr(rec, 'X'))                    //ako rec sadrzi 'X' u sebi
                modifikuj(rec);
            strcat(novi, rec);
            strcat(novi, " ");
        }
    }

    novi[strlen(novi)-1] = '\0';
    puts(novi);
    return 0;
}

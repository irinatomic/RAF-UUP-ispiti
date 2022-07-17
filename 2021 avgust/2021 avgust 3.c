#include <stdio.h>
#include <string.h>
#include <math.h>

char opcijeStr[] = "[0]Kraj programa \n[1]Ucitavanje podataka \n[2]Poeni za prolazak predmeta \n[3]Broj studenata po poenima \nOpcija: ";

typedef struct{

    char smer[2];
    int index, god;
    float test1, klk1;
    float test2, klk2;
    struct Student* next;

}Student;

typedef struct{

    char smer[2];
    int god;
    float prosek;
    struct Studenti* next;

}Studenti;

int postojiGodUListi(Student* head, int god){

    while(head){
        if(head->god == god)
            return 1;
        head = head->next;
    }
    return 0;
}

int postojiGodIIndex(char smer[], int god, Student* head){

    while(head){
        if(head->god == god && strcmp(head->smer, smer) == 0)
            return 1;
        head = head->next;
    }
    return 0;
}

Studenti* createStudenti(char smer[], int god, Student* head){

    Studenti* newStudenti = (Studenti*) malloc(sizeof(Studenti));
    strcpy(newStudenti->smer, smer);
    newStudenti->god = god;

    int brojac = 0;
    float zbirPoena = 0;
    while(head){
        if(head->god == god && strcmp(head->smer, smer) == 0){
            zbirPoena += head->test1 + head->klk1 + head->test2 + head->klk2;
            brojac++;
        }
        head = head->next;
    }

    newStudenti->prosek = zbirPoena/brojac;
    newStudenti->next = NULL;
    return newStudenti;
}

void createList2(Student* head){

    Student* headCopy = head;
    for(int god = 2020; postojiGodUListi(headCopy, god); god--){

        char smer1[] = "RI";
        if(postojiGodIIndex(smer1, god, headCopy)){
            Studenti* newStudenti = createStudenti(smer1, god, headCopy);
            printf("%d %s %.2f \n", newStudenti->god, newStudenti->smer, newStudenti->prosek);
        }

        char smer2[] = "RN";
        if(postojiGodIIndex(smer2, god, headCopy)){
            Studenti* newStudenti = createStudenti(smer2, god, headCopy);
            printf("%d %s %.2f \n", newStudenti->god, newStudenti->smer, newStudenti->prosek);
        }

        char smer3[] = "RM";
        if(postojiGodIIndex(smer3, god, headCopy)){
            Studenti* newStudenti = createStudenti(smer3, god, headCopy);
            printf("%d %s %.2f \n", newStudenti->god, newStudenti->smer, newStudenti->prosek);
        }
    }

    return;
}

int poeniZaProlazakIter(Student* head, int granica){

    int brojac = 0;
    while(head){
        int brPoenaStudenta = head->test1 + head->klk1 + head->test2 + head->klk2;
        if(abs(51 - brPoenaStudenta) > granica)
            brojac++;
        head = head->next;
    }
    return brojac;
}

int poeniZaProlazakRek(Student* head, int granica, int* brojac){

    if(head == NULL)
        return *brojac;

    int brPoenaStudenta = head->test1 + head->klk1 + head->test2 + head->klk2;
        if(abs(51 - brPoenaStudenta) > granica)
            (*brojac)++;

    poeniZaProlazakRek(head->next, granica, brojac);
}

float strToFloat(char str[]){

    float broj = 0;
    float k = 0.1;
    int i = 0;
    for(i; i < strlen(str) && str[i] != '.'; i++)
        broj = broj*10 + (str[i] - '0');

    i++;
    for(i; i < strlen(str) && str[i] != '\n'; i++){
        broj += (str[i] - '0')*k;
        k *= 0.1;
    }
    return broj;
}

Student* createStudent(char str[]){

    Student* newStudent = (Student*) malloc(sizeof(Student));

    char* token = strtok(str, ",");
    strcpy(newStudent->smer, token);
    token = strtok(NULL, ",");
    newStudent->index = atoi(token);
    token = strtok(NULL, ",");
    newStudent->god = atoi(token);
    token = strtok(NULL, ",");
    newStudent->test1 = strToFloat(token);
    token = strtok(NULL, ",");
    newStudent->klk1 = strToFloat(token);
    token = strtok(NULL, ",");
    newStudent->test2 = strToFloat(token);
    token = strtok(NULL, ",\n");
    newStudent->klk2 = strToFloat(token);
    newStudent->next = NULL;
    return newStudent;
}

Student* addStudent(Student* head, Student* newStudent){

    if(head == NULL)                                        //ako je lista prazna
        return newStudent;

    if(strcmp(newStudent->smer, head->smer) < 0 || (strcmp(newStudent->smer, head->smer) == 0 && newStudent->index < head->index) ||
       (strcmp(newStudent->smer, head->smer) == 0 && newStudent->index == head->index && newStudent->god < head->god)){                         //ako staljamo na pocetak
        newStudent->next = head;
        return newStudent;
    }

    Student* prev = NULL;
    Student* tmp = head;
    while(tmp && strcmp(newStudent->smer, tmp->smer) > 0){
        prev = tmp;
        tmp = tmp->next;
    }

    while(tmp && strcmp(newStudent->smer, tmp->smer) == 0 && newStudent->index > tmp->index){
        prev = tmp;
        tmp = tmp->next;
    }

    while(tmp && strcmp(newStudent->smer, tmp->smer) == 0 && newStudent->index == tmp->index && newStudent->god > tmp->god){
        prev = tmp;
        tmp = tmp->next;
    }

    if(tmp == NULL){
        prev->next = newStudent;
        return head;
    }

    newStudent->next = tmp;
    prev->next = newStudent;
    return head;
}

void ispisiListu(Student* head){

    while(head){
        printf("%s %d %d %.2f %.2f %.2f %.2f\n", head->smer, head->index, head->god, head->test1, head->klk1, head->test2, head->klk2);
        head = head->next;
    }
    printf("\n");
    return;
}

void izbrisiListu(Student* head){

    while(head){
        Student* tmp = head;
        head = head->next;
        free(tmp);
    }
    return;
}

Student* ucitajFajl(Student* head, char fileName[]){

    FILE* fp = fopen(fileName, "r");

    if(fp == NULL){
        printf("Greska pri ucitavanju \n");
        fclose(fp);
        return NULL;
    }

    char fileLine[100];
    while(!feof(fp)){
        fgets(fileLine, sizeof(fileLine), fp);
        Student* newStudent = createStudent(fileLine);
        head = addStudent(head, newStudent);
    }
    fclose(fp);
    return head;
}

int main(){

    Student* head = NULL;
    int n;
    do{
        printf("%s", opcijeStr);
        scanf("%d", &n);
        fflush(stdin);
        if(n == 1){
            char fileName[] = "studenti-UUP.txt";
            head = ucitajFajl(head, fileName);
            ispisiListu(head);
        }
        else if(n == 2){
            int brPoena;
            printf("Unesite minimalni granicni broj poena koji fali studentima za prolaz: ");
            scanf("%d", &brPoena);
            fflush(stdin);
            int brojac = 0;
            printf("iterativno %d \n", poeniZaProlazakIter(head, brPoena));
            printf("rekurzivno %d \n", poeniZaProlazakRek(head, brPoena, &brojac));
        }
        else if(n == 3){
            createList2(head);
        }
        else continue;

    }while(n != 0);

    izbrisiListu(head);
    head = NULL;
    printf("Kraj programa \n");
    return 0;
}

#include <stdio.h>
#include <string.h>

char opcijeStr[] = "[0]Kraj programa \n[1]Ucitavanje podataka \n[2]Najveci broj indexa za smer i godinu \n[3]Broj studenata po poenima \nOpcija: ";

typedef struct{

    char smer[2];
    int index, god;
    float test1, klk1, test2, klk2;
    struct Student* next;

}Student;

int najveciIndexZaSmerIGodinuIter(Student* head, char smer[], int god){

    int maxIndex = 0;
    while(head){
        if(head->god == god && strcmp(head->smer, smer) == 0)
            maxIndex = (head->index > maxIndex)? head->index: maxIndex;
        head = head->next;
    }
    return maxIndex;
}

int najveciIndexZaSmerIGodinuRek(Student* head, char smer[], int god, int* maxIndex){

    if(head == NULL)
        return *maxIndex;

    if(head->god == god && strcmp(head->smer, smer) == 0)
        *maxIndex = (head->index > *maxIndex)? head->index: *maxIndex;

    najveciIndexZaSmerIGodinuRek(head->next, smer, god, maxIndex);
}

int strToFloat(char str[]){

    float broj = 0;
    int i = 0;
    for(i; i < strlen(str) && str[i] != '.'; i++)
        broj = broj*10 + (str[i] - '0');

    i++;
    float k = 0.1;
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
    token = strtok(NULL, "\n");
    newStudent->klk2 = strToFloat(token);
    newStudent->next = NULL;
    return newStudent;
}

Student* addStudent(Student* head, Student* newStudent){

    if(head == NULL)                //ako je lista prazna
        return newStudent;

    float brPoenaNew = newStudent->test1 + newStudent->klk1 + newStudent->test2 + newStudent->klk2;

    if(brPoenaNew >= (head->test1 + head->klk1 + head->test2 + head->klk2)){             //ako dodajemo na pocetak
        newStudent->next = head;
        return newStudent;
    }

    Student* prev = NULL;
    Student* tmp = head;
    while(tmp && brPoenaNew < (tmp->test1 + tmp->klk1 + tmp->test2 + tmp->klk2)){
        prev = tmp;
        tmp = tmp->next;
    }

    if(tmp == NULL){                                                //ako dodajemo na kraj
        prev->next = newStudent;
        return head;
    }

    newStudent->next = tmp;
    prev->next = newStudent;
    return head;
}

double maxPoena(Student* head){

    double max = 0;
    while(head){
        double poeniHead = head->test1 + head->klk1 + head->test2 + head->klk2;
        max = (poeniHead > max)? poeniHead: max;
        head = head->next;
    }
    return max;
}

typedef struct{
    int niz[10];                    //0.eleemenat: 0-10; 1. element: 11-20
}brojStudenataPoRasponima;

int brojStudenataSaPoenimaURasponu(Student* head, float min, float max){

    int brojac = 0;
    while(head){
        double poeniHead = head->test1 + head->klk1 + head->test2 + head->klk2;
        brojac = (poeniHead > min && poeniHead < max)? brojac+1: brojac;
        head = head->next;
    }
    return brojac;
}

brojStudenataPoRasponima* kreirajStrukturu(Student* head){

    brojStudenataPoRasponima* strukt1 = (brojStudenataPoRasponima*) malloc(sizeof(brojStudenataPoRasponima));
    int brELemenata = ((int)maxPoena(head)/10)%10 + 1;

    strukt1->niz[0] = brojStudenataSaPoenimaURasponu(head, 0, 10);
    for(int i = 0; i < brELemenata; i++)
        strukt1->niz[i] = brojStudenataSaPoenimaURasponu(head, i*10+1, (i+1)*10);
    for(int i = brELemenata; i < 10; i++)
        strukt1->niz[i] = -1;
    return strukt1;
}

void ispisiStrukturu(brojStudenataPoRasponima* strukt){

    printf("raspon: 0 - 10 broj studenata %d \n", strukt->niz[0]);
    for(int i = 1; i < 10; i++){
        if(strukt->niz[i] > -1)
            printf("raspon: %d - %d broj studenata %d \n", i*10+1, (i+1)*10, strukt->niz[i]);
    }
    printf("\n");
    return;
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
        //printf("%s %d %d %.2f %.2f %.2f %.2f \n", newStudent->smer, newStudent->index, newStudent->god, newStudent->test1, newStudent->klk1, newStudent->test2, newStudent->klk2);
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
            char smer[2];
            printf("Unesite smer: ");
            scanf("%s", smer);
            fflush(stdin);
            int god;
            printf("Unesite godinu: ");
            scanf("%d", &god);
            fflush(stdin);
            int maxIndex = 0;
            printf("iterativno %d \n", najveciIndexZaSmerIGodinuIter(head, smer, god));
            printf("rekurzivno %d \n", najveciIndexZaSmerIGodinuRek(head, smer, god, &maxIndex));
        }
        else if(n == 3){
            brojStudenataPoRasponima* strukt1 = kreirajStrukturu(head);
            ispisiStrukturu(strukt1);
        }
        else continue;

    }while(n != 0);

    izbrisiListu(head);
    head = NULL;
    printf("Kraj programa \n");
    return 0;
}

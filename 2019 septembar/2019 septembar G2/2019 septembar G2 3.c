#include <stdio.h>
#include <string.h>

//pitanja.txt
//KOPIJA LISTE - SAMO U STRUKTURI CUVAM I OG STRING NA OSNOVU KOJEG PRAVIM nodeCopies (ideja)

char opcijeStr[] = "[0]Kraj programa \n[1]Ucitavanje podataka \n[2]Broj studenata sa vise od x poena \n[3]Ispis sortirano po broju poena \nOpcija: ";

typedef struct{

    char ime;
    char prezime[30];
    int index, god;
    char smer[2];
    int poeni;
    struct Student* next;

}Student;

Student* createStudent(char str[]){

    Student* newStudent = (Student*) malloc(sizeof(Student));

    int poeni = 0, k = 1;
    for(int i = strlen(str)-1; str[i] != ','; i--){                             //uzimamo poene od kraja stringa
        poeni += (str[i] - '0')*k;
        k *= 10;
    }

    int i = 0;
    for(i = 0; str[i] != '@'; i++){}
    str[i] = '\0';                                                              //uzimamo u str sve do @ znaka

    char ime = str[0];                                                          //ime je prvi karakter u stringu
    char smer[] = {str[strlen(str)-2], str[strlen(str)-1], '\0'};
    char god[] = {str[strlen(str)-4], str[strlen(str)-3], '\0'};

    int index = 0;                                                              //index na faxu, brojIndexa
    k = 1;
    i = strlen(str)-5;
    for(i; str[i] >= '0' && str[i] <= '9'; i--){
        index += (str[i] - '0')*k;
        k *= 10;
    }

    char prezime[30];
    k = 0;                                                                         //k koristimo kao prezimeIndex
    for(int j = 1; j <= i; j++)
        prezime[k++] = str[j];
    prezime[k] = '\0';

    newStudent->ime = ime;
    strcpy(newStudent->prezime, prezime);
    newStudent->index = index;
    newStudent->god = atoi(god);
    strcpy(newStudent->smer, smer);
    newStudent->poeni = poeni;
    newStudent->next = NULL;
    return newStudent;
}

Student* addStudent(Student* head, Student* newStudent){

    if(head == NULL)                                //sort: smer(rastuce) -> god(opadajuce) -> index(opadajuce)
        return newStudent;

    if(strcmp(newStudent->smer, head->smer) < 0){
        newStudent->next = head;
        return newStudent;
    }

    if(head->next == NULL){
        head->next == newStudent;
        return head;
    }

    Student* prev = NULL;
    Student* tmp = head;
    while(tmp != NULL && strcmp(newStudent->smer, tmp->smer) > 0){          //izlazimo iz petlje ako je smer isti ili veci
        prev = tmp;
        tmp = tmp->next;
    }

    while(tmp != NULL && newStudent->god < tmp->god){                       //izlazimo iz petlje ako je godina ista ili veca
        prev = tmp;
        tmp = tmp->next;
    }

    while(tmp != NULL && newStudent->index < tmp->index){                   //izlazimo iz petlja ako je index isti ili veci
        prev = tmp;
        tmp = tmp->next;
    }

    if(tmp == NULL){                                                         //ako smo na kraju liste
        prev->next = newStudent;
        return head;
    }

    newStudent->next = tmp;
    prev->next = newStudent;
    return head;
}

int brojStudenataViseOdUnetogBrojaIter(Student* head, int granica){

    int brojac = 0;
    while(head != NULL){
        if(head->poeni > granica)
            brojac++;
        head = head->next;
    }
    return brojac;
}

int brojStudenataViseOdUnetogBrojaRek(Student* head, int granica, int* brojac){

    if(head == NULL)
        return *brojac;

    if(head->poeni > granica)
        (*brojac)++;

    brojStudenataViseOdUnetogBrojaRek(head->next, granica, brojac);
}

void ispisiSortPoBrojuPoena(Student* head){

    int maxPoen = 0;
    Student* headCopy = head;
    while(headCopy != NULL){
        maxPoen = (headCopy->poeni > maxPoen)? headCopy->poeni: maxPoen;
        headCopy = headCopy->next;
    }

    for(int i = maxPoen; i >= 0; i--){
        headCopy = head;
        while(headCopy != NULL){
            if(headCopy->poeni == i)
                printf("%s %d %s %d\n", headCopy->prezime, headCopy->index, headCopy->smer, headCopy->poeni);
            headCopy = headCopy->next;
        }
    }
    printf("\n");
    return;
}

void ispisiListu(Student* head){

    while(head != NULL){
        printf("%c %s %d %d %s %d \n", head->ime, head->prezime, head->index, head->god, head->smer, head->poeni);
        head = head->next;
    }
    printf("\n");
    return;
}

void izbrisiListu(Student* head){

    while(head != NULL){
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
        fileLine[strlen(fileLine)-1] = '\0';
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

        if(n == 1){
            char naziv[30];
            printf("Unesite ime fajla: ");
            scanf("%s", naziv);
            head = ucitajFajl(head, naziv);
            ispisiListu(head);
        }
        else if(n == 2){
            int granica;
            printf("Unesite donju granicu broja poena: ");
            scanf("%d", &granica);
            int brojac = 0;
            printf("Iterativno %d \n", brojStudenataViseOdUnetogBrojaIter(head, granica));
            printf("Rekurzivno %d \n", brojStudenataViseOdUnetogBrojaRek(head, granica, &brojac));
            printf("\n");
        }
        else if(n == 3){
            ispisiSortPoBrojuPoena(head);
        }
        else continue;

    }while(n != 0);

    izbrisiListu(head);
    head = NULL;
    printf("Kraj programa");
    return 0;
}

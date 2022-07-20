#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *meseci[12] = {"Januar", "Februar", "Mart", "April", "Maj", "Jun", "Jul", "Avgust", "Septembar", "Oktobar", "Novembar", "Decembar"};

typedef struct node node;
typedef struct node {
    int mesec, godina, bruto, neto;
    node *next;
} node;

int __atoi(char *s) {
    int ret = 0;
    for (int i = 0 ; i < strlen(s) ; i++)
        if (s[i] >= '0' && s[i] <= '9')
            ret = ret * 10 + s[i] - '0';
    return ret;
}

int mes_to_int(char *s) {
    for (int i = 0 ; i < 12 ; i++)
        if(strcmp(s, meseci[i]) == 0)
            return i + 1;
    return 0;
}

int cmp(node *a, node *b) {
    return a -> bruto < b -> bruto;
}

node *insert(node *head, node *x) {
    if (head == NULL)
        return x;

    if (cmp(x, head)) {
        x -> next = head;
        return x;
    }
    node *walk = head, *prev = 0;

    while (cmp(walk, x) && walk != NULL) {
        prev = walk;
        walk = walk -> next;
    }

    prev -> next = x;
    x -> next = walk;
    return head;
}

node *read(char *file_name) {
    FILE *f = fopen(file_name, "r");
    if (!f) {
        printf("Greksa pri otvaranju fajla\n");
        exit(-1);
    }

    node *head = NULL;

    char buffer[200];
    while (fgets(buffer, 200, f)) {
        node *tmp = malloc(sizeof(node));
        char mesec[30];
        int godina;
        char bruto[30], neto[30];
        sscanf(buffer, "%s %d %s %s", &mesec, &godina, &bruto, &neto);
        tmp -> mesec = mes_to_int(mesec);
        tmp -> godina = godina;
        tmp -> bruto = __atoi(bruto); // ima nekoliko linija gde hiljade nisu odvojene nulom tako da ???? idk
        tmp -> neto = __atoi(neto);
        tmp -> next = 0;
        head = insert(head, tmp);
    }
    fclose(f);
    return head;
}

void print_list_it(node *head) {
    while (head != NULL) {
        printf("%d %d %d %d\n", head -> mesec, head -> godina, head ->bruto, head -> neto);
        head = head -> next;
    }
}

void print_list_re(node *head) {
    if (head == NULL) return;
    printf("%d %d %d %d\n", head -> mesec, head -> godina, head ->bruto, head -> neto);
    print_list_re(head -> next);
}

void print_list_it_raspon(node *head, int l, int u) {
    while (head != NULL) {
        if (head -> neto >= l && head -> neto <= u)
            printf("%d %d %d %d\n", head -> mesec, head -> godina, head ->bruto, head -> neto);
        head = head -> next;
    }
}

void print_list_re_raspon(node *head, int l, int u) {
    if (head == NULL) return;
    if (head -> neto >= l && head -> neto <= u)
        printf("%d %d %d %d\n", head -> mesec, head -> godina, head ->bruto, head -> neto);
    print_list_re(head -> next);
}

void delete(node *head) {
    node *walk = head;
    node *tmp;
    while (walk != NULL) {
        tmp = walk -> next;
        free(walk);
        walk = tmp;
    }
}

void razlika(node *head) {
    node *walk = head;

    int razlika[12];
    int flag[12];

    for (int i = 0 ; i < 12 ; i++) 
        flag[i] = razlika[i] = 0;

    while (walk != NULL) {
        flag[walk -> mesec - 1]++;
        if (walk -> godina == 2020)
            razlika[walk -> mesec - 1] += walk -> neto;
        else razlika[walk -> mesec - 1] -= walk -> neto;
        walk = walk -> next;
    }

    for (int i = 0 ; i < 12 ; i++) {
        if (flag[i] == 2) {
            printf("%d %s %d\n", abs(razlika[i]), meseci[i], razlika > 0 ? 2020 : 2019);
        }
    }

}

void help() {
    printf("a) učitavanje podataka\n"
           "b) ispis u rasponu\n"
           "c) ispisati razliku između istih meseci\n"
           "d) izlaz iz programa i brisanje liste\n");
}

int main() {
    char choice;

    node *lista = NULL;

    do {
        help();
        choice = getchar();
        if (choice == '\n' || choice == '\r')
            choice = getchar(); // za LF ili CR (enter)
        switch (choice)
        {
        case 'a':
            lista = read("prosecnaZarada.txt");
            break;
        case 'b':
            int l, u;
            scanf("%d %d", &l, &u);
            print_list_it_raspon(lista, l, u);
            // print_list_re_raspon(lista, l, u);
            break;
        case 'c':
            razlika(lista);
            break;
        case 'd':
            delete(lista);
            return 0;
            break;
        default:
            break;
        }
    } while (choice != 'd');

    return 0;
}
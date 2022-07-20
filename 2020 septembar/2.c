#include <stdio.h>
#include <string.h>

void insert(char *input, int n, char *pos, char c) {
    for (char *i = input + n - 1 ; i > pos && i > input; i--) 
        *i = *(i - 1);
    *pos = c;
}

void __remove(char *input, int n, char *pos) {
    for (char *i = pos ; i < input + n - 1 && *i != 0; i++) 
        *i = *(i + 1);
}

int main() {
    char input[1000];
    memset(input, 0, sizeof(char) * 1000);
    fgets(input, 1000, stdin);
    
    char *token = strtok(input, " .,\n");
    while (token) {
        char tmp[200];
        strncpy(tmp, token, 200);
        // printf("%s\n", token);

        int reps = 0;
        char *_1 = NULL, *_2 = NULL;

        for (char *it = tmp ; *it != 0 ; it++) {
            if (*it >= 'A' && *it <= 'Z') {
                reps++;
                if (!_1) 
                    _1 = it;
                else if (!_2)
                    _2 = it;
            }
        }

        if (reps == 1) {
            char t = (*_1 ^ ' '); // c ^ ' ' nam daje c u suprotnom case-u (npr 'a' ^ ' ' == 'A')
            for (char i = t ; i >= 'a' ; i--) {
                insert(tmp, 100, _1 + 1, i);
            }

            for (char i = 'a' ; i <= t ; i++) {
                insert(tmp, 100, _1, i);
            }
        }
        else if (reps == 2) {
            int t = (*_2 ^ ' ') - 'a' + 1;
            if (t > _2 - tmp)
                t = _2 - tmp;
            for (int i = 0 ; i < t ; i++)
                __remove(tmp, 100, _2 + 1);
                
            t = (*_1 ^ ' ') - 'a' + 1;
            if (t > _1 - tmp)
                t = _1 - tmp;
            for (int i = 0 ; i < t ; i++) {
                __remove(tmp, 100, _1 - 1);
                _1--;
            }
        }

        token = strtok(NULL, " .,\n");
        printf("%s ", tmp);
    }

    return 0;
}
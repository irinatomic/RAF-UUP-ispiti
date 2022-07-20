#include <stdio.h>

int izracunaj_podmatricu(int matrica[100][100], int _i, int _j, int d) {
    int s = 0;
    for (int k = 0 ; k < d ; k++)
        s += matrica[_i + k][_j + k];

    return s / d;
}

int main() {
    int n, m;
    int matrica[100][100];

    scanf("%d %d", &n, &m);

    for (int i = 0 ; i < n ; i++)
        for(int j = 0 ; j < m ; j++)
            scanf("%d", &matrica[i][j]);

    int res = 0, res_i, res_j, res_d;

    int min_d = m;
    if (n < m) min_d = n;

    for (int d = 1 ; d <= min_d ; d++) {
        for (int i = 0 ; i < n - min_d + 1 ; i++)
            for (int j = 0 ; j < m - min_d + 1 ; j++) {
                int tmp = izracunaj_podmatricu(matrica, i, j, d);
                if (tmp >= res) {
                    res = tmp;
                    res_i = i;
                    res_j = j;
                    res_d = d;
                }
            }
    }

    printf("(%d,%d) %dX%d\n", res_i, res_j, res_d, res_d);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

int main() {
    int i, j, k = 0;
    int flag = 1, a[16], g[16], r[20], div[16], n, m;
    system("clear");
    printf("\nEnter the degree of generator: ");
    scanf("%d", &n);
    printf("Enter the generator: ");
    for (i = 0; i <= n; ++i) {
        scanf("%d", &g[i]);
    }
    printf("\nEnter the degree of the frame: ");
    scanf("%d", &m);
    printf("\nEnter the frame: ");
    for (i = 0; i <= m; ++i) {
        scanf("%d", &a[i]);
    }
    if (m<n || (g[0]&&g[n]) == 0) {
        printf("Not a proper generator\n");
        exit(0);
    }
    for (i = m+1; i <= m+n; ++i) {
        a[i] = 0;
    }
    for (j = 0; j <= n; ++j) {
        r[j] = a[j];
    }
    for (i = n; i <= m + n; ++i) {
        if (i > n) {
            for (j = 0; j < n; ++j) {
                r[j] = r[j + 1];
            }
            r[j] = a[i];
        }
        if (r[0]) {
            div[k++] = 1;
        } else {
            div[k++] = 0;
            continue;
        }
        for (j = 0; j <= n; ++j) {
            r[j] = r[j] ^ g[j];
        }
    }


    printf("\nQuotient is: ");
    for (j = 0; j < k; ++j) {
        printf("%d", div[j]);
    }
    printf("\nRemainder is: ");
    for (i = 1; i <= n; ++i) {
        printf("%d", r[i]);
    }
    printf("\nTransmitted frame is: ");
    for (i = m+1,j=1; i <= m+n; ++i,++j) {
        a[i] = r[j];
    }
    for (i = 0; i <= m+n; ++i) {
        printf("%d", a[i]);
    }
    printf("\n");
    printf("\nEnter the degree of the frame: ");
    scanf("%d", &m);
    printf("\nEnter the frame: ");
    for (i = 0; i <= m; ++i) {
        scanf("%d", &a[i]);
    }
    for (j = 0; j <= n; ++j) {
        r[j] = a[j];
    }
    k = 0;
    for (i = n; i <= m; ++i) {
        if (i > n) {
            for (j = 0; j < n; ++j) {
                r[j] = r[j + 1];
            }
            r[j] = a[i];
        }
        if (r[0]) {
            div[k++] = 1;
        } else {
            div[k++] = 0;
            continue;
        }
        for (j = 0; j <= n; ++j) {
            r[j] = r[j] ^ g[j];
        }
    }
    printf("\nQuotient is: ");
    for (j = 0; j < k; ++j) {
        printf("%d", div[j]);
    }
    printf("\nRemainder is: ");
    for (i = 1; i <= n; ++i) {
        printf("%d", r[i]);
    }
    for (i = 1; i <= n; ++i) {
        if (r[i]) {
            flag = 0;
        }
    }
    if (flag) {
        printf("\nNo Error\n");
    } else {
        printf("\nError\n");
    }
    return 0;
}

// #include "stdafx.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX 100

unsigned int minimum(unsigned int x, unsigned int y){
    return(x < y ? x : y);
}

unsigned int maximum(unsigned int x, unsigned int y){
    return(x > y ? x : y);
}

unsigned int gcd(unsigned int x, unsigned int y){
    if(x == y){
        return x;
    } else{
        return(gcd(minimum(x,y), maximum(x, y) - minimum(x, y)));
    }
}

unsigned int xpowy_modn(unsigned int x, unsigned int y, unsigned int n){
    unsigned int r = 1;
    while(y > 0){
        if((int)(y % 2) == 1)
            r = (r * x) % n;
        x = (x * x) % n;
        y = y / 2;
    }
    return r;
}

unsigned int findEncryptionKey(unsigned int z){
    unsigned int e;
    do{
        printf("\nEnter a number a that is relatively prime to z and < z: ");
        scanf("%d", &e);
        if(e >= z){
            continue;
        }
    } while(gcd(e, z) != 1);
    return e;
}

unsigned int findDecryptionKey(unsigned int e, unsigned int z){
    unsigned int d;
    for(d = 2; d < z; d++){
        if(((long int)(e * d) % (long int)z) == 1){
            break;
        }
    }
    return d;
}
int main(){
    unsigned int plainText[MAX], cipherText[MAX], p, q, z, n, e, d;
    char msg[MAX];
    int i;
read:
    do{
        printf("\nEnter two large prime numbers p and q: ");
        scanf("%d%d", &p, &q);
    }while(p == q);
    
    n = p * q;
    z = (p - 1) * (q - 1);
    printf("\nn = %d, z = %d", n, z);
    if(n < 120){
        printf("\nPlease keep n >= 120");
        goto read;
    }

    e = findEncryptionKey(z);
    d = findDecryptionKey(e, z);

    printf("\nPublic key = {%d, %d}", e, n);
    printf("\nPrivate key = {%d, %d}", d, n);

    printf("\nEnter a string consisting of only letters a-z, A-Z: ");
    scanf("%s", msg);

    for(i = 0; i < strlen(msg); i++){
        plainText[i] = msg[i];
        printf("\n%c = %d: ", plainText[i], plainText[i]);
        }
    printf("\n\nCipher text: \n");
    for(i = 0; i < strlen(msg); i++){
        cipherText[i] = xpowy_modn(plainText[i], e, n);
        printf("\n%d = %c", cipherText[i], cipherText[i]);
    }
    printf("\n\nPlain Text: \n");
    for(i = 0; i < strlen(msg); i++){
        plainText[i] = xpowy_modn(cipherText[i], d, n);
        printf("\n%c = %d", plainText[i], plainText[i]);
    }

    return 0;
}

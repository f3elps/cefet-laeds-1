#include <stdio.h>

void dec2bin(int dec) {
    if (dec > 1) {
        dec2bin(dec / 2);
    }
    printf("%d", dec % 2);
}

int main() {
    int n;
    printf("Digite um numero inteiro: ");
    scanf("%d", &n);
    printf("Resultado: ");
    dec2bin(n);
    printf("\n");
    return 0;
}
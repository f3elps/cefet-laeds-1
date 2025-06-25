#include <stdio.h>
#include <string.h>
 
int main() {
    char palavra[1000];
    
    while (fgets(palavra, sizeof(palavra), stdin) != NULL) {
        char letras[26];

        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < 1; j++) {
                letras[i] = 0;
            }
        }

        int quantidadeLetras[strlen(palavra)];

        for (int i = 0; i < strlen(palavra); i++) {
            letras[i] = palavra[i];
            quantidadeLetras[i] = 0;
        }

        for (int i = 0; i < strlen(palavra); i++) {
            for (int j = 0; j < strlen(palavra); j++) {
                if (letras[j] == palavra[i]) {
                    quantidadeLetras[j]++;
                    break;
                }
            } 
        }

        int jaTemImpar = 0;
        int letrasNecessarias = 0;

        for (int i = 0; i < strlen(palavra); i++) {
            if (quantidadeLetras[i] == 0) break;
            if (quantidadeLetras[i] % 2 == 1) {
                if (!jaTemImpar) {
                    jaTemImpar = 1;
                } else if (palavra[i] != 10) {
                    letrasNecessarias++;
                }
            }
        }

        printf("%d\n", letrasNecessarias);
 
    }

    return 0;
}
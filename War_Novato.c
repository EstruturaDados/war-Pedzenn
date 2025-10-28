#include <stdio.h>
#include <string.h>

// Definição da struct Territorio
typedef struct {
    char nome[50];
    char corExercito[30];
    int numeroTropas;
} Territorio;

int main() {
    Territorio territorios[5];  // Vetor estático com 5 territórios
    int i;

    printf("=== Cadastro de Territórios - Desafio WAR (Nível Novato) ===\n\n");

    // Cadastro dos territórios
    for (i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);

        // Lê o nome do território
        printf("Nome do território: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0'; // remove '\n'

        // Lê a cor do exército
        printf("Cor do exército: ");
        fgets(territorios[i].corExercito, sizeof(territorios[i].corExercito), stdin);
        territorios[i].corExercito[strcspn(territorios[i].corExercito, "\n")] = '\0'; // remove '\n'

        // Lê o número de tropas
        printf("Número de tropas: ");
        scanf("%d", &territorios[i].numeroTropas);
        getchar(); // limpa o buffer do '\n' após o scanf

        printf("\n");
    }

    // Exibe o estado atual do mapa
    printf("=== Estado Atual do Mapa ===\n");
    for (i = 0; i < 5; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].corExercito);
        printf("Número de Tropas: %d\n", territorios[i].numeroTropas);
    }

    printf("\n=== Fim do Cadastro ===\n");

    return 0;
}

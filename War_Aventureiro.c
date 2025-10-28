#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct {
    char nome[50];
    char corExercito[30];
    int numeroTropas;
} Territorio;


void cadastrarTerritorios(Territorio *territorios, int n) {
    for (int i = 0; i < n; i++) {
        printf("=== Cadastro do Território %d ===\n", i + 1);

        printf("Nome do território: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';

        printf("Cor do exército: ");
        fgets(territorios[i].corExercito, sizeof(territorios[i].corExercito), stdin);
        territorios[i].corExercito[strcspn(territorios[i].corExercito, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &territorios[i].numeroTropas);
        getchar(); 

        printf("\n");
    }
}

void exibirMapa(Territorio *territorios, int n) {
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < n; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].corExercito);
        printf("Número de Tropas: %d\n", territorios[i].numeroTropas);
    }
    printf("\n");
}

void batalhar(Territorio *atacante, Territorio *defensor) {
    if (atacante->numeroTropas <= 1) {
        printf("\n❌ %s não tem tropas suficientes para atacar!\n", atacante->nome);
        return;
    }
    if (defensor->numeroTropas <= 0) {
        printf("\n⚠️  %s já foi conquistado anteriormente!\n", defensor->nome);
        return;
    }

    int dadoAtaque = (rand() % 6) + 1;
    int dadoDefesa = (rand() % 6) + 1;

    printf("\n🎲 %s ataca %s!\n", atacante->nome, defensor->nome);
    printf("Dado de Ataque: %d | Dado de Defesa: %d\n", dadoAtaque, dadoDefesa);

    if (dadoAtaque >= dadoDefesa) {
        defensor->numeroTropas--;
        printf("💥 Ataque bem-sucedido! %s perde 1 tropa.\n", defensor->nome);

        if (defensor->numeroTropas <= 0) {
            defensor->numeroTropas = atacante->numeroTropas / 2; // transfere metade das tropas
            atacante->numeroTropas /= 2;
            strcpy(defensor->corExercito, atacante->corExercito);
            printf("🏳️ %s foi conquistado por %s!\n", defensor->nome, atacante->corExercito);
        }
    } else {
        atacante->numeroTropas--;
        printf("🛡️ Defesa bem-sucedida! %s perde 1 tropa.\n", atacante->nome);
    }
}

int main() {
    srand(time(NULL)); // inicializa o gerador de números aleatórios
    int n = 5;
    int opcao, atacante, defensor;


    Territorio *territorios = (Territorio *)calloc(n, sizeof(Territorio));
    if (territorios == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    printf("=== Desafio WAR Estruturado - Nível Aventureiro ===\n\n");
    cadastrarTerritorios(territorios, n);

    // Loop interativo de batalhas
    do {
        exibirMapa(territorios, n);

        printf("Deseja realizar um ataque? (1 = sim / 0 = não): ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {
            printf("\nEscolha o território atacante (1 a %d): ", n);
            scanf("%d", &atacante);
            getchar();

            printf("Escolha o território defensor (1 a %d): ", n);
            scanf("%d", &defensor);
            getchar();

            if (atacante < 1 || atacante > n || defensor < 1 || defensor > n || atacante == defensor) {
                printf("❌ Escolha inválida! Tente novamente.\n");
                continue;
            }

            batalhar(&territorios[atacante - 1], &territorios[defensor - 1]);
        }

    } while (opcao != 0);

    printf("\n🕹️ Fim das batalhas! Estado final do mapa:\n");
    exibirMapa(territorios, n);

 
    free(territorios);

    return 0;
}

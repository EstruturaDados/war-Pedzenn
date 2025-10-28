#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOTAL_TERRITORIOS 5


typedef struct {
    char nome[50];
    char corExercito[30];
    int numeroTropas;
    int conquistado;
} Territorio;

void inicializarMapa(Territorio* mapa);
void exibirMapa(const Territorio* mapa, int tamanho);
void atacar(Territorio* mapa, int tamanho);
int simularBatalha(Territorio* atacante, Territorio* defensor);
void atribuirMissao(char* destino, char* missoes[], int totalMissoes);
int verificarMissao(const char* missao, Territorio* mapa, int tamanho);
void menuPrincipal(Territorio* mapa, int tamanho, char* missaoJogador);


int main() {
    srand(time(NULL));

    Territorio* mapa = (Territorio*) calloc(TOTAL_TERRITORIOS, sizeof(Territorio));
    if (!mapa) {
        printf("Erro ao alocar memória para o mapa.\n");
        return 1;
    }

    inicializarMapa(mapa);

    
    char* missoes[] = {
        "Conquistar 3 territorios",
        "Eliminar todos os exercitos da cor Verde",
        "Controlar todos os territorios com mais de 5 tropas",
        "Conquistar a Europa",
        "Dominar todos os territorios de cor Azul"
    };
    int totalMissoes = 5;

    
    char* missaoJogador = (char*) malloc(100 * sizeof(char));
    if (!missaoJogador) {
        printf("Erro ao alocar memória para a missão.\n");
        free(mapa);
        return 1;
    }

    atribuirMissao(missaoJogador, missoes, totalMissoes);
    printf("Missão atribuída ao jogador: %s\n\n", missaoJogador);

    
    menuPrincipal(mapa, TOTAL_TERRITORIOS, missaoJogador);

    
    free(missaoJogador);
    free(mapa);

    return 0;
}




void inicializarMapa(Territorio* mapa) {
    const char* nomes[] = {"América do Sul", "América do Norte", "Europa", "África", "Ásia"};
    const char* cores[] = {"Vermelho", "Azul", "Verde", "Amarelo", "Preto"};
    const int tropasIniciais[] = {4, 6, 5, 3, 7};

    for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
        strcpy(mapa[i].nome, nomes[i]);
        strcpy(mapa[i].corExercito, cores[i]);
        mapa[i].numeroTropas = tropasIniciais[i];
        mapa[i].conquistado = 0;
    }
}

// Exibe o estado atual do mapa
void exibirMapa(const Territorio* mapa, int tamanho) {
    printf("\n=== ESTADO ATUAL DO MAPA ===\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d. %s | Exército: %s | Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].corExercito, mapa[i].numeroTropas);
    }
    printf("=============================\n\n");
}


void atacar(Territorio* mapa, int tamanho) {
    int atacante, defensor;

    exibirMapa(mapa, tamanho);

    printf("Escolha o território atacante (1-%d): ", tamanho);
    scanf("%d", &atacante);
    printf("Escolha o território defensor (1-%d): ", tamanho);
    scanf("%d", &defensor);

    if (atacante < 1 || atacante > tamanho || defensor < 1 || defensor > tamanho) {
        printf("Escolha inválida.\n");
        return;
    }

    if (atacante == defensor) {
        printf("Um território não pode atacar a si mesmo!\n");
        return;
    }

    simularBatalha(&mapa[atacante - 1], &mapa[defensor - 1]);
}


int simularBatalha(Territorio* atacante, Territorio* defensor) {
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n%s (atacante) rolou: %d\n", atacante->nome, dadoAtacante);
    printf("%s (defensor) rolou: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante >= dadoDefensor) {
        defensor->numeroTropas--;
        printf("%s venceu a batalha!\n", atacante->nome);
        if (defensor->numeroTropas <= 0) {
            defensor->numeroTropas = 1;
            defensor->conquistado = 1;
            strcpy(defensor->corExercito, atacante->corExercito);
            printf("%s foi conquistado!\n", defensor->nome);
        }
        return 1;
    } else {
        atacante->numeroTropas--;
        printf("%s defendeu com sucesso!\n", defensor->nome);
        return 0;
    }
}


void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}


int verificarMissao(const char* missao, Territorio* mapa, int tamanho) {
    // Exemplo de lógica simples (poderia ser expandida)
    if (strcmp(missao, "Conquistar 3 territorios") == 0) {
        int conquistados = 0;
        for (int i = 0; i < tamanho; i++) {
            if (mapa[i].conquistado) conquistados++;
        }
        if (conquistados >= 3) return 1;
    }

    if (strcmp(missao, "Eliminar todos os exercitos da cor Verde") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].corExercito, "Verde") == 0)
                return 0;
        }
        return 1;
    }

    if (strcmp(missao, "Controlar todos os territorios com mais de 5 tropas") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (mapa[i].numeroTropas <= 5) return 0;
        }
        return 1;
    }

    if (strcmp(missao, "Conquistar a Europa") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].nome, "Europa") == 0 && mapa[i].conquistado)
                return 1;
        }
        return 0;
    }

    if (strcmp(missao, "Dominar todos os territorios de cor Azul") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].corExercito, "Azul") == 0 && !mapa[i].conquistado)
                return 0;
        }
        return 1;
    }

    return 0;
}


void menuPrincipal(Territorio* mapa, int tamanho, char* missaoJogador) {
    int opcao;
    do {
        printf("=== MENU PRINCIPAL ===\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missão\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                atacar(mapa, tamanho);
                exibirMapa(mapa, tamanho);
                if (verificarMissao(missaoJogador, mapa, tamanho)) {
                    printf("\n🎉 Missão cumprida! Você venceu o jogo! 🎉\n");
                    opcao = 0;
                }
                break;
            case 2:
                printf("\nSua missão atual: %s\n", missaoJogador);
                if (verificarMissao(missaoJogador, mapa, tamanho))
                    printf("✅ Missão cumprida!\n");
                else
                    printf("❌ Missão ainda não concluída.\n");
                break;
            case 0:
                printf("\nEncerrando o jogo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 0);
}

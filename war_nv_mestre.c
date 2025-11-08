#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição de uma estrutura que representa um território do jogo
typedef struct {
    char nome[30];   // Nome do território
    char cor[10];    // Cor (exército) que controla o território
    int tropas;      // Quantidade de tropas presentes no território
} Territorio;

// Função que executa um ataque entre dois territórios
void atacar(Territorio *atacante, Territorio *defensor) {
    // Sorteia valores entre 1 e 6 para simular o lançamento dos dados
    int dadoAtaque = rand() % 6 + 1;
    int dadoDefesa = rand() % 6 + 1;

    printf("\n%s ataca %s!\n", atacante->nome, defensor->nome);
    printf("Dado atacante: %d | Dado defensor: %d\n", dadoAtaque, dadoDefesa);

    // Se o ataque for bem-sucedido (dado do atacante >= dado do defensor)
    if (dadoAtaque >= dadoDefesa) {
        defensor->tropas -= 1; // O defensor perde uma tropa
        // Caso o defensor perca todas as tropas, o território é conquistado
        if (defensor->tropas <= 0) {
            strcpy(defensor->cor, atacante->cor); // O território muda de cor
            defensor->tropas = atacante->tropas / 2; // Transfere parte das tropas do atacante
            printf("%s conquistou %s!\n", atacante->nome, defensor->nome);
        }
    } else {
        // Se o atacante perder o confronto, perde uma tropa
        atacante->tropas -= 1;
        printf("%s perdeu uma tropa.\n", atacante->nome);
    }
}

// Função que escolhe aleatoriamente uma missão e a atribui a um jogador
void atribuirMissao(char *destino, char *missoes[], int totalMissoes) {
    int idx = rand() % totalMissoes; // Índice aleatório
    strcpy(destino, missoes[idx]);   // Copia a missão sorteada para o destino
}

// Função que mostra o estado atual do mapa (territórios, cores e tropas)
void exibirMapa(Territorio *mapa, int n) {
    printf("\nMapa Atual:\n");
    for (int i = 0; i < n; i++){
        printf("%d: %s | Cor: %s | Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Função para liberar toda a memória alocada dinamicamente
void liberarMemoria(Territorio *mapa, char **missoes, int numJogadores) {
    free(mapa); // Libera o vetor de territórios
    for (int i = 0; i < numJogadores; i++)
        free(missoes[i]); // Libera cada missão individual
    free(missoes); // Libera o vetor de ponteiros
}

int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios com o tempo atual

    int n, numJogadores = 2;
    printf("Número de territórios: ");
    scanf("%d", &n);
    getchar(); // Limpa o buffer do teclado

    // Aloca dinamicamente memória para o vetor de territórios
    Territorio *mapa = (Territorio *)calloc(n, sizeof(Territorio));

    // Cadastro dos territórios
    for (int i = 0; i < n; i++) {
        printf("Território %d nome: ", i + 1);
        fgets(mapa[i].nome, 30, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0'; // Remove o '\n' final

        printf("Cor do exército: ");
        fgets(mapa[i].cor, 10, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0'; // Remove o '\n' final

        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); // Limpa o buffer
    }

    // Lista de missões pré-definidas
    char *listaMissoes[] = {
        "Destruir o exército Verde",
        "Conquistar 3 territórios",
        "Elimine todas as tropas Vermelhas",
        "Conquistar territórios seguidos",
        "Manter mais de 5 tropas em um território"
    };

    // Aloca dinamicamente o vetor de missões dos jogadores
    char **missoesJogadores = (char **)malloc(numJogadores * sizeof(char *));
    for (int i = 0; i < numJogadores; i++) {
        missoesJogadores[i] = (char *)malloc(100 * sizeof(char));
        atribuirMissao(missoesJogadores[i], listaMissoes, 5);
        printf("Missão do Jogador %d: %s\n", i + 1, missoesJogadores[i]);
    }

    // Menu principal do jogo
    int opcao;
    do {
        exibirMapa(mapa, n);
        printf("\nMenu:\n1 - Atacar\n2 - Verificar Missão\n0 - Sair\nOpção: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {
            // O jogador escolhe quem ataca e quem defende
            int atk, def;
            printf("Escolha atacante: "); scanf("%d", &atk);
            printf("Escolha defensor: "); scanf("%d", &def);
            getchar();
            atacar(&mapa[atk - 1], &mapa[def - 1]); // Chama a função de ataque
        } else if (opcao == 2) {
            // Mostra as missões dos jogadores
            printf("Verificação de missões (exemplo simplificado):\n");
            for (int i = 0; i < numJogadores; i++)
                printf("Jogador %d missão: %s\n", i + 1, missoesJogadores[i]);
        }
    } while (opcao != 0); // Sai do jogo quando o usuário digita 0

    // Libera toda a memória antes de encerrar o programa
    liberarMemoria(mapa, missoesJogadores, numJogadores);
    return 0;
}

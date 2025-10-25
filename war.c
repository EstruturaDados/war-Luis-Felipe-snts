// Inclusão das Bibliotecas com as funções que serão utilizadas no decorrer do código
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Definição de Constantes Universais
#define MAX_TERRITORIOS 5
#define TAM_STRING 100

// Declaração da STRUCT Território
struct TERRITORIOS {
    char nome[TAM_STRING];
    char cor[TAM_STRING];
    int tropas;
};

// Função de limpeza para prevenir erros de leitura
void clean_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função Principal
int main() {
    struct TERRITORIOS Territorio[MAX_TERRITORIOS];
    int opcao;

    do {
        printf("\n===================\n");
        printf("       WAR \n");
        printf("===================\n\n");
        printf(" 1 - Iniciar Jogo\n");
        printf(" 0 - Sair\n\n");
        printf("ESCOLHA UMA OPÇÃO: ");
        
        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
        }
        clean_buffer();

        switch (opcao) {
            case 1:
                printf("\n >> A BATALHA IRÁ COMEÇAR! CHEGOU A HORA DE MONTAR OS %d TERRITÓRIOS <<\n\n", MAX_TERRITORIOS);
                // Uso do comando FOR para fazer a leitura de cada dado armazenado sequencialmente no vetor Territorio
                for (int i = 0; i < MAX_TERRITORIOS; i++) {
                    printf(" --- CADASTRO DO %dº TERRITÓRIO ---\n", i + 1);

                    printf(" Digite o Nome do %dº Território: ", i + 1);
                    fgets(Territorio[i].nome, TAM_STRING, stdin);
                    Territorio[i].nome[strcspn(Territorio[i].nome, "\n")] = '\0';

                    printf(" Digite a Cor do Exército do %dº Território: ", i + 1);
                    fgets(Territorio[i].cor, TAM_STRING, stdin);
                    Territorio[i].cor[strcspn(Territorio[i].cor, "\n")] = '\0';

                    printf(" Digite o Número de Tropas: ");
                    scanf("%d", &Territorio[i].tropas);
                    clean_buffer();
                    printf("\n");
                }
                
                printf("\n=============================\n");
                printf(" MAPA DO MUNDO - ESTADO ATUAL\n");
                printf("=============================\n");

                //Listagem dos dados armazenados no vetor com o uso do comando FOR
                for (int i = 0; i < MAX_TERRITORIOS; i++) {
                    printf("\nTERRITÓRIO %d: ", i + 1);
                    printf("\n - Nome: %s", Territorio[i].nome);
                    printf("\n - Dominado por: Exército %s", Territorio[i].cor);
                    printf("\n - Tropas: %d", Territorio[i].tropas);
                    printf("\n");
                }
                
                printf("\n\n Pressione ENTER para continuar...");
                getchar();
                break;
                
            case 0:
                printf("\n\n Saindo...\n");
                break;

            default:
                printf(" OPÇÃO INVÁLIDA! Tente Novamente\n");
                printf(" Pressione ENTER para continuar...");
                getchar();
                break;
        }
    } while (opcao != 0);

    return 0;
}
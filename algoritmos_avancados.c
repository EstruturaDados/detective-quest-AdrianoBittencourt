#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*============================================================
    STRUCTS
============================================================*/

// Estrutura de cada cômodo da mansão
typedef struct Sala {
    char nome[50];
    char pista[100];  // pista opcional, pode estar vazia
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// Nó da árvore BST para pistas coletadas
typedef struct PistaNode {
    char pista[100];
    struct PistaNode *esquerda;
    struct PistaNode *direita;
} PistaNode;

/*============================================================
    FUNÇÕES DE CRIAÇÃO
============================================================*/

// Cria dinamicamente uma sala com nome e pista opcional
Sala* criarSala(char nome[], char pista[]) {
    Sala *nova = (Sala*) malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

// Cria dinamicamente um nó de pista para BST
PistaNode* criarPistaNode(char pista[]) {
    PistaNode *novo = (PistaNode*) malloc(sizeof(PistaNode));
    strcpy(novo->pista, pista);
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

/*============================================================
    FUNÇÕES DA ÁRVORE DE PISTAS (BST)
============================================================*/

// Insere uma pista na BST de forma ordenada
PistaNode* inserirPista(PistaNode *raiz, char pista[]) {
    if (raiz == NULL)
        return criarPistaNode(pista);

    if (strcmp(pista, raiz->pista) < 0)
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    else if (strcmp(pista, raiz->pista) > 0)
        raiz->direita = inserirPista(raiz->direita, pista);

    // Se for igual, não insere duplicada
    return raiz;
}

// Exibe todas as pistas em ordem alfabética
void exibirPistas(PistaNode *raiz) {
    if (raiz == NULL) return;
    exibirPistas(raiz->esquerda);
    printf("- %s\n", raiz->pista);
    exibirPistas(raiz->direita);
}

/*============================================================
    FUNÇÃO DE EXPLORAÇÃO DA MANSÃO
============================================================*/

void explorarSalasComPistas(Sala *atual, PistaNode **arvorePistas) {
    char opcao;

    while (1) {
        printf("\nVocê está na sala: %s\n", atual->nome);

        if (strlen(atual->pista) > 0) {
            printf("Você encontrou uma pista: %s\n", atual->pista);
            *arvorePistas = inserirPista(*arvorePistas, atual->pista);
            // Evitar coletar a mesma pista novamente
            atual->pista[0] = '\0';
        } else {
            printf("Nenhuma pista nesta sala.\n");
        }

        printf("Escolha o caminho: esquerda (e), direita (d), sair (s): ");
        scanf(" %c", &opcao);

        if (opcao == 's') {
            printf("Saindo da exploração...\n");
            break;
        } else if (opcao == 'e') {
            if (atual->esquerda != NULL)
                explorarSalasComPistas(atual->esquerda, arvorePistas);
            else
                printf("Não há sala à esquerda.\n");
        } else if (opcao == 'd') {
            if (atual->direita != NULL)
                explorarSalasComPistas(atual->direita, arvorePistas);
            else
                printf("Não há sala à direita.\n");
        } else {
            printf("Opção inválida! Tente novamente.\n");
        }

        // Depois de escolher, volta à sala atual
        break;
    }
}

/*============================================================
    FUNÇÃO PRINCIPAL
============================================================*/

int main() {
    // Criando o mapa fixo da mansão
    Sala *hall = criarSala("Hall de Entrada", "Chave misteriosa");
    Sala *cozinha = criarSala("Cozinha", "Pegada de sapato");
    Sala *biblioteca = criarSala("Biblioteca", "Carta rasgada");
    Sala *quarto = criarSala("Quarto", "Diário antigo");
    Sala *escritorio = criarSala("Escritório", "");

    // Ligando salas (árvore binária fixa)
    hall->esquerda = cozinha;
    hall->direita = biblioteca;
    cozinha->esquerda = quarto;
    cozinha->direita = escritorio;

    PistaNode *arvorePistas = NULL; // BST para pistas coletadas

    printf("=== Bem-vindo ao Detective Quest: Coleta de Pistas ===\n");

    explorarSalasComPistas(hall, &arvorePistas);

    printf("\n=== Todas as pistas coletadas em ordem alfabética ===\n");
    exibirPistas(arvorePistas);

    return 0;
}

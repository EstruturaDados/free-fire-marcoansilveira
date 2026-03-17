#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ----------------------------------------------------
// Código da Ilha – Nível Novato
// Sistema de Mochila de Sobrevivência
// ----------------------------------------------------

// Estrutura que representa um item da mochila
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

// ----------------------------------------------------
// Função para listar os itens da mochila
// ----------------------------------------------------
void listarItens(struct Item mochila[], int numItens) {

    printf("\n--- ITENS NA MOCHILA (%d/10) ---\n", numItens);
    printf("-------------------------------------------------\n");
    printf("NOME            | TIPO        | QUANTIDADE\n");
    printf("-------------------------------------------------\n");

    for (int i = 0; i < numItens; i++) {

        printf("%-15s | %-10s | %d\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }

    printf("-------------------------------------------------\n");
}

// ----------------------------------------------------
// Busca sequencial por nome
// ----------------------------------------------------
int buscarItem(struct Item mochila[], int numItens, char nome[]) {

    for (int i = 0; i < numItens; i++) {

        if (strcmp(mochila[i].nome, nome) == 0) {
            return i;
        }
    }

    return -1;
}

// ----------------------------------------------------
// Inserir item na mochila
// ----------------------------------------------------
void inserirItem(struct Item mochila[], int *numItens) {

    if (*numItens >= 10) {

        printf("\nMochila cheia!\n");
        return;
    }

    struct Item novo;

    printf("\n--- Adicionar Novo Item ---\n");

    printf("Nome do item: ");
    scanf("%s", novo.nome);

    printf("Tipo do item (arma, municao, cura, etc.): ");
    scanf("%s", novo.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    mochila[*numItens] = novo;

    (*numItens)++;

    printf("\nItem '%s' adicionado com sucesso!\n", novo.nome);

    listarItens(mochila, *numItens);
}

// ----------------------------------------------------
// Remover item da mochila
// ----------------------------------------------------
void removerItem(struct Item mochila[], int *numItens) {

    if (*numItens == 0) {

        printf("\nA mochila esta vazia!\n");
        return;
    }

    char nome[30];

    printf("\n--- Remover Item ---\n");
    printf("Digite o nome do item a ser removido: ");
    scanf("%s", nome);

    int pos = buscarItem(mochila, *numItens, nome);

    if (pos == -1) {

        printf("\nItem '%s' nao encontrado!\n", nome);
        return;
    }

    for (int i = pos; i < *numItens - 1; i++) {

        mochila[i] = mochila[i + 1];
    }

    (*numItens)--;

    printf("\nItem '%s' removido com sucesso!\n", nome);

    listarItens(mochila, *numItens);
}

// ----------------------------------------------------
// Menu principal
// ----------------------------------------------------
void exibirMenu(int numItens) {

    printf("\nMOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
    printf("===========================================\n");
    printf("Itens na Mochila: %d/10\n\n", numItens);

    printf("1. Adicionar Item\n");
    printf("2. Remover Item\n");
    printf("3. Listar Itens na Mochila\n");
    printf("0. Sair\n");

    printf("-------------------------------------------\n");
}

// ----------------------------------------------------
// Função principal
// ----------------------------------------------------
int main() {

    struct Item mochila[10];

    int numItens = 0;
    int opcao;

    do {

        exibirMenu(numItens);

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                inserirItem(mochila, &numItens);
                break;

            case 2:
                removerItem(mochila, &numItens);
                break;

            case 3:
                listarItens(mochila, numItens);
                break;

            case 0:
                printf("\nSaindo do sistema...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}
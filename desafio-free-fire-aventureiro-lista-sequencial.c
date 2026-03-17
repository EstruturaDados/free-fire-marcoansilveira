#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ----------------------------------------------------
// STRUCT ITEM
// ----------------------------------------------------
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

// Contadores
int comparacoesSeq = 0;
int comparacoesBin = 0;

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
// Inserir item na mochila
// ----------------------------------------------------
void inserirItem(struct Item mochila[], int *n) {

    if (*n >= 10) {
        printf("Mochila cheia!\n");
        return;
    }

    printf("Nome: ");
    scanf("%s", mochila[*n].nome);

    printf("Tipo do item (arma, municao, cura, etc.): ");
    scanf("%s", mochila[*n].tipo);

    printf("Quantidade: ");
    scanf("%d", &mochila[*n].quantidade);

    (*n)++;

    listarItens(mochila, *n);
}

// ----------------------------------------------------
// Remover item da mochila
// ----------------------------------------------------
void removerItem(struct Item mochila[], int *n) {

    char nome[30];
    printf("Nome para remover: ");
    scanf("%s", nome);

    for (int i = 0; i < *n; i++) {

        if (strcmp(mochila[i].nome, nome) == 0) {

            for (int j = i; j < *n - 1; j++) {
                mochila[j] = mochila[j + 1];
            }

            (*n)--;

            printf("Removido!\n");

            listarItens(mochila, *n);

            return;
        }
    }

    printf("Nao encontrado!\n");
}

// ----------------------------------------------------
// Busca sequencial por nome
// ----------------------------------------------------
int buscaSequencial(struct Item mochila[], int n, char nome[]) {

    comparacoesSeq = 0;

    for (int i = 0; i < n; i++) {

        comparacoesSeq++;

        if (strcmp(mochila[i].nome, nome) == 0) {
            return i;
        }
    }

    return -1;
}

// ----------------------------------------------------
// Ordenar itens 
// ----------------------------------------------------
void ordenar(struct Item mochila[], int n) {

    struct Item temp;

    for (int i = 0; i < n - 1; i++) {

        for (int j = 0; j < n - i - 1; j++) {

            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {

                temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }

    printf("Ordenado por nome!\n");
}

// ----------------------------------------------------
// Busca Binária 
// ----------------------------------------------------
int buscaBinaria(struct Item mochila[], int n, char nome[]) {

    int inicio = 0, fim = n - 1;
    comparacoesBin = 0;

    while (inicio <= fim) {

        int meio = (inicio + fim) / 2;

        comparacoesBin++;

        int cmp = strcmp(mochila[meio].nome, nome);

        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    return -1;
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
    printf("4. Buscar (pesquisa Binária) Item na Mochila\n");
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

        //printf("\n1 Inserir\n2 Remover\n3 Listar\n4 Buscar (Seq)\n5 Ordenar\n6 Buscar (Bin)\n0 Sair\n");
        //scanf("%d", &op);

        char nome[30];
        int pos;

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

            case 4:
                printf("Nome para pesquisa (Binária): ");
                scanf("%s", nome);

                pos = buscaSequencial(mochila, numItens, nome);

                printf("Pos: %d | Comparacoes: %d\n", pos, comparacoesSeq);
                break;

            case 5:
                ordenar(mochila, numItens);
                break;

            case 6:
                printf("Nome: ");
                scanf("%s", nome);

                pos = buscaBinaria(mochila, numItens, nome);

                printf("Pos: %d | Comparacoes: %d\n", pos, comparacoesBin);
                break;
        }

    } while (opcao != 0);

    return 0;
}
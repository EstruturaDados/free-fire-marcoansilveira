#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ----------------------------------------------------
// STRUCTS
// ----------------------------------------------------
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

struct No {
    struct Item dados;
    struct No* proximo;
};

int comparacoesSeq = 0;

// 🔧 PROTÓTIPOS (corrige erro de declaração implícita)
void listar(struct No* inicio);
int contarItens(struct No* inicio);

// ----------------------------------------------------
// Inserir item na mochila
// ----------------------------------------------------
void inserir(struct No** inicio) {

    struct No* novo = (struct No*) malloc(sizeof(struct No));

    printf("Nome: ");
    scanf("%s", novo->dados.nome);

    printf("Tipo do item (arma, municao, cura, etc.): ");
    scanf("%s", novo->dados.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = *inicio;
    *inicio = novo;

    listar(*inicio); // 🔧 CORREÇÃO
}

// ----------------------------------------------------
// Contar número de itens na mochila 
// ----------------------------------------------------
int contarItens(struct No* inicio) {

    int contador = 0;
    struct No* atual = inicio;

    while (atual != NULL) {
        contador++;
        atual = atual->proximo;
    }

    return contador;
}

// ----------------------------------------------------
// Função para listar os itens da mochila
// ----------------------------------------------------
void listar(struct No* inicio) {

    struct No* atual = inicio;

    printf("\n--- ITENS NA MOCHILA (%d/10) ---\n", contarItens(inicio));
    printf("-------------------------------------------------\n");
    printf("NOME            | TIPO        | QUANTIDADE\n");
    printf("-------------------------------------------------\n");

    while (atual != NULL) {

        printf("%s | %s | %d\n",
               atual->dados.nome,
               atual->dados.tipo,
               atual->dados.quantidade);

        atual = atual->proximo;
    }
}

// ----------------------------------------------------
// Remover item da mochila
// ----------------------------------------------------
void remover(struct No** inicio) {

    char nome[30];
    printf("Nome: ");
    scanf("%s", nome);

    struct No* atual = *inicio;
    struct No* anterior = NULL;

    while (atual != NULL) {

        if (strcmp(atual->dados.nome, nome) == 0) {

            if (anterior == NULL)
                *inicio = atual->proximo;
            else
                anterior->proximo = atual->proximo;

            free(atual);

            printf("Removido!\n");

            listar(*inicio); // 🔧 CORREÇÃO

            return;
        }

        anterior = atual;
        atual = atual->proximo;
    }

    printf("Nao encontrado!\n");
}

// ----------------------------------------------------
// Busca Sequencial 
// ----------------------------------------------------
struct No* buscar(struct No* inicio, char nome[]) {

    comparacoesSeq = 0;

    struct No* atual = inicio;

    while (atual != NULL) {

        comparacoesSeq++;

        if (strcmp(atual->dados.nome, nome) == 0) {
            return atual;
        }

        atual = atual->proximo;
    }

    return NULL;
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
    printf("4. Buscar (sequencial) Item na Mochila\n");
    printf("0. Sair\n");

    printf("-------------------------------------------\n");
}

// ----------------------------------------------------
// MAIN
// ----------------------------------------------------
int main() {

    struct No* inicio = NULL;
    int opcao;

    do {

        exibirMenu(contarItens(inicio));

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        char nome[30];
        struct No* res;

        switch (opcao) {

            case 1:
                inserir(&inicio);
                break;

            case 2:
                remover(&inicio);
                break;

            case 3:
                listar(inicio);
                break;

            case 4:
                printf("Nome: ");
                scanf("%s", nome);

                res = buscar(inicio, nome);

                if (res != NULL)
                    printf("Encontrado! Comparacoes: %d\n", comparacoesSeq);
                else
                    printf("Nao encontrado! Comparacoes: %d\n", comparacoesSeq);
                break;
        }

    } while (opcao != 0);

    return 0;
}
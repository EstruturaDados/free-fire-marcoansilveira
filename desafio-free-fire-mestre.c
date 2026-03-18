#include <stdio.h>
#include <string.h>

#define MAX_ITENS 20

// ===================== ESTRUTURA =====================
typedef struct {
    char nome[50];
    char tipo[20];
    int quantidade;
    int prioridade;
} Componente;

// ===================== VARIAVEIS GLOBAIS =====================
Componente mochila[MAX_ITENS];
int totalItens = 0;

// 0 = nao ordenado | 1 = nome | 2 = tipo | 3 = prioridade
int statusOrdenacao = 0;

// ===================== UTIL =====================
void trocar(Componente* a, Componente* b) {
    Componente temp = *a;
    *a = *b;
    *b = temp;
}

// ===================== LISTAR =====================
void listarInventario() {
    printf("\n--- INVENTARIO ATUAL (%d/%d) ---\n", totalItens, MAX_ITENS);
    printf("------------------------------------------------------------\n");
    printf("NOME            | TIPO        | QUANTIDADE | PRIORIDADE\n");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < totalItens; i++) {
        printf("%-15s | %-11s | %-10d | %d\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade,
               mochila[i].prioridade);
    }

    printf("------------------------------------------------------------\n");
}

// ===================== ADICIONAR =====================
void adicionarComponente() {
    if (totalItens >= MAX_ITENS) {
        printf("\nMochila cheia!\n");
        return;
    }

    Componente c;

    printf("\n--- Coletando Novo Componente ---\n");
    printf("Nome: ");
    scanf("%s", c.nome);

    printf("Tipo (Estrutural, Eletronico, Energia): ");
    scanf("%s", c.tipo);

    printf("Quantidade: ");
    scanf("%d", &c.quantidade);

    do {
        printf("Prioridade de Montagem (1-5): ");
        scanf("%d", &c.prioridade);
    } while (c.prioridade < 1 || c.prioridade > 5);

    mochila[totalItens++] = c;

    statusOrdenacao = 0;

    printf("\nComponente '%s' adicionado!\n", c.nome);
    listarInventario();

    printf("\nPressione Enter para continuar...");
    getchar(); getchar();
}

// ===================== REMOVER =====================
void removerComponente() {
    char nome[50];
    printf("\nNome do componente a remover: ");
    scanf("%s", nome);

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            totalItens--;
            statusOrdenacao = 0;

            printf("Componente removido!\n");
            return;
        }
    }

    printf("Componente nao encontrado!\n");
}

// ===================== ORDENACOES =====================
int ordenarPorNome() {
    int comparacoes = 0;

    for (int i = 0; i < totalItens - 1; i++) {
        for (int j = 0; j < totalItens - 1 - i; j++) {
            comparacoes++;
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                trocar(&mochila[j], &mochila[j + 1]);
            }
        }
    }

    statusOrdenacao = 1;
    return comparacoes;
}

int ordenarPorTipo() {
    int comparacoes = 0;

    for (int i = 0; i < totalItens - 1; i++) {
        for (int j = 0; j < totalItens - 1 - i; j++) {
            comparacoes++;
            if (strcmp(mochila[j].tipo, mochila[j + 1].tipo) > 0) {
                trocar(&mochila[j], &mochila[j + 1]);
            }
        }
    }

    statusOrdenacao = 2;
    return comparacoes;
}

int ordenarPorPrioridade() {
    int comparacoes = 0;

    for (int i = 0; i < totalItens - 1; i++) {
        int menor = i;

        for (int j = i + 1; j < totalItens; j++) {
            comparacoes++;
            if (mochila[j].prioridade < mochila[menor].prioridade) {
                menor = j;
            }
        }

        if (menor != i) {
            trocar(&mochila[i], &mochila[menor]);
        }
    }

    statusOrdenacao = 3;
    return comparacoes;
}

// ===================== BUSCA BINARIA =====================
int buscaBinaria(char nome[]) {
    int inicio = 0, fim = totalItens - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;

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

// ===================== MENU =====================
void exibirMenu() {
    printf("\n=============================================================\n");
    printf(" PLANO DE FUGA - CODIGO DA ILHA (NIVEL MESTRE)\n");
    printf("=============================================================\n");

    printf("Itens na Mochila: %d/%d\n", totalItens, MAX_ITENS);

    printf("Status da Ordenacao por Nome: ");
    if (statusOrdenacao == 0) printf("NAO ORDENADO\n");
    else if (statusOrdenacao == 1) printf("ORDENADO\n");
    else printf("NAO ORDENADO\n");

    printf("\n1. Adicionar Componente\n");
    printf("2. Descartar Componente\n");
    printf("3. Listar Componentes (Inventario)\n");
    printf("4. Organizar Mochila (Ordenar Componentes)\n");
    printf("5. Busca Binaria por Componente-Chave (por nome)\n");
    printf("0. ATIVAR TORRE DE FUGA (Sair)\n");
    printf("-------------------------------------------------------------\n");
}

// ===================== MAIN =====================
int main() {
    int opcao;

    do {
        exibirMenu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarComponente();
                break;

            case 2:
                removerComponente();
                break;

            case 3:
                listarInventario();
                printf("\nPressione Enter para continuar...");
                getchar(); getchar();
                break;

            case 4: {
                int criterio, comparacoes;

                printf("\n--- Estrategia de Organizacao ---\n");
                printf("1. Por Nome (Ordem Alfabetica)\n");
                printf("2. Por Tipo\n");
                printf("3. Por Prioridade de Montagem\n");
                printf("0. Cancelar\n");

                printf("Escolha o criterio: ");
                scanf("%d", &criterio);

                if (criterio == 1) {
                    comparacoes = ordenarPorNome();
                    printf("\nMochila organizada por NOME.\n");
                } else if (criterio == 2) {
                    comparacoes = ordenarPorTipo();
                    printf("\nMochila organizada por TIPO.\n");
                } else if (criterio == 3) {
                    comparacoes = ordenarPorPrioridade();
                    printf("\nMochila organizada por PRIORIDADE.\n");
                } else {
                    break;
                }

                printf("Analise de Desempenho: Foram necessarias %d comparacoes.\n", comparacoes);
                listarInventario();

                printf("\nPressione Enter para continuar...");
                getchar(); getchar();

                break;
            }

            case 5: {
                if (statusOrdenacao != 1) {
                    printf("\nALERTA: A busca binaria requer que a mochila esteja ordenada por NOME.\n");
                    printf("Use a Opcao 4 para organizar a mochila primeiro.\n");
                    break;
                }

                char nome[50];
                printf("\nDigite o nome do componente: ");
                scanf("%s", nome);

                int pos = buscaBinaria(nome);

                if (pos != -1) {
                    printf("\nComponente encontrado!\n");
                    printf("Nome %s | Tipo %s | Quantidade %d | Prioridade %d\n",
                           mochila[pos].nome,
                           mochila[pos].tipo,
                           mochila[pos].quantidade,
                           mochila[pos].prioridade);
                } else {
                    printf("\nComponente nao encontrado!\n");
                }

                break;
            }

        }

    } while (opcao != 0);

    printf("\nFuga ativada... Boa sorte!\n");

    return 0;
}
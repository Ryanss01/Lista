#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int dado;
    struct No *anterior;
    struct No *proximo;
} No;

typedef struct Lista {
    No *inicio;
    No *fim;
} Lista;

void inicializar(Lista *lista);
void inserirInicio(Lista *lista, int valor);
void inserirFinal(Lista *lista, int valor);
void inserirPosicao(Lista *lista, int valor, int posicao);
void removerInicio(Lista *lista);
void removerFinal(Lista *lista);
void removerValor(Lista *lista, int valor);
No *buscar(Lista *lista, int valor);
void imprimirDireto(Lista *lista);
void imprimirInverso(Lista *lista);
int contarElementos(Lista *lista);
void liberarLista(Lista *lista);

int main() {
    Lista lista;
    int opcao, valor, posicao;
    No *resultado;

    inicializar(&lista);

    do {
        printf("\n===== MENU =====\n");
        printf("1 - Inserir no inicio\n");
        printf("2 - Inserir no final\n");
        printf("3 - Inserir em uma posicao\n");
        printf("4 - Remover do inicio\n");
        printf("5 - Remover do final\n");
        printf("6 - Remover um valor\n");
        printf("7 - Buscar um valor\n");
        printf("8 - Imprimir do inicio ao final\n");
        printf("9 - Imprimir do final ao inicio\n");
        printf("10 - Contar elementos\n");
        printf("11 - Remover todos os elementos\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                 printf("Valor: ");
                 scanf("%d", &valor);
                 inserirInicio(&lista, valor);
                 printf("\nElemento inserido no inicio!\n");
                 break;

            case 2:
                 printf("Valor: ");
                 scanf("%d", &valor);
                 inserirFinal(&lista, valor);
                 printf("\nElemento inserido no final!\n");
                 break;

            case 3:
                printf("Valor: ");
                scanf("%d", &valor);
                printf("Posicao: ");
                scanf("%d", &posicao);
                inserirPosicao(&lista, valor, posicao);
                break;

            case 4:
                removerInicio(&lista);
                break;

            case 5:
                removerFinal(&lista);
                break;

            case 6:
                printf("Valor que deseja remover: ");
                scanf("%d", &valor);
                removerValor(&lista, valor);
                break;

            case 7:
                printf("Valor que deseja buscar: ");
                scanf("%d", &valor);
                resultado = buscar(&lista, valor);

                if (resultado != NULL)
                    printf("Valor encontrado.\n");
                else
                    printf("Valor nao encontrado.\n");
                break;

            case 8:
                imprimirDireto(&lista);
                break;

            case 9:
                imprimirInverso(&lista);
                break;

            case 10:
                printf("Quantidade de elementos: %d\n",
                       contarElementos(&lista));
                break;

            case 11:
                liberarLista(&lista);
                printf("Todos os elementos foram removidos.\n");
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    liberarLista(&lista);

    return 0;
}

void inicializar(Lista *lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
}

void inserirInicio(Lista *lista, int valor) {
    No *novo = (No *) malloc(sizeof(No));

    if (novo == NULL) {
        printf("Erro ao alocar memoria.\n");
        return;
    }

    novo->dado = valor;
    novo->anterior = NULL;
    novo->proximo = lista->inicio;

    if (lista->inicio != NULL)
        lista->inicio->anterior = novo;
    else
        lista->fim = novo;

    lista->inicio = novo;
}

void inserirFinal(Lista *lista, int valor) {
    No *novo = (No *) malloc(sizeof(No));

    if (novo == NULL) {
        printf("Erro ao alocar memoria.\n");
        return;
    }

    novo->dado = valor;
    novo->proximo = NULL;
    novo->anterior = lista->fim;

    if (lista->fim != NULL)
        lista->fim->proximo = novo;
    else
        lista->inicio = novo;

    lista->fim = novo;
}

void inserirPosicao(Lista *lista, int valor, int posicao) {
    No *atual;
    No *novo;
    int i;

    if (posicao < 1 || posicao > contarElementos(lista) + 1) {
        printf("Posicao invalida.\n");
        return;
    }

    if (posicao == 1) {
        inserirInicio(lista, valor);
        return;
    }

    if (posicao == contarElementos(lista) + 1) {
        inserirFinal(lista, valor);
        return;
    }

    atual = lista->inicio;

    for (i = 1; i < posicao; i++)
        atual = atual->proximo;

    novo = (No *) malloc(sizeof(No));

    if (novo == NULL) {
        printf("Erro ao alocar memoria.\n");
        return;
    }

    novo->dado = valor;
    novo->anterior = atual->anterior;
    novo->proximo = atual;

    atual->anterior->proximo = novo;
    atual->anterior = novo;
}

void removerInicio(Lista *lista) {
    No *aux;

    if (lista->inicio == NULL) {
        printf("A lista esta vazia.\n");
        return;
    }

    aux = lista->inicio;
    lista->inicio = aux->proximo;

    if (lista->inicio != NULL)
        lista->inicio->anterior = NULL;
    else
        lista->fim = NULL;

    free(aux);
}

void removerFinal(Lista *lista) {
    No *aux;

    if (lista->fim == NULL) {
        printf("A lista esta vazia.\n");
        return;
    }

    aux = lista->fim;
    lista->fim = aux->anterior;

    if (lista->fim != NULL)
        lista->fim->proximo = NULL;
    else
        lista->inicio = NULL;

    free(aux);
}

No *buscar(Lista *lista, int valor) {
    No *atual = lista->inicio;

    while (atual != NULL) {
        if (atual->dado == valor)
            return atual;

        atual = atual->proximo;
    }

    return NULL;
}

void removerValor(Lista *lista, int valor) {
    No *aux = buscar(lista, valor);

    if (aux == NULL) {
        printf("Valor nao encontrado.\n");
        return;
    }

    if (aux == lista->inicio) {
        removerInicio(lista);
        return;
    }

    if (aux == lista->fim) {
        removerFinal(lista);
        return;
    }

    aux->anterior->proximo = aux->proximo;
    aux->proximo->anterior = aux->anterior;
    free(aux);
}

void imprimirDireto(Lista *lista) {
    No *atual = lista->inicio;

    if (atual == NULL) {
        printf("A lista esta vazia.\n");
        return;
    }

    while (atual != NULL) {
        printf("%d ", atual->dado);
        atual = atual->proximo;
    }

    printf("\n");
}

void imprimirInverso(Lista *lista) {
    No *atual = lista->fim;

    if (atual == NULL) {
        printf("A lista esta vazia.\n");
        return;
    }

    while (atual != NULL) {
        printf("%d ", atual->dado);
        atual = atual->anterior;
    }

    printf("\n");
}

int contarElementos(Lista *lista) {
    int quantidade = 0;
    No *atual = lista->inicio;

    while (atual != NULL) {
        quantidade++;
        atual = atual->proximo;
    }

    return quantidade;
}

void liberarLista(Lista *lista) {
    No *atual = lista->inicio;
    No *aux;

    while (atual != NULL) {
        aux = atual;
        atual = atual->proximo;
        free(aux);
    }

    lista->inicio = NULL;
    lista->fim = NULL;
}

#include <stdio.h>
#include <stdlib.h>

// ===== TÓPICO 1 - ESTRUTURA DE DADOS =====
// Cada elemento armazena um valor e os endereços dos elementos vizinhos.
typedef struct No {
    int dado;
    struct No *anterior;
    struct No *proximo;
} No;

// A lista mantém referências ao primeiro e ao último elemento.
typedef struct Lista {
    No *inicio;
    No *fim;
} Lista;

// Protótipos das funções
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


// ===== TÓPICO 2 - INICIALIZAÇÃO E INSERÇÕES =====

// Inicializa a lista sem elementos.
void inicializar(Lista *lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
}

// Adiciona um valor à primeira posição da lista.
void inserirInicio(Lista *lista, int valor) {
    No *novo = (No *) malloc(sizeof(No));

    if (novo == NULL) {
        printf("Erro ao alocar memória.\n");
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

// Acrescenta um valor ao final da lista.
void inserirFinal(Lista *lista, int valor) {
    No *novo = (No *) malloc(sizeof(No));

    if (novo == NULL) {
        printf("Erro ao alocar memória.\n");
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

// Adiciona um valor à posição indicada pelo usuário.
void inserirPosicao(Lista *lista, int valor, int posicao) {
    No *atual;
    No *novo;
    int i;

    if (posicao < 1 || posicao > contarElementos(lista) + 1) {
        printf("Posição inválida.\n");
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
        printf("Erro ao alocar memória.\n");
        return;
    }

    novo->dado = valor;
    novo->anterior = atual->anterior;
    novo->proximo = atual;

    atual->anterior->proximo = novo;
    atual->anterior = novo;
}


// ===== TÓPICO 3 - REMOÇÃO DE ELEMENTOS =====

// Exclui o primeiro elemento da lista.
void removerInicio(Lista *lista) {
    No *aux;

    if (lista->inicio == NULL) {
        printf("A lista está vazia.\n");
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

// Exclui o último elemento da lista.
void removerFinal(Lista *lista) {
    No *aux;

    if (lista->fim == NULL) {
        printf("A lista está vazia.\n");
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

// Localiza e exclui a primeira ocorrência do valor informado.
void removerValor(Lista *lista, int valor) {
    No *aux = buscar(lista, valor);

    if (aux == NULL) {
        printf("Valor não encontrado.\n");
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


// ===== TÓPICO 4 - BUSCA, PERCORRIMENTO E CONTAGEM =====

// Procura o valor e retorna o endereço do elemento encontrado ou NULL.
No *buscar(Lista *lista, int valor) {
    No *atual = lista->inicio;

    while (atual != NULL) {
        if (atual->dado == valor)
            return atual;

        atual = atual->proximo;
    }

    return NULL;
}

// Exibe os valores do início ao final.
void imprimirDireto(Lista *lista) {
    No *atual = lista->inicio;

    if (atual == NULL) {
        printf("A lista está vazia.\n");
        return;
    }

    while (atual != NULL) {
        printf("%d ", atual->dado);
        atual = atual->proximo;
    }

    printf("\n");
}

// Exibe os valores do final ao início.
void imprimirInverso(Lista *lista) {
    No *atual = lista->fim;

    if (atual == NULL) {
        printf("A lista está vazia.\n");
        return;
    }

    while (atual != NULL) {
        printf("%d ", atual->dado);
        atual = atual->anterior;
    }

    printf("\n");
}

// Retorna a quantidade de elementos armazenados.
int contarElementos(Lista *lista) {
    int quantidade = 0;
    No *atual = lista->inicio;

    while (atual != NULL) {
        quantidade++;
        atual = atual->proximo;
    }

    return quantidade;
}


// ===== TÓPICO 5 - MENU PRINCIPAL =====
// O menu lê a opção escolhida e chama a operação correspondente.
int main() {
    Lista lista;
    int opcao, valor, posicao;
    No *resultado;

    inicializar(&lista);

    do {
        printf("\n===== MENU =====\n");
        printf("1 - Inserir no início\n");
        printf("2 - Inserir no final\n");
        printf("3 - Inserir em uma posição\n");
        printf("4 - Remover do início\n");
        printf("5 - Remover do final\n");
        printf("6 - Remover um valor\n");
        printf("7 - Buscar um valor\n");
        printf("8 - Exibir do início ao final\n");
        printf("9 - Exibir do final ao início\n");
        printf("10 - Contar elementos\n");
        printf("11 - Remover todos os elementos\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Valor: ");
                scanf("%d", &valor);
                inserirInicio(&lista, valor);
                break;

            case 2:
                printf("Valor: ");
                scanf("%d", &valor);
                inserirFinal(&lista, valor);
                break;

            case 3:
                printf("Valor: ");
                scanf("%d", &valor);
                printf("Posição: ");
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
                printf("Valor que deseja excluir: ");
                scanf("%d", &valor);
                removerValor(&lista, valor);
                break;

            case 7:
                printf("Valor que deseja procurar: ");
                scanf("%d", &valor);
                resultado = buscar(&lista, valor);

                if (resultado != NULL)
                    printf("Valor encontrado.\n");
                else
                    printf("Valor não encontrado.\n");
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
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    liberarLista(&lista);

    return 0;
}


// ===== TÓPICO 6 - LIBERAÇÃO DA MEMÓRIA =====
// Percorre a lista, libera cada elemento e redefine início e fim como NULL.
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

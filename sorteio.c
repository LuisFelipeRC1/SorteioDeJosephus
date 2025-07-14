#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct participante {
    struct participante *proxParticipante;
    int cpf;
    char nome[50];
} Participante;

typedef struct {
    Participante *inicio;
    Participante *fim;
    int quantidade;
} Lista;

void inicializa(Lista *lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->quantidade = 0;
}

int adicionarParticipante(Lista *lista, char nome[], int cpf) {
    Participante *novo = (Participante *)malloc(sizeof(Participante));
    if (!novo) return -1;

    strcpy(novo->nome, nome);
    novo->cpf = cpf;

    if (lista->quantidade == 0) {
        lista->inicio = novo;
        lista->fim = novo;
        novo->proxParticipante = novo;
    } else {
        lista->fim->proxParticipante = novo;
        novo->proxParticipante = lista->inicio;
        lista->fim = novo;
    }

    lista->quantidade++;
    return 0;
}


void mostrarParticipantes(Lista *lista) {
    if (lista->quantidade == 0) {
        printf("Nenhum participante na lista.\n");
        return;
    }

    Participante *atual = lista->inicio;
    printf("\nParticipantes restantes:\n");
    for (int i = 0; i < lista->quantidade; i++) {
        printf("Nome: %s | CPF: %d\n", atual->nome, atual->cpf);
        atual = atual->proxParticipante;
    }
}

void eliminarParticipante(Lista *lista, int m) {
    Participante *atual = lista->inicio;
    Participante *anterior = lista->fim;

    for (int i = 1; i < m; i++) {
        anterior = atual;
        atual = atual->proxParticipante;
    }

    printf("\nNúmero sorteado: %d\n", m);
    printf("Eliminado: %s | CPF: %d\n", atual->nome, atual->cpf);

    if (atual == lista->inicio)
        lista->inicio = atual->proxParticipante;
    if (atual == lista->fim)
        lista->fim = anterior;

    anterior->proxParticipante = atual->proxParticipante;

    free(atual);
    lista->quantidade--;

    mostrarParticipantes(lista);
}


void liberarLista(Lista *lista) {
    if (lista->quantidade == 0) return;

    Participante *atual = lista->inicio;
    Participante *prox;

    for (int i = 0; i < lista->quantidade; i++) {
        prox = atual->proxParticipante;
        free(atual);
        atual = prox;
    }
}



int main() {
    Lista *lista = malloc(sizeof(Lista));
    if (!lista) {
        return -1;
    }
    inicializa(lista);

    int n;
    printf("Quantos participantes? ");
    scanf("%d", &n);
    getchar();  

    for (int i = 0; i < n; i++) {
        char nome[50];
        int cpf;

        printf("Nome do participante %d: ", i + 1);
        fgets(nome, sizeof(nome), stdin);
        nome[strcspn(nome, "\n")] = '\0'; 

        printf("CPF do participante %d: ", i + 1);
        scanf("%d", &cpf);
        getchar();  

        adicionarParticipante(lista, nome, cpf);
    }

    srand(time(NULL)); 

    while (lista->quantidade > 1) {
        int m = (rand() % lista->quantidade) + 1;
        eliminarParticipante(lista, m);
    }

    printf("\n VENCEDOR \n");
    printf("Nome: %s | CPF: %d\n", lista->inicio->nome, lista->inicio->cpf);

    free(lista->inicio);  
    free(lista);          
    return 0;
}

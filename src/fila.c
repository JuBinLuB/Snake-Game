#include <stdio.h>
#include <stdlib.h>

#include "fila.h"

void FFVazia(TFila *Fila) {
    Fila->frente = (TCelula *)malloc(sizeof(TCelula));
    Fila->tras = Fila->frente;
    Fila->frente->prox = NULL;
    Fila->tamanho = 0;
}

int VaziaF(TFila Fila) {
    return (Fila.frente == Fila.tras);
}

void Enfileirar(TItem Item, TFila *Fila) {
    Fila->tras->prox = (TCelula *)malloc(sizeof(TCelula));
    Fila->tras = Fila->tras->prox;
    Fila->tras->item = Item;
    Fila->tras->prox = NULL;
    Fila->tamanho++;
}

void Desenfileirar(TFila *Fila, TItem *Item) {
    TCelula *Aux;

    if (!VaziaF(*Fila)) {
        Aux = Fila->frente->prox;
        Fila->frente->prox = Aux->prox;
        *Item = Aux->item;
        free(Aux);

        if (Fila->frente->prox == NULL) {
            Fila->tras = Fila->frente;
        }
        Fila->tamanho--;
    }
}

void LiberarFila(TFila *Fila) {
    while (!VaziaF(*Fila)) {
        Desenfileirar(Fila, &Fila->frente->item);
    }
    free(Fila->frente);
}

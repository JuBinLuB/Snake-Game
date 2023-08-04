#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "util.h"

typedef struct fila {
    TCelula *frente;
    TCelula *tras;
    int tamanho;
} TFila;

void FFVazia(TFila *Fila);

int VaziaF(TFila Fila);

void Enfileirar(TItem Item, TFila *Fila);

void Desenfileirar(TFila *Fila, TItem *Item);

void LiberarFila(TFila *Fila);

#endif // FILA_H_INCLUDED

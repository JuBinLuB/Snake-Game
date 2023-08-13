#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    VERMELHO = 1,
    VERDE,
    AZUL,
    AMARELO,
    MARROM,
    LILAS
} TCor;

typedef struct {
    int x;
    int y;
    TCor cor;
} TItem;

typedef struct celula {
    TItem item;
    struct celula *prox;
} TCelula;

#endif // UTIL_H_INCLUDED

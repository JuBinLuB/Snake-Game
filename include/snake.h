#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <time.h>

#include "fila.h"

void Configurar();

void IniciarCampo(int x, int y);

void DesenharCampo();

void DesenharMoldura(int x, int y);

void DesenharComida();

void DesenharCobra();

void VerificarColisoes();

void VerificarComida();

void Mover(int key);

void Randomizar(TItem *item);

#endif // SNAKE_H_INCLUDED

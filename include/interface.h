#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>

#include "snake.h"

#define ALTURA 20
#define LARGURA 20
#define VELOCIDADE 14

void ConfigurarJanela();

void TratarEventos();

void MenuPrincipal();

void Inicializa();

void Desenha();

void DesenhaTexto(void *font, char *string);

void AlteraTamanhoJanela(GLsizei w, GLsizei h);

void Timer(int valor);

void TeclasEspeciais(int key, int x, int y);

void Teclado(unsigned char key, int x, int y);

#endif // INTERFACE_H_INCLUDED

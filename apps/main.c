#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>

#include "interface.h"

int main(int argc, char **argv) {
    // Inicializacao da GLUT.
    glutInit(&argc, argv);

    // Define o modo de operação da Glut.
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    // Configuracoes da Janela.
    ConfigurarJanela();

    // Tratamento de eventos e funcoes callback.
    TratarEventos();

    // Inicializacao de parametros.
    Inicializa();

    // Inicia o processamento e aguarda interacoes do usuario.
    glutMainLoop();
    return 0;
}

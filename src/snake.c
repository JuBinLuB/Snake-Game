#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/gl.h>
#include <GL/glut.h>

#include "snake.h"

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

#define CORES 3

/***********************************
 *   DEFINICAO DE VARIAVEIS GLOBAIS
 ***********************************/
TFila snake;
TItem apple;
int LARGURA;
int ALTURA;
int DIRECAO;
int EATEN;
int SCORE;

void IniciarCampo(int x, int y) {
    LARGURA = x;
    ALTURA = y;
}

void Configurar() {
    // Cria a Fila que ira representar a snake.
    FFVazia(&snake);

    // Define a posicao inicial da snake como sendo o centro da arena.
    snake.frente->item.x = LARGURA / 2;
    snake.frente->item.y = ALTURA / 2;

    // Define a direcao inicial de movimento.
    DIRECAO = RIGHT;

    // Inicializacao de demais variaveis.
    EATEN = 1;
    SCORE = 0;
}

void DesenharCampo() {
    for (int i = 1; i < LARGURA; i++) {
        for (int j = 1; j < ALTURA; j++) {
            DesenharMoldura(i, j);
        }
    }
}

void DesenharMoldura(int x, int y) {
    // Altera o tamanho do ponto.
    glPointSize(2);

    // Especificacao de primitivas graficas.
    glBegin(GL_POINTS);
        // Define a cor do ponto.
        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(x, y);
    glEnd();
}

void DesenharComida() {
    if (EATEN) {
        // Gera coordenadas aleatorias para a comida.
        Randomizar(&apple);
    }

    // Define o valor da variavel como falso.
    EATEN = 0;

    // Define a cor da comida.
    glColor3f(1.0, 0.0, 0.0); 

    // Desenha a comida.
    glRectd(apple.x, apple.y, apple.x + 1, apple.y + 1);
}

void DesenharCobra() {
    // Altera a DIRECAO do movimento da snake baseado nas interacoes do usuario.
    switch(DIRECAO) {
    case UP:
        snake.frente->item.y++;
        break;
    case DOWN:
        snake.frente->item.y--;
        break;
    case RIGHT:
        snake.frente->item.x++;
        break;
    case LEFT:
        snake.frente->item.x--;
        break;
    }

    // Define a cor da cabeca da snake.
    glColor3f(0.5, 1.0, 0.5);

    // Desenha a cabeca da snake.
    glRectd(snake.frente->item.x, snake.frente->item.y, snake.frente->item.x + 1, snake.frente->item.y + 1);

    // Verifica se a cabeca cruzou a borda esquerda da arena.
    VerificarColisoes();

    // Verifica se comeu a comida.
    VerificarComida();
}

void VerificarColisoes() {
    // Verifica se a cabeca cruzou a borda esquerda da arena.
    if (snake.frente->item.x < 0) {
        snake.frente->item.x = LARGURA - 1;
    }
    // Verifica se a cabeca cruzou a borda direita da arena.
    if (snake.frente->item.x > LARGURA - 1) {
        snake.frente->item.x = 0;
    }
    // Verifica se a cabeca cruzou a borda inferior da arena.
    if (snake.frente->item.y < 0) {
        snake.frente->item.y = ALTURA - 1;
    }
    // Verifica se a cabeca cruzou a borda superior da arena.
    if (snake.frente->item.y > ALTURA - 1) {
        snake.frente->item.y = 0;
    }
}

void VerificarComida() {
    // Verificando se a cobra comeu a comida.
    if ((snake.frente->item.x == apple.x) && (snake.frente->item.y == apple.y)) {
        EATEN = 1;
        // SCORE++;
    }
}

void Mover(int key) {
    // Logica para a leitura da entrada de dados pelo teclado.
    switch (key) {
    case GLUT_KEY_UP:
        if (DIRECAO != DOWN) {
            DIRECAO = UP;
        }
        break;
    case GLUT_KEY_DOWN:
        if (DIRECAO != UP) {
            DIRECAO = DOWN;
        }
        break;
    case GLUT_KEY_LEFT:
        if (DIRECAO != RIGHT) {
            DIRECAO = LEFT;
        }
        break;
    case GLUT_KEY_RIGHT:
        if (DIRECAO != LEFT) {
            DIRECAO = RIGHT;
        }
        break;
    case GLUT_KEY_F1:
        // Liberando a memoria alocada para a SNAKE.
        LiberarFila(&snake);

        // Finaliza a aplicacao.
        exit(0);
        break;
    }
}

void Randomizar(TItem *item) {
    srand(time(NULL));
    item->x = 1 + rand() % (LARGURA - 2);
    item->y = 1 + rand() % (ALTURA - 2);
    // item->cor = 1 + rand() % CORES;
}

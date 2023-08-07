#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <time.h>

#include "snake.h"

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

// #define CORES 3

/********************************************
 * VARIAVEIS GLOBAIS
 ********************************************/
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
    snake.tras->item.x = LARGURA / 2;
    snake.tras->item.y = ALTURA / 2;

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
    glPointSize(1.88);

    // Especificacao de primitivas graficas.
    glBegin(GL_POINTS);
        // Define a cor do ponto.
        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(x, y);
    glEnd();
}

void GerarComida() {
    srand(time(NULL));
    apple.x = 1 + rand() % (LARGURA - 1);
    apple.y = 1 + rand() % (ALTURA - 1);
}

void DesenharComida() {
    if (EATEN) {
        // Gera coordenadas aleatorias para a comida.
        GerarComida();
    }

    // Define o valor da variavel como falso.
    EATEN = 0;

    // Define a cor da comida.
    glColor3f(1.0, 0.5, 0.5); 

    // Desenha a comida.
    glRectd(apple.x, apple.y, apple.x + 1, apple.y + 1);
}

void DesenharCobra() {
    // Gera uma nova celula na direcao do movimento.
    Enfileirar(snake.tras->item, &snake);

    // Altera a DIRECAO do movimento da snake baseado nas interacoes do usuario.
    switch(DIRECAO) {
    case UP:
        // snake.frente->item.y++;
        snake.tras->item.y++;
        break;
    case DOWN:
        // snake.frente->item.y--;
        snake.tras->item.y--;
        break;
    case RIGHT:
        // snake.frente->item.x++;
        snake.tras->item.x++;
        break;
    case LEFT:
        // snake.frente->item.x--;
        snake.tras->item.x--;
        break;
    }

    // Celula auxiliar para percorrer a Fila e desenhar o corpo da snake.
    TCelula *SnakeCorpo = snake.frente;

    for (int i = 0; i < snake.tamanho; i++) {
        if (SnakeCorpo != snake.frente) {
            // Define a cor do corpo da snake.
            glColor3f(0.6, 0.88, 0.6);

            // Desenha o corpo da snake.
            glRectd(SnakeCorpo->item.x, SnakeCorpo->item.y, SnakeCorpo->item.x + 1, SnakeCorpo->item.y + 1);
        } else {
            // Define a cor da cabeca da snake.
            glColor3f(0.5, 1.0, 0.5);

            // Desenha a cabeca da snake.
            glRectd(snake.tras->item.x, snake.tras->item.y, snake.tras->item.x + 1, snake.tras->item.y + 1);
        }
        // Avanca "SnakeCorpo" para a proxima posicao da Fila.
        SnakeCorpo = SnakeCorpo->prox;
    }

    // Verifica se a snake colidiu consigo mesma ou cruzou as bordas da arena.
    VerificarColisoes();

    // Verifica se comeu a comida.
    VerificarComida();
}

void MoverCobra(int key) {
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
    default:
        // Liberando a memoria alocada para a SNAKE.
        LiberarFila(&snake);
        // Finaliza a aplicacao.
        exit(0);
        break;
    }
}

void VerificarColisoes() {
    // Verifica se a cabeca cruzou a borda esquerda da arena.
    if (snake.tras->item.x < 0) {
        snake.tras->item.x = LARGURA - 1;
    }
    // Verifica se a cabeca cruzou a borda direita da arena.
    if (snake.tras->item.x > LARGURA - 1) {
        snake.tras->item.x = 0;
    }
    // Verifica se a cabeca cruzou a borda inferior da arena.
    if (snake.tras->item.y < 0) {
        snake.tras->item.y = ALTURA - 1;
    }
    // Verifica se a cabeca cruzou a borda superior da arena.
    if (snake.tras->item.y > ALTURA - 1) {
        snake.tras->item.y = 0;
    }

    // Celula auxiliar para percorrer a Fila.
    TCelula *Aux = snake.frente;

    // Verifica se a snake colidiu consigo mesma.
    for (int i = 0; i < snake.tamanho; i++) {
        if (snake.tras->item.x == Aux->item.x && snake.tras->item.y == Aux->item.y) {
            // Libera a memoria alocada para a SNAKE.
            LiberarFila(&snake);
            // Finaliza a aplicacao.
            exit(0);
        }
        Aux = Aux->prox;
    }
}

void VerificarComida() {
    // Celula auxiliar representando a cauda da snake.
    TCelula *SnakeCauda = snake.frente;

    // Verificando se a cobra comeu a comida.
    if ((snake.tras->item.x == apple.x) && (snake.tras->item.y == apple.y)) {
        EATEN = 1;
        SCORE++;
    } else {
        // Desenfileira a cauda para manter o tamanho da snake.
        Desenfileirar(&snake, &SnakeCauda->item);
    }
}

void ConfigurarPlacar(char *string) {
    strcpy(string, "SCORE: ");

    // String auxiliar para armazenar o SCORE.
    char textoScore[10];

    // Convertendo o inteiro "SCORE" em texto e armazenando-o na string "textoScore".
    sprintf(textoScore, "%d", SCORE);

    // Concatenando a string "textoScore" ao final de "string".
    strcat(string, textoScore);
}

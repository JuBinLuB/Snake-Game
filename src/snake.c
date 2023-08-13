#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <time.h>
#include <string.h>

#include "snake.h"

// Variaveis globais.
TFila snake;
TItem comida;
int LARGURA;
int ALTURA;
int DIRECAO;
int CONSUMIDO;
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

    // Define a cor inicial da cabeca da cobra.
    snake.tras->item.cor = 1 + rand() % CORES;

    // Define a direcao inicial de movimento.
    DIRECAO = RIGHT;

    // Inicializacao de demais variaveis.
    CONSUMIDO = 1;
    SCORE = 0;
}

void DesenharCampo() {
    // Desenha a grade pontilhada do campo.
    for (int i = 0; i <= LARGURA; i++) {
        for (int j = 0; j <= ALTURA; j++) {
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

void DesenharComida() {
    if (CONSUMIDO) {
        // Gera coordenadas aleatorias para a comida.
        GerarComida();
        
        // Define o valor da variavel como falso.
        CONSUMIDO = 0;
    }

    // Define a cor da comida.
    if (comida.cor == VERMELHO) {
        // Define a cor como VERMELHO.
        glColor3f(1.0, 0.5, 0.5);
    } else if (comida.cor == VERDE) {
        // Define a cor como VERDE.
        glColor3f(0.5, 1.0, 0.5);
    } else if (comida.cor == AZUL) {
        // Define a cor como AZUL.
        glColor3f(0.5, 0.5, 1.0);
    } else if (comida.cor == AMARELO) {
        // Define a cor como AMARELO.
        glColor3f(1.0, 1.0, 0.0);
    } else if (comida.cor == MARROM) {
        // Define a cor como MARROM.
        glColor3f(0.4, 0.2, 0.2);
    } else if (comida.cor == LILAS) {
        // define a cor como LILAS.
        glColor3f(2.0, 0.5, 1.5);
    }

    // Desenha a comida.
    glRectd(comida.x, comida.y, comida.x + 1, comida.y + 1);
}

void GerarComida() {
    srand(time(NULL));
    comida.x = 1 + rand() % (LARGURA - 1);
    comida.y = 1 + rand() % (ALTURA - 1);
    comida.cor = 1 + rand() % CORES;
}

void DesenharCobra() {
    // Gera uma nova celula na direcao do movimento.
    Enfileirar(snake.tras->item, &snake);

    // Altera a DIRECAO do movimento da snake baseado nas interacoes do usuario.
    switch(DIRECAO) {
    case UP:
        snake.tras->item.y++;
        break;
    case DOWN:
        snake.tras->item.y--;
        break;
    case RIGHT:
        snake.tras->item.x++;
        break;
    case LEFT:
        snake.tras->item.x--;
        break;
    }

    // Atualiza as cores dos segmentos do corpo da snake.
    AtualizarCoresCobra();

    // Celula auxiliar para percorrer a Fila e desenhar o corpo da snake.
    TCelula *SnakeCorpo = snake.frente;

    for (int i = 0; i < snake.tamanho; i++) {
        if (SnakeCorpo != snake.frente) {
            // Define a cor do corpo da snake.
            if (SnakeCorpo->item.cor == VERMELHO) {
                // Define a cor como VERMELHO.
                glColor3f(0.88, 0.6, 0.6);
            } else if (SnakeCorpo->item.cor == VERDE) {
                // Define a cor como VERDE.
                glColor3f(0.6, 0.88, 0.6);
            } else if (SnakeCorpo->item.cor == AZUL) {
                // Define a cor como AZUL.
                glColor3f(0.6, 0.6, 0.88);
            } else if (SnakeCorpo->item.cor == AMARELO) {
                // Define a cor como AMARELO.
                glColor3f(88.0, 88.0, 0.2);
            } else if (SnakeCorpo->item.cor == MARROM) {
                // Define a cor como MARROM.
                glColor3f(0.38, 0.18, 0.18);
            } else if (SnakeCorpo->item.cor == LILAS) {
                // define a cor como LILAS.
                glColor3f(1.88, 0.6, 1.6);
            }

            // Desenha o corpo da snake.
            glRectd(SnakeCorpo->item.x, SnakeCorpo->item.y, SnakeCorpo->item.x + 1, SnakeCorpo->item.y + 1);
        } else {
            // Define a cor da cabeca da snake.
            if (snake.tras->item.cor == VERMELHO) {
                // Define a cor como VERMELHO.
                glColor3f(1.0, 0.5, 0.5);
            } else if (snake.tras->item.cor == VERDE) {
                // Define a cor como VERDE.
                glColor3f(0.5, 1.0, 0.5);
            } else if (snake.tras->item.cor == AZUL) {
                // Define a cor como AZUL.
                glColor3f(0.5, 0.5, 1.0);
            } else if (snake.tras->item.cor == AMARELO) {
                // Define a cor como AMARELO.
                glColor3f(1.0, 1.0, 0.0);
            } else if (snake.tras->item.cor == MARROM) {
                // Define a cor como MARROM.
                glColor3f(0.4, 0.2, 0.2);
            } else if (snake.tras->item.cor == LILAS) {
                // define a cor como LILAS.
                glColor3f(2.0, 0.5, 1.5);
            }

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

void AtualizarCoresCobra() {
    // Celula auxiliar para percorrer a Fila e atualizar as cores dos segmentos do corpo da cobra.
    TCelula *Aux = snake.frente;

    // Armazena a cor do primeiro segmento.
    int corAnterior = Aux->item.cor;

    // Percorre os segmentos da snake ate o penultimo, o imediatamente anterior ao final da Fila.
    while (Aux->prox != snake.tras) {
        // Armazena a cor atual do segmento.
        int corAtual = Aux->prox->item.cor;

        // Atribui a cor do segmento anterior ao segmento atual.
        Aux->prox->item.cor = corAnterior;

        // Atualiza a cor anterior para a cor atual
        corAnterior = corAtual;

        // Avanca "Aux" para a proxima posicao da Fila.
        Aux = Aux->prox;
    }
}

void MoverCobra(int key) {
    // Logica para a leitura da entrada de dados, verificando os valores callback de teclado.
    switch (key) {
    case GLUT_KEY_UP:
        // Caso a tecla pressionada seja "UP" e "DIRECAO" for diferente de "DOWN", define a direcao para CIMA.
        if (DIRECAO != DOWN) {
            DIRECAO = UP;
        }
        break;
    case GLUT_KEY_DOWN:
        // Caso a tecla pressionada seja "DOWN" e "DIRECAO" for diferente de "UP", define a direcao para BAIXO.
        if (DIRECAO != UP) {
            DIRECAO = DOWN;
        }
        break;
    case GLUT_KEY_LEFT:
        // Caso a tecla pressionada seja "LEFT" e "DIRECAO" for diferente de "RIGHT", define a direcao para ESQUERDA.
        if (DIRECAO != RIGHT) {
            DIRECAO = LEFT;
        }
        break;
    case GLUT_KEY_RIGHT:
        // Caso a tecla pressionada seja "RIGTH" e "DIRECAO" for diferente de "LEFT", define a direcao para DIREITA.
        if (DIRECAO != LEFT) {
            DIRECAO = RIGHT;
        }
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
            // Libera a memoria alocada para a SNAKE e finaliza a aplicacao.
            EncerrarJogo();
        }
        Aux = Aux->prox;
    }
}

void VerificarComida() {
    // Celula auxiliar representando a cauda da snake.
    TCelula *SnakeCauda = snake.frente;

    // Verificando se a snake comeu a comida.
    if ((snake.tras->item.x == comida.x) && (snake.tras->item.y == comida.y)) {
        CONSUMIDO = 1;
        SCORE++;
        
        // Atribui a cor da comida ao segmento da snake que representa a cauda.
        SnakeCauda->item.cor = comida.cor;
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

void EncerrarJogo() {
    // Liberando a memoria alocada para a SNAKE.
    LiberarFila(&snake);

    // Finaliza a aplicacao.
    exit(0);
}

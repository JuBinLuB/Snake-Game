#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>

#include "interface.h"

// Variaveis globais.
int MENU_ABERTO = 1;

// Define o modo de operacao da Glut.
void ConfigurarJanela() {
    // Define as coordenadas X e Y onde ficara o canto superior esquerdo da janela.
    glutInitWindowPosition(450, 100);

    // Define a largura e a altura do tamanho da janela. 
    glutInitWindowSize(600, 600);

    // Cria a janela e define o texto que sera exibido na barra de titulo.
    glutCreateWindow("Snake");
}

// Tratamento de eventos e funcoes callback.
void TratarEventos() {
    // Responsavel por redesenhar a janela sempre que necessario.
    glutDisplayFunc(Desenha);

    // Trata o evento referente ao redimensionamento da janela.
    glutReshapeFunc(AlteraTamanhoJanela);

    // Responsavel por fazer a GLUT esperar milisegundos antes de chamar a funcao.
    glutTimerFunc(0, Timer, 0);

    // Trata o evento de pressionar teclas especiais do teclado.
    glutSpecialFunc(TeclasEspeciais);

    // Trata o evento de pressionar teclas ASCII.
    glutKeyboardFunc(Teclado);
}

void MenuPrincipal() {
    // Define a cor do texto.
    glColor3f(0.83, 0.82, 0.76);

    // Exibicao da opcao de menu "STAR GAME" na tela usando caracteres bitmap.
    glRasterPos2f((LARGURA - 4.95) / 2, (ALTURA / 2) + 2);
    DesenhaTexto(GLUT_BITMAP_HELVETICA_18, "[SPACE] START GAME");

    // Exibicao da opcao de menu "QUIT GAME" na tela usando caracteres bitmap.
    glRasterPos2f((LARGURA - 4.95) / 2, (ALTURA / 2));
    DesenhaTexto(GLUT_BITMAP_HELVETICA_18, "[ESC] QUIT GAME");
}

// Inicializacao de parametros.
void Inicializa() {
    // Define a cor de fundo da janela de visualizacao.
    glClearColor(0.14, 0.16, 0.18, 1.0);

    // Inicializa a grade do jogo.
    IniciarCampo(LARGURA, ALTURA);

    // Inicializa as configuracoes gerais do jogo.
    Configurar();
}

// Funcao callback chamada para fazer o desenho da janela.
void Desenha() {
    // Limpa a janela de visualizacao com a cor de fundo especificada.
    glClear(GL_COLOR_BUFFER_BIT);

    if (MENU_ABERTO) {
        // Exibe o "Menu Principal" ao executar a aplicacao.
        MenuPrincipal();
    } else {
        // Funcoes diretamente relacionadas ao SNAKE.
        DesenharCampo();
        DesenharCobra();
        DesenharComida();

        // Define a cor para o texto.
        glColor3f(1.0, 1.0, 1.0);

        // String que sera exibida na tela.
        char mensagemScore[20];

        // Configura o SCORE que sera exibido na tela, armazenando-o na string "mensagemScore".
        ConfigurarPlacar(mensagemScore);

        // Exibicao do SCORE na tela usando caracteres bitmap.
        glRasterPos2f(((LARGURA - 2) / 2), ALTURA - 0.5);
        DesenhaTexto(GLUT_BITMAP_HELVETICA_18, mensagemScore);
    }

    // Executa os comandos OpenGL.
    glutSwapBuffers();
}

// Funcao callback que recebe fonte e texto para ser exibido na tela usando caracteres bitmap.
void DesenhaTexto(void *font, char *string) {
    while(*string) {
        // Exibe um caractere do tipo bitmap.
        glutBitmapCharacter(font, *string++);
    }
}

// Funcao callback chamada para redimensionar a janela sempre que o tamanho for alterado.
void AlteraTamanhoJanela(GLsizei w, GLsizei h) {
    // Evita a divisao por zero.
    if (h == 0) {
        h = 1;
    }

    // Especifica as dimensões da Viewport(janela onde será feito o desenho).
    glViewport(0, 0, w, h);

    // Inicializa o sistema de coordenadas.
    glMatrixMode(GL_PROJECTION);

    // Substitui a matriz atual pela matriz de identidade.
    glLoadIdentity();

    // Descreve uma matriz de perspectiva que produz uma projeção paralela.
    if (w <= h) {
        // Ajusta a projeção para manter a proporção da janela.
        gluOrtho2D(0.0, LARGURA, 0.0, ALTURA * h / w);
    } else {
        // Ajusta a projeção em modo janela cheia.
        gluOrtho2D(((-LARGURA * w / h) + 20) / 2, ((LARGURA * w / h) + 20) / 2, 0.0, ALTURA);
    }

    // Avisa a OpenGL que todas as futuras alterações irão afetar o que é desenhado.
    glMatrixMode(GL_MODELVIEW);
}

// Funcao callback chamada pela GLUT a cada intervalo de tempo.
void Timer(int valor) {
    // Redesenha o quadrado com as novas coordenadas.
    glutPostRedisplay();

    // Obtendo quantidade "X" de frames em 1 segundo, dividindo 1000 milisegundos por VELOCIDADE.
    glutTimerFunc(1000 / VELOCIDADE, Timer, 0);
}

// Funcao callback chamada para tratar o evento de pressionar teclas especiais do teclado.
void TeclasEspeciais(int key, int x, int y) {
    // Funcao para efetuar a leitura dos dados e mover o objeto.
    MoverCobra(key);
}

// Funcao callback chamada para tratar o evento de teclado.
void Teclado(unsigned char key, int x, int y) {
    // Fecha o MENU e inicia a aplicacao ao pressionar a tecla "space".
    if (key == 32) {
        MENU_ABERTO = 0;
    }
    // Finaliza a aplicacao ao pressionar a tecla "esc".
    if (key == 27) {
        // Libera a memoria alocada para a SNAKE e finaliza a aplicacao.
        EncerrarJogo();
    }
}

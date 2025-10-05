#include <glut.h>
#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14
#endif

// Tamanho do cubo
const float TAMANHO_CUBO = 2.0f;

// Posição e raio da bola
float bolaX = 0.0f;
float bolaY = 0.0f;
float bolaZ = 0.0f;
const float RAIO_BOLA = 0.2f;

// Velocidade da bola
float velocidadeBolaX = 0.02f;
float velocidadeBolaY = 0.015f;
float velocidadeBolaZ = 0.01f;

// Cor e material da bola (azul)
GLfloat bolaAmbiente[] = {0.0f, 0.0f, 0.2f, 1.0f};
GLfloat bolaDifusa[] = {0.0f, 0.0f, 1.0f, 1.0f};
GLfloat bolaEspecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat bolaBrilho[] = {25.0f};

// Posição da câmera
float distanciaCamera = 7.0f;
float anguloCameraY = 48.0f;
float anguloCameraX = 30.0f;


// Desenha a esfera azul
void desenhaBola() {
    glPushMatrix();
    glTranslatef(bolaX, bolaY, bolaZ);
    glMaterialfv(GL_FRONT, GL_AMBIENT, bolaAmbiente);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, bolaDifusa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, bolaEspecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, bolaBrilho);
    glutSolidSphere(RAIO_BOLA, 30, 30);
    glPopMatrix();
}

// Desenha o cubo branco
void desenhaCuboWireframe() {
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);
    glutWireCube(TAMANHO_CUBO * 2.0f);
    glEnable(GL_LIGHTING);
}

// Função principal de desenho
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Posiciona a câmera
    float camX = distanciaCamera * cos(anguloCameraY * M_PI / 180.0) * cos(anguloCameraX * M_PI / 180.0);
    float camY = distanciaCamera * sin(anguloCameraX * M_PI / 180.0);
    float camZ = distanciaCamera * sin(anguloCameraY * M_PI / 180.0) * cos(anguloCameraX * M_PI / 180.0);
    gluLookAt(camX, camY, camZ,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    // Desenha o cubo e a bola
    desenhaCuboWireframe();
    desenhaBola();
    glutSwapBuffers();
}

// Atualiza a posição da bola e verifica colisões
void atualizaPosicaoBola(int valor) {
    // Move a bola
    bolaX += velocidadeBolaX;
    bolaY += velocidadeBolaY;
    bolaZ += velocidadeBolaZ;

    // Checa colisão com as paredes do cubo
    float limite = TAMANHO_CUBO - RAIO_BOLA;

    // Colisão no eixo X
    if (bolaX > limite) {
        bolaX = limite;
        velocidadeBolaX = -velocidadeBolaX;
    } else if (bolaX < -limite) {
        bolaX = -limite;
        velocidadeBolaX = -velocidadeBolaX;
    }

    // Colisão no eixo Y
    if (bolaY > limite) {
        bolaY = limite;
        velocidadeBolaY = -velocidadeBolaY;
    } else if (bolaY < -limite) {
        bolaY = -limite;
        velocidadeBolaY = -velocidadeBolaY;
    }

    // Colisão no eixo Z
    if (bolaZ > limite) {
        bolaZ = limite;
        velocidadeBolaZ = -velocidadeBolaZ;
    } else if (bolaZ < -limite) {
        bolaZ = -limite;
        velocidadeBolaZ = -velocidadeBolaZ;
    }

    // Redesenha a cena
    glutPostRedisplay();

    // Agenda a próxima atualização
    glutTimerFunc(16, atualizaPosicaoBola, 0);
}

// --- Funções de Inicialização e Principal ---

void inicializaGL() {
    glClearColor(0.1f, 0.1f, 0.1f, 0.5f);
    glEnable(GL_DEPTH_TEST);

    // Configura a iluminação
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat posicaoLuz[] = {TAMANHO_CUBO * 1.5f, TAMANHO_CUBO * 1.5f, TAMANHO_CUBO * 1.5f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
    GLfloat luzAmbiente[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat luzDifusa[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat luzEspecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
}

void remodela(int largura, int altura) {
    if (altura == 0) altura = 1;
    float aspecto = (float)largura / (float)altura;
    glViewport(0, 0, largura, altura);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, aspecto, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

// Função principal
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Esfera no Cubo");

    glutDisplayFunc(display);
    glutReshapeFunc(remodela);
    glutTimerFunc(16, atualizaPosicaoBola, 0);

    inicializaGL();
    glutMainLoop();
    return 0;
}

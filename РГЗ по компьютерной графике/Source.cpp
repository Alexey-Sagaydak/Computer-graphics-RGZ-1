#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <complex>
#include <stdlib.h>

void display(void);
void resize(int width, int height);
void init(void);
double random();

int main(int argc, char** argv) {
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50, 10);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Fractal Leda");
    glutReshapeFunc(resize);
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

void display(void) {
    double a = 0.85, b = 0.9, k = 0.4, p = 7.7;
    char str[] = "Alexey Sagaidak ABT-113, fractal 'Leda'";
    std::complex <double> z = 0.0;

    glColor3d(1, 1, 1);
    for (int i = 0; i < sizeof(str) / sizeof(char); i++) {
        glRasterPos3d(-2 + 0.1 * i, -3, 0);
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, str[i]);
    }

    glPointSize(1);
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
    for (int i = 0; i <= 50000; i++) {
        z = a + b * z * exp(std::complex<double>(0, (k - p / (1 + abs(z * z)))));
        glColor3d(random(), random(), random());
        glVertex3d(real(z) * 2.5 - 1.5, imag(z) * 2.5 + 2, 0);
    }
    glEnd();
    glFlush();
}

double random() {
    return (double)rand() / (double)RAND_MAX;
}

void resize(int width, int height) {
    glutReshapeWindow(800, 800);
}

void init(void) {
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5.0, 5.0, -5.0, 5.0, 2.0, 12.0);
    gluLookAt(0, 0, 5, 0, 1, 0, 0, 1, 0);
    glMatrixMode(GL_MODELVIEW);
}

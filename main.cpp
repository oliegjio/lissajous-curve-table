#include <GL/glut.h>
#include <ctime>
#include <cmath>
#include <iostream>

#define WIN_WIDTH 800
#define WIN_HEIGHT 800

clock_t current_time = clock();
clock_t last_time = current_time;
float dt = 0;
float elapsed = 0.0f;

size_t cells_number = 10;
float cell_size = 10.0f;
float table_size = cells_number * cell_size;
float iteration = 0.0f;
float angle_step = 0.1f;

void draw_table_border() {
    float xs = 0.0f;
    float ys = 0.0f;

    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    while (xs <= table_size) {
        glVertex2f(xs, 0.0f);
        glVertex2f(xs, table_size);
        xs += cell_size;
    }
    while (ys <= table_size) {
        glVertex2f(0.0f, ys);
        glVertex2f(table_size, ys);
        ys += cell_size;
    }
    glEnd();
}

void polar(float angle) {
    float r = cell_size / 2;
    float x = r * cosf(angle);
    float y = r * sinf(angle);
    glVertex2f(x, y);
}

void draw_cell(size_t x, size_t y) {
//    float cell_speed_x = x * angle_step;
//    float cell_speed_y = y * angle_step;

    glPushMatrix();

    glTranslatef(x * cell_size, y * cell_size, 0.0f);

    glPointSize(2.0f);
    glColor3f(1.0f, 0.0f, 0.0f);

    float current_angle = 0.0f;

    glBegin(GL_POINTS);
    while (current_angle < 1.0f) {
        polar(current_angle);
        current_angle = iteration * angle_step * x;
    }
    glEnd();

    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    for (size_t i = 0; i < cells_number; i++) {
        for (size_t j = 0; j < cells_number; j++) {
            draw_cell(i, j);
        }
    }
    draw_table_border();

    glutSwapBuffers();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, table_size, table_size, 0.0f, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);

    glutPostRedisplay();
}

void idle()
{
    current_time = clock();
    dt = static_cast<float>(current_time - last_time) / CLOCKS_PER_SEC;
    last_time = current_time;

    elapsed += dt;
    if (elapsed < 1.0f) return;
    elapsed = 0.0f;

    iteration += 1;

    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutCreateWindow("Window Title");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}
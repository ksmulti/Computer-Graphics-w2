#include <GL/glut.h>

float xBoundary = -0.9;
float yBoundary = 0.9;
float length = 0.1;
float interval = 0.25;

void display(void)
{
    int i = 0;
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
        glColor3f(1.0, 0, 0);
        glVertex2f(xBoundary, yBoundary);
        glColor3f(0,1.0, 0);
        glVertex2f(xBoundary + length, yBoundary - length);
        glColor3f(0, 0, 1.0);
        glVertex2f(xBoundary - length, yBoundary - length);
        i++;

        glColor3f(1.0, 0, 0);//1i
        glVertex2f(xBoundary + i*interval, yBoundary);
        glColor3f(0, 1.0, 0);
        glVertex2f(xBoundary + i*interval + length, yBoundary - length);
        glColor3f(0, 0, 1.0);
        glVertex2f(xBoundary + i*interval - length, yBoundary - length);
        i++;
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(1.0, 0, 0);//2i
        glVertex2f(xBoundary + i*interval, yBoundary);
        glColor3f(0, 1.0, 0);
        glVertex2f(xBoundary + i*interval + length, yBoundary - length);
        glColor3f(0, 0, 1.0);
        glVertex2f(xBoundary + i*interval - length, yBoundary - length);
        glVertex2f(xBoundary + i*interval, yBoundary - 2*length);
        i++;
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0, 0, 0);//3i
        glVertex2f(xBoundary + i*interval, yBoundary);
        glColor3f(0, 1.0, 0);
        glVertex2f(xBoundary + i*interval + length, yBoundary - length);
        glColor3f(0, 0, 1.0);
        glVertex2f(xBoundary + i*interval - length, yBoundary - length);
        glVertex2f(xBoundary + i*interval - 1.5*length, yBoundary);
        i++;
    glEnd();
    
    glBegin(GL_QUADS);
        glColor3f(1.0, 0, 0);
        glVertex2f(xBoundary + i*interval, yBoundary);
        glColor3f(0, 1.0, 0);
        glVertex2f(xBoundary + i*interval + length, yBoundary);
        glColor3f(0, 0, 1.0);
        glVertex2f(xBoundary + i*interval + length, yBoundary - length);
        glColor3f(0, 0, 1.0);
        glVertex2f(xBoundary + i*interval, yBoundary - length);
        i++;
    glEnd();

    glBegin(GL_QUAD_STRIP);
        glColor3f(1.0, 0, 0);
        glVertex2f(xBoundary + i*interval, yBoundary);
        glColor3f(0, 1.0, 0);
        glVertex2f(xBoundary + i*interval + length, yBoundary);
        glColor3f(0, 0, 1.0);
        glVertex2f(xBoundary + i*interval, yBoundary - length);
        glColor3f(0, 0, 1.0);
        glVertex2f(xBoundary + i*interval + length, yBoundary - length);

        glColor3f(0, 0, 1.0);
        glVertex2f(xBoundary + i*interval + 2 * length, yBoundary);
        glColor3f(0, 0, 1.0);
        glVertex2f(xBoundary + i*interval + 2 * length, yBoundary - length);
        i++;
    glEnd();
    
    glBegin(GL_POLYGON);
        glColor3f(1.0, 0, 0);
        glVertex2f(xBoundary + i*interval, yBoundary);
        glColor3f(0, 1.0, 0);
        glVertex2f(xBoundary + i*interval + length, yBoundary);
        glColor3f(0, 0, 1.0);
        glVertex2f(xBoundary + i*interval + length, yBoundary - length);
        glColor3f(0, 0, 1.0);
        glVertex2f(xBoundary + i*interval, yBoundary - length);
        i++;
    glEnd();
    
    glFlush();
}

void init()
{
}

void Keyboard(unsigned char key, int x, int y)
{
    GLint glint;
    switch (key)
    {
    case 13:
        
        glGetIntegerv(GL_SHADE_MODEL, &glint);
        if (glint == GL_FLAT)
            glShadeModel(GL_SMOOTH);
        else
            glShadeModel(GL_FLAT);
        glutPostRedisplay();
        break;
    }
}

int main(int argc, char **argv)
{
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("simple");
    glutDisplayFunc(display);
    init();
    glutKeyboardFunc(Keyboard);
    glutMainLoop();
}
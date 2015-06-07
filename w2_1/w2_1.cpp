#include <GL/glut.h>

static GLfloat glfloatArray[] =
{
    -0.5, -0.5,
    0, 0,
    0.5, 0.7,
};

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, glfloatArray);
    glDrawArrays(GL_LINE_LOOP, 0, 3);
    glFlush();
}

void init()
{
}

void Keyboard(unsigned char key, int x, int y)
{

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
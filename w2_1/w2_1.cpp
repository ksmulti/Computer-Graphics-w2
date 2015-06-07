#include <GL/glut.h>

static GLfloat glfloatVertexArray[] =
{
    -0.9,   -0.9,
    -0.8,   -0.7,
    -0.9, -0.8,
    -0.6, -0.6,
    -0.4, -0.7,
    -0.6, -0.8,
};

static GLfloat glfloatColorArray[] =
{
    1.0,     0,      0,
    0,       1.0,    0,
    0,       0,      1.0,
    1.0, 0, 0,
    0, 1.0, 0,
    0, 0, 1.0,
};

GLuint indices[] = { 5, 0, 2, 4};

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    
    glVertexPointer(2, GL_FLOAT, 0, glfloatVertexArray);
    glColorPointer(3, GL_FLOAT, 0, glfloatColorArray);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, indices);

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
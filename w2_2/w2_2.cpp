#include <GL/glut.h>

GLint vertex[] = 
{-1, -1, -1,  //0
-1, -1, 1,  //1
-1, 1, -1,  //2
-1, 1, 1,  //3
1, -1, -1,  //4
1, -1, 1,  //5
1, 1, -1,  //6
1, 1, 1 }; //7

GLfloat color[] =
{ 0, 0, 0,
0, 0, 1,
0, 1, 0,
0, 1, 1,
1, 0, 0,
1, 0, 1,
1, 1, 0,
1, 1, 1 };

GLuint indices[] =
{ 0, 1, 3, 2,
0, 1, 5, 4,
0, 4, 6, 2,
7, 5, 4, 6,
7, 3, 2, 6,
7, 3, 1, 5 };

float LookAtX = 0.0;
float LookAtY = 0.0;
float LookAtZ = 2.0;

void display(void)
{
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, color);
    glVertexPointer(3, GL_INT, 0, vertex);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-5, 5, 5, -5, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(LookAtX, LookAtY, LookAtZ,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    //glRotatef(45, 1, 0, 0);
    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, indices);

    glFlush();
}

void init()
{
}

void Keyboard(unsigned char key, int x, int y)
{

}

void Special(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        LookAtX = LookAtX - 0.1;
        break;
    case GLUT_KEY_RIGHT:
        LookAtX = LookAtX + 0.1;
        break;
    case GLUT_KEY_UP:
        LookAtZ = LookAtZ + 0.1;
        break;
    case GLUT_KEY_DOWN:
        LookAtZ = LookAtZ - 0.1;
        break;
    case GLUT_KEY_F11:
        LookAtY = LookAtY - 0.1;
        break;
    case GLUT_KEY_F12:
        LookAtY = LookAtY + 0.1;
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("simple");
    glutDisplayFunc(display);
    init();
    glutSpecialFunc(Special);
    glutMainLoop();
}
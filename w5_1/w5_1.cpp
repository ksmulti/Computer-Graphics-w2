#include <GL/glew.h>
#include <GL/glut.h>
#include <stddef.h>
#include <stdio.h>

#define BUFFER_OFFSET(bytes) ((GLubyte*) NULL + (bytes))

GLuint buffer[3];

GLint vertex[] =
{ -1, -1, -1,  //0
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

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-5, 5, 5, -5, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(LookAtX, LookAtY, LookAtZ,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0);

    glViewport(0, 0, 500, 500);
    glEnable(GL_VIEWPORT);

    //glRotatef(45, 1, 0, 0);
    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

    glFlush();
}

void init()
{
    glGenBuffers(3, buffer);

    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));

    glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_INT, 0, BUFFER_OFFSET(0));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    GLfloat FogColor[] =
    { 1, 1, 1, 0 };
    glFogf(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_START, 2);
    glFogf(GL_FOG_END, 5);
    glFogfv(GL_FOG_COLOR, FogColor);
    glFogf(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_COORD_SRC, GL_FRAGMENT_DEPTH);
    glEnable(GL_FOG);

    glScissor(0, 0, 350, 350);
    glEnable(GL_SCISSOR_TEST);
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
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        printf("Error: %s\n", glewGetErrorString(err));
    }
    printf("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    init();
    glutDisplayFunc(display);
    glutSpecialFunc(Special);
    glutMainLoop();
}
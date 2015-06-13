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

    //glShadeModel(GL_FLAT);
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


    GLfloat mat_ambient[] = { 0, 0, 0, 0 };
    GLfloat mat_diffuse[] = { 1, 0.6, 0.7, 1 };
    GLfloat mat_specular[] = { 1, 0.4, 0.5, 1 };
    GLfloat no_shininess[] = { 0.0 };
    GLfloat low_shininess[] = { 5.0 };
    GLfloat hig_shininess[] = { 100.0 };
    GLfloat mat_emission[] = { 0, 0, 0, 0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, low_shininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission);
    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, BUFFER_OFFSET(0));


    GLfloat spot_direction[] = { 0.0f, 0.0f, 1.0f};
    GLfloat light_position[] = { 4.0f, 2.0f, 3.0f, 1 };
    GLfloat light_ambient[] = { 0, 0, 0, 0 };
    GLfloat light_diffuse[] = { 0.2, 0.3, 0.4, 1 };
    GLfloat light_specular[] = { 1, 0.4, 0.7, 1 };
    GLfloat light_shininess[] = { 5.0 };
    GLfloat light_emission[] = { 0, 0, 0, 0 };
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF,90);
    //glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1.0);
    //glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
    //glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 2);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.25);
    //glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.5);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_SHININESS, light_shininess);
    glLightfv(GL_LIGHT0, GL_EMISSION, light_emission);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);

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
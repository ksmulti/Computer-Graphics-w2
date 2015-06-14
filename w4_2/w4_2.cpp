#include <GL/glew.h>
#include <GL/glut.h>
#include <stddef.h>
#include <stdio.h>

#define BUFFER_OFFSET(bytes) ((GLubyte*) NULL + (bytes))

typedef struct BmpHeader
{
    unsigned char HEADER_NAME[2];
    unsigned char SIZE[4];
    unsigned int UNUSE1;
    unsigned int UNUSE2;
    unsigned long PIXEL_ARRAY_BEGIN;
}BMP_HEADER;

typedef struct DIBHeader
{
    unsigned long DIB_HEADER_SIZE;
    unsigned long IMAGE_WIDTH;
    unsigned long IMAGE_HEIGHT;
    unsigned int PLANE_AMOUNT;
    unsigned int BITS_PER_PIXEL;
    unsigned long COMPRESSION_USED;
    unsigned long PIXEL_ARRAY_SIZE;
    unsigned long H_RESOLUTION;
    unsigned long V_RESOLUTION;
    unsigned long PALETTLE_COLOR;
    unsigned long IMPORTANT_COLOR;
}DIB_HEADER;

typedef struct Color{
    unsigned char B;
    unsigned char G;
    unsigned char R;
}COLOR;

typedef struct image{
    BMP_HEADER ImageBMP_HEADER;
    DIB_HEADER ImageDIB_HEADER;
}IMAGE;

int Height;
int Width;
IMAGE ReadImage;
COLOR ImageData[600][800];

GLuint buffer[4];

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

GLfloat texturepointer[] =
{ 0, 0,
0, 0,
0, 0,
0, 1,
0, 0,
1, 0,
0, 0,
1, 1 };

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

    //glRotatef(45, 1, 0, 0);
    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

    glFlush();
}

int LoadFile(FILE* fptrSet, char *image_name, IMAGE *image)
{
    int i;
    fopen_s(&fptrSet, image_name, "rb");

    if (fptrSet != NULL)
    {
        fread(&(image->ImageBMP_HEADER), sizeof(image->ImageBMP_HEADER), 1, fptrSet);
        fseek(fptrSet, 0x000E, SEEK_SET);
        fread(&(image->ImageDIB_HEADER), sizeof(image->ImageDIB_HEADER), 1, fptrSet);
        Width = image->ImageDIB_HEADER.IMAGE_WIDTH;
        Height = image->ImageDIB_HEADER.IMAGE_HEIGHT;
        fseek(fptrSet, 0x0036, SEEK_SET);
        for (int i = 0; i<Height; i++)
        {
            fread(ImageData[i], sizeof(COLOR), Width, fptrSet);
        }
        if (image->ImageBMP_HEADER.HEADER_NAME[0] == 'B'&&image->ImageBMP_HEADER.HEADER_NAME[1] == 'M')
        {
            printf("The image was loaded!\n");
            return 0;
        }
        else
        {
            printf("The image is not bmp!\n");
            return -1;
        }
    }
    fclose(fptrSet);
}

void init()
{

    FILE *fptr = NULL;
    if (LoadFile(fptr, ".\\image1.bmp", &ReadImage) == -1)
    {
        return;
    }
    printf("Image information:\n");
    printf("Image size:%dKB\n", (54 + ReadImage.ImageDIB_HEADER.IMAGE_HEIGHT*ReadImage.ImageDIB_HEADER.IMAGE_WIDTH * 24 / 8) / 1024);
    printf("Image height:%d\n", ReadImage.ImageDIB_HEADER.IMAGE_HEIGHT);
    printf("Image width:%d\n\n", ReadImage.ImageDIB_HEADER.IMAGE_WIDTH);

    GLuint TextureNames[1];
    glGenTextures(1, TextureNames);
    glBindTexture(GL_TEXTURE_2D, TextureNames[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ReadImage.ImageDIB_HEADER.IMAGE_WIDTH, ReadImage.ImageDIB_HEADER.IMAGE_HEIGHT, 0, GL_BGR, GL_UNSIGNED_BYTE, ImageData);
    glEnable(GL_TEXTURE_2D);

    glGenBuffers(4, buffer);

    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
    //glEnableClientState(GL_COLOR_ARRAY);
    //glColorPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));

    glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_INT, 0, BUFFER_OFFSET(0));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, buffer[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texturepointer), texturepointer, GL_STATIC_DRAW);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, BUFFER_OFFSET(0));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
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
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <windows.h>
#include "gl/imageloader3.h"

using namespace std;

GLuint _textureId;
GLuint _textureId2;
GLuint _textureId3;
GLuint _textureId4;
GLuint _textureId5;
GLuint _textureId6;
GLuint _textureId7;
GLuint _textureId8;
GLuint _textureId9;


//load gambar to tekstur
GLuint loadTexture(Image* image) {
    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    return textureId;
}

#define FPS 120
#define TO_RADIANS 3.14/180.0

//  Anggota Kelompok 9
//  Muhamad Riyanto (672021601)
//  Muhamad Amirudin (672021601)
//  Ragil Nike Pratistha (672019052)
//  Dava Mahendra P (672019233)

static int slices = 50;
static int stacks = 50;

const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

const int width = 1280;
const int height = 720;
int i;
float sudut;
double x_geser, y_geser, z_geser;

float pitch = 0.0, yaw = 0.0;
float camX = 0.0, camZ = 0.0, terbang = 25.0;

void display();
void reshape(int w, int h);
void timer(int);
void passive_motion(int, int);
void camera();
void keyboard(unsigned char key, int x, int y);
void keyboard_up(unsigned char key, int x, int y);


struct Motion {
    bool Forward, Backward, Left, Right, Naik, Turun;
};
Motion motion = { false,false,false,false,false,false };

void kubus(int x, int y, int z, int p, int t, int l) {
    //alas
    glBegin(GL_QUADS);
    glVertex3f(x, y, z);
    glVertex3f(x + p, y, z);
    glVertex3f(x + p, y, z + l);
    glVertex3f(x, y, z + l);
    glEnd();

    //atas
    glBegin(GL_QUADS);
    glVertex3f(x, y + t, z);
    glVertex3f(x + p, y + t, z);
    glVertex3f(x + p, y + t, z + l);
    glVertex3f(x, y + t, z + l);
    glEnd();

    //kiri
    glBegin(GL_QUADS);
    glVertex3f(x, y, z);
    glVertex3f(x, y, z + l);
    glVertex3f(x, y + t, z + l);
    glVertex3f(x, y + t, z);
    glEnd();

    //kanan
    glBegin(GL_QUADS);
    glVertex3f(x + p, y, z);
    glVertex3f(x + p, y, z + l);
    glVertex3f(x + p, y + t, z + l);
    glVertex3f(x + p, y + t, z);
    glEnd();

    //depan
    glBegin(GL_QUADS);
    glVertex3f(x, y, z);
    glVertex3f(x + p, y, z);
    glVertex3f(x + p, y + t, z);
    glVertex3f(x, y + t, z);
    glEnd();

    //belakang
    glBegin(GL_QUADS);
    glVertex3f(x, y, z + l);
    glVertex3f(x + p, y, z + l);
    glVertex3f(x + p, y + t, z + l);
    glVertex3f(x, y + t, z + l);
    glEnd();


}

void tembok1() {
    //tembok depan
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-250.0, 50.0, 250.1);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(250.0, 50.0, 250.1);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(250.0, 200.0, 250.1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-250.0, 200.0, 250.1);
    glEnd();

    //tembok belakang
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-250.0, 50.0, -250.1);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(250.0, 50.0, -250.1);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(250.0, 200.0, -250.1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-250.0, 200.0, -250.1);
    glEnd();

    //tembok kiri
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-250.1, 50.0, -250);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-250.1, 50.0, 250);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-250.1, 200.0, 250);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-250.1, 200.0, -250);
    glEnd();

    //tembok kanan
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(250.1, 50.0, -250);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(250.1, 50.0, 250);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(250.1, 200.0, 250);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(250.1, 200.0, -250);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void tembok2() {
    //tembok depan
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-150.0, 200.0, 150.1);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(150.0, 200.0, 150.1);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(150.0, 350.0, 150.1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-150.0, 350.0, 150.1);
    glEnd();

    //tembok belakang
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-150.0, 200.0, -150.1);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(150.0, 200.0, -150.1);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(150.0, 350.0, -150.1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-150.0, 350.0, -150.1);
    glEnd();

    //tembok kiri
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-150.1, 200.0, -150.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-150.1, 200.0, 150.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-150.1, 350.0, 150.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-150.1, 350.0, -150.0);
    glEnd();

    //tembok kanan
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(150.1, 200.0, -150.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(150.1, 200.0, 150.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(150.1, 350.0, 150.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(150.1, 350.0, -150.0);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void tembok3() {
    //tembok depan
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId4);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-120.0, 460.0, 120.1);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(120.0, 460.0, 120.1);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(120.0, 550.0, 120.1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-120.0, 550.0, 120.1);
    glEnd();

    //tembok blkng
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId4);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-120.0, 460.0, -120.1);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(120.0, 460.0, -120.1);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(120.0, 550.0, -120.1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-120.0, 550.0, -120.1);
    glEnd();

    //tembok kiri
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId4);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-120.1, 460.0, -120.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-120.1, 460.0, 120.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-120.1, 550.0, 120.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-120.1, 550.0, -120.0);
    glEnd();

    //tembok kanan
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId4);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(120.1, 460.0, -120.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(120.1, 460.0, 120.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(120.1, 550.0, 120.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(120.1, 550.0, -120.0);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void tembok4() {
    //tembok depan
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-120.0, 660.0, 120.1);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(120.0, 660.0, 120.1);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(120.0, 790.0, 120.1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-120.0, 790.0, 120.1);
    glEnd();

    //tembok blkng
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-120.0, 660.0, -120.1);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(120.0, 660.0, -120.1);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(120.0, 790.0, -120.1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-120.0, 790.0, -120.1);
    glEnd();

    //tembok kiri
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-120.1, 660.0, -120.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-120.1, 660.0, 120.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-120.1, 790.0, 120.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-120.1, 790.0, -120.0);
    glEnd();

    //tembok kanan
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(120.1, 660.0, -120.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(120.1, 660.0, 120.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(120.1, 790.0, 120.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(120.1, 790.0, -120.0);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void atas_pintu() {
    //lt1 depan
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId8);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-150.0, 350.0, 150.1);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(150.0, 350.0, 150.1);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(150.0, 400.0, 150.1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-150.0, 400.0, 150.1);
    glEnd();

    //lt1 blkng
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId8);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-150.0, 350.0, -150.1);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(150.0, 350.0, -150.1);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(150.0, 400.0, -150.1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-150.0, 400.0, -150.1);
    glEnd();

    //lt1 kiri
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId8);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-150.1, 350.0, -150.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-150.1, 350.0, 150.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-150.1, 400.0, 150.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-150.1, 400.0, -150.0);
    glEnd();

    //lt1 kanan
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId8);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(150.1, 350.0, -150.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(150.1, 350.0, 150.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(150.1, 400.0, 150.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(150.1, 400.0, -150.0);
    glEnd();

    //lt1 kiri
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId8);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-150.0, 350.0, -150.1);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-150.0, 350.0, 150.1);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-150.0, 400.0, 150.1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-150.0, 400.0, -150.1);
    glEnd();

    //lt2 depan
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId7);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-120.0, 550.0, 120.1);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(120.0, 550.0, 120.1);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(120.0, 600.0, 120.1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-120.0, 600.0, 120.1);
    glEnd();

    //lt2 blkng
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId7);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-120.0, 550.0, -120.1);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(120.0, 550.0, -120.1);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(120.0, 600.0, -120.1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-120.0, 600.0, -120.1);
    glEnd();

    //lt2 kiri
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId7);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-120.1, 550.0, -120.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-120.1, 550.0, 120.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-120.1, 600.0, 120.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-120.1, 600.0, -120.0);
    glEnd();

    //lt2 kanan
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId7);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(120.1, 550.0, -120.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(120.1, 550.0, 120.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(120.1, 600.0, 120.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(120.1, 600.0, -120.0);
    glEnd();

    //lt3 depan
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId7);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-120.0, 790.0, 120.1);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(120.0, 790.0, 120.1);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(120.0, 850.0, 120.1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-120.0, 850.0, 120.1);
    glEnd();

    //lt2 blkng
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId7);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-120.0, 790.0, -120.1);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(120.0, 790.0, -120.1);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(120.0, 850.0, -120.1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-120.0, 850.0, -120.1);
    glEnd();

    //lt2 kiri
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId7);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-120.1, 790.0, -120.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-120.1, 790.0, 120.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-120.1, 850.0, 120.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-120.1, 850.0, -120.0);
    glEnd();

    //lt2 kanan
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId7);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(120.1, 790.0, -120.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(120.1, 790.0, 120.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(120.1, 850.0, 120.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(120.1, 850.0, -120.0);
    glEnd();
}

void ataplt1() {
    //atap depan
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId3);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-280.0, 405.0, 280.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(280.0, 405.0, 280.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(150.0, 440.0, 150.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-150.0, 440.0, 150.0);
    glEnd();

    //atap blkng
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId3);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-280.0, 405.0, -280.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(280.0, 405.0, -280.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(150.0, 440.0, -150.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-150.0, 440.0, -150.0);
    glEnd();

    //atap kiri
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId3);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-280.0, 405.0, -280.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-280.0, 405.0, 280.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-150.0, 440.0, 150.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-150.0, 440.0, -150.0);
    glEnd();

    //atap kanan
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId3);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(280.0, 405.0, -280.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(280.0, 405.0, 280.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(150.0, 440.0, 150.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(150.0, 440.0, -150.0);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void ataplt2() {
    //atap depan
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId3);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-230.0, 605.0, 230.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(230.0, 605.0, 230.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(120.0, 645.0, 120.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-120.0, 645.0, 120.0);
    glEnd();

    //atap blkng
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId3);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-230.0, 605.0, -230.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(230.0, 605.0, -230.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(120.0, 645.0, -120.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-120.0, 645.0, -120.0);
    glEnd();

    //atap kiri
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId3);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-230.0, 605.0, -230.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-230.0, 605.0, 230.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-120.0, 645.0, 120.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-120.0, 645.0, -120.0);
    glEnd();

    //atap kiri
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId3);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(230.0, 605.0, -230.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(230.0, 605.0, 230.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(120.0, 645.0, 120.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(120.0, 645.0, -120.0);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void ataplt3() {
    //atap depan
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId3);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-230.0, 850.0, 230.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(230.0, 850.0, 230.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(40.0, 950.0, 40.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-40.0, 950.0, 40.0);
    glEnd();

    //atap blkng
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId3);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-230.0, 850.0, -230.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(230.0, 850.0, -230.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(40.0, 950.0, -40.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-40.0, 950.0, -40.0);
    glEnd();

    //atap kiri
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId3);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-230.0, 850.0, -230.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-230.0, 850.0, 230.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-40.0, 950.0, 40.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-40.0, 950.0, -40.0);
    glEnd();

    //atap kiri
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId3);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(230.0, 850.0, -230.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(230.0, 850.0, 230.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(40.0, 950.0, 40.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(40.0, 950.0, -40.0);
    glEnd();


    glDisable(GL_TEXTURE_2D);
}

void alas_atap() {
    //lt1
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId6);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-280, 399.9, 280);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(280, 399.9, 280);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(280, 399.9, -280);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-280, 399.9, -280);
    glEnd();

    //lt2
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId6);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-230, 599.9, 230);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(230, 599.9, 230);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(230, 599.9, -230);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-230, 599.9, -230);
    glEnd();

    //lt3
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId6);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-230, 844.9, 230);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(230, 844.9, 230);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(230, 844.9, -230);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-230, 844.9, -230);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void pucuk_kotak() {
    glColor3f(0.87f, 0.78f, 0.53f);
    kubus(-40, 950, -40, 80, 25, 80); //alas kotak

    glColor3f(0.77f, 0.68f, 0.43f);
    kubus(-7, 1000, -7, 14, 75, 14); //tingkat 1
    kubus(-5, 1075, -5, 10, 75, 10); //tingkat 2
    kubus(-2, 1150, -2, 4, 50, 4); //tingkat 3

    glColor3d(0.87f, 0.78f, 0.53f);
    glTranslated(0, 980, 0);
    glutSolidSphere(30, 50, 50);
    glTranslated(0, -980, 0);

    glColor3d(1, 0, 0);
    glTranslated(0, 1175, 0);
    glutSolidSphere(5, 50, 50);
    glTranslated(0, 20, 0);
    glutSolidSphere(4, 50, 50);

    glColor3d(1, 1, 0.4f);
    glTranslated(0, -165, 0);
    glRotated(90, 1, 0, 0);
    glutSolidTorus(3, 15, 50, 50);
    glRotated(-90, 1, 0, 0);

    glTranslated(0, 15, 0);
    glRotated(90, 1, 0, 0);
    glutSolidTorus(3, 14, 50, 50);
    glRotated(-90, 1, 0, 0);

    glTranslated(0, 15, 0);
    glRotated(90, 1, 0, 0);
    glutSolidTorus(3, 13, 50, 50);
    glRotated(-90, 1, 0, 0);

    glTranslated(0, 15, 0);
    glRotated(90, 1, 0, 0);
    glutSolidTorus(3, 12, 50, 50);
    glRotated(-90, 1, 0, 0);

    glTranslated(0, 15, 0);
    glRotated(90, 1, 0, 0);
    glutSolidTorus(3, 11, 50, 50);
    glRotated(-90, 1, 0, 0);

    glTranslated(0, 15, 0);
    glRotated(90, 1, 0, 0);
    glutSolidTorus(3, 10, 50, 50);
    glRotated(-90, 1, 0, 0);

    glTranslated(0, 15, 0);
    glRotated(90, 1, 0, 0);
    glutSolidTorus(3, 9, 50, 50);
    glRotated(-90, 1, 0, 0);

    glTranslated(0, 15, 0);
    glRotated(90, 1, 0, 0);
    glutSolidTorus(3, 8, 50, 50);
    glRotated(-90, 1, 0, 0);




}

void pagarlt1() {
    //pilar ngadek
    glColor3f(0.99f, 0.36f, 0.16f);
    kubus(-340, 200, 330, 10, 50, 10); //kiri depan
    kubus(-340, 200, -340, 10, 50, 10); //kiri belakang
    kubus(330, 200, 330, 10, 50, 10); //kanan depan
    kubus(330, 200, -340, 10, 50, 10); //kanan belkang

    //depan
    kubus(-340, 245, 335, 680, 5, 5);
    kubus(-340, 230, 335, 680, 5, 5);
    kubus(-340, 220, 335, 680, 5, 5);
    kubus(-340, 210, 335, 680, 5, 5);

    //blkng
    kubus(-340, 245, -340, 680, 5, 5);
    kubus(-340, 230, -340, 680, 5, 5);
    kubus(-340, 220, -340, 680, 5, 5);
    kubus(-340, 210, -340, 680, 5, 5);

    //kiri
    kubus(-340, 245, -340, 5, 5, 680);
    kubus(-340, 230, -340, 5, 5, 680);
    kubus(-340, 220, -340, 5, 5, 680);
    kubus(-340, 210, -340, 5, 5, 680);

    //kanan
    kubus(335, 245, -340, 5, 5, 680);
    kubus(335, 230, -340, 5, 5, 680);
    kubus(335, 220, -340, 5, 5, 680);
    kubus(335, 210, -340, 5, 5, 680);

    //depan berdiri
    glTranslated(-300, 200, 335);
    kubus(0, 0, 0, 5, 30, 5); //kiri
    glTranslated(35, 0, 0);
    kubus(0, 0, 0, 5, 50, 5);
    glTranslated(35, 0, 0);
    kubus(0, 0, 0, 5, 30, 5);
    glTranslated(35, 0, 0);
    kubus(0, 0, 0, 5, 50, 5);
    glTranslated(35, 0, 0);
    kubus(0, 0, 0, 5, 30, 5);
    glTranslated(35, 0, 0);
    kubus(0, 0, 0, 5, 50, 5);
    glTranslated(35, 0, 0);
    kubus(0, 0, 0, 5, 30, 5);
    glTranslated(35, 0, 0);
    kubus(0, 0, 0, 5, 50, 5);
    glTranslated(35, 0, 0);
    kubus(0, 0, 0, 5, 30, 5);
    glTranslated(35, 0, 0);
    kubus(0, 0, 0, 5, 50, 5);
    glTranslated(35, 0, 0);
    kubus(0, 0, 0, 5, 30, 5);
    glTranslated(35, 0, 0);
    kubus(0, 0, 0, 5, 50, 5);
    glTranslated(35, 0, 0);
    kubus(0, 0, 0, 5, 30, 5);
    glTranslated(35, 0, 0);
    kubus(0, 0, 0, 5, 50, 5);
    glTranslated(35, 0, 0);
    kubus(0, 0, 0, 5, 30, 5);
    glTranslated(35, 0, 0);
    kubus(0, 0, 0, 5, 50, 5);
    glTranslated(35, 0, 0);
    kubus(0, 0, 0, 5, 30, 5);
    glTranslated(35, 0, 0);
    kubus(0, 0, 0, 5, 50, 5);

    //kanan berdiri
    glTranslated(40, 0, -35);//depan
    kubus(0, 0, 0, 5, 50, 5);
    glTranslated(0, 0, -35);
    kubus(0, 0, 0, 5, 30, 5);
    glTranslated(0, 0, -35);
    kubus(0, 0, 0, 5, 50, 5);
    glTranslated(0, 0, -35);
    kubus(0, 0, 0, 5, 30, 5);
    glTranslated(0, 0, -35);
    kubus(0, 0, 0, 5, 50, 5);
    glTranslated(0, 0, -35);
    kubus(0, 0, 0, 5, 30, 5);
    glTranslated(0, 0, -35);
    kubus(0, 0, 0, 5, 50, 5);
    glTranslated(0, 0, -35);
    kubus(0, 0, 0, 5, 30, 5);
    glTranslated(0, 0, -35);
    kubus(0, 0, 0, 5, 50, 5);
    glTranslated(0, 0, -35);
    kubus(0, 0, 0, 5, 30, 5);
    glTranslated(0, 0, -35);
    kubus(0, 0, 0, 5, 50, 5);
    glTranslated(0, 0, -35);
    kubus(0, 0, 0, 5, 30, 5);
    glTranslated(0, 0, -35);
    kubus(0, 0, 0, 5, 50, 5);
    glTranslated(0, 0, -35);
    kubus(0, 0, 0, 5, 30, 5);
    glTranslated(0, 0, -35);
    kubus(0, 0, 0, 5, 50, 5);
    glTranslated(0, 0, -35);
    kubus(0, 0, 0, 5, 30, 5);
    glTranslated(0, 0, -35);
    kubus(0, 0, 0, 5, 50, 5);
    glTranslated(0, 0, -35);
    kubus(0, 0, 0, 5, 30, 5);
    glTranslated(0, 0, -40);
    kubus(0, 0, 0, 5, 50, 5);

    //belakang berdiri
    glTranslated(-40, 0, 0);//kanan
    kubus(0, 0, 0, 5, 50, 5);
    glTranslated(-35, 0, 0);
    kubus(0, 0, 0, 5, 30, 5);
    glTranslated(-35, 0, 0);
    kubus(0, 0, 0, 5, 50, 5);
    glTranslated(-35, 0, 0);
    kubus(0, 0, 0, 5, 30, 5);
    glTranslated(-35, 0, 0);
    kubus(0, 0, 0, 5, 50, 5);
    glTranslated(-35, 0, 0);
    kubus(0, 0, 0, 5, 30, 5);
    glTranslated(-35, 0, 0);
    kubus(0, 0, 0, 5, 50, 5);
    glTranslated(-35, 0, 0);
    kubus(0, 0, 0, 5, 30, 5);
    glTranslated(-35, 0, 0);
    kubus(0, 0, 0, 5, 50, 5);
    glTranslated(-35, 0, 0);
    kubus(0, 0, 0, 5, 30, 5);
    glTranslated(-35, 0, 0);
    kubus(0, 0, 0, 5, 50, 5);
    glTranslated(-35, 0, 0);
    kubus(0, 0, 0, 5, 30, 5);
    glTranslated(-35, 0, 0);
    kubus(0, 0, 0, 5, 50, 5);
    glTranslated(-35, 0, 0);
    kubus(0, 0, 0, 5, 30, 5);
    glTranslated(-35, 0, 0);
    kubus(0, 0, 0, 5, 50, 5);
    glTranslated(-35, 0, 0);
    kubus(0, 0, 0, 5, 30, 5);
    glTranslated(-35, 0, 0);
    kubus(0, 0, 0, 5, 50, 5);
    glTranslated(-35, 0, 0);
    kubus(0, 0, 0, 5, 30, 5);
    glTranslated(-40, 0, 0);
    kubus(0, 0, 0, 5, 50, 5);

    //kiri berdiri
    glTranslated(0, 0, 40);//depan
    kubus(0, 0, 0, 5, 50, 5);
    glTranslated(0, 0, 35);
    kubus(0, 0, 0, 5, 30, 5);
    glTranslated(0, 0, 35);
    kubus(0, 0, 0, 5, 50, 5);
    glTranslated(0, 0, 35);
    kubus(0, 0, 0, 5, 30, 5);
    glTranslated(0, 0, 35);
    kubus(0, 0, 0, 5, 50, 5);
    glTranslated(0, 0, 35);
    kubus(0, 0, 0, 5, 30, 5);
    glTranslated(0, 0, 35);
    kubus(0, 0, 0, 5, 50, 5);
    glTranslated(0, 0, 35);
    kubus(0, 0, 0, 5, 30, 5);
    glTranslated(0, 0, 35);
    kubus(0, 0, 0, 5, 50, 5);
    glTranslated(0, 0, 35);
    kubus(0, 0, 0, 5, 30, 5);
    glTranslated(0, 0, 35);
    kubus(0, 0, 0, 5, 50, 5);
    glTranslated(0, 0, 35);
    kubus(0, 0, 0, 5, 30, 5);
    glTranslated(0, 0, 35);
    kubus(0, 0, 0, 5, 50, 5);
    glTranslated(0, 0, 35);
    kubus(0, 0, 0, 5, 30, 5);
    glTranslated(0, 0, 35);
    kubus(0, 0, 0, 5, 50, 5);
    glTranslated(0, 0, 35);
    kubus(0, 0, 0, 5, 30, 5);
    glTranslated(0, 0, 35);
    kubus(0, 0, 0, 5, 50, 5);
    glTranslated(0, 0, 35);
    kubus(0, 0, 0, 5, 30, 5);

    glTranslated(340, -200, -300);


}

void pagarlt2() {
    //pilar ngadek
    glColor3f(0.99f, 0.36f, 0.16f);
    kubus(-180, 450, 170, 10, 40, 10); //kiri depan
    kubus(-180, 450, -180, 10, 40, 10); //kiri belakang
    kubus(170, 450, 170, 10, 40, 10); //kanan depan
    kubus(170, 450, -180, 10, 40, 10); //kanan belkang

    //depan
    kubus(-180, 485, 175, 360, 5, 5);
    kubus(-180, 470, 175, 360, 5, 5);

    //depan_berdiri
    kubus(-35, 450, 175, 5, 20, 4.95);
    kubus(-65, 450, 175, 5, 40, 4.95);
    kubus(-95, 450, 175, 5, 20, 4.95);
    kubus(-125, 450, 175, 5, 40, 4.95);
    kubus(-155, 450, 175, 5, 20, 4.95);
    kubus(-2.5, 450, 175, 5, 40, 4.95);//tengah
    kubus(30, 450, 175, 5, 20, 4.95);
    kubus(60, 450, 175, 5, 40, 4.95);
    kubus(90, 450, 175, 5, 20, 4.95);
    kubus(120, 450, 175, 5, 40, 4.95);
    kubus(150, 450, 175, 5, 20, 4.95);

    //blkng
    kubus(-180, 485, -175, 360, 5, -5);
    kubus(-180, 475, -175, 360, 5, -5);
    kubus(-180, 465, -175, 360, 5, -5);

    //blkng_berdiri
    kubus(-35, 450, -175, 5, 20, -4.95);
    kubus(-65, 450, -175, 5, 40, -4.95);
    kubus(-95, 450, -175, 5, 20, -4.95);
    kubus(-125, 450, -175, 5, 40, -4.95);
    kubus(-155, 450, -175, 5, 20, -4.95);
    kubus(-2.5, 450, -175, 5, 40, -4.95);//tengah
    kubus(30, 450, -175, 5, 20, -4.95);
    kubus(60, 450, -175, 5, 40, -4.95);
    kubus(90, 450, -175, 5, 20, -4.95);
    kubus(120, 450, -175, 5, 40, -4.95);
    kubus(150, 450, -175, 5, 20, -4.95);

    //kiri
    kubus(-180, 485, -180, 5, 5, 360);
    kubus(-180, 475, -180, 5, 5, 360);
    kubus(-180, 465, -180, 5, 5, 360);

    kubus(-175, 450, -35, -4.95, 20, 5);
    kubus(-175, 450, -65, -4.95, 40, 5);
    kubus(-175, 450, -95, -4.95, 20, 5);
    kubus(-175, 450, -125, -4.95, 40, 5);
    kubus(-175, 450, -155, -4.95, 20, 5);
    kubus(-175, 450, -2.5, -4.95, 40, 5);//tengah
    kubus(-175, 450, 35, -4.95, 20, 5);
    kubus(-175, 450, 65, -4.95, 40, 5);
    kubus(-175, 450, 95, -4.95, 20, 5);
    kubus(-175, 450, 125, -4.95, 40, 5);
    kubus(-175, 450, 155, -4.95, 20, 5);

    //kanan
    kubus(180, 485, -180, -5, 5, 360);
    kubus(180, 475, -180, -5, 5, 360);
    kubus(180, 465, -180, -5, 5, 360);

    kubus(175, 450, -35, 4.95, 20, 5);
    kubus(175, 450, -65, 4.95, 40, 5);
    kubus(175, 450, -95, 4.95, 20, 5);
    kubus(175, 450, -125,4.95, 40, 5);
    kubus(175, 450, -155,4.95, 20, 5);
    kubus(175, 450, -2.5,4.95, 40, 5);//tengah
    kubus(175, 450, 35, 4.95, 20, 5);
    kubus(175, 450, 65, 4.95, 40, 5);
    kubus(175, 450, 95, 4.95, 20, 5);
    kubus(175, 450, 125,4.95, 40, 5);
    kubus(175, 450, 155,4.95, 20, 5);

}

void pagarlt3() {
    //pilar ngadek
    glColor3f(0.99f, 0.36f, 0.16f);
    kubus(-180, 650, 170, 10, 50, 10); //kiri depan
    kubus(-180, 650, -180, 10, 50, 10); //kiri belakang
    kubus(170, 650, 170, 10, 50, 10); //kanan depan
    kubus(170, 650, -180, 10, 50, 10); //kanan belkang

    //depan
    kubus(-180, 695, 175, 360, 5, 5);
    kubus(-180, 680, 175, 360, 5, 5);

    //depan_berdiri
    kubus(-35, 650, 175, 5, 30, 4.95);
    kubus(-65, 650, 175, 5, 50, 4.95);
    kubus(-95, 650, 175, 5, 30, 4.95);
    kubus(-125, 650, 175, 5, 50, 4.95);
    kubus(-155, 650, 175, 5, 30, 4.95);
    kubus(-2.5, 650, 175, 5, 50, 4.95);//tengah
    kubus(30, 650, 175, 5, 30, 4.95);
    kubus(60, 650, 175, 5, 50, 4.95);
    kubus(90, 650, 175, 5, 30, 4.95);
    kubus(120, 650, 175, 5, 50, 4.95);
    kubus(150, 650, 175, 5, 30, 4.95);

    //blkng
    kubus(-180, 695, -175, 360, 5, -5);
    kubus(-180, 680, -175, 360, 5, -5);

    //blkng_berdiri
    kubus(-35, 650, -175, 5, 30, -4.95);
    kubus(-65, 650, -175, 5, 40, -4.95);
    kubus(-95, 650, -175, 5, 30, -4.95);
    kubus(-125, 650, -175, 5, 40, -4.95);
    kubus(-155, 650, -175, 5, 30, -4.95);
    kubus(-2.5, 650, -175, 5, 40, -4.95);//tengah
    kubus(30, 650, -175, 5, 30, -4.95);
    kubus(60, 650, -175, 5, 40, -4.95);
    kubus(90, 650, -175, 5, 30, -4.95);
    kubus(120, 650, -175, 5, 40, -4.95);
    kubus(150, 650, -175, 5, 30, -4.95);

    //kiri
    kubus(-180, 695, -180, 5, 5, 360);
    kubus(-180, 680, -180, 5, 5, 360);

    //kiri_berdiri
    kubus(-180, 485, -180, 5, 5, 360);
    kubus(-180, 475, -180, 5, 5, 360);
    kubus(-180, 465, -180, 5, 5, 360);

    kubus(-175, 650, -35, -4.95, 30, 5);
    kubus(-175, 650, -65, -4.95, 50, 5);
    kubus(-175, 650, -95, -4.95, 30, 5);
    kubus(-175, 650, -125, -4.95, 50, 5);
    kubus(-175, 650, -155, -4.95, 30, 5);
    kubus(-175, 650, -2.5, -4.95, 50, 5);//tengah
    kubus(-175, 650, 35, -4.95, 30, 5);
    kubus(-175, 650, 65, -4.95, 50, 5);
    kubus(-175, 650, 95, -4.95, 30, 5);
    kubus(-175, 650, 125, -4.95, 50, 5);
    kubus(-175, 650, 155, -4.95, 30, 5);

    //kanan
    kubus(180, 695, -180, -5, 5, 360);
    kubus(180, 680, -180, -5, 5, 360);

    //kanan
    kubus(180, 485, -180, -5, 5, 360);
    kubus(180, 475, -180, -5, 5, 360);
    kubus(180, 465, -180, -5, 5, 360);

    kubus(175, 650, -35, 4.95, 30, 5);
    kubus(175, 650, -65, 4.95, 50, 5);
    kubus(175, 650, -95, 4.95, 30, 5);
    kubus(175, 650, -125, 4.95, 50, 5);
    kubus(175, 650, -155, 4.95, 30, 5);
    kubus(175, 650, -2.5, 4.95, 50, 5);//tengah
    kubus(175, 650, 35, 4.95, 30, 5);
    kubus(175, 650, 65, 4.95, 50, 5);
    kubus(175, 650, 95, 4.95, 30, 5);
    kubus(175, 650, 125, 4.95, 50, 5);
    kubus(175, 650, 155, 4.95, 30, 5);
}

void ground() {
    glBegin(GL_QUADS);
    glColor3f(0.3f, 0.9f, 0.3f);
    glVertex3f(-1000.0, 0, -1000.0);
    glVertex3f(1000.0, 0, -1000.0);
    glVertex3f(1000.0, 0, 1000.0);
    glVertex3f(-1000.0, 0, 1000.0);
    glEnd();
}

void lantai1() {

}

void pagar_lantai1() {

}

void tekstur_lantai() {
    //lt1
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId9);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-340, 200.1, 340);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(340, 200.1, 340);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(340, 200.1, -340);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-340, 200.1, -340);
    glEnd();

    //lt2
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId9);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-180, 460.1, 180);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(180, 460.1, 180);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(180, 460.1, -180);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-180, 460.1, -180);
    glEnd();

    //lt3
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId9);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-180, 660.1, 180);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(180, 660.1, 180);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(180, 660.1, -180);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-180, 660.1, -180);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void papan_nama() {
    //glColor3f(0.90f, 0.40f, 0.24f);
    //kubus(335, 0, 450, 10, 50, 10); //kayu
    //kubus(400, 50, 450, 140, 70, 10); //alas
}

void draw(void) {
    // Mulai tuliskan isi pikiranmu disini
    lantai1();
    ground();

    glColor3f(0.3f, 0.3f, 0.3f);
    kubus(-400, 0, -400, 800, 50, 800); //alas

    glColor3f(0.9f, 0.9f, 0.9f);
    kubus(-250, 50, -250, 500, 150, 500); //tingkat 1
    kubus(-150, 200, -150, 300, 250, 300); //tingkat 2
    kubus(-120, 450, -120, 240, 200, 240); //tingkat 3
    kubus(-120, 650, -120, 240, 210, 240); //tingkat 4

    glColor3f(0.90f, 0.40f, 0.24f);
    kubus(-340, 190, -340, 680, 10, 680); //alas tingkat 1
    kubus(-180, 450, -180, 360, 10, 360); //alas tingkat 2
    kubus(-180, 650, -180, 360, 10, 360); //alas tingkat 3

    glColor3f(0.47f, 0.72f, 0.71f);
    kubus(-280, 400, -280, 560, 5, 560); //alas atap tingkat 1
    kubus(-230, 600, -230, 460, 5, 460); //alas atap tingkat 2
    kubus(-230, 845, -230, 460, 5, 460); //alas atap tingkat 3

    //cagak
    glColor3f(0.99f, 0.36f, 0.16f);
    kubus(-110, 50, 330, 10, 150, 10); //kiri depan
    kubus(100, 50, 330, 10, 150, 10); //kanan depan
    kubus(-110, 50, -340, 10, 150, 10); //kiri blkng
    kubus(100, 50, -340, 10, 150, 10); //kanan blkng
    kubus(-340, 50, -5, 10, 150, 10); //kiri kastil
    kubus(330, 50, -5, 10, 150, 10); //kanan kastil

    //cagak lt1
    glColor3f(0.99f, 0.36f, 0.16f);
    kubus(-110, 200, 270, 10, 200, 10); //kiri depan
    kubus(100, 200, 270, 10, 200, 10); //kanan depan
    kubus(-110, 200, -280, 10, 200, 10); //kiri blkng
    kubus(100, 200, -280, 10, 200, 10); //kanan blkng
    kubus(-280, 200, -5, 10, 200, 10); //kiri kastil
    kubus(270, 200, -5, 10, 200, 10); //kanan kastil



    tembok1();
    tembok2();
    tembok3();
    tembok4();
    atas_pintu();
    ataplt1();
    ataplt2();
    ataplt3();
    pagarlt1();
    pagarlt2();
    pagarlt3();
    alas_atap();
    tekstur_lantai();
    papan_nama();

    pucuk_kotak();

    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    camera();
    draw();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50, 16.0 / 9.0, 2, 10000);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int) {
    glutPostRedisplay();
    glutWarpPointer(width / 2, height / 2);
    glutTimerFunc(1000 / FPS, timer, 0);
}

void passive_motion(int x, int y) {
    int dev_x, dev_y;
    dev_x = (width / 2) - x;
    dev_y = (height / 2) - y;
    yaw += (float)dev_x / 20.0;
    pitch += (float)dev_y / 20.0;
}

void camera() {
    if (motion.Forward) {
        camX += cos((yaw + 90) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90) * TO_RADIANS) * 2;
    }
    if (motion.Backward) {
        camX += cos((yaw + 90 + 180) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90 + 180) * TO_RADIANS) * 2;
    }
    if (motion.Left) {
        camX += cos((yaw + 90 + 90) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90 + 90) * TO_RADIANS) * 2;
    }
    if (motion.Right) {
        camX += cos((yaw + 90 - 90) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90 - 90) * TO_RADIANS) * 2;
    }
    if (motion.Naik) {
        terbang -= 2.0;
    }
    if (motion.Turun) {
        terbang += 2.0;
    }

    if (pitch >= 70)
        pitch = 70;
    if (pitch <= -90)
        pitch = -90;


    glRotatef(-pitch, 1.0, 0.0, 0.0);
    glRotatef(-yaw, 0.0, 1.0, 0.0);

    glTranslatef(-camX, -terbang, -350 - camZ);
    if (terbang < 25)
        terbang = 24;
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'W':
    case 'w':
        motion.Forward = true;
        break;
    case 'A':
    case 'a':
        motion.Left = true;
        break;
    case 'S':
    case 's':
        motion.Backward = true;
        break;
    case 'D':
    case 'd':
        motion.Right = true;
        break;
    case 'E':
    case 'e':
        motion.Naik = true;
        break;
    case 'Q':
    case 'q':
        motion.Turun = true;
        break;
    case '6':
        x_geser += 0.5;
        break;
    case '4':
        x_geser -= 0.5;
        break;
    case '8':
        y_geser += 0.5;
        break;
    case '2':
        y_geser -= 0.5;
        break;
    case '9':
        z_geser -= 0.5;
        break;
    case '1':
        z_geser += 0.5;
        break;
    case '`': // KELUAR DARI PROGRAM
        exit(1);
    }
}

void keyboard_up(unsigned char key, int x, int y) {
    switch (key) {
    case 'W':
    case 'w':
        motion.Forward = false;
        break;
    case 'A':
    case 'a':
        motion.Left = false;
        break;
    case 'S':
    case 's':
        motion.Backward = false;
        break;
    case 'D':
    case 'd':
        motion.Right = false;
        break;
    case 'E':
    case 'e':
        motion.Naik = false;
        break;
    case 'Q':
    case 'q':
        motion.Turun = false;
        break;
    }
}

void init(void) {
    glClearColor(0.529, 0.807, 0.921, 0.0);
    glutSetCursor(GLUT_CURSOR_NONE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LEQUAL);
    glutWarpPointer(width / 2, height / 2);

    //pencahayaan
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //set cahaya
    GLfloat qaAmbientLight[] = { 0.3,0.3,0.3,1.0 };
    GLfloat qaDiffuseLight[] = { 0.8,0.8,0.8,0.8 };
    GLfloat qaSpecularLight[] = { 1,1,1,1 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);
    //posisi cahaya
    GLfloat posisilampu[] = { 5,5,5,2 };
    glLightfv(GL_LIGHT0, GL_POSITION, posisilampu);

    //gambar1
    Image* image1 = loadBMP("tem1.bmp");
    _textureId = loadTexture(image1);
    delete image1;
    Image* image2 = loadBMP("tem2.bmp");
    _textureId2 = loadTexture(image2);
    delete image2;
    Image* image3 = loadBMP("aa.bmp");
    _textureId3 = loadTexture(image3);
    delete image3;
    Image* image4 = loadBMP("tem3.bmp");
    _textureId4 = loadTexture(image4);
    delete image4;

    Image* image6 = loadBMP("alas_atap.bmp");
    _textureId6 = loadTexture(image6);
    delete image6;
    Image* image7 = loadBMP("atas_pintu.bmp");
    _textureId7 = loadTexture(image7);
    delete image7;
    Image* image8 = loadBMP("atas_pintu_.bmp");
    _textureId8 = loadTexture(image8);
    delete image8;
    Image* image9 = loadBMP("lantai.bmp");
    _textureId9 = loadTexture(image9);
    delete image9;

    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_MODELVIEW);
    glOrtho(-1, 1, -1, 1, -1, 1);
    glPointSize(2.0);
    glLineWidth(2.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("TR GRAFKOM");

    init();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(passive_motion);
    glutTimerFunc(0, timer, 0);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboard_up);
    glutMainLoop();

    return 0;
}

//
//  copy_main.cpp
//  pro
//
//  Created by Nameira Rana on 20/06/2021.
//

#include </usr/local/Cellar/glfw/3.3.3/include/GLFW/glfw3.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <cmath>
#include <math.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <stdio.h>
#include <time.h>
#include <vector>

#include "Matrix2f.h"
#include "Matrix3f.h"
#include "Matrix4f.h"
#include "Quat4f.h"
#include "Vector2f.h"
#include "Vector3f.h"
#include "Vector4f.h"
#include "util.h"
#include <fstream>
using namespace std;
struct wave{
    float k;
    float w;
    float A;
    float phi;
}
w1,w2;
float timeX = 0.0;
float timeY = 0.0;
vector<Vector2f> locations;
vector<Vector2f> locations_old;
vector<Vector3f> colours;
vector<Vector2f> water;
void keyboardFunc( unsigned char key, int x, int y ){
    switch ( key )
    {
    case 27: // Escape key
        exit(0);
        break;
    }
    glutPostRedisplay();
}
GLubyte fish[] = {
  0x00, 0x60, 0x01, 0x00,
  0x00, 0x90, 0x01, 0x00,
  0x03, 0xf8, 0x02, 0x80,
  0x1c, 0x37, 0xe4, 0x40,
  0x20, 0x40, 0x90, 0x40,
  0xc0, 0x40, 0x78, 0x80,
  0x41, 0x37, 0x84, 0x80,
  0x1c, 0x1a, 0x04, 0x80,
  0x03, 0xe2, 0x02, 0x40,
  0x00, 0x11, 0x01, 0x40,
  0x00, 0x0f, 0x00, 0xe0,
};
GLfloat randomFloatX() {
    int number = rand() % 160;
    return (GLfloat)number;
}
GLfloat randomFloatY() {
    int number = rand() % 60;
    number += 10;
    return -(GLfloat)number;
}

GLfloat randomColour() {
    return (GLfloat)rand()/RAND_MAX;
}
void wave_reshape(int w,int h){
    glViewport(0,0,20 * 30, 20 * 30);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 160, 0, 90);
    glMatrixMode(GL_MODELVIEW);

}
float wave_ordinate(float k, float w, float A, float phi, float x){
    return A * sin( (k*x) - (w*timeX) + phi);
}

void wave_display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(0.0,0.0,1.0);
    glTranslatef(0.0,75.0,0.0);
    glBegin(GL_LINE_STRIP);
    for(float x = 0 ; x < 160 ; x+=0.5){
        float y = wave_ordinate(w1.k, w1.w, w1.A, w1.phi, x);
        glVertex2d(x, y);
    }
    glEnd();
    
    for( int j = 0; j < 10; j++){
        srand((unsigned) time(0));
        for(int i = 0; i < 20 ; i++){
            glColor3f(0.0, 0.0, 0.0);
            glRasterPos3f(locations_old[i][0], locations_old[i][1], 0.0);
            glBitmap(27, 11, 0.0, 0.0, 0.0, 0.0, fish);
              
            glColor3f(colours[i][0], colours[i][1], colours[i][2]);
            glRasterPos3f(locations[i][0], locations[i][1], 0.0);
            glBitmap(27, 11, 0.0, 0.0, 0.0, 0.0, fish);
            
            locations_old[i][0] = locations[i][0];
            locations_old[i][1] = locations[i][1];
            int result = (rand() % 4);
            if( result == 0){
                  //cout<<"UP";
                locations[i][1]+=0.01;
                if(locations[i][1] > -10){
                    locations[i][1] = -75;
                }
                  
            }
            else if( result == 1){
                //cout<<"Down";
                locations[i][1]-=0.01;
                if(locations[i][1] < -75){
                    locations[i][1] = -10;
                }
            }
            else{
                //cout<<"Forward";
                locations[i][0]-=0.006;
                if(locations[i][0] < 0){
                    locations[i][0] = 160;
                }
            }
        }
    }
    glEnd();
    glutSwapBuffers();
}
void timer(int){
    glutPostRedisplay();
    timeX+=0.2;
    glutTimerFunc(1000.0/60.0,timer,0);
}
int main(int argc, char **argv) {
    w1.k = 0.09;
    w1.A = 6;
    w1.w = 0.1;
    w1.phi = 0;
    w2.k = 0.09;
    w2.A = 6;
    w2.w = 0.1;
    w2.phi = 0;
    for (int i = 0; i < 20; i++) {
        float colour1 = randomColour();
        float colour2 = randomColour();
        float colour3 = randomColour();
        colours.push_back(Vector3f(colour1, colour2, colour3));
        float x = randomFloatX();
        float y = randomFloatY();
        locations.push_back(Vector2f(x, y));
        locations_old.push_back(Vector2f(x, y));
    }
    glutInit(&argc, argv);
    glutInitWindowSize(20 * 30, 20 * 30);
    glutCreateWindow("Fishies");
    //glEnable(GL_CULL_FACE);
    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_TEXTURE_3D);
    glutReshapeFunc(wave_reshape);
    glutDisplayFunc(wave_display);
    glutKeyboardFunc(keyboardFunc);
    glutTimerFunc(100, timer, 0);
    glutMainLoop();
}

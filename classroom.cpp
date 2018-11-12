/*
*
* Transform3DCuboid.cpp
*
*   This program shows a 3-D cuboid in rotation.
*
* To compile:
*   gcc Transform3DCuboid.cpp -lglut -lGL -lGLU
*/
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
 
using namespace std;
 
//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y) {
    switch (key) {
        case 27: //Escape key
            exit(0);
    }
}
 
//Initializes 3D rendering
void initRendering() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING); //Enable lighting
    glEnable(GL_LIGHT0); //Enable light #0
    glEnable(GL_LIGHT1); //Enable light #1
    glEnable(GL_NORMALIZE); //Automatically normalize normals
    //glShadeModel(GL_SMOOTH); //Enable smooth shading
}
 
//Called when the window is resized
void handleResize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}
 
float _angle = -70.0f;


void drawCube(float dimensions[], float center[], float colour[]) {

    //Set the colour here
    glColor3f(colour[0], colour[1], colour[2]);
    glBegin(GL_QUADS);
 
    //Front
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-dimensions[0]-center[0], -dimensions[1]-center[1], dimensions[2]-center[2]);
    glVertex3f(dimensions[0]-center[0], -dimensions[1]-center[1], dimensions[2]-center[2]);
    glVertex3f(dimensions[0]-center[0], dimensions[1]-center[1], dimensions[2]-center[2]);
    glVertex3f(-dimensions[0]-center[0], dimensions[1]-center[1], dimensions[2]-center[2]);
 
    //Right
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(dimensions[0]-center[0], -dimensions[1]-center[1], -dimensions[2]-center[2]);
    glVertex3f(dimensions[0]-center[0], dimensions[1]-center[1], -dimensions[2]-center[2]);
    glVertex3f(dimensions[0]-center[0], dimensions[1]-center[1], dimensions[2]-center[2]);
    glVertex3f(dimensions[0]-center[0], -dimensions[1]-center[1], dimensions[2]-center[2]);
 
    //Back
    glNormal3f(dimensions[0]-center[0], dimensions[1]-center[1], -dimensions[2]-center[2]);
    glVertex3f(-dimensions[0]-center[0], -dimensions[1]-center[1], -dimensions[2]-center[2]);
    glVertex3f(-dimensions[0]-center[0], dimensions[1]-center[1], -dimensions[2]-center[2]);
    glVertex3f(dimensions[0]-center[0], dimensions[1]-center[1], -dimensions[2]-center[2]);
    glVertex3f(dimensions[0]-center[0], -dimensions[1]-center[1], -dimensions[2]-center[2]);
 
    //Left
    glNormal3f(-dimensions[0]-center[0], dimensions[1]-center[1], dimensions[2]-center[2]);
    glVertex3f(-dimensions[0]-center[0], -dimensions[1]-center[1], -dimensions[2]-center[2]);
    glVertex3f(-dimensions[0]-center[0], -dimensions[1]-center[1], dimensions[2]-center[2]);
    glVertex3f(-dimensions[0]-center[0], dimensions[1]-center[1], dimensions[2]-center[2]);
    glVertex3f(-dimensions[0]-center[0], dimensions[1]-center[1], -dimensions[2]-center[2]);

    //Top
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-dimensions[0]-center[0], dimensions[1]-center[1], dimensions[2]-center[2]);
    glVertex3f(dimensions[0]-center[0], dimensions[1]-center[1], dimensions[2]-center[2]);
    glVertex3f(dimensions[0]-center[0], dimensions[1]-center[1], -dimensions[2]-center[2]);
    glVertex3f(-dimensions[0]-center[0], dimensions[1]-center[1], -dimensions[2]-center[2]);

    //Bottom
    glNormal3f(dimensions[0]-center[0], -1.0f, 0.0f);
    glVertex3f(-dimensions[0]-center[0], -dimensions[1]-center[1], dimensions[2]-center[2]);
    glVertex3f(dimensions[0]-center[0], -dimensions[1]-center[1], dimensions[2]-center[2]);
    glVertex3f(dimensions[0]-center[0], -dimensions[1]-center[1], -dimensions[2]-center[2]);
    glVertex3f(-dimensions[0]-center[0], -dimensions[1]-center[1], -dimensions[2]-center[2]);
 
    glEnd();
 
}
 
//Draws the 3D scene
void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
 
    //Translate the entire system to some other place (can use this for manual camera motion?)
    glTranslatef(0.0f, 0.0f, -20.0f);
 
    //Add ambient light
    GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f}; //Color (0.2, 0.2, 0.2)
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
 
    //Add positioned light
    GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
    GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f}; //Positioned at (4, 0, 8)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
 
    //Add directed light
    GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f}; //Color (0.5, 0.2, 0.2)
    //Coming from the direction (-1, 0.5, 0.5)
    GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
 
    glRotatef(_angle, 1.0f, 0.0f, 1.0f);

    //Chair sample

    float dimensions[3], center[3], colour[3];
    dimensions[0] = 3.0f; dimensions[1] = 10.0f; dimensions[2] = 0.3f;
    center[0] = center[1] = 0.0f; center[2] = -4.0f;
    colour[0] = 1.0f; colour[1] = colour[2] = 0.0f;
    drawCube(dimensions, center, colour);

    dimensions[0] = 3.0f; dimensions[1] = 5.0f; dimensions[2] = 0.3f;
    center[0] = 0.0f; center[1] = -5.0f; center[2] = 4.0f;
    colour[1] = 1.0f; colour[0] = colour[2] = 0.0f;
    drawCube(dimensions, center, colour);

    dimensions[0] = 3.0f; dimensions[1] = 0.3f; dimensions[2] = 4.3f;
    center[0] = center[1] = center[2] = 0.0f;
    colour[2] = 1.0f; colour[0] = colour[1] = 0.0f;
    drawCube(dimensions, center, colour);  

    //Chair sample end

    //BUG: flicker while rotating chair (probably due to changing views and decision of which surface to show)  

    glutSwapBuffers();
}
 
void update(int value) {
    _angle += 1.5f;
    if (_angle > 360) {
        _angle -= 360;
    }
 
    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}
 
int main(int argc, char** argv) {
    //Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
 
    //Create the window
    glutCreateWindow("Rotating 3D Cuboid");
    initRendering();
 
    //Set handler functions
    glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(handleResize);
 
    //Add a timer
   glutTimerFunc(25, update, 0);
 
    glutMainLoop();
}

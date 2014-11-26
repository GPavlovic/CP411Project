#include <GL/glew.h>
#include <GL/glut.h>

#include "glaux.h" // for reading bmp files
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "Shape.hpp"
#include "Camera.hpp"
#include "World.hpp"
#include "lodepng.h"
#include "Duck.hpp"

GLint winWidth = 800, winHeight = 800;

// move the view setting to camera
//GLfloat xeye = 3.0, yeye = 3.0, zeye = 7.0;  //  Viewing-coordinate origin.
//GLfloat xref = 0.0, yref = 0.0, zref = 0.0;  //  Look-at point.
//GLfloat Vx = 0.0, Vy = 1.0, Vz = 0.0;        //  View up vector.
//GLfloat vangle = 40.0, dnear = 1.0, dfar = 10.0;

// temp share variable
GLfloat theta = 0.0;

GLfloat red = 1.0, green = 1.0, blue = 1.0;  //color

GLint moving = 0, xBegin = 0, yBegin = 0, coordinate = 1, type = 1,
		selected = 0;

GLfloat P = 1.0;

GLint style = 1, lightOn = 0, showLight = 1, lightAdjust = 1;

//Lighting substitute lx, ly, lz
GLfloat position[] = { 1.8, 1.8, 1.5, 1.0 };
GLfloat positionSolar[] = { 0.0, 0.0, 0.0, 1.0 };

GLfloat ambient[] = { 0.1, 0.1, 0.3, 1.0 };
GLfloat diffuse[] = { 0.6, 0.6, 1.0, 1.0 };
GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };

//GLfloat lmodel_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
//GLfloat local_view[] = { 0.0 };

//Material
GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat mat_ambient_color[] = { 1, 1, 1, 1 };
GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat high_shininess[] = { 100.0 };
GLfloat mat_emission[] = { 1, 1, 1, 1 };

Camera myEye;
World myWorld;

GLuint programObject; // GLSL object

// Array to hold the ducks
Duck duckArray[10];
// Array to hold times for launching ducks
GLfloat launchTimes[10];
// Counters for the timer function
//// Time that has passed by
GLfloat timePassed;
//// Number of ducks to draw from the array.
GLfloat numDucksDrawn;

// Location of the mouse
GLint mouseXCurr, mouseYCurr;

GLuint texture[3];
vector<unsigned char> texture2[2];


bool loadbmp(UINT textureArray[], LPSTR strFileName, int ID) {
	if (!strFileName)
		return false;
	AUX_RGBImageRec *pBitMap = auxDIBImageLoad(strFileName);
	if (pBitMap == NULL)
		exit(0);

	glGenTextures(1, &textureArray[ID]);
	glBindTexture(GL_TEXTURE_2D, textureArray[ID]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, pBitMap->sizeX, pBitMap->sizeY, 0, GL_RGB,
	GL_UNSIGNED_BYTE, pBitMap->data);
	return true;
}

void display(void) {

	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-winWidth / 2, winWidth / 2, -winHeight / 4, 3 * winHeight / 4);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0); // Set display-window color to black

	// Background of the sky
	glColor3f(0.68, 0.85, 0.9);
    glBegin(GL_POLYGON);
    glVertex2f(winWidth / 2, 0.0);
    glVertex2f(winWidth / 2, 3 * winHeight / 4);
    glVertex2f(-winWidth / 2, 3 * winHeight / 4);
    glVertex2f(-winWidth / 2, 0.0);
    glEnd();

    // TODO: Fix the tree
//	glPushMatrix();
//	glEnable(GL_TEXTURE_2D);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexImage2D(GL_TEXTURE_2D, 0, 4, 150, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, &texture2[0]);
//	glBegin(GL_QUADS);
//	glTexCoord2f(0.0, 1.0); glVertex2f(-winWidth / 2, 1.71 * winWidth / 4);
//	glTexCoord2f(1.0, 1.0); glVertex2f(-winWidth / 4, 1.71 * winWidth / 4);
//	glTexCoord2f(1.0, 0.0); glVertex2f(-winWidth / 4, 0.0);
//	glTexCoord2f(0.0, 0.0); glVertex2f(-winWidth / 2, 0.0);
//	glEnd();
//	glPopMatrix();
//	glDisable(GL_TEXTURE_2D);

    // TODO: Fix the bush
//	glPushMatrix();
//	glEnable(GL_TEXTURE_2D);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexImage2D(GL_TEXTURE_2D, 0, 4, 150, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, &texture2[0]);
//	glBegin(GL_QUADS);
//	glTexCoord2f(0.0, 1.0); glVertex2f((winWidth / 2) - 112, 136);
//	glTexCoord2f(1.0, 1.0); glVertex2f(winWidth / 2, 136);
//	glTexCoord2f(1.0, 0.0); glVertex2f(winWidth / 2, 0.0);
//	glTexCoord2f(0.0, 0.0); glVertex2f((winWidth / 2) - 112, 0.0);
//	glEnd();
//	glPopMatrix();
//	glDisable(GL_TEXTURE_2D);

	// Texture of the grass
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	// Left side of the screen grass
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0); glVertex2f(-winWidth / 2, winHeight / 8 + 20);
	glTexCoord2f(1.0, 1.0); glVertex2f(0.0, winHeight / 8 + 20);
	glTexCoord2f(1.0, 0.0); glVertex2f(0.0, 0.0);
	glTexCoord2f(0.0, 0.0); glVertex2f(-winWidth / 2, 0.0);
	glEnd();
	// Right side of the screen grass
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0); glVertex2f(0.0, winHeight / 8 + 20);
	glTexCoord2f(1.0, 1.0); glVertex2f(winWidth / 2, winHeight / 8 + 20);
	glTexCoord2f(1.0, 0.0); glVertex2f(winWidth / 2, 0.0);
	glTexCoord2f(0.0, 0.0); glVertex2f(0.0, 0.0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	// The ground colour of original duck hunt
	glColor3f(0.55, 0.54, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(winWidth / 2, 0.0);
	glVertex2f(winWidth / 2, -winHeight / 2);
	glVertex2f(-winWidth / 2, -winHeight / 2);
	glVertex2f(-winWidth / 2, 0.0);
	glEnd();

	// Texture of the grass
	glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, texture[1]);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0); glVertex2f(100, winHeight / 8 + 100);
	glTexCoord2f(1.0, 1.0); glVertex2f(winWidth / 2, winHeight / 8 + 100);
	glTexCoord2f(1.0, 0.0); glVertex2f(winWidth / 2, 100);
	glTexCoord2f(0.0, 0.0); glVertex2f(100, 100);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	// Draw ducks from Duck array, if they are in the range
	for (int i = 0; i<numDucksDrawn; i++) {
		// Draw ducks in the duck array
	}

	// Draw crosshair
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(mouseXCurr+5, mouseYCurr);
	glVertex2f(mouseXCurr-5, mouseYCurr);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(mouseXCurr, mouseYCurr+5);
	glVertex2f(mouseXCurr, mouseYCurr-5);
	glEnd();

	glFlush();
	glutSwapBuffers();
}

void winReshapeFcn(GLint newWidth, GLint newHeight) {
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	winWidth = newWidth;
	winHeight = newHeight;
}

void mouseAction(int button, int action, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
		// Shoot gun
			// Calculate direction
			// Animate
			// Check for hit
	}

	glutPostRedisplay();
}

void mouseMotion(GLint x, GLint y) {
	GLfloat rx, ry, rz, theta;

}

void passiveMotion(GLint x, GLint y){
	mouseXCurr = x - 400;
	mouseYCurr = 600 - y;

	glutPostRedisplay();
}

void reset() {


	glutPostRedisplay();
}

// Increment positions of the ducks in the array
void incrementDucks(int keepGoing) {
	int i;

	for (i = 0; i<numDucksDrawn; i++) {
		// Increment the ducks position for ducks in the duckArray
	}

	glutTimerFunc(40, incrementDucks, 1);
}

void init(void) {

	myWorld.myLight->SetLight(1.8, 1.8, 1.5, 1.0);

	myEye.SetCamera(3.0, 3.0, 7.0, 0, 1, 0, 0, 0.0, 0, 20.0, 1.0, 10.0);

	glClearColor(0.0, 0.0, 0.0, 1.0);  // Set display-window color to black
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, winWidth, winHeight, 0.0);
	glColor3f(1.0, 0.0, 0.0);

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_SMOOTH);

	// load texture here for the world, weapons, and ducks
	loadbmp(texture, "textures/ground.bmp", 0);
	loadbmp(texture, "textures/red.bmp", 1);
//	loadbmp(texture, "textures/tree.bmp", 1);
//	loadbmp(texture, "textures/bush.bmp", 2);

	// This function runs through duck array and increments x value of duck
	incrementDucks(1);

	// Create 10 random times for ducks to be launched.
	for(int i = 0; i < 10; i ++) //for loop needed for 6 different random heights
				{
					launchTimes[i] = (rand() % 3000) + 1;
				}
	// Create 10 ducks
	for(int i = 0; i < 10; i ++) //for loop needed for 6 different random heights
	{

		duckArray[i].height=(rand() % 300) + 80;
	}

}



void mainMenu(GLint option) {
	switch (option) {
	case 1:
		reset();
		break;
	case 2:
		exit(0);
		break;
	}
	glutPostRedisplay();
}

void menu() {


	glutCreateMenu(mainMenu);      // Create main pop-up menu.
	// Possible game options, like timing of duck launches or something
	glutAddMenuEntry(" Reset ", 1);
	glutAddMenuEntry(" Quit", 2);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("DuckHunt by Braden Poirier and Goran Pavlovic");

	glewInit();
	init();
	menu();

	glutDisplayFunc(display);
	glutMotionFunc(mouseMotion);
	glutMouseFunc(mouseAction);
	glutPassiveMotionFunc(passiveMotion);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();

	return 0;
}


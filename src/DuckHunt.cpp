//TODO: Possible features- Dog? 3D cube for levels? multi-directional flying? Different ducks?
#include <GL/glew.h>
#include <GL/glut.h>
#include <sstream>
#include "glaux.h" // for reading bmp files
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <Windows.h>
#include <MMSystem.h>
#include "Shape.hpp"
#include "Camera.hpp"
#include "World.hpp"
#include "Duck.hpp"
#include "Zapper.hpp"

#define numDucksInLevel1 1
#define numDucksInLevel2 1
#define numDucksInLevel3 1
#define numDucksInLevel4 1


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
GLint duckSize = 50;

GLint style = 1, lightOn = 0, showLight = 1, lightAdjust = 1;
//The player's overall score.
GLint playerScore=0;

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
Duck duckArray[numDucksInLevel4];
// Array to hold times for launching ducks
GLfloat launchTimes[numDucksInLevel4];
// Counters for the timer functionk
//// Time that has passed by
GLfloat timePassed;
//// Number of ducks to draw from the array.
GLint numDucksDrawn=0;
//Number of ducks in game
GLint numDucksInLevel=0;
// Location of the mouse
GLint mouseXCurr, mouseYCurr;

// Zapper
Zapper myZapper;

GLuint texture[16];
vector<unsigned char> texture2[2];

GLint duckIsDying=0,gameIsStarting=1;

//Used to indicate to the display function to display the level number.
GLint level1IsStarting=1, level2IsStarting=1, level3IsStarting=1, level4IsStarting=1,
		level1Finished=0, level2Finished=0, level3Finished=0, level4Finished=0,levelIsFinished,duckPosition=0, currLevel = 1, endOfGame = 0;

void startLevel(int level);
void startNextLevel(int level);
void make_RGBA_texture_from_RGB_pixels( GLubyte *pixels, int width, int height );

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
	make_RGBA_texture_from_RGB_pixels(pBitMap->data,pBitMap->sizeX, pBitMap->sizeY);
	return true;
}
void make_RGBA_texture_from_RGB_pixels( GLubyte *pixels, int width, int height )
{
	int texture_size = width*height;
	GLubyte* RGBA_pixels = new GLubyte[ texture_size*4 ];
	for ( int i=0; i<texture_size;i++)	{
		RGBA_pixels[i*4] = pixels[i*3];
		RGBA_pixels[i*4+1] = pixels[i*3+1];
		RGBA_pixels[i*4+2] = pixels[i*3+2];

		if ( pixels[i*3+0] == 255 && pixels[i*3+1] == 255 && pixels[i*3+2] == 255 )
			RGBA_pixels[i*4+3] = 0;
		else
			RGBA_pixels[i*4+3] = 255;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, RGBA_pixels );
	delete []RGBA_pixels;
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
    glVertex3f(winWidth / 2, 0.0, 0.0);
	glVertex3f(winWidth / 2, 3 * winHeight / 4, 0.0);
	glVertex3f(-winWidth / 2, 3 * winHeight / 4, 0.0);
	glVertex3f(-winWidth / 2, 0.0, 0.0);
    glEnd();


    // The bush
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, texture[9]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0); glVertex2f((winWidth / 2) - 128, 203);
	glTexCoord2f(1.0, 1.0); glVertex2f(winWidth / 2, 203);
	glTexCoord2f(1.0, 0.0); glVertex2f(winWidth / 2, 75.0);
	glTexCoord2f(0.0, 0.0); glVertex2f((winWidth / 2) - 128, 75.0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glColor3f(1, 1, 1);

	// Draw ducks from Duck array, if they are in the range
	for(int i = 0; i < numDucksDrawn; i ++)
	{
		if (!duckArray[i].shot==1){
			// Texture of the duck.
			duckArray[i].draw(0);
		}
	}

    // Draw the tree
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, texture[8]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0); glVertex2f(-winWidth / 2, 1.71 * winWidth / 4 + 85);
	glTexCoord2f(1.0, 1.0); glVertex2f(-winWidth / 4, 1.71 * winWidth / 4 + 85);
	glTexCoord2f(1.0, 0.0); glVertex2f(-winWidth / 4, 85.0);
	glTexCoord2f(0.0, 0.0); glVertex2f(-winWidth / 2, 85.0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	// Draw any dead ducks
	void drawOneDeadDuck();
	drawOneDeadDuck();

	// The ground colour of original duck hunt
	glColor3f(0.55, 0.54, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(winWidth / 2, 0.0, 0.0);
	glVertex3f(winWidth / 2, -winHeight / 2, 0.0);
	glVertex3f(-winWidth / 2, -winHeight / 2, 0.0);
	glVertex3f(-winWidth / 2, 0.0, 0.0);
	glEnd();
	// Texture of the grass
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	// Left side of the screen grass
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0); glVertex3f(-winWidth / 2, winHeight / 8 + 20, 0.1);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.0, winHeight / 8 + 20, 0.1);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.0, 0.0, 0.1);
	glTexCoord2f(0.0, 0.0); glVertex3f(-winWidth / 2, 0.0, 0.1);
	glEnd();
	// Right side of the screen grass
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.0, winHeight / 8 + 20, 0.1);
	glTexCoord2f(1.0, 1.0); glVertex3f(winWidth / 2, winHeight / 8 + 20, 0.1);
	glTexCoord2f(1.0, 0.0); glVertex3f(winWidth / 2, 0.0, 0.1);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, 0.1);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);


	// For the first level show the introscreen
	if (level1IsStarting) {
		// The intro outline
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_POLYGON);
		glVertex3f(205 ,45, 0.4);
		glVertex3f(205,255, 0.4);
		glVertex3f(-205, 255, 0.4);
		glVertex3f(-205, 45, 0.4);
		glEnd();
		// The intro texture
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glBindTexture(GL_TEXTURE_2D, texture[7]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 1.0); glVertex3f(-200, 250, 0.4);
		glTexCoord2f(1.0, 1.0); glVertex3f(200, 250, 0.4);
		glTexCoord2f(1.0, 0.0); glVertex3f(200, 50, 0.4);
		glTexCoord2f(0.0, 0.0); glVertex3f(-200, 50, 0.4);
		glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	}

	// The outline of the score-board
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_POLYGON);
		glVertex3f(winWidth/2-15 , -winHeight / 4+5, 0.2);
		glVertex3f(winWidth/2-15,(-winHeight / 4)+55, 0.2);
		glVertex3f(winWidth / 2-125, (-winHeight / 4)+55, 0.2);
		glVertex3f(winWidth/2-125, -winHeight / 4+5, 0.2);
		glEnd();

	// The score-board
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex3f(winWidth/2-20 , -winHeight / 4+10, 0.3);
		glVertex3f(winWidth/2-20, (-winHeight / 4)+50, 0.3);
		glVertex3f(winWidth/2-120, (-winHeight / 4)+50, 0.3);
		glVertex3f(winWidth/2-120, -winHeight / 4+10, 0.3);
		glEnd();

	    if((level2IsStarting&&level1Finished)||(level3IsStarting&&level2Finished)||(level4IsStarting&&level3Finished)){
		// Displaying the level number.
				glColor3f(1.0, 1.0, 1.0);
				glBegin(GL_POLYGON);
				glVertex3f(205 ,45, 0.4);
				glVertex3f(205,255, 0.4);
				glVertex3f(-205, 255, 0.4);
				glVertex3f(-205, 45, 0.4);
				glEnd();

			// The level-board
				glPushMatrix();
				glEnable(GL_TEXTURE_2D);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glBindTexture(GL_TEXTURE_2D, texture[8 + currLevel]);
				glBegin(GL_QUADS);
				glTexCoord2f(0.0, 1.0); glVertex3f(-200, 250, 0.4);
				glTexCoord2f(1.0, 1.0); glVertex3f(200, 250, 0.4);
				glTexCoord2f(1.0, 0.0); glVertex3f(200, 50, 0.4);
				glTexCoord2f(0.0, 0.0); glVertex3f(-200, 50, 0.4);
				glEnd();
				glPopMatrix();
				glDisable(GL_TEXTURE_2D);
	    }

	    if (endOfGame) {
	    	// The level board outline
			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_POLYGON);
			glVertex3f(205 ,45, 0.4);
			glVertex3f(205,255, 0.4);
			glVertex3f(-205, 255, 0.4);
			glVertex3f(-205, 45, 0.4);
			glEnd();
			// The level board
			glPushMatrix();
			glEnable(GL_TEXTURE_2D);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glBindTexture(GL_TEXTURE_2D, texture[15]);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 1.0); glVertex3f(-200, 250, 0.4);
			glTexCoord2f(1.0, 1.0); glVertex3f(200, 250, 0.4);
			glTexCoord2f(1.0, 0.0); glVertex3f(200, 50, 0.4);
			glTexCoord2f(0.0, 0.0); glVertex3f(-200, 50, 0.4);
			glEnd();
			glPopMatrix();
			glDisable(GL_TEXTURE_2D);

			// Print the players final score
			std::ostringstream score;
			score << playerScore;
			glColor3f(1.0f, 1.0f, 1.0f);//needs to be called before RasterPos
			glRasterPos2i(0, 100);
			void * font = GLUT_BITMAP_9_BY_15;
			for (std::string::iterator i = score.str().begin(); i != score.str().end(); ++i)
			{
				char c = *i;
				glutBitmapCharacter(font, c);
			}
	    }
	//Display Player score
	// First the word "Score:"
	glColor3f(1.0f, 1.0f, 1.0f);//needs to be called before RasterPos
	glRasterPos2i(winWidth/2 - 93, 35 - winHeight/2 + winHeight/4);
	std::ostringstream oss1;
	std::ostringstream oss2;
	oss1 << "Score: ";
	oss2 << playerScore;
	void * font = GLUT_BITMAP_9_BY_15;

	for (std::string::iterator i = oss1.str().begin(); i != oss1.str().end(); ++i)
	{
		char c = *i;
		glutBitmapCharacter(font, c);
	}
	// Now the actual player score
	glColor3f(1.0f, 1.0f, 1.0f);//needs to be called before RasterPos
	glRasterPos2i(winWidth/2 - 93, 20 - winHeight/2 + winHeight/4);
	for (std::string::iterator i = oss2.str().begin(); i != oss2.str().end(); ++i)
	{
		char c = *i;
		glutBitmapCharacter(font, c);
	}

	// Draw gun
	myZapper.updateLoc();
	myZapper.draw();


	// Draw crosshair
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(mouseXCurr+5, mouseYCurr, 0.4);
	glVertex3f(mouseXCurr-5, mouseYCurr, 0.4);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(mouseXCurr, mouseYCurr+5, 0.4);
	glVertex3f(mouseXCurr, mouseYCurr-5, 0.4);
	glEnd();

	glFlush();
	glutSwapBuffers();
}

void drawOneDeadDuck() {
	// Draw dead ducks from Duck array, if they are in the range.
		for(int i = 0; i < numDucksDrawn; i ++)
		{
			if(duckArray[i].dying==1&&duckArray[i].shot==1){
				if(duckIsDying==1){
					//Shot
					duckArray[i].draw(1);
				}
				else if(duckIsDying==2){
					//Falling right
					duckArray[i].draw(2);
				}
				else if(duckIsDying==3){
					//Falling left
					duckArray[i].draw(3);
				}
				else{
					//Off screen
					duckArray[i].dying=0;
				}
			}
		}
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
		for(int i = 0; i < numDucksDrawn; i++) //Find the duck that was shot.
		{
			double radius = sqrt(duckSize*duckSize+duckSize*duckSize); //Calculate Radius.
			double dx = (duckArray[i].distance+duckSize - x+winWidth/2), dy = (duckArray[i].height+duckSize-(winHeight/2+winHeight/4)+y);
			double distance = sqrt((dx * dx + dy * dy));
			if (distance <= radius && !duckArray[i].shot) {
				playerScore+=1500;
				duckArray[i].shot=1;
				duckArray[i].dying=1;
				duckIsDying=1;
				void killDucks(int notDeadYet);
				PlaySound("sounds/shot.wav", NULL, SND_ASYNC | SND_FILENAME);
				killDucks(1);
			}
		}
	}

	glutPostRedisplay();
}

void mouseMotion(GLint x, GLint y) {
	GLfloat rx, ry, rz, theta;

}

//Move the cross-hair according to the mouse position.
void passiveMotion(GLint x, GLint y){
	mouseXCurr = x - winWidth/2;
	mouseYCurr = winHeight/2+winHeight/4 - y;

	glutPostRedisplay();
}

void reset() {


	glutPostRedisplay();
}

// Increment positions of the ducks in the array
void incrementDucks(int keepGoing) {
	for (int i = 0; i < numDucksDrawn; i++) {
		if (!duckArray[i].shot == 1 && duckArray[numDucksInLevel - 1].distance <= winWidth / 2 - 10) {
			//Increment x position of duck. Ducks get faster after each level.
			if (level3Finished) {
				duckArray[i].distance += 40;
			} else if (level2Finished) {
				duckArray[i].distance += 30;
			} else if (level1Finished) {
				duckArray[i].distance += 20;
			} else {
				duckArray[i].distance += 10;
			}
		} else if (duckArray[numDucksInLevel - 1].distance > winWidth / 2 - 10 || duckArray[numDucksInLevel - 1].shot) {
			//The last duck has left the screen or has been shot. The level is over.
			if (level3Finished) {
				level4Finished = 1;
			} else if (level2Finished) {
				level3Finished = 1;
			} else if (level1Finished) {
				level2Finished = 1;
			} else {
				level1Finished = 1;
			}
			//TODO:Create delay for ducks to fall off screen before next level begins
			//Clear the duck array to prepare for next level.
			for (int i = 0; i < numDucksInLevel; i++) {
				duckArray[i].distance = -winWidth / 2;
				duckArray[i].height = 0;
				duckArray[i].shot = 0;
				duckArray[i].dying = 0;
			}
			numDucksDrawn = 0;
			return;
		}
	}
	glutPostRedisplay();
	if (keepGoing) {
		glutTimerFunc(40, incrementDucks, 1);
	}
}

// Put the ducks into the game
void generateDucks(int keepGoing) {
	GLfloat time=launchTimes[numDucksDrawn];
	numDucksDrawn+=1;
	if (keepGoing && numDucksDrawn<numDucksInLevel) {
		glutTimerFunc(time, generateDucks, 1);
	}
}

// Alternate between wing up/down
void flyDucks(int wingsUp) {
	//Check if there are any ducks on the screen that have not been shot.
	//If so, we will play a quacking noise.
	int notShot = 0;
	Duck thisDuckIsntShot;
	for (int i = 0; i < numDucksDrawn; i++) {

		if (!duckArray[i].shot == 1) {
			notShot = 1;
			thisDuckIsntShot = duckArray[i];
		}
	}
	//Check that the last duck is still on the screen.
	//If so, draw animation.
	if (duckArray[numDucksInLevel - 1].distance + 550 <= winWidth) {
		//This required some hacking around to find the right time to quack the second time.
		//(Since the .wav file contains two quacks, and we dont want to quack after every wing
		//flap.
		if (wingsUp % 2 == 0 && wingsUp <= 10) {
			duckPosition=0;
			glutTimerFunc(200, flyDucks, wingsUp + 1);

		} else if (wingsUp % 2 == 1 && wingsUp <= 10 && wingsUp != 5) {
			duckPosition=1;
			glutTimerFunc(200, flyDucks, wingsUp + 1);
		} else if (duckArray[numDucksInLevel - 1].distance<= winWidth/2) {
			duckPosition=2;
			if (wingsUp != 5 || gameIsStarting) {
				if (notShot) {
					if (thisDuckIsntShot.distance <= winWidth/2) {
						PlaySound("sounds/quack.wav", NULL,
								SND_ASYNC | SND_FILENAME);
					}
				}
				gameIsStarting = 0;
				glutTimerFunc(200, flyDucks, 1);
			} else {
				glutTimerFunc(200, flyDucks, wingsUp + 1);
			}
		}
	}
}

//Create delays for dead duck animation
void killDucks(int notDeadYet) {
	if(notDeadYet==1){
		//Shot
		glutTimerFunc(200, killDucks, 2);
	}
	else if(notDeadYet==2){
		//Fall left
		duckIsDying=2;
		glutTimerFunc(150, killDucks, 3);
	}
	else if(notDeadYet==3){
		duckIsDying=3;
		//Fall right
		glutTimerFunc(150, killDucks, 4);
	}
	else if(notDeadYet==4){
		duckIsDying=2;
		//Fall right
		glutTimerFunc(150, killDucks, 5);
	}
	else if(notDeadYet==5){
		duckIsDying=3;
		//Fall right
		glutTimerFunc(150, killDucks, 6);
	}
	else if(notDeadYet==6){
		duckIsDying=2;
		//Fall right
		glutTimerFunc(150, killDucks, 7);
	}
	else if(notDeadYet==7){
		duckIsDying=3;
		//Fall right
		glutTimerFunc(150, killDucks, 8);
	}

	else{
		duckIsDying=0;
	}
}


// Make any shot duck "fall" into the grass.
void fallingDucks(int keepGoing) {
	for (int i = 0; i < numDucksDrawn; i++) {
		if (duckArray[i].dying==1&&duckArray[i].shot==1 &&duckArray[i].height >= -winHeight/2) {
				duckArray[i].height-= 10;
		}
	}
	glutPostRedisplay();
	if(!(level2IsStarting&&level1Finished)||(level3IsStarting&&level2Finished)||(level4IsStarting&&level3Finished)){
		glutTimerFunc(40, fallingDucks, 1);
	}
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
	loadbmp(texture, "textures/wingsDown.bmp", 1);
	loadbmp(texture, "textures/red.bmp", 2);
	loadbmp(texture, "textures/dead.bmp", 3);
	loadbmp(texture, "textures/zapper.bmp", 4);
	loadbmp(texture, "textures/wingsUp.bmp", 5);
	loadbmp(texture, "textures/quack.bmp", 6);
	loadbmp(texture, "textures/introScreen.bmp", 7);
	loadbmp(texture, "textures/tree.bmp", 8);
	loadbmp(texture, "textures/bush.bmp", 9);
	loadbmp(texture, "textures/level2.bmp", 10);
	loadbmp(texture, "textures/level3.bmp", 11);
	loadbmp(texture, "textures/level4.bmp", 12);
	loadbmp(texture, "textures/falling1.bmp", 13);
	loadbmp(texture, "textures/falling2.bmp", 14);
	loadbmp(texture, "textures/endScreen.bmp", 15);
	//loadbmp(texture, "textures/level1.bmp", 5);

	PlaySound("sounds/start.wav", NULL, SND_ASYNC | SND_FILENAME);
	//Start level 1
	numDucksInLevel=numDucksInLevel1;
	glutTimerFunc(7000, startLevel, 1);
}

void startLevel(int level){
	currLevel++;
	//check which level it is.
	if (level == 1) {
		level1IsStarting = 0;
		numDucksInLevel=numDucksInLevel1;
	} else if (level == 2) {
		level2IsStarting = 0;
		numDucksInLevel=numDucksInLevel2;
	} else if (level == 3) {
		level3IsStarting = 0;
		numDucksInLevel=numDucksInLevel3;
	} else if (level == 4) {
		level4IsStarting = 0;
		numDucksInLevel=numDucksInLevel4;
	} else {
		//TODO: Display player's final score.
		endOfGame = 1;
		glutPostRedisplay();
	}
	if (!endOfGame) {
		// This function runs through duck array and increments x value of duck
		incrementDucks(1);
		// Create random times for ducks to be launched.
		for(int i = 0; i < numDucksInLevel; i ++)
			{
				launchTimes[i] = (rand() % 1000) + 1000;
			}
		// Create ducks.
		for(int i = 0; i < numDucksInLevel; i ++)
			{
				duckArray[i].height=(rand() % 280) + 120;
			}
		generateDucks(1);
		flyDucks(1);
		void fallingDucks(int keepGoing);
		fallingDucks(1);
		startNextLevel(level);
	}
}

void startNextLevel(int level) {
	if (level == 1) {
		levelIsFinished=level1Finished;
	} else if (level == 2) {
		levelIsFinished=level2Finished;
	} else if (level == 3) {
		levelIsFinished=level3Finished;
	} else if (level == 4) {
		levelIsFinished=level4Finished;
	} else {
		//Exit screen
	}
	if(!levelIsFinished){
		glutTimerFunc(40, startNextLevel, level);
	}
	else{
		if(level!=4){
			PlaySound("sounds/start.wav", NULL, SND_ASYNC | SND_FILENAME);
		}
		glutTimerFunc(7000, startLevel, level + 1);

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
	//TODO: Possible game options, like timing of duck launches or something
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
	glutSetCursor(GLUT_CURSOR_NONE);
	glutMainLoop();

	return 0;
}


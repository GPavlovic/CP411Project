#include "Zapper.hpp"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define PI 3.14159265

extern GLint winWidth, winHeight;
extern GLuint texture[5];
extern GLint mouseXCurr, mouseYCurr;
int shouldUpdate = 0;
GLfloat radianRot = 0;

Zapper::Zapper() {
	// Bottom left
	location[0][0] = -32;
	location[0][1] = -256;
	// Top left
	location[1][0] = -32;
	location[1][1] = 0;
	// Top right
	location[2][0] = 32;
	location[2][1] = 0;
	// Bottom right
	location[3][0] = 32;
	location[3][1] = -256;

	// Rotation of the weapon
	rotation = 1;
}

void Zapper::draw() {
	// Texture of the Zapper.
	glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, texture[4]);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(location[0][0], location[0][1]);
	glTexCoord2f(0.0, 1.0); glVertex2f(location[1][0], location[1][1]);
	glTexCoord2f(1.0, 1.0); glVertex2f(location[2][0], location[2][1]);
	glTexCoord2f(1.0, 0.0); glVertex2f(location[3][0], location[3][1]);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void Zapper::calcRot() {
// TODO(Goran): Calculate the rotation in order to point at the mouse location.
	if (mouseXCurr <= -winWidth /3) { // Mouse is on the left side of the screen
		rotation = 0;
	} else if (mouseXCurr >= winWidth / 3) { // Mouse is on the right side of the screen
		rotation = 2;
	} else { // Mouse is in the center of the screen
		rotation = 1;
	}
}

void Zapper::updateLoc() {
	switch(rotation) {
		case 0: {
			// Bottom left
			location[0][0] = -32;
			location[0][1] = -256;
			// Top left
			location[1][0] = -32;
			location[1][1] = 0;
			// Top right
			location[2][0] = 32;
			location[2][1] = 0;
			// Bottom right
			location[3][0] = 32;
			location[3][1] = -256;

			// Update bottom left vertex
			location[0][0] = location[0][0] * cos(PI/4) - location[0][1] * sin(PI/4);
			location[0][1] = location[0][1] * cos(PI/4) + location[0][0] * sin(PI/4);
			// Update top left vertex
			location[1][0] = location[1][0] * cos(PI/4) - location[1][1] * sin(PI/4);
			location[1][1] = location[1][1] * cos(PI/4) + location[1][0] * sin(PI/4);
			// Update top right vertex
			location[2][0] = location[2][0] * cos(PI/4) - location[2][1] * sin(PI/4);
			location[2][1] = location[2][1] * cos(PI/4) + location[2][0] * sin(PI/4);
			// Update bottom right vertex
			location[3][0] = location[3][0] * cos(PI/4) - location[3][1] * sin(PI/4);
			location[3][1] = location[3][1] * cos(PI/4) + location[3][0] * sin(PI/4);

			break;
		}
		case 1: {
			// Bottom left
			location[0][0] = -32;
			location[0][1] = -256;
			// Top left
			location[1][0] = -32;
			location[1][1] = 0;
			// Top right
			location[2][0] = 32;
			location[2][1] = 0;
			// Bottom right
			location[3][0] = 32;
			location[3][1] = -256;
			break;
		}
		case 2: {
			// Bottom left
			location[0][0] = -32;
			location[0][1] = -256;
			// Top left
			location[1][0] = -32;
			location[1][1] = 0;
			// Top right
			location[2][0] = 32;
			location[2][1] = 0;
			// Bottom right
			location[3][0] = 32;
			location[3][1] = -256;

			// Update bottom left vertex
			location[0][0] = location[0][0] * cos(-PI/4) - location[0][1] * sin(-PI/4);
			location[0][1] = location[0][1] * cos(-PI/4) + location[0][0] * sin(-PI/4);
			// Update top left vertex
			location[1][0] = location[1][0] * cos(-PI/4) - location[1][1] * sin(-PI/4);
			location[1][1] = location[1][1] * cos(-PI/4) + location[1][0] * sin(-PI/4);
			// Update top right vertex
			location[2][0] = location[2][0] * cos(-PI/4) - location[2][1] * sin(-PI/4);
			location[2][1] = location[2][1] * cos(-PI/4) + location[2][0] * sin(-PI/4);
			// Update bottom right vertex
			location[3][0] = location[3][0] * cos(-PI/4) - location[3][1] * sin(-PI/4);
			location[3][1] = location[3][1] * cos(-PI/4) + location[3][0] * sin(-PI/4);

			break;
		}
	}

}

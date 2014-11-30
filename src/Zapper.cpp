#include "Zapper.hpp"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

extern GLint winWidth, winHeight;
extern GLuint texture[16];
extern GLint mouseXCurr, mouseYCurr;

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

void Zapper::updateLoc() {
	// Bottom left
	location[0][0] = mouseXCurr - 32;
	location[0][1] = -256;
	// Top left
	location[1][0] = mouseXCurr - 32;
	location[1][1] = 0;
	// Top right
	location[2][0] = mouseXCurr + 32;
	location[2][1] = 0;
	// Bottom right
	location[3][0] = mouseXCurr + 32;
	location[3][1] = -256;
}

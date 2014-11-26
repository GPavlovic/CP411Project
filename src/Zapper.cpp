#include "Zapper.hpp"

extern GLint winWidth, winHeight;
extern Duck duckArray[10];
extern GLint mouseXCurr, mouseYCurr;

Zapper::Zapper() {
	// Bottom left
	location[0][0] = -22;
	location[0][1] = -150;
	// Top left
	location[1][0] = -22;
	location[1][1] = 0;
	// Top right
	location[2][0] = 23;
	location[2][1] = 0;
	// Bottom right
	location[3][0] = 23;
	location[3][1] = -150;
}

void Zapper::draw() {
	// Texture of the Zapper.
	glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, texture[2]);

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
}

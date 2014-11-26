#ifndef ZAPPER_H
#define ZAPPER_H

#include <GL/glut.h>

class Zapper {
protected:
	GLfloat location[4][2];	// Original location of the gun
	GLint rotation; // Current rotation to point at mouse
public:
	Zapper(); // Zapper constructor
	void draw(); // Drawing the Zapper
	void calcRot(); // Calculate the rotation of the gun
};

#endif
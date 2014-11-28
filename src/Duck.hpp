#ifndef DUCK_H
#define DUCK_H

#include <GL/glut.h>

class Duck {
protected:


public:
	Duck(); // Duck constructor
	void draw(int); // Drawing the duck
	GLfloat height, distance;	// Circle for the location of the duck
	GLint shot, dying; // Current action the duck is performing
};



#endif

#ifndef DUCK_H
#define DUCK_H

#include <GL/glut.h>

class Duck {
protected:
	GLfloat height, distance;	// Circle for the location of the duck
	GLint shot; // Current action the duck is performing

public:
	Duck(); // Duck constructor
	void draw(); // Drawing the duck
};



#endif

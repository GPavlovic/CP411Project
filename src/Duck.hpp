#ifndef DUCK_H
#define DUCK_H

#include <GL/glut.h>

#include "Shape.hpp"

class Duck: public Shape{
protected:


public:
	Duck(); // Duck constructor
	void draw(); // Drawing the duck
	GLfloat height, distance;	// Circle for the location of the duck
	GLint shot; // Current action the duck is performing
};



#endif

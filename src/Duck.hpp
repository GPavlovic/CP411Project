#ifndef DUCK_H
#define DUCK_H

#include <GL/glut.h>

#include "Shape.hpp"

class Duck: public Shape{
protected:
	GLfloat location;	// Circle for the location of the duck
	GLint wingsUp, wingsDown, shot; // Current action the duck is performing

public:
	Duck(); // Duck constructor
	void draw(); // Drawing the duck
};



#endif

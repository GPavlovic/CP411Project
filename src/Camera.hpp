#ifndef LIGHT_H
#define LIGHT_H

#include <GL/glut.h>
#include "Shape.hpp"

class Camera: public Shape {
public:
	// eye at center of eye coordinate system, y as V-up vector
	GLfloat xref, yref, zref;   // look at point
	GLfloat vangle, dnear, dfar;  // view angle,

	Camera();

	void SetCamera(GLfloat xeye1, GLfloat yeye1, GLfloat zeye, GLfloat Vx1,
			GLfloat Vy1, GLfloat Vz1, GLfloat xref1, GLfloat yref1,
			GLfloat zref1, GLfloat vangle1, GLfloat dnear1, GLfloat dfar1);

	void draw();
};

#endif


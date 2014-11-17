#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <GL/glut.h>
#include "Shape.hpp"


class Light: public Shape {

public:

	GLfloat P;

	Light();

	~Light() {};

	void SetLight(GLfloat lx1,  GLfloat ly1, GLfloat lz1, GLfloat P1);

	void draw();
};

#endif


#ifndef SOLAR_H
#define SOLAR_H

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#include <GL/glut.h>
#include "glaux.h" // for reading bmp files

#include "Sphere.hpp"

class Solar  {
protected:

public:
	Sphere* Sun;
	Sphere* Earth;
	Sphere* Moon;

	Solar();
	void draw_world();
	void set_color(GLfloat, GLfloat, GLfloat);
	void reset();
	bool loadbmp(UINT textureArray[], LPSTR strFileName, int ID);

};

#endif

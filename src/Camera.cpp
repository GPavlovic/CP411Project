#include "Camera.hpp"

Camera::Camera() {
	this->MC.mat[0][3] = 3;
	this->MC.mat[1][3] = 3;
	this->MC.mat[2][3] = 7;
	this->MC.mat[0][1] = 0;
	this->MC.mat[1][1] = 1;
	this->MC.mat[2][1] = 0;
	xref = 0.0;
	yref = 0.0;
	zref = 0.0;
	vangle = 40.0;
	dnear = 0.0;
	dfar  = 10.0;
}

void Camera::SetCamera(	GLfloat xeye1,  GLfloat yeye1, GLfloat zeye1,
		GLfloat Vx1,  GLfloat Vy1, GLfloat Vz1,
		GLfloat xref1,  GLfloat yref1, GLfloat zref1,
		GLfloat vangle1, GLfloat dnear1, GLfloat dfar1) {

	this->MC.mat[0][3] = xeye1;
	this->MC.mat[1][3] = yeye1;
	this->MC.mat[2][3] = zeye1;
	this->MC.mat[0][1] = Vx1;
	this->MC.mat[1][1] = Vy1;
	this->MC.mat[2][1] = Vz1;

	xref = xref1;
	yref =  yref1;
	zref = zref1;
    vangle = vangle1;
    dnear = dnear1;
    dfar = dfar1;
}

void Camera::draw() {}




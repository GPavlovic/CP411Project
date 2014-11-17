#include "Light.hpp"

extern GLint showLight;

Light::Light() {
	P = 1.0;
	this->MC.mat[0][3] = 1.8;
	this->MC.mat[1][3] = 1.8;
	this->MC.mat[2][3] = 1.5;
}


void Light::SetLight(GLfloat lx1,  GLfloat ly1, GLfloat lz1, GLfloat P1) {
	this->MC.mat[0][3] = lx1;
	this->MC.mat[1][3] = ly1;
	this->MC.mat[2][3] = lz1;
    P = P1;
}

void Light::draw() {
	if (showLight) {
		glPushMatrix();
		this->ctm_multiply();
		glScalef(1, 1, 1);
		glColor3f(P, P, P);
		glutSolidSphere(0.1, 20, 20);
		glPopMatrix();
	}
}



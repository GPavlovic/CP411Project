#include "Duck.hpp"

extern GLint winWidth, winHeight;
extern GLuint texture[4];
extern Duck duckArray[10];

Duck::Duck() {
	this->distance = -winWidth/2;
	this->height=0;
	this->shot=0;
	this->dying=0;
	// Find random point on left side of sky, change lanuchHeight
}

void Duck::draw(int dead){
	// Texture of the duck.
	glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	if(dead)
		glBindTexture(GL_TEXTURE_2D, texture[3]);
	else
	    glBindTexture(GL_TEXTURE_2D, texture[1]);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0); glVertex2f(this->distance, 100 + this->height);
	glTexCoord2f(1.0, 1.0); glVertex2f(this->distance + 100, 100 + this->height);
	glTexCoord2f(1.0, 0.0); glVertex2f(this->distance + 100, this->height);
	glTexCoord2f(0.0, 0.0); glVertex2f(this->distance, this->height);
	glEnd();
	glDisable(GL_TEXTURE_2D);

}

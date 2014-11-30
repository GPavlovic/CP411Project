#include "Duck.hpp"

extern GLint winWidth, winHeight, duckPosition;
extern GLuint texture[15];
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
	if(dead==1)
		glBindTexture(GL_TEXTURE_2D, texture[3]); //Draw shot duck
	else if(dead==2)
		glBindTexture(GL_TEXTURE_2D, texture[13]); //Draw falling left duck
	else if(dead==3)
		glBindTexture(GL_TEXTURE_2D, texture[14]); //Draw falling right duck
	else if (duckPosition==1)
		glBindTexture(GL_TEXTURE_2D, texture[5]); //Draw flying duck
	else if(duckPosition==2)
		glBindTexture(GL_TEXTURE_2D, texture[6]); //Draw quacking duck
	else
		glBindTexture(GL_TEXTURE_2D, texture[1]); //Draw coasting duck

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0); glVertex2f(this->distance, 100 + this->height);
	glTexCoord2f(1.0, 1.0); glVertex2f(this->distance + 100, 100 + this->height);
	glTexCoord2f(1.0, 0.0); glVertex2f(this->distance + 100, this->height);
	glTexCoord2f(0.0, 0.0); glVertex2f(this->distance, this->height);
	glEnd();
	glDisable(GL_TEXTURE_2D);

}

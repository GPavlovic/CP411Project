#include "Duck.hpp"

extern GLint winWidth, winHeight;

Duck::Duck() {
	this->distance = -winWidth/2;
	this->height=0;
	this->shot=0;
	// Find random point on left side of sky, change lanuchHeight

}

void Duck::draw(){
	// Draw the texture at the location, with the given action it is performing (wingsUp, wingsDown, shot)
	// Do not draw if shot = 1
}

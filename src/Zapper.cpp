#include "Zapper.hpp"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define PI 3.14159265

extern GLint winWidth, winHeight;
extern GLuint texture[5];
extern GLint mouseXCurr, mouseYCurr;

Zapper::Zapper() {
	// Bottom left
	location[0][0] = -22;
	location[0][1] = -150;
	// Top left
	location[1][0] = -22;
	location[1][1] = 0;
	// Top right
	location[2][0] = 23;
	location[2][1] = 0;
	// Bottom right
	location[3][0] = 23;
	location[3][1] = -150;

	// Rotation of the weapon
	rotation = 0;
}

void Zapper::draw() {
	// Texture of the Zapper.
	glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, texture[2]);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(location[0][0], location[0][1]);
	glTexCoord2f(0.0, 1.0); glVertex2f(location[1][0], location[1][1]);
	glTexCoord2f(1.0, 1.0); glVertex2f(location[2][0], location[2][1]);
	glTexCoord2f(1.0, 0.0); glVertex2f(location[3][0], location[3][1]);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void Zapper::calcRot() {
// TODO(Goran): Calculate the rotation in order to point at the mouse location.
	GLint mouseVector[2][2];
	GLint gunVector[2][2];
	GLint resultVector[2][2];
	GLint dist1, dist2, dist3;
	GLfloat temp;

	// Set current mouse vector, moved 150 pixels up in order to add to the gun vector properly
	mouseVector[0][0] = 0; // Tail X
	mouseVector[0][1] = 150; // Tail Y
	mouseVector[1][0] = mouseXCurr; // Head X
	mouseVector[1][1] = mouseYCurr + 150; // Head Y

	// Set the current gun vector, from the origin
	gunVector[0][0] = 0; // Tail X
	gunVector[0][1] = 0; // Tail Y
	gunVector[1][0] = 0; // Head X
	gunVector[1][1] = 150; // Head Y

	// Calculate the result vector (adding mouse and gun vectors)
	resultVector[0][0] = 0; // Tail X
	resultVector[0][1] = 0; // Tail Y
	resultVector[1][0] = mouseVector[1][0]; // Head X
	resultVector[1][1] = mouseVector[1][1] + gunVector[1][1] - 150; // Head Y

	// Find the length of the result vector
	dist1 = sqrt(pow(resultVector[1][0], 2) + pow(resultVector[1][1], 2));
	// Find the length of the gun vector
	dist2 = 150;
	// Find the length of the mouse vector
	dist3 = sqrt(mouseXCurr * mouseXCurr + mouseYCurr * mouseYCurr);

	printf("dist1: %d, dist2: %d, dist3: %d\n", dist1, dist2, dist3);
	// Calculate the angle
	//rotation = acos((pow(dist1,2)+pow(dist2,2)-pow(dist3,2))/(2 * dist1 * dist2));
	rotation = acos(0.2);
	printf("Rotation 0: %d\n", rotation);
	rotation = (rotation * 180.0) / PI; // Convert from radians to degrees
	printf("Rotation 1: %d\n", rotation);
	// If the mouse is in positive X then the angle of rotation should be negative to rotate clockwise
	if (location[1][0] > 0) {
		rotation = -rotation;
	}
	printf("rotation 2: %d\n", rotation);
}

void Zapper::updateLoc() {
	// Update bottom left vertex
	location[0][0] = location[0][0] * cos(rotation) - location[0][1] * sin(rotation);
	location[0][1] = location[0][1] * cos(rotation) + location[0][0] * sin(rotation);
	// Update top left vertex
	location[1][0] = location[1][0] * cos(rotation) - location[1][1] * sin(rotation);
	location[1][1] = location[1][1] * cos(rotation) + location[1][0] * sin(rotation);
	// Update top right vertex
	location[2][0] = location[2][0] * cos(rotation) - location[2][1] * sin(rotation);
	location[2][1] = location[2][1] * cos(rotation) + location[2][0] * sin(rotation);
	// Update bottom right vertex
	location[3][0] = location[3][0] * cos(rotation) - location[3][1] * sin(rotation);
	location[3][1] = location[3][1] * cos(rotation) + location[3][0] * sin(rotation);
}

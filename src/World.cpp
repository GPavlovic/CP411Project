/**
 * File: World.hpp
 */

#include "World.hpp"

extern GLint showLight;

World::World() {

//	list[0] = new Cube();
//	list[1] = new Cube();

	myLight = new Light();

    /* object list
	ObjectList.push_back(list[0]);
	ObjectList.push_back(list[1]);
    */

	/* object vector
	ObjectVector = new std::vector<Shape*>(2);
	std::vector<Shape*>& ObjectVecotrRef = *ObjectVector;
	ObjectVectorRef[0] = list[0];
	ObjectVectorRef[1] = list[1];
    */
}

World::~World(){
//    delete list[0];
//    delete list[1];

	delete myLight;
}

void World::clean(){
//    delete list[0];
//    delete list[1]
	delete myLight;
	myLight = NULL;
}


void World::reSet(){
//    delete list[0];
//    delete list[1]
	delete myLight;
	myLight = new Light();
}


void World::draw_world() {

	if (showLight) {
		myLight->draw();
	}
}


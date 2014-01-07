// Explode.cpp
// Explode class used for easier access in vector lists


#define _USE_MATH_DEFINES	// Pi variable

#include "Explode.h"
#include "glut.h"
#include <cstdio>
#include <math.h>

Explode::~Explode(){
}

// Inital Explode generation set fields
Explode::Explode(int bType, float angleStart, Coordinate p){
	pos = p;
	angle = angleStart;
	ExplodeType = bType;
	age = 1;
	switch(ExplodeType){
		case 1:	// Default Explode
			colour[0] = 0.0;
			colour[1] = 0.3;
			colour[2] = 0.0;
			size = 2.0;
			break;
		case 2:	// second Explode type
			colour[0] = 0.3;
			colour[1] = 0.5;
			colour[2] = 0.0;
			size = 2.5;
			break;
		case 3:	// third Explode type
			colour[0] = 1.0;
			colour[1] = 0.0;
			colour[2] = 1.0;
			size = 0.8;
			break;
		}	
}



// Returns the age value
int Explode::getAge(){
	return age;
}

// Sets the age value
void Explode::setAge(int a){
	age = a;
}

// Returns the size of the Explode
float Explode::getSize(){
	return size;
}

// Set Explode size
void Explode::setSize(float newSize){
	size = newSize;
}

// Set the colour
void Explode::setColour(float r, float g, float b){
	colour[0] = r;
	colour[1] = g;
	colour[2] = b;
}

// Set the Explode type
void Explode::setExplodeType(int a){
	ExplodeType = a;
}

// Returns the ExplodeType
int Explode::getExplodeType(){
	return ExplodeType;
}

// Set the position
void Explode::setPosition(Coordinate p){
	pos = p;
}

// Return the Explodes position
Coordinate Explode::getPosition(){
	return pos;
}


// update the Explode
// This will calculate the new pos and velocity based on acceleration and speed
void Explode::Update(){
	
	age += 1;
	
	if(age > 45)
		age = 0;
	// Updat the explosion

	angle += 1.4;
	float radian = angle * (M_PI/180);
	pos.x = 155 * cosf(radian);
	pos.z = 155 * sinf(radian);
	
	
}


// Render the Explode
void Explode::Render(){

	
	glPushMatrix();
	if(age == 0){
		glColor4f(1.0, 1.0, 1.0, 1.0); // Destroyed make it red
	}else
		glColor4f(colour[0], colour[1], colour[2], 1.0);	// normal colour

	glTranslated(pos.x, pos.y, pos.z);			// Translate to its position
	switch (ExplodeType){					// Draw the specific type of Explode
		case 1:
			glutSolidSphere(size, 15, 15);
			break;
		case 2:
			glutSolidCube(size);
			break;
		case 3:
			glutWireSphere(size, 15, 15);
			break;
	}
	glPopMatrix();
}
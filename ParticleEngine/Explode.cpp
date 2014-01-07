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
			colour[0] = 1.0;
			colour[1] = 0.0;
			colour[2] = 0.0;
			size = 2.0;
			moveDist = 0.2;
			// Set up particle positions
			// Front Right
			particles[0].setX(pos.x + size);
			particles[0].setY(pos.y + size);
			particles[0].setZ(pos.z + size);
			// Top back right
			particles[1].setX(pos.x + size);
			particles[1].setY(pos.y + size);
			particles[1].setZ(pos.z - size);
			// top front left
			particles[2].setX(pos.x - size);
			particles[2].setY(pos.y + size);
			particles[2].setZ(pos.z + size);
			// top back left
			particles[3].setX(pos.x - size);
			particles[3].setY(pos.y + size);
			particles[3].setZ(pos.z - size);
			// bottom front right
			particles[4].setX(pos.x + size);
			particles[4].setY(pos.y - size);
			particles[4].setZ(pos.z + size);
			// bottom back right
			particles[5].setX(pos.x + size);
			particles[5].setY(pos.y - size);
			particles[5].setZ(pos.z - size);
			// bottom front left
			particles[6].setX(pos.x - size);
			particles[6].setY(pos.y - size);
			particles[6].setZ(pos.z + size);
			// bottom back left
			particles[7].setX(pos.x - size);
			particles[7].setY(pos.y - size);
			particles[7].setZ(pos.z - size);
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
	
	if(age > 35)
		age = 0;
	// Update the explosion
	/*angle += 1.4;
	float radian = angle * (M_PI/180);
	pos.x = 155 * cosf(radian);
	pos.z = 155 * sinf(radian);*/

	// Set up particle positions
	// Front Right
	particles[0].setX(particles[0].x + moveDist);
	particles[0].setY(particles[0].y + moveDist);
	particles[0].setZ(particles[0].z + moveDist);
	// Top back right
	particles[1].setX(particles[1].x + moveDist);
	particles[1].setY(particles[1].y + moveDist);
	particles[1].setZ(particles[1].z - moveDist);
	// top front left
	particles[2].setX(particles[2].x - moveDist);
	particles[2].setY(particles[2].y + moveDist);
	particles[2].setZ(particles[2].z + moveDist);
	// top back left
	particles[3].setX(particles[3].x - moveDist);
	particles[3].setY(particles[3].y + moveDist);
	particles[3].setZ(particles[3].z - moveDist);
	// bottom front right
	particles[4].setX(particles[4].x + moveDist);
	particles[4].setY(particles[4].y - moveDist);
	particles[4].setZ(particles[4].z + moveDist);
	// bottom back right
	particles[5].setX(particles[5].x + moveDist);
	particles[5].setY(particles[5].y - moveDist);
	particles[5].setZ(particles[5].z - moveDist);
	// bottom front left
	particles[6].setX(particles[6].x - moveDist);
	particles[6].setY(particles[6].y - moveDist);
	particles[6].setZ(particles[6].z + moveDist);
	// bottom back left
	particles[7].setX(particles[7].x - moveDist);
	particles[7].setY(particles[7].y - moveDist);
	particles[7].setZ(particles[7].z - moveDist);	
	
}


// Render the Explode
void Explode::Render(){

		
	glColor4f(colour[0], colour[1], colour[2], 1.0);	// normal colour

	switch (ExplodeType){					// Draw the specific type of Explode
	case 1:
		for(int i = 0; i < 8; i++){
			glPushMatrix();
			glTranslated(particles[i].x, particles[i].y, particles[i].z);
			//glRotatef(-45, 0.0, 0.0, 1.0);
			glScalef(2.0, 2.0 , 2.0);
			glutWireTetrahedron();
			glPopMatrix();
		}
			break;
		case 2:
			glPushMatrix();
			glTranslated(pos.x, pos.y, pos.z);
			glutSolidCube(size);
			glPopMatrix();
			break;
		case 3:
			glPushMatrix();
			glTranslated(pos.x, pos.y, pos.z);
			glutWireSphere(size, 15, 15);
			glPopMatrix();
			break;
	}
}
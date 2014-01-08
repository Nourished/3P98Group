// Powers.cpp
// Powers class used for easier access in vector lists


#define _USE_MATH_DEFINES	// Pi variable

#include "Powers.h"
#include "glut.h"
#include <cstdio>
#include <math.h>

Powers::~Powers(){
}

// Inital Powers generation set fields
Powers::Powers(int pt, float angleStart, Coordinate p){
	pos = p;
	angle = angleStart;
	powerType = pt;
	powerRotate = 0.0;
	switch(powerType){
		case 1:	// First power
			colour[0] = 1.0;
			colour[1] = 0.0;
			colour[2] = 0.0;
			age = 500;
			size = 2.0;
			break;
		case 2:	// Second power
			colour[0] = 0.3;
			colour[1] = 0.5;
			colour[2] = 0.0;
			age = 500;
			size = 2.0;
			break;
		case 3:	// third Power
			colour[0] = 1.0;
			colour[1] = 0.0;
			colour[2] = 1.0;
			age = 500;
			size = 3.0;
			break;
		}	
}

// Returns the age value
int Powers::getAge(){
	return age;
}

// Sets the age value
void Powers::setAge(int a){
	age = a;
}


// Set the colour
void Powers::setColour(float r, float g, float b){
	colour[0] = r;
	colour[1] = g;
	colour[2] = b;
}

// Set the Powers type
void Powers::setPowerType(int a){
	powerType = a;
}

// Returns the PowerType
int Powers::getPowerType(){
	return powerType;
}

// Returns the size
float Powers::getSize(){
	return size;
}

// Set the position
void Powers::setPosition(Coordinate p){
	pos = p;
}

// Return the Powerss position
Coordinate Powers::getPosition(){
	return pos;
}

// Set the angle
void Powers::setAngle(float a){
	angle = a;
}

// Return the Powerss position
float Powers::getAngle(){
	return angle;
}


// update the Powers
// This will calculate the new pos and velocity based on acceleration and speed
void Powers::Update(){
	
	age -= 1;

	if ( powerRotate >=360 ){ //update enemy donut rotation
			 powerRotate = 0;
		}else{
			powerRotate += 10;
		}
	// Doesnt move
}


// Render the Powers
void Powers::Render(){
	
	
	
	glColor4f(colour[0], colour[1], colour[2], 1.0);	// normal colour
	
	switch (powerType){					// Draw the specific type of Powers
		case 1: //Power type 1
			glPushMatrix();
			glTranslated(pos.x, pos.y, pos.z);	
			glutSolidTeapot(size*2);
			glPopMatrix();
			glPushMatrix();		
			glTranslated(pos.x, pos.y, pos.z);	
			glColor4f(1.0, 1.0, 0.0 , 1.0);			
			glRotated(powerRotate , 0.0 , 1.0 , 0.0);
			glutSolidTorus(size, size*3 , 50, 50);	  //change 4.0 to size in project			
			glPopMatrix();				
			break;
		case 2: //Power type 2
			glPushMatrix();
			glTranslated(pos.x, pos.y, pos.z);			// Translate to its position
			glutSolidTeapot(size*2);
			glPopMatrix();
			glPushMatrix();		
			glTranslated(pos.x, pos.y, pos.z);			// Translate to its position
			glColor4f(1.0, 1.0, 0.0 , 1.0);			
			glRotated(powerRotate , 0.0 , 1.0 , 0.0);
			glutSolidTorus(size, size*3 , 50, 50);	  			
			glPopMatrix();				break;
		case 3: //Power type 3
			glPushMatrix();
			glTranslated(pos.x, pos.y, pos.z);			// Translate to its position
			glutSolidTeapot(size*2);
			glPopMatrix();
			glPushMatrix();	
			glTranslated(pos.x, pos.y, pos.z);			// Translate to its position
			glColor4f(1.0, 1.0, 0.0 , 1.0);			
			glRotated(powerRotate , 0.0 , 1.0 , 0.0);
			glutSolidTorus(size, size*3 , 50, 50);	  		
			glPopMatrix();	
			break;
	}	

	
}
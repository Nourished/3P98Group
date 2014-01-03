// Eric Gummerson	4585469
// Bullet.cpp
// Bullet class used for easier access in vector lists
// Contains information on the Bullet
// Including speed, velocity, acceleration, position
// Colour, Bullet type

#define _USE_MATH_DEFINES	// Pi variable

#include "Bullet.h"
#include "glut.h"
#include <cstdio>
#include <math.h>

Bullet::~Bullet(){
}

// Inital Bullet generation set fields
Bullet::Bullet(int bType, bool d, float angleStart, Coordinate p){
	pos = p;
	angle = angleStart;
	dir = d;
	bulletType = bType;
	age = 1;
	alpha = 1.0;	
	switch(bulletType){
		case 1:	// Default bullet
			colour[0] = 0.0;
			colour[1] = 0.0;
			colour[2] = 0.0;
			speed = 1.0;
			size = 2.0;
			break;
		case 2:	// second bullet type
			colour[0] = 0.3;
			colour[1] = 0.5;
			colour[2] = 0.0;
			speed = 1.4;
			size = 3.5;
			break;
		case 3:	// third bullet type
			colour[0] = 1.0;
			colour[1] = 0.0;
			colour[2] = 1.0;
			speed = 0.7;
			size = 4.5;
			break;
		}	
}



// Returns the age value
int Bullet::getAge(){
	return age;
}

// Sets the age value
void Bullet::setAge(int aStatus){
	age = aStatus;
}


// Set Bullet size
void Bullet::setSize(float newSize){
	size = newSize;
}

// ~~~~~~ IS SPEED NEEDED ??? ~~~~~~~~
// Set the speed, cannot be set past 8
void Bullet::setSpeed(double sp){
	if(sp < 8.01)
		speed = sp;
	else
		speed = 8;	// Max speed
}//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// Set the colour
void Bullet::setColour(float r, float g, float b){
	colour[0] = r;
	colour[1] = g;
	colour[2] = b;
}

// Set the Bullet type
void Bullet::setBulletType(int a){
	bulletType = a;
}

// Set the alpha (visibility) of the Bullet
void Bullet::setAlpha(double alp){
	alpha = alp;
}

// Returns the bulletType
int Bullet::getBulletType(){
	return bulletType;
}

// Set the position
void Bullet::setPosition(Coordinate p){
	pos = p;
}

// Return the Bullets position
Coordinate Bullet::getPosition(){
	return pos;
}


// update the Bullet
// This will calculate the new pos and velocity based on acceleration and speed
void Bullet::Update(){
	
	age += 1;
	
	if(age > 65)
		age = 0;
	// Move the bullet in a straight line
	if(dir){
		// Right
		angle += 1.4 * speed;
		float radian = angle * (M_PI/180);
		pos.x = 155 * cosf(radian);
		pos.z = 155 * sinf(radian);
	}else {
		// Left
		angle -= 1.4 * speed;
		float radian = angle * (M_PI/180);
		pos.x = 155 * cosf(radian);
		pos.z = 155 * sinf(radian);

	}
	
}


// Render the Bullet
void Bullet::Render(){

	glPushMatrix();
	glColor4f(colour[0], colour[1], colour[2], alpha);	// Colour it
	glTranslated(pos.x, pos.y, pos.z);			// Translate to its position
	switch (bulletType){					// Draw the specific type of Bullet
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
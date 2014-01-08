// Bullet.cpp
// Bullet class used for easier access in vector lists


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
	bulletRotation = 0.0;
	switch(bulletType){
		case 1:	// Default bullet
			colour[0] = 1.0;
			colour[1] = 0.0;
			colour[2] = 0.0;
			speed = 1.2;
			size = 2.0;
			break;
		case 2:	// second bullet type
			colour[0] = 0.3;
			colour[1] = 0.5;
			colour[2] = 0.0;
			speed = 1.2;
			size = 2.0;
			break;
		case 3:	// third bullet type
			colour[0] = 1.0;
			colour[1] = 0.0;
			colour[2] = 1.0;
			speed = 1.4;
			size = 3.0;
			break;
		}	
}

// Returns the age value
int Bullet::getAge(){
	return age;
}

// Sets the age value
void Bullet::setAge(int a){
	age = a;
}

// Returns the size of the bullet
float Bullet::getSize(){
	return size;
}

// Set Bullet size
void Bullet::setSize(float newSize){
	size = newSize;
}

// Set the speed
void Bullet::setSpeed(double sp){	
	speed = sp;

}

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
	
	if(age > 60)
		age = 0;
	// Move the bullet in a straight line
	if(dir){
		// Left
		angle += 1.4 * speed;
		float radian = angle * (M_PI/180);
		pos.x = 155 * cosf(radian);
		pos.z = 155 * sinf(radian);
	}else {
		// Right
		angle -= 1.4 * speed;
		float radian = angle * (M_PI/180);
		pos.x = 155 * cosf(radian);
		pos.z = 155 * sinf(radian);

	}

	if ( bulletRotation >=360 ){ //update enemy donut rotation
			 bulletRotation = 0;
		}else{
			bulletRotation += 10;
		}
	
}

// Render the Bullet
void Bullet::Render(){
	
	
	if(age == 0){
		glColor4f(1.0, 1.0, 1.0, alpha); // Destroyed make it red
	}else
		glColor4f(colour[0], colour[1], colour[2], alpha);	// normal colour

	
	switch (bulletType){					// Draw the specific type of Bullet
		case 1: //bullet type 2
			glPushMatrix();
			glTranslated(pos.x, pos.y, pos.z);			// Translate to its position
			glutSolidSphere(size, 15, 15);
			glPopMatrix();				
			break;
		case 2: //bullet type 2
			glPushMatrix();
			glTranslated(pos.x, pos.y, pos.z);			// Translate to its position
			glutSolidSphere(size, 15, 15);
			glPopMatrix();
			glPushMatrix();
			glTranslated(pos.x, pos.y+5, pos.z);			// Translate to its position
			glutSolidSphere(size, 15, 15);
			glPopMatrix();

			if(dir){
				// Left
				glPushMatrix();
				glTranslated(pos.x, pos.y, pos.z);			// Translate to its position
				glRotatef(-90, 0.0 , 1.0 , 0.0 );
				glutSolidCone(size, 15, 25,25);
				glPopMatrix();

				glPushMatrix();
				glTranslated(pos.x, pos.y+5, pos.z);			// Translate to its position
				glRotatef(-90, 0.0 , 1.0 , 0.0 );
				glutSolidCone(size, 15, 25,25);
				glPopMatrix();

				}else{
				// Right
				glPushMatrix();
				glTranslated(pos.x, pos.y, pos.z);			// Translate to its position
				glRotatef(90, 0.0 , 1.0 , 0.0 );
				glutSolidCone(size, 15, 25,25);
				glPopMatrix();

				glPushMatrix();
				glTranslated(pos.x, pos.y+5, pos.z);			// Translate to its position
				glRotatef(90, 0.0 , 1.0 , 0.0 );
				glutSolidCone(size, 15, 25,25);
				glPopMatrix();
				}			
			break;
		case 3: //bullet type 3
			glPushMatrix();
				glTranslated(pos.x-4, pos.y, pos.z);			// Translate to its position
				glRotatef(bulletRotation, 0.7 , 1.0 , 0.4 );
				glScalef(size, size, size);
				glutSolidTetrahedron();
			glPopMatrix();

			glPushMatrix();
				glTranslated(pos.x-4, pos.y+5, pos.z);			// Translate to its position
				glRotatef(bulletRotation, 0.7 , 1.0 , 0.4 );
				glScalef(size, size, size);
				glutSolidTetrahedron();
			glPopMatrix();

			glPushMatrix();
				glTranslated(pos.x+1, pos.y+2.5, pos.z);			// Translate to its position
				glRotatef(bulletRotation, 0.7 , 1.0 , 0.4 );
				glScalef(size, size, size);
				glutSolidTetrahedron();
			glPopMatrix();
			break;
	}	
}
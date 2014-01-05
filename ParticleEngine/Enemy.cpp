// Enemy.cpp


#define _USE_MATH_DEFINES	// Pi variable

#include "Enemy.h"
#include "glut.h"
#include <cstdio>
#include <math.h>

Enemy::~Enemy(){
}

// Inital Enemy generation set fields
Enemy::Enemy(int bType, bool d, float angleStart, Coordinate p){
	pos = p;
	angle = angleStart;
	dir = d;
	enemyType = bType;
	age = 1;
	alpha = 1.0;	
	switch(enemyType){
		case 1:	// Default Enemy
			colour[0] = 0.0;
			colour[1] = 1.0;
			colour[2] = 0.0;
			speed = 0.4;
			size = 1.5;
			break;
		case 2:	// second Enemy type
			colour[0] = 0.0;
			colour[1] = 0.8;
			colour[2] = 0.4;
			speed = 0.7;
			size = 2.5;
			break;
		case 3:	// third Enemy type
			colour[0] = 1.0;
			colour[1] = 0.0;
			colour[2] = 1.0;
			speed = 0.9;
			size = 3.5;
			break;
		}	
}



// Returns the age value
int Enemy::getAge(){
	return age;
}

// Sets the age value
void Enemy::setAge(int aStatus){
	age = aStatus;
}

// Returns the size of the enemy
float Enemy::getSize(){
	return size;
}

// Set Enemy size
void Enemy::setSize(float newSize){
	size = newSize;
}

// ~~~~~~ IS SPEED NEEDED ??? ~~~~~~~~
// Set the speed, cannot be set past 8
void Enemy::setSpeed(double sp){
	if(sp < 8.01)
		speed = sp;
	else
		speed = 8;	// Max speed
}//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// Set the colour
void Enemy::setColour(float r, float g, float b){
	colour[0] = r;
	colour[1] = g;
	colour[2] = b;
}

// Set the Enemy type
void Enemy::setEnemyType(int a){
	enemyType = a;
}

// Returns the EnemyType
int Enemy::getEnemyType(){
	return enemyType;
}

// Set the alpha (visibility) of the Enemy
void Enemy::setAlpha(double alp){
	alpha = alp;
}


// Set the position
void Enemy::setPosition(Coordinate p){
	pos = p;
}

// Return the Enemys position
Coordinate Enemy::getPosition(){
	return pos;
}


// update the Enemy
// This will calculate the new pos and velocity based on acceleration and speed
void Enemy::Update(){
	
	// Move the Enemy in a straight line
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


// Render the Enemy
void Enemy::Render(){

	glPushMatrix();
	glColor4f(colour[0], colour[1], colour[2], alpha);	// Colour it
	glTranslated(pos.x, pos.y, pos.z);			// Translate to its position
	switch (enemyType){					// Draw the specific type of Enemy
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
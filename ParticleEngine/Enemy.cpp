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
// This will calculate the new pos for the enemy
// Depending on the enemy, goes in a straight line or heads towards the player
void Enemy::Update(Coordinate pp, float pa){
	float ar, range;

	switch(enemyType){
	case 1:	// First enemy type
		// Move the Enemy in a straight line
		if(dir){
			// Right
			angle += 1.4 * speed;
			if(angle > 360.0)
				angle -= 360.0;
			float radian = angle * (M_PI/180);
			pos.x = 155 * cosf(radian);
			pos.z = 155 * sinf(radian);
		}else {
			// Left
			angle -= 1.4 * speed;
			if(angle < 0.0)
				angle += 360.0;
			float radian = angle * (M_PI/180);
			pos.x = 155 * cosf(radian);
			pos.z = 155 * sinf(radian);
		}
		break;
	case 2:	// Second enemy, moves close to player when in range
		// Move towards player if within a range
		// Angle between player and enemy
		ar = angle > pa ? angle - pa: pa - angle; // Bigger angle - smaller angle
		// Make sure angle is the smallest angle
		if(ar > 180)
			ar = 360 - ar;
		range = (155*2) * M_PI * ar / 360;	// Distance between player/enemy
		if(range > 200){
			// Straight line if too far
			if(dir){
				// Right
				angle += 0.9 * speed;
				if(angle > 360.0)
					angle -= 360.0;
				float radian = angle * (M_PI/180);
				pos.x = 155 * cosf(radian);
				pos.z = 155 * sinf(radian);
			}else {
				// Left
				angle -= 0.9 * speed;
				if(angle < 0.0)
					angle += 360.0;
				float radian = angle * (M_PI/180);
				pos.x = 155 * cosf(radian);
				pos.z = 155 * sinf(radian);
			}
		}else {
			// In range start 
			// Move y direction closer
			pos.y = pos.getY() > pp.getY() ? pos.y - 0.2 : pos.y + 0.2;
			// Move towards player angle
			if(pa > angle)
				angle += 0.75 * speed;
			else
				angle -= 0.75 * speed;
			if(angle > 360.0)
				angle -= 360.0;
			if(angle < 0.0)
				angle += 360.0;
			float radian = angle * (M_PI/180);
			pos.x = 155 * cosf(radian);
			pos.z = 155 * sinf(radian);
			
		}
		break;
	case 3: // third enemy
		// Move towards player always		
		// Move y direction closer
		pos.y = pos.getY() > pp.getY() ? pos.y - 0.2 : pos.y + 0.2;
		// Move towards player angle
		if(pa > angle)
			angle += 0.45 * speed;
		else
			angle -= 0.45 * speed;

		if(angle > 360.0)
			angle -= 360.0;
		if(angle < 0.0)
			angle += 360.0;

		float radian = angle * (M_PI/180);
		pos.x = 155 * cosf(radian);
		pos.z = 155 * sinf(radian);

		break;		
	}
	
}


// Render the Enemy
void Enemy::Render(){

	glPushMatrix();
	glColor4f(colour[0], colour[1], colour[2], alpha);	// Colour it
	//glTranslated(pos.x, pos.y, pos.z);			// Translate to its position
	switch (enemyType){					// Draw the specific type of Enemy
		case 1:
			glPushMatrix();
	glColor4f(1.0, 0.0, 0.0 , 1.0);	
	glTranslatef(pos.x,pos.y,pos.z);
	glutWireCube(10);	
	glPopMatrix();

	glPushMatrix();
	glColor4f(0.0,1.0,0.0 ,1.0);  //top front right
	glTranslatef(pos.x+5 , pos.y+6.0 , pos.z+5);
	glRotatef(-45, 1.0, 0.0, 0.0);
	glScalef(2.0, 2.0 , 2.0);
	glutWireTetrahedron();
	glPopMatrix();

	glPushMatrix();
	glColor4f(0.0,1.0,0.0 ,1.0); //top back right
	glTranslatef(pos.x+5 , pos.y+6.0 , pos.z-5);
	glRotatef(-45, 1.0, 0.0, 0.0);
	glScalef(2.0, 2.0 , 2.0);
	glutWireTetrahedron();
	glPopMatrix();

	glPushMatrix();
	glColor4f(0.0, 1.0, 0.0 ,1.0); //top front left
	glTranslatef(pos.x-5 , pos.y+6.0 , pos.z+5);
	glRotatef(45, 1.0, 0.0, 0.0);
	glScalef(2.0, 2.0 , 2.0);
	glutWireTetrahedron();
	glPopMatrix();

	glPushMatrix();
	glColor4f(0.0, 1.0, 0.0 ,1.0); //top back left
	glTranslatef( pos.x-5 , pos.y+ 6.0 , pos.z-5);
	glRotatef(45, 1.0, 0.0, 0.0);
	glScalef(2.0, 2.0 , 2.0);
	glutWireTetrahedron();
	glPopMatrix();

	glPushMatrix();
	glColor4f(0.0, 1.0, 0.0 ,1.0); //bottom front right
	glTranslatef(pos.x+5 , pos.y-6.2 , pos.z+5);
	glRotatef(45, 0.0, 0.0, 1.0);
	glScalef(2.0, 2.0 , 2.0);
	glutWireTetrahedron();
	glPopMatrix();

	glPushMatrix();
	glColor4f(0.0, 1.0, 0.0 ,1.0); //bottom back right
	glTranslatef(pos.x+5 , pos.y-6.2 , pos.z-5);
	glRotatef(-45, 0.0, 0.0, 1.0);
	glScalef(2.0, 2.0 , 2.0);
	glutWireTetrahedron();
	glPopMatrix();

	glPushMatrix();
	glColor4f(0.0, 1.0, 0.0 ,1.0); //bottom front left
	glTranslatef(pos.x-5 , pos.y-6.2 , pos.z+5);
	glRotatef(45, 0.0, 0.0, 1.0);
	glScalef(2.0, 2.0 , 2.0);
	glutWireTetrahedron();
	glPopMatrix();

	glPushMatrix();
	glColor4f(0.0, 1.0, 0.0 ,1.0); //bottom back left
	glTranslatef(pos.x-5 , pos.y-6.2 , pos.z-5);
	glRotatef(-45, 0.0, 0.0, 1.0);
	glScalef(2.0, 2.0 , 2.0);
	glutWireTetrahedron();
	glPopMatrix();
	
			break;
		case 2:
			glTranslatef(pos.x,pos.y,pos.z);
			glutSolidCube(size);
			break;
		case 3:
			glTranslatef(pos.x,pos.y,pos.z);
			glutWireSphere(size, 15, 15);
			break;
	}
	glPopMatrix();
}
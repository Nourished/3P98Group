// Player.cpp

#define _USE_MATH_DEFINES	// Pi variable

#include "Player.h"
#include "glut.h"
#include <cstdio>
#include <math.h>

Player::~Player(){
}

// Inital Player generation set fields
Player::Player(){
	playerStatus = 1;
	size = 3.6;
	alpha = 1.0;		
	bullet = 1;
	// Colour
	colour[0] = 1.0;
	colour[1] = 0.0;
	colour[2] = 0.0;
}

// Set the status of the player (shooting / not shooting)
// True == shooting, false = not shooting
void Player::setShooting(bool shoot){
	shooting = shoot;
}

// If the player weapon status
bool Player::getShooting(){
	return shooting;
}

// Add/Subtract from the up/down movement
void Player::addYMovement(float yMove){
	pos.y += yMove;
	if(pos.y > 150)
		pos.y = 150;
	if(pos.y < 1.0)
		pos.y = 1.0;
}

// Add/Subtract from the left/right movement
// xzMove is the angle from its original position
// 155 is radius away from the origin
void Player::addXZMovement(float xzMove){
	float radian = xzMove * (M_PI/180);
	pos.x = 155 * cosf(radian);
	pos.z = 155 * sinf(radian);
}

// Get player size
float Player::getSize(){
	return size;
}

// Set Player size
void Player::setSize(float newSize){
	size = newSize;
}

// Set the colour
void Player::setColour(float r, float g, float b){
	colour[0] = r;
	colour[1] = g;
	colour[2] = b;
}

// Set the Player type
void Player::setPlayerStatus(int a){
	playerStatus = a;	
}

// Returns the player status
int Player::getPlayerStatus(){
	return playerStatus;
}

// Set the bullet type
void Player::setBullet(int a){
	bullet = a;	
	powerUpTimer = 500;
}

// Returns the player status
int Player::getBullet(){
	return bullet;
}

// Set the alpha (visibility) of the Player
void Player::setAlpha(double alp){
	alpha = alp;
}


// Set the position
void Player::setPosition(Coordinate p){
	pos = p;
}

// Return the players position
Coordinate Player::getPosition(){
	return pos;
}

// used to reset the position to a user defined point and velocity
void Player::resetPosition(Coordinate p){			
	// Position
	pos = p;

}

// update the Player
// This will calculate the new pos and velocity based on acceleration and speed
void Player::Update(){
	
	// Collision detection	
	if(powerUpTimer > 0)
		powerUpTimer--;
	else
		bullet = 1;
}

// Render the Player
void Player::Render(){
	
	GLfloat light_ambient[] = {0.0, 0.0, 0.0, 0.0};
    GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 0.0};
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 0.0};
    GLfloat light_position[] = {pos.x, pos.y, pos.z, 1};
	glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT2, GL_POSITION, light_position);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128.0 );
 	glEnable(GL_LIGHT2); 


	glPushMatrix();
	glColor4f(1.0, 0.0, 0.0 , 1.0);
	glTranslated(pos.x, pos.y, pos.z);
	glutSolidCube(5);
	glColor4f(0.0, 0.0, 1.0, 1.0);
	glPopMatrix();
	glPushMatrix();
	glTranslated(pos.x-15, pos.y+2.4, pos.z);
	glScalef(5,2,2);
	glutSolidCube(5);
	glPopMatrix();

	//wing!!! #1
	glPushMatrix();
	glColor4f(0.0, 1.0, 0.0 , 1.0);	
	glTranslated(pos.x-15, pos.y+5, pos.z+5);
	glRotatef(90, 1.0 , 0.0 , 0.0);
	glScalef(5,10,5); //side
	glBegin(GL_TRIANGLES);
		glVertex3f(0,0,0);
		glVertex3f(1, 0 , 0);
		glVertex3f(0,1,0);
	glEnd();
	glBegin(GL_TRIANGLES); //side
		glVertex3f(0,0,1);
		glVertex3f(1, 0 , 1);
		glVertex3f(0,1,1);
	glEnd();
	glColor4f(1.0, 0.0, 0.0 , 1.0);
	glBegin(GL_POLYGON); // back
		glVertex3f(0,0,0);
		glVertex3f(0, 0 , 1);
		glVertex3f(0,1,1);
		glVertex3f(0,1,0);
	glEnd();
	glColor4f(1.0, 0.5, 0.5 , 1.0);
	glBegin(GL_POLYGON); //front face
		glVertex3f(0,1,0);
		glVertex3f(1, 0 , 0);
		glVertex3f(1,0,1);
		glVertex3f(0,1,1);
	glEnd();
	glColor4f(1.0, 0.0, 1.0 , 1.0);
	glBegin(GL_POLYGON); //bottom
		glVertex3f(0,0,0);
		glVertex3f(1, 0 , 0);
		glVertex3f(1,0,1);
		glVertex3f(0,0,1);
	glEnd();
	glPopMatrix();

	//wing!!! #2
	glPushMatrix();
	glColor4f(0.0, 1.0, 0.0 , 1.0);
	glTranslated(pos.x-15, pos.y, pos.z-5);
	glRotatef(-90, 1.0 , 0.0 , 0.0);
	glScalef(5,10,5); //side
	glBegin(GL_TRIANGLES);
		glVertex3f(0,0,0);
		glVertex3f(1, 0 , 0);
		glVertex3f(0,1,0);
	glEnd();
	glBegin(GL_TRIANGLES); //side
		glVertex3f(0,0,1);
		glVertex3f(1, 0 , 1);
		glVertex3f(0,1,1);
	glEnd();
	glColor4f(1.0, 0.0, 0.0 , 1.0);
	glBegin(GL_POLYGON); // back
		glVertex3f(0,0,0);
		glVertex3f(0, 0 , 1);
		glVertex3f(0,1,1);
		glVertex3f(0,1,0);
	glEnd();
	glColor4f(1.0, 0.5, 0.5 , 1.0);
	glBegin(GL_POLYGON); //front face
		glVertex3f(0,1,0);
		glVertex3f(1, 0 , 0);
		glVertex3f(1,0,1);
		glVertex3f(0,1,1);
	glEnd();
	glColor4f(1.0, 0.0, 1.0 , 1.0);
	glBegin(GL_POLYGON); //bottom
		glVertex3f(0,0,0);
		glVertex3f(1, 0 , 0);
		glVertex3f(1,0,1);
		glVertex3f(0,0,1);
	glEnd();
	glPopMatrix();
	//the hatch!!!

	glPushMatrix();
	glColor4f(0.0, 1.0, 0.0 , 1.0);
	glTranslated(pos.x-15, pos.y+7.5, pos.z-2.5);
	glScalef(10,10,5); //side
	glBegin(GL_TRIANGLES);
	glVertex3f(0,0,0);
	glVertex3f(1, 0 , 0);
	glVertex3f(0,1,0);
	glEnd();
	glBegin(GL_TRIANGLES); //side
	glVertex3f(0,0,1);
	glVertex3f(1, 0 , 1);
	glVertex3f(0,1,1);
	glEnd();
	glColor4f(1.0, 0.0, 0.0 , 1.0);
	glBegin(GL_POLYGON); // back
	glVertex3f(0,0,0);
	glVertex3f(0, 0 , 1);
	glVertex3f(0,1,1);
	glVertex3f(0,1,0);
	glEnd();
	glColor4f(1.0, 0.5, 0.5 , 1.0);
	glBegin(GL_POLYGON); //front face
	glVertex3f(0,1,0);
	glVertex3f(1, 0 , 0);
	glVertex3f(1,0,1);
	glVertex3f(0,1,1);
	glEnd();
	glColor4f(1.0, 0.0, 1.0 , 1.0);
	glBegin(GL_POLYGON); //bottom
	glVertex3f(0,0,0);
	glVertex3f(1, 0 , 0);
	glVertex3f(1,0,1);
	glVertex3f(0,0,1);
	glEnd();
	glPopMatrix();
}
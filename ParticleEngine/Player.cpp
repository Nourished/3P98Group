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
	size = 2;
	lives = 3;
	speed = 5.0;
	alpha = 1.0;		
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

bool Player::getShooting(){
	return shooting;
}

// Returns the age value
int Player::numberofLives(){
	return lives;
}

// Sets the age value
void Player::setLives(int a){
	lives = a;
}

// Sets the age value
void Player::addLives(int a){
	lives += a;
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

// ~~~~~~ IS SPEED NEEDED ??? ~~~~~~~~
// Set the speed, cannot be set past 8
void Player::setSpeed(double sp){
	if(sp < 8.01)
		speed = sp;
	else
		speed = 8;	// Max speed
}//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// Set the colour
void Player::setColour(float r, float g, float b){
	colour[0] = r;
	colour[1] = g;
	colour[2] = b;
}

// Set the Player type
void Player::setPlayerStatus(int a){
	playerStatus = a;
	if(a == 2)
		alpha = 0.01;
}

// Returns the player status
int Player::getPlayerStatus(){
	return playerStatus;
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

	lives = 3;
	speed = 5.0;
	
	// Position
	pos = p;

}

// update the Player
// This will calculate the new pos and velocity based on acceleration and speed
void Player::Update(){
	
	// Collision detection	
	
}


// Render the Player
void Player::Render(){
	
	GLfloat light_ambient[] = {0.0, 0.0, 0.0, 0.0};
    GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 0.0};
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 0.0};
    GLfloat light_position[] = {pos.x, pos.y, pos.z, 1};
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128.0 );
 	glEnable(GL_LIGHT1); 

	if(playerStatus == 2){
		alpha += 0.02;
		if(alpha == 0.49)
			alpha = 0.38;
		if(alpha == 0.78)
			alpha = 0.59;
		if(alpha > 0.96){
			alpha = 1.0;
			playerStatus = 1;
		}
	}
	
	glPushMatrix();
	glColor4f(colour[0], colour[1], colour[2], alpha);	// Colour it
	glTranslated(pos.x, pos.y, pos.z);			// Translate to its position	
	glutSolidSphere(size, 15, 15);			
	glPopMatrix();
}
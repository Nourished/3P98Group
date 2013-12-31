// Eric Gummerson	4585469
// Player.cpp
// Player class used for easier access in vector lists
// Contains information on the Player
// Including speed, velocity, acceleration, position
// Colour, Player type

#include "Player.h"
#include "glut.h"
#include "RNG.h"
#include <cstdio>

// Random generator
RNG rnd;

Player::~Player(){
}

// Inital Player generation set fields
Player::Player(Coordinate p, Coordinate v){
	partType = 1;
	size = 2;
	age = 1;
	speed = rnd.random(4.0, 8.0);
	alpha = 1.0;

	pos = p;
	vel = v;
		
	// Colour
	colour[0] = rnd.random(0.01, 1.0);
	colour[1] = rnd.random(0.01, 1.0);
	colour[2] = rnd.random(0.01, 1.0);
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
int Player::ageStatus(){
	return age;
}

// Sets the age value
void Player::setAgeStatus(int aStatus){
	age = aStatus;
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
void Player::setPlayerType(int a){
	partType = a;
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


// Set the velocity
void Player::setVelocity(Coordinate v){
	vel = v;
}

Coordinate Player::getVelocity(){
	return vel;
}

// used to reset the position to a user defined point and velocity
void Player::resetPosition(Coordinate p, Coordinate v){

	age = 1;
	speed = rnd.random(4.0, 8.0);
	
	// Position
	pos = p;
	// Velocity
	vel = v;
}

// update the Player
// This will calculate the new pos and velocity based on acceleration and speed
void Player::Update(){
	
	Coordinate newPos;
	double pSpeed = (speed / 100.0);	// Half the percentage of max speed (10)

	//age += 0.1; // Age > 1000 we reset it

	newPos.x = pos.x + (vel.x * pSpeed);
	newPos.y = pos.y + (vel.y * pSpeed);
	newPos.z = pos.z + (vel.z * pSpeed);

	// Update the Players position
	setPosition(newPos);
	
}


// Render the Player
void Player::Render(){

	glPushMatrix();
	glColor4f(colour[0], colour[1], colour[2], alpha);	// Colour it
	glTranslated(pos.x, pos.y, pos.z);			// Translate to its position
	glRotated(1.0, 1.0, 1.0, 0.0);			
	switch (partType){					// Draw the specific type of Player
		case 1:
			glutSolidSphere(size, 15, 15);
			break;
		case 2:
			glutSolidCube(size);
			break;
		case 3:
			glutWireSphere(size, 15, 15);
			break;
		case 4:
			glutWireCube(size);
			break;
		case 5:
			glPointSize(size*2);
			glBegin(GL_POINTS);
			glVertex3f(0,0,0);
			glEnd();
			break;
	}
	glPopMatrix();
}
// Eric Gummerson	4585469
// Particle.cpp
// Particle class used for easier access in vector lists
// Contains information on the particle
// Including speed, velocity, acceleration, position
// Colour, particle type

#include "Particle.h"
#include "glut.h"
#include "RNG.h"
#include <cstdio>

// Random generator
RNG rnd;

Particle::~Particle(){
}

// Inital particle generation set fields
Particle::Particle(){
	partType = 1;
	size = 2;
	age = 1;
	speed = rnd.random(4.0, 8.0);
	alpha = 1.0;

	acc.x = 0.0;
	acc.y = -9.8;
	acc.z = 0.0;

	pos.x = 0.0;
	pos.y = 2;
	pos.z = 0.0;

	vel.x = 0.0;
	vel.y = 0;
	vel.z = 0.0;
	
	// Colour
	colour[0] = rnd.random(0.01, 1.0);
	colour[1] = rnd.random(0.01, 1.0);
	colour[2] = rnd.random(0.01, 1.0);
}

// Particle initalized with position and velocity
Particle::Particle(double posX, double posY, double posZ, double velX, double velY, double velZ){
	partType = 1;
	size = 2;
	age = 1;
	alpha = 1.0;
	speed = rnd.random(4.0, 8.0);

	acc.x = 0.0;
	acc.y = -9.8;
	acc.z = 0.0;

	pos.x = posX;
	pos.y = posY;
	pos.z = posZ;

	vel.x = velX;
	vel.y = velY;
	vel.z = velZ;

	// Colour
	colour[0] = rnd.random(0.01, 1.0);
	colour[1] = rnd.random(0.01, 1.0);
	colour[2] = rnd.random(0.01, 1.0);
};

// Initalize particle with speed, position, velocity and colour
Particle::Particle(double sp, double posX, double posY, double posZ, double velX, double velY, double velZ, float colR, float colG, float colB, float colA){

	alpha = colA;
	partType = 1;
	size = 2;
	age = 1;
	speed = speed;

	pos.x = posX;
	pos.y = posY;
	pos.z = posZ;

	vel.x = velX;
	vel.y = velY;
	vel.z = velZ;

	acc.x = 0.0;
	acc.y = -9.8;
	acc.z = 0.0;

	colour[0] = colR;
	colour[1] = colG;
	colour[2]  =colB;
}

// It is dead if age is 0, used to remove particles out of bounds
// Or have expired in time
int Particle::isAlive(){
	return age;
}

// Set the speed, cannot be set past 8
void Particle::setSpeed(double sp){
	if(sp < 8.01)
		speed = sp;
	else
		speed = 8;	// Max speed
}

// Set the colour
void Particle::setColour(float r,float g, float b){
	colour[0] = r;
	colour[1] = g;
	colour[2] = b;
}

// Set particle size
void Particle::setSize(float newSize){
	size = newSize;
}

// update the particle
// This will calculate the new pos and velocity based on acceleration and speed
void Particle::Update(){
	
	double newPos[3];
	double newVel[3];
	double pSpeed = (speed / 100.0);	// Half the percentage of max speed (10)

	age += 0.1; // Age > 1000 we reset it

	newPos[0] = pos.x + (vel.x * pSpeed);
	newVel[0] = vel.x + (acc.x * pSpeed);

	newPos[1] = pos.y + (vel.y * (pSpeed)) + (0.25 * (acc.y * (0.0025)));
	newVel[1] = vel.y + (acc.y * pSpeed);

	newPos[2] = pos.z + (vel.z * pSpeed);
	newVel[2] = vel.z + (acc.z * pSpeed);

	// Check where the particle is
	// Change its velocities if it bounces or falls through a hole


	// Is it on the surfaceound	
	if(newPos[0] < 65 && newPos[0] > -65 && newPos[2] < 65 && newPos[2] > -65){
		// Did it enter the black hole
		// If it is within the rectangle area
		if (newPos[1] <= size){			// Depending on size of particle we can determine when
										// it is visually hitting the ground
			if(newVel[1] < 0.8 && newVel[1] > -0.8){	// Not as much bouncing so we make it sit on the top and slowly come to a halt
			newPos[1] = size;
			speed *= 0.4;
		}else {
			// Hole, does nothing
			if(newPos[0] < -7 && newPos[0] > -23 && newPos[2] < 23 && newPos[2] > 7){			
			}else {		// Otherwise it bounces, set velocity in other direction
				newVel[1] *= -0.67;
				speed *= .88;
				newPos[1] = size;
			}
		}
		// Friction of ground Set age close to 1000 so it will reset in a few seconds
		if(speed < 0.05)
			if(age <= 994.0)
				age = 994.0;
		}
	}

	// Update the particles position and velocity
	setPosition(newPos[0], newPos[1], newPos[2]);
	setVelocity(newVel[0], newVel[1], newVel[2]);

	
	// Boundaries for the new position, remove element if gone
	// Below the grid
	if(pos.y < -35)
		age = 0;

	// Out of bounds, old age	
	if (pos.y >= 150){
		age = 0;
	}
	if (pos.x >= 250 || pos.x < -250 || pos.z >= 250 || pos.z < -250){
		age = 0;
	}
	if(age > 1000){
		age = 0;
	}
}

// Set the alpha (visibility) of the particle
void Particle::setAlpha(double alp){
	alpha = alp;
}

// Change the acceleration by adding to the current totals
void Particle::changeAcceleration(double aX, double aY, double aZ){
	acc.x += aX;
	acc.y += aY;
	acc.z += aZ;
}

// Set the acceleration
void Particle::setAcceleration(double aX, double aY, double aZ){
	acc.x = aX;
	acc.y = aY;
	acc.z = aZ;
}

// Set the position
void Particle::setPosition(double pX, double pY, double pZ){
	pos.x = pX;
	pos.y = pY;
	pos.z = pZ;
}

// Set the velocity
void Particle::setVelocity(double vX, double vY, double vZ){
	vel.x = vX;
	vel.y = vY;
	vel.z = vZ;
}

// Set the particle type
void Particle::setParticleType(int a){
	partType = a;
}

// Used to reset the position to the spout
void Particle::resetPosition(){
	age = 1;
	speed = rnd.random(4.0, 8.0);
	acc.x = 0.0;
	acc.y = -9.8;
	acc.z = 0.0;
	// Position
	pos.x = rnd.stdDeviation(0, 1.5);
	pos.y = rnd.stdDeviation(17, 2.0);
	pos.z = rnd.stdDeviation(0, 1.5);
	// Velocity
	vel.x = rnd.stdDeviation(0, 3.0);
	vel.y = rnd.stdDeviation(22.0, 4.0);
	vel.z = rnd.stdDeviation(0, 3.0);
}

// used to reset the position to a user defined point and velocity
void Particle::resetPosition(double pX, double pY, double pZ, double vX, double vY, double vZ){

	age = 1;
	speed = rnd.random(4.0, 8.0);
	acc.x = 0.0;
	acc.y = -9.8;
	acc.z = 0.0;
	// Position
	pos.x = pX;
	pos.y = pY;
	pos.z = pZ;
	// Velocity
	vel.x = vX;
	vel.y = vY;
	vel.z = vZ;
}

// Render the particle
void Particle::Render(){

	glPushMatrix();
	glColor4f(colour[0], colour[1], colour[2], alpha);	// Colour it
	glTranslated(pos.x, pos.y, pos.z);			// Translate to its position
	glRotated(1.0, 1.0, 1.0, 0.0);			
	switch (partType){					// Draw the specific type of particle
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
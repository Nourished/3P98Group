// Bullet.h

#include "Coordinate.h"

#pragma once
class Bullet {	
	
	protected: 
		Coordinate pos;		// Position of the Bullet
		int age;			// Age of bullet, 0 = dead and remove
		float alpha;		// Visibility
		float colour[3];	// Colour
		int bulletType;		// different bullet effects
		float size;			// Size of the Bullet
		double speed;		// For powerups
		bool dir;			// True = right, false = left, used for direction
		float angle;		// Where the bullet is on the circle
	

	public:
		// create a bullet with a given type, direction, angle on circle, and position
		Bullet(int bType, bool d, float angleStart, Coordinate p);
		~Bullet();


	int getAge();
	void setAge(int a);

	void setSize(float newSize);
	float getSize();

	void setSpeed(double sp);
	void setColour(float r, float g, float b);
	void setBulletType(int a);
	int getBulletType();
	void setAlpha(double alp);

	void setPosition(Coordinate p);
	Coordinate getPosition();
	
	void Update();	// Collision
	void Render();	// Draw

};

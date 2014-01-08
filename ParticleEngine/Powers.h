// Powers.h

#include "Coordinate.h"

#pragma once
class Powers {	
	
	protected: 
		Coordinate pos;		// Position of the Powers
		int age;			// Age of Powers, 0 = dead and remove
		float colour[3];	// Colour
		int powerType;		// different Powers effects
		float size;			// Size of the Powers
		float angle;		// Where the Powers is on the circle
		float powerRotate;  //Rotating donut

	public:
		// create a Powers with a given type, direction, angle on circle, and position
		Powers(int pt, float angleStart, Coordinate p);
		~Powers();


	int getAge();
	void setAge(int a);

	void setColour(float r, float g, float b);

	void setPowerType(int a);
	int getPowerType();

	void setAngle(float a);
	float getAngle();

	float getSize();

	void setPosition(Coordinate p);
	Coordinate getPosition();
	
	void Update();	// Collision
	void Render();	// Draw

};

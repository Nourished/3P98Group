// Explode.h

#include "Coordinate.h"

#pragma once
class Explode {	
	
	protected: 
		Coordinate pos;		// Position of the Explode
		Coordinate particles[8];
		int age;			// Age of Explode, 0 = dead and remove
		float colour[3];	// Colour
		int ExplodeType;	// different Explode effects
		float size;			// Size of the Explode
		float moveDist;		// Moving distance during update
		float angle;		// Where the Explode is on the circle
	

	public:
		// create a Explode with a given type, direction, angle on circle, and position
		Explode(int bType, float angleStart, Coordinate p);
		~Explode();


	int getAge();
	void setAge(int a);

	void setSize(float newSize);
	float getSize();
		
	void setColour(float r, float g, float b);

	void setExplodeType(int a);
	int getExplodeType();

	void setPosition(Coordinate p);
	Coordinate getPosition();
	
	void Update();	// Move the explosion
	void Render();	// Draw

};

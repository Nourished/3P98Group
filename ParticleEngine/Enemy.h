// Eric Gummerson	4585469
// Enemy.h
#include "Coordinate.h"

class Enemy {	
	
	protected: 
		Coordinate pos;		// Position of the Enemy
		int age;			// Age of Enemy, 0 = dead and remove
		float alpha;		// Visibility
		float colour[3];	// Colour
		int enemyType;		// different Enemy effects
		float size;			// Size of the Enemy
		double speed;		// For powerups
		bool dir;			// True = right, false = left, used for direction
		float angle;		// Where the Enemy is on the circle
		

	public:
		// create a Enemy with a given type, direction, angle on circle, and position
		Enemy(int bType, bool d, float angleStart, Coordinate p);
		~Enemy();


	int getAge();
	void setAge(int l);

	void setSize(float newSize);
	float getSize();

	void setSpeed(double sp);
	void setColour(float r, float g, float b);
	void setEnemyType(int a);
	int getEnemyType();
	void setAlpha(double alp);

	void setPosition(Coordinate p);
	Coordinate getPosition();
	
	void Update();	// Collision
	void Render();	// Draw

};

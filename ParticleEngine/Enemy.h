// Enemy.h

#include "Coordinate.h"
#pragma once
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
		float enemy2Rotation; // Rotation angle for enemies
		float enemy3Rotation; // Third enemy rotation
		float bossRotation;   // Bos rotation
		bool boss;			// Is he a boss
		int bossHealth;		// Boss health

	public:
		// create a Enemy with a given type, direction, angle on circle, and position
		Enemy(int bType, bool d, float angleStart, Coordinate p);
		~Enemy();


	int getAge();
	void setAge(int l);

	bool getBoss();
	void setBoss(bool b);

	int getBossHealth();
	void setBossHealth(int b);
	void addBossHealth(int b);
	void relocateBoss();

	void setSize(float newSize);
	float getSize();

	void setAngle(float newAngle);
	float getAngle();

	void setSpeed(double sp);

	void setColour(float r, float g, float b);
	void addColour(float r, float g, float b);

	void setEnemyType(int a);
	int getEnemyType();
	void setAlpha(double alp);

	void setPosition(Coordinate p);
	Coordinate getPosition();
	
	void Update(Coordinate pp, float pa);	// Player position and angle on circle
	void Render();	// Draw

};

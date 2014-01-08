// Player.h

#include "Coordinate.h"

#pragma once
class Player {	
	
	protected: 
		Coordinate pos;		// Position of the player
		int bullet;			// Bullet type
		float alpha;		// Visibility
		float colour[3];	// Colour
		int playerStatus;	// 1 = alive, 2 = dead
		float size;			// Size of the player, powerups can affect?
		int direction;		// Which direction the player is shooting
		bool shooting;		// Is the player shooting
		int powerUpTimer;	// Timer for powerups

	public:
		Player();
		~Player();

	void setShooting(bool shoot);
	bool getShooting();

	void addYMovement(float yMove);
	void addXZMovement(float xzMove);

	void setSize(float newSize);
	float getSize();

	void setColour(float r, float g, float b);

	void setPlayerStatus(int a);
	int getPlayerStatus();

	void setBullet(int a);
	int getBullet();

	void setAlpha(double alp);

	void setPosition(Coordinate p);
	Coordinate getPosition();

	
	void resetPosition(Coordinate p); // Reset the position

	void Update();	// Collision
	void Render();	// Draw

};

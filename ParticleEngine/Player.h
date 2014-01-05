// Player.h

#include "Coordinate.h"

#pragma once
class Player {	
	
	protected: 
		Coordinate pos;		// Position of the player
		int lives;			// Number of lives
		float alpha;		// Visibility
		float colour[3];	// Colour
		int playerStatus;	// 1 = alive, 2 = reviving, 3 = dead
		float size;			// Size of the player, powerups can affect?
		double speed;		// For powerups
		int direction;		// Which direction the player is shooting
		bool shooting;		// Is the player shooting

	public:
		Player();
		~Player();

	void setShooting(bool shoot);
	bool getShooting();

	int numberofLives();
	void setLives(int a);
	void addLives(int a);

	void addYMovement(float yMove);
	void addXZMovement(float xzMove);

	void setSize(float newSize);
	float getSize();
	void setSpeed(double sp);
	void setColour(float r, float g, float b);

	void setPlayerStatus(int a);
	int getPlayerStatus();

	void setAlpha(double alp);

	void setPosition(Coordinate p);
	Coordinate getPosition();

	
	void resetPosition(Coordinate p); // Reset the position

	void Update();	// Collision
	void Render();	// Draw

};

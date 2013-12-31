// Eric Gummerson	4585469
// Player.h
#include "Coordinate.h"

class Player {	
	
	protected: 
		Coordinate pos, vel;// Position and velocity of the player
		int age;			// Can be used for powerups?
		float alpha;		// Visibility
		float colour[3];	// Colour
		int partType;		// Used for the Player shape/object
		float size;			// Size of the player, powerups can affect?
		double speed;		// Is this needed?
		int direction;		// Which direction the player is shooting
		bool shooting;		// Is the player shooting

	public:
		Player();
		~Player();

	void setShooting(bool shoot);
	bool getShooting();

	int ageStatus();
	void setAgeStatus(int aStatus);

	void setSize(float newSize);
	void setSpeed(double sp);
	void setColour(float r, float g, float b);
	void setPlayerType(int a);
	void setAlpha(double alp);

	void setPosition(Coordinate p);
	Coordinate getPosition();

	void setVelocity(Coordinate v);
	Coordinate getVelocity();

	void resetPosition(Coordinate p, Coordinate v); // Reset the position

	void Update();
	void Render();
	

	Player(Coordinate p, Coordinate v);

};

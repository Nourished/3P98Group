// Levels.h

#pragma once
class Levels {	
	
	protected: 
		int numEnemiesKilled;	// Number of enemies killed
		int level;				// Levels 1-10
		bool boss;				// true if boss, false if normal
		int difficulty;			// 1 easy, 2 normal, 3 hard
		int score;				// Score
		int killsToLevel;		// Kills needed to get to the next level
		int lives;				// Lives for the game
		int nextPowerScore;		// Score needed to spawn the next powerup

	public:
		// create a Levels with a given type, direction, angle on circle, and position
		Levels();
		~Levels();

	void addKilled(int a);
	void removeKilled(int a);
	void setKilled(int a);
	int getKilled();

	void addScore(int a);
	void setScore(int a);
	int getScore();

	void setPowerScore(int a);
	void addPowerScore(int a);
	int getPowerScore();

	void addLives(int a);
	void setLives(int a);
	int getLives();
	
	void increaseLevel(int a);
	void lowerLevel(int a);
	void setLevel(int a);
	int getLevel();

	void setBoss(bool a);
	bool getBoss();

	void increaseDiff(int a);
	void lowerDiff(int a);
	void setDiff(int a);
	int getDiff();
	
	void setKillsNeededToLevelUp(int a);
	int getKillsNeededToLevelUp();

	void reset();
	int Update();
	

};

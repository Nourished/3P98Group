// Eric Gummerson	4585469
// Particle.h

class Particle {
	typedef struct _vec{
		double x,y,z;
	} Vec;
	
	protected: 
		Vec pos, vel, acc;
		float age;	// 0 age means its dead
		float alpha;	
		float colour[3];
		int partType;	// Used for the particle shape/object
		float size;
		double speed;

	public:
		Particle();
		~Particle();

	void changeAcceleration(double aX, double aY, double aZ);
	void setSize(float newSize);
	void setSpeed(double sp);
	void setColour(float r,float g, float b);
	void setParticleType(int a);
	void setAlpha(double alp);
	void setAcceleration(double aX, double aY, double aZ);
	void setPosition(double pX, double pY, double pZ);
	void setVelocity(double vX, double vY, double vZ);
	void resetPosition();
	void resetPosition(double pX, double pY, double pZ, double vX, double vY, double vZ);
	void Update();
	void Render();
	int isAlive();

	Particle(double posX, double posY, double posZ, double velX, double velY, double velZ);
	Particle(double sp, double posX, double posY, double posZ, double velX, double velY, double velZ, float colR, float colG, float colB, float colA);
};

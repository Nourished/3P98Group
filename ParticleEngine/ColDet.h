// ColDet.h

#include <cmath>
class ColDet {
	
	public:
		ColDet::ColDet(){};
		ColDet::~ColDet(){};

	bool ColDet::collide(float x1, float y1, float z1, float r1, float x2, float y2, float z2, float r2){

		float xd, yd, zd, dist;
		// Find distances between two points
		xd = x2-x1;
        yd = y2-y1;
        zd = z2-z1;
        dist = sqrtf(xd*xd + yd*yd + zd*zd);
		
		// Compare the radiuses
		if(r1 + r2 >= dist)
			return true; //collision
		return false;    //no collision    



	}

};

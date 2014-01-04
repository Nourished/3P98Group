// ColDet.h

#include <cmath>
#include "Coordinate.h"
class ColDet {
	
	public:
		ColDet::ColDet(){};
		ColDet::~ColDet(){};

	bool ColDet::collide(Coordinate p1, float r1, Coordinate p2, float r2){

		float xd, yd, zd, dist;
		// Find distances between two points
		xd = p2.getX() - p1.getX();
        yd = p2.getY() - p1.getY();
        zd = p2.getZ() - p1.getZ();
        dist = sqrtf(xd*xd + yd*yd + zd*zd);
		
		// Compare the radiuses
		if(r1 + r2 >= dist)
			return true; //collision
		return false;    //no collision    



	}

};

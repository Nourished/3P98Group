// Simple class which will contain x,y,z values
// Will be used with collision detection (i assume)

class Coordinate {		
	
	public:
		double x, y, z;
		Coordinate();
		~Coordinate();

		double getX(){
			return x;
		}
		double getY(){
			return y;
		}
		double getZ(){
			return z;
		}

		void setX(double x1){
			x = x1;
		}
		void setY(double y1){
			y = y1;

		}
		void setZ(double z1){
			z = z1;
		}

	Coordinate(double x, double y, double z);
};
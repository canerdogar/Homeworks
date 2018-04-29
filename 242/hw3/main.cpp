#include <iostream>
//#include "qtree.h"
#include "coordinate.h"
#include "rectangle.h"

using namespace std;

int main(){

	Coordinate c1(0,1); 
	Coordinate c2(1,2); 
	Rectangle r1(c1,c2); 
	Coordinate c3(0,0); 
	Coordinate c4(1,3); 
	Rectangle r2(c3,c4); 
	if(r1.intersects(r2))cout<<"tamamsin"<<endl;
	else cout<<"fuckyou"<<endl;
}
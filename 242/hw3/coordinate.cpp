#include "coordinate.h"

Coordinate::Coordinate()
{
	x=0;
	y=0;
}
Coordinate::Coordinate(int xi, int yi)
{
	x=xi;
	y=yi;	
}
Coordinate::Coordinate(const Coordinate& rhs)
{
	x=rhs.x;
	y=rhs.y;
}
Coordinate::~Coordinate()
{

}
int Coordinate::getx() const
{
	return x;
}
int Coordinate::gety() const
{
	return y;
}
void Coordinate::setx(int xi)
{
	x=xi;
}
void Coordinate::sety(int yi)
{
	y=yi;
}
Coordinate Coordinate::operator+(const Coordinate& rhs) const
{
	Coordinate result;
	result.setx(x+rhs.getx());
	result.sety(y+rhs.gety());
	return result;
}

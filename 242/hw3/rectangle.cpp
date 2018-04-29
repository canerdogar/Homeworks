#include "rectangle.h"

Rectangle::Rectangle(const Coordinate& rhs1, const Coordinate& rhs2)
{
	xtop=rhs1.getx();
	ytop=rhs1.gety();
	xbot=rhs2.getx();
	ybot=rhs2.gety();
}
Rectangle::Rectangle(const Rectangle& rhs)
{
	xtop=rhs.getTopLeft().getx();
	ytop=rhs.getTopLeft().gety();
	xbot=rhs.getBottomRight().getx();
	ybot=rhs.getBottomRight().gety();
}
Rectangle::~Rectangle()
{

}
Coordinate Rectangle::getTopLeft() const
{
	Coordinate result;
	result.setx(xtop);
	result.sety(ytop);
	return result;
}
Coordinate Rectangle::getBottomRight() const
{
	Coordinate result;
	result.setx(xbot);
	result.sety(ybot);
	return result;
}
void Rectangle::setTopLeft(const Coordinate& rhs)
{
	xtop=rhs.getx();
	ytop=rhs.gety();
}
void Rectangle::setBottomRight(const Coordinate& rhs)
{
	xbot=rhs.getx();
	ybot=rhs.gety();
}
bool Rectangle::contains(const Coordinate& rhs) const
{
	if(xtop<=rhs.getx() && ytop<=rhs.gety() && xbot>=rhs.getx() && ybot>=rhs.gety())
		return true;
	else 
		return false;
}
bool Rectangle::intersects(const Rectangle& rhs) const
{
	Coordinate topRight(rhs.getBottomRight().getx(),rhs.getTopLeft().gety());
	Coordinate bottomLeft(rhs.getTopLeft().getx(),rhs.getBottomRight().gety());	
	if(contains(rhs.getTopLeft()) || contains(rhs.getBottomRight()) || contains(bottomLeft) || contains(topRight))
		return true;
	else
		return false;	
}

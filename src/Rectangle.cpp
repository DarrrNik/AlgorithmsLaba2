#include "Rectangle.h"

Rectangle::Rectangle(Point2i lowerLeft, Point2i upperRight) :
	lowerLeftCorner(lowerLeft), upperRightCorner(upperRight) {}

Point2i& Rectangle::GetUpperRightCorner()
{
	return upperRightCorner;
}

Point2i& Rectangle::GetLowerLeftCorner()
{
	return lowerLeftCorner;
}
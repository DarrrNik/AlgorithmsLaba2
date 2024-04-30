#pragma once
#include <utility>
#include "Point2i.h"

class Rectangle
{
public:
	Rectangle(Point2i lowerLeft = Point2i(), Point2i upperRight = Point2i());

	Point2i& GetUpperRightCorner();
	Point2i& GetLowerLeftCorner();
private:
	Point2i lowerLeftCorner, upperRightCorner;
};


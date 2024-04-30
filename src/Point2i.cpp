#include "Point2i.h"


Point2i::Point2i(int x_, int y_) :
	x(x_), y(y_) {}

int& Point2i::GetX()
{
	return x;
}

int& Point2i::GetY()
{
	return y;
}

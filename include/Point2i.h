#pragma once
class Point2i
{
public:
	Point2i(int x_ = -1, int y_ = -1);

	int& GetX();
	int& GetY();
private:
	int x, y;
};


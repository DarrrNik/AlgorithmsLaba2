#include "RectanglesProblem.h"

int BruteForceAlg(std::vector<Rectangle>& rectangles, Point2i& point)
{
	int count = 0;
	for (Rectangle& rectangle : rectangles) {
		bool isInRect = (point.GetX() < rectangle.GetUpperRightCorner().GetX() &&
			point.GetX() >= rectangle.GetLowerLeftCorner().GetX() &&
			point.GetY() < rectangle.GetUpperRightCorner().GetY() &&
			point.GetY() >= rectangle.GetLowerLeftCorner().GetY());
		if (isInRect)
			++count;
	}
	return count;
}

void RectanglesMappingAlgPreparation(std::vector<Rectangle>& rectangles, std::unique_ptr<std::unique_ptr<int[]>[]>& map,
	std::vector<int>& vecX, std::vector<int>& vecY)
{
	std::set<int> setX;
	std::set<int> setY;
	for (Rectangle& rec : rectangles) {
		setX.insert(rec.GetLowerLeftCorner().GetX());
		setX.insert(rec.GetUpperRightCorner().GetX());
		setY.insert(rec.GetLowerLeftCorner().GetY());
		setY.insert(rec.GetUpperRightCorner().GetY());
	}

	for (int x : setX) vecX.push_back(x);
	for (int y : setY) vecY.push_back(y);

	map = std::make_unique<std::unique_ptr<int[]>[]>(vecX.size());
	for (int i = 0; i < vecX.size(); ++i) {
		map[i] = std::make_unique<int[]>(vecY.size());
		for (int j = 0; j < vecY.size(); ++j)
			map[i][j] = 0;
	}

	for (Rectangle& rec : rectangles) {
		int indLeftX = BinSearch(vecX, rec.GetLowerLeftCorner().GetX());
		int indLeftY = BinSearch(vecY, rec.GetLowerLeftCorner().GetY());
		int indRightX = BinSearch(vecX, rec.GetUpperRightCorner().GetX());
		int indRightY = BinSearch(vecY, rec.GetUpperRightCorner().GetY());
		for (int x = indLeftX; x < indRightX; ++x) {
			for (int y = indLeftY; y < indRightY; ++y) {
				++map[x][y];
			}
		}
	}
}

int BinSearch(const std::vector<int>& vec, int target)
{
	int left = 0, right = vec.size() - 1;
	int mid = (left + right) / 2;
	while (left <= right) {
		mid = (left + right) / 2;
		if (target < vec[mid]) right = mid - 1;
		if (target > vec[mid]) left = mid + 1;
		if (target == vec[mid]) return mid;
	}
	return right; 
}

int RectanglesMappingAlg(std::unique_ptr<std::unique_ptr<int[]>[]>& map, std::vector<int>& vecX, std::vector<int>& vecY, Point2i& p)
{
	int indX = BinSearch(vecX, p.GetX());
	int indY = BinSearch(vecY, p.GetY());

	if (indX < 0 || indX > vecX.size() || indY < 0 || indY > vecY.size())
		return 0;
	return map[indX][indY];
}

std::vector<Rectangle> RectanglesGeneration(int vecSize)
{
	std::vector<Rectangle> rectangles(vecSize);
	for (int i = 0; i < vecSize; ++i) {
		rectangles[i].GetLowerLeftCorner().GetX() = rectangles[i].GetLowerLeftCorner().GetY() = 10 * i;
		rectangles[i].GetUpperRightCorner().GetX() = rectangles[i].GetUpperRightCorner().GetY() = 10 * (2 * vecSize - i);
	}
	return rectangles;
}

std::vector<Point2i> PointsGeneration(int vecSize)
{
	std::vector<Point2i> points(vecSize);
	for (size_t i = 0; i < vecSize; i++)
	{
		points[i].GetX() = ModPow(7369 * i, 31, 20 * vecSize);
		points[i].GetY() = ModPow(7351 * i, 31, 20 * vecSize);
	}
	return points;
}

long long ModPow(long long x, int pow, long long mod)
{
	if (pow == 0)
		return 1;

	if (pow % 2 == 0) {
		long long z = ModPow(x, pow / 2, mod);
		return (z * z) % mod;
	}
	else {
		long long z = ModPow(x, (pow - 1) / 2, mod);
		return (x * z * z) % mod;
	}
}

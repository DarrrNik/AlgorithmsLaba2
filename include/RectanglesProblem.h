#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <set>
#include <chrono>
#include <iostream>
#include "Rectangle.h"
#include "PersistentSegmentTree.h"

int BruteForceAlg(std::vector<Rectangle>& rectangles, Point2i& point);

void RectanglesMappingAlgPreparation(std::vector<Rectangle>& rectangles, std::unique_ptr<std::unique_ptr<int[]>[]>& map,
	std::vector<int>& vecX, std::vector<int>& vecY);

int BinSearch(const std::vector<int>& vec, int target);

int RectanglesMappingAlg(std::unique_ptr<std::unique_ptr<int[]>[]>& map, std::vector<int>& vecX, std::vector<int>& vecY, Point2i& p);

std::vector<Rectangle> RectanglesGeneration(int vecSize);

std::vector<Point2i> PointsGeneration(int vecSize);

long long ModPow(long long x, int pow, long long mod);
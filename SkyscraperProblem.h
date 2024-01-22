#pragma once

#include <vector>
#include <algorithm>
#include <iostream>

typedef struct Skyscraper {
	int left, right, height;
}Skycrapper;
typedef struct Point {
	int x, y;
}Point;

std::vector<Point> HeightsMatrix(std::vector<Skyscraper> heights);

std::vector<Point> HeightsArray(std::vector<Skycrapper> heights);
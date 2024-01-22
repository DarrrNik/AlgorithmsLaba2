#include "SkyscraperProblem.h"

int main() {
	std::vector<Skycrapper> heights{
		Skycrapper{ 1, 3, 2 },
		Skycrapper{ 2, 4, 3 },
		Skycrapper{ 4, 5, 1 }
	};
	std::vector<Point> ansMatrix = HeightsMatrix(heights);
	std::vector<Point> ansArray = HeightsArray(heights);

	return 0;
}
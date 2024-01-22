#include "SkyscraperProblem.h"

std::vector<Point> HeightsMatrix(std::vector<Skyscraper> heights)
{
    int maxRight = -1, maxHeight = -1;
    for (auto it : heights) {
        maxRight = std::max(maxRight, it.right);
        maxHeight = std::max(maxHeight, it.height);
    }
    ++maxRight; ++maxHeight;

    int** heightMatrix = new int* [maxRight];
    for (int i = 0; i < maxRight; ++i) {
        heightMatrix[i] = new int[maxHeight];
        for (int j = 0; j < maxHeight; ++j) heightMatrix[i][j] = 0;
    }

    for (auto it : heights) 
        for (int x = it.left; x <= it.right; ++x) 
            for (int y = 0; y <= it.height; ++y) 
                heightMatrix[x][y] = 1;

    std::vector<Point> ans;

    int y = 0;
    for (int x = 0; x < maxRight; ++x) {
        if (y < maxHeight - 1 && x < maxRight - 1 && heightMatrix[x][y + 1] /*&& heightMatrix[x + 1][y + 1]*/) {
            while (y < maxHeight - 1 && heightMatrix[x][y + 1]) ++y;
            ans.push_back(Point{ x, y });
            continue;
        }
        if (y > 0 && x < maxRight - 1 && !heightMatrix[x + 1][y]) {
            while (y > 0 && !heightMatrix[x + 1][y]) --y;
            ans.push_back(Point{ x, y });
            continue;
        }
    }
    ans.push_back(Point{ maxRight - 1, 0 });
    return ans;
}

std::vector<Point> HeightsArray(std::vector<Skycrapper> heights)
{
    int maxRight = -1;
    for (auto it : heights) maxRight = std::max(it.right, maxRight);
    ++maxRight;

    int* heightArray = new int[maxRight];
    for (int i = 0; i < maxRight; ++i) heightArray[i] = 0;

    for (auto it : heights)
        for (int i = it.left; i <= it.right; ++i)
            heightArray[i] = std::max(heightArray[i], it.height);

    std::vector<Point> ans;

    for (int x = 0; x < maxRight; ++x) {
        if (x > 0 && heightArray[x - 1] < heightArray[x])
            ans.push_back(Point{ x, heightArray[x] });
        if (x > 0 && heightArray[x - 1] > heightArray[x])
            ans.push_back(Point{ x - 1, heightArray[x] });
    }
    ans.push_back(Point{ maxRight - 1, 0 });
    return ans;
}

#include "RectanglesProblem.h"

int main() {
    std::vector<Point2i> points = PointsGeneration(100000);
    int recsSize = 1;
    for (int x = 1; x < 10; ++x) {
        std::vector<Rectangle> rectangles = RectanglesGeneration(recsSize);
        std::unique_ptr<std::unique_ptr<int[]>[]> map;
        std::vector<int> vecX, vecY;
        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        RectanglesMappingAlgPreparation(rectangles, map, vecX, vecY);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << "Mapping algorithm preparation time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << '\n';
        start = std::chrono::steady_clock::now();
        PersistentSegmentTree segTree(vecY, vecX, rectangles);
        end = std::chrono::steady_clock::now();
        std::cout << "Segment tree algorithm preparation time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << '\n';

        long long algsTime = 0;
        for (int i = 0; i < 5; ++i) {
            start = std::chrono::steady_clock::now();
            for (Point2i p : points)
                BruteForceAlg(rectangles, p);
            end = std::chrono::steady_clock::now();
            algsTime += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        }
        std::cout << "\Brute force algorithm time : " << algsTime / 5 << '\n';
        algsTime = 0;
        for (int i = 0; i < 5; ++i) {
            start = std::chrono::steady_clock::now();
            for (Point2i p : points)
                RectanglesMappingAlg(map, vecX, vecY, p);
            end = std::chrono::steady_clock::now();
            algsTime += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        }
        std::cout << "Mapping algorithm time : " << algsTime / 5 << '\n';
        algsTime = 0;
        for (int i = 0; i < 5; ++i) {
            start = std::chrono::steady_clock::now();
            for (Point2i p : points)
                segTree.GetAnswer(p, vecX, vecY);
            end = std::chrono::steady_clock::now();
            algsTime += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        }
        std::cout << "Segment tree algorithm time : " << algsTime / 5 << "\n\n\n";
        
        recsSize *= 2;
    }
    std::cin >> recsSize;
    return 0;
}
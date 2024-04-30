#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <memory>

class Point2i
{
public:
	Point2i(int x_ = -1, int y_ = -1);

	int& GetX();
	int& GetY();
private:
	int x, y;
};

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

template<typename T>
class Node
{
public:
	Node(T val = 0, Node<T>* lft = nullptr, Node<T>* rght = nullptr, int lftInd = 0, int rghtInd = 0);


	T value;
	Node<T>* left, * right;
	int leftInd, rightInd;
};

template<typename T>
inline Node<T>::Node(T val, Node<T>* lft, Node<T>* rght, int lftInd, int rghtInd) :
	value(val), left(lft), right(rght), leftInd(lftInd), rightInd(rghtInd) {}


class Rectangle
{
public:
	Rectangle(Point2i lowerLeft = Point2i(), Point2i upperRight = Point2i());

	Point2i& GetUpperRightCorner();
	Point2i& GetLowerLeftCorner();
private:
	Point2i lowerLeftCorner, upperRightCorner;
};

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

struct Action {
	int x;
	int yBottom, yUp;
	int action;
};

class PersistentSegmentTree
{
public:
	PersistentSegmentTree(const std::vector<int>& vecY, const std::vector<int>& vecX, std::vector<Rectangle>& rectangles);

	int GetAnswer(Point2i p, const std::vector<int>& vecX, const std::vector<int>& vecY);
private:
	int SearchInTree(Node<int>* head, int target);
	Node<int>* BuildEmptyTree(int left, int right);
	void BuildPersistentSegmentTree(std::vector<Rectangle>& rectangles, const std::vector<int>& vecX, const std::vector<int>& vecY);
	Node<int>* ModifySegment(Node<int>* head, int left, int right, int val);
	std::vector<Node<int>*> heads;
};

PersistentSegmentTree::PersistentSegmentTree(const std::vector<int>& vecY, const std::vector<int>& vecX, std::vector<Rectangle>& rectangles) : heads(rectangles.size() * 2, nullptr)
{
	BuildPersistentSegmentTree(rectangles, vecX, vecY);
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

int PersistentSegmentTree::GetAnswer(Point2i p, const std::vector<int>& vecX, const std::vector<int>& vecY)
{
	int xInd = BinSearch(vecX, p.GetX());
	int yInd = BinSearch(vecY, p.GetY());
	if (xInd < 0 || xInd >= vecX.size() || yInd < 0 || yInd >= vecY.size())
		return 0;
	return SearchInTree(heads[xInd], yInd);
}

int PersistentSegmentTree::SearchInTree(Node<int>* head, int target)
{
	if (!head) return 0;
	int mid = (head->leftInd + head->rightInd) / 2;
	if (target < mid)
		return head->value + SearchInTree(head->left, target);
	return head->value + SearchInTree(head->right, target);
}

Node<int>* PersistentSegmentTree::BuildEmptyTree(int left, int right)
{
	if (left + 1 == right)
		return new Node<int>(0, nullptr, nullptr, left, right);
	return new Node<int>(0, BuildEmptyTree(left, (left + right) / 2), BuildEmptyTree((left + right) / 2, right), left, right);
}

void PersistentSegmentTree::BuildPersistentSegmentTree(std::vector<Rectangle>& rectangles, const std::vector<int>& vecX, const std::vector<int>& vecY)
{
	if (rectangles.empty())
		return;

	std::vector<Action> actions(rectangles.size() * 2);
	{
		int j = 0;
		for (Rectangle& rec : rectangles) {
			actions[j++] = {
				BinSearch(vecX, rec.GetLowerLeftCorner().GetX()),
				BinSearch(vecY, rec.GetLowerLeftCorner().GetY()),
				BinSearch(vecY, rec.GetUpperRightCorner().GetY()),
				1
			};
			actions[j++] = {
				BinSearch(vecX, rec.GetUpperRightCorner().GetX()),
				BinSearch(vecY, rec.GetLowerLeftCorner().GetY()),
				BinSearch(vecY, rec.GetUpperRightCorner().GetY()),
				-1
			};
		}
	}
	std::sort(actions.begin(), actions.end(), [](const Action& a, const Action& b) {return a.x < b.x; });

	Node<int>* head = BuildEmptyTree(0, vecY.size());
	int ind = 0;
	int endX = actions[0].x;
	for (const Action& act : actions) {
		if (endX != act.x) {
			heads[ind++] = head;
			endX = act.x;
		}
		head = ModifySegment(head, act.yBottom, act.yUp, act.action);
	}

}

Node<int>* PersistentSegmentTree::ModifySegment(Node<int>* head, int left, int right, int val)
{
	if (left <= head->leftInd && right >= head->rightInd)
		return new Node<int>(head->value + val, head->left, head->right, head->leftInd, head->rightInd);
	if (left >= head->rightInd || right <= head->leftInd)
		return head;
	return new Node<int>(head->value, ModifySegment(head->left, left, right, val), ModifySegment(head->right, left, right, val), head->leftInd, head->rightInd);
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

int main() {
	int n;
	std::cin >> n;
	std::vector<Rectangle> rectangles(n);
	for (Rectangle& rect : rectangles) {
		std::cin >> rect.GetLowerLeftCorner().GetX() >> rect.GetLowerLeftCorner().GetY();
		std::cin >> rect.GetUpperRightCorner().GetX() >> rect.GetUpperRightCorner().GetY();
	}
	int m;
	std::cin >> m;
	std::vector<Point2i> points(m);
	for (Point2i& p : points) {
		std::cin >> p.GetX() >> p.GetY();
	}
	std::vector<int> vecX, vecY;
	std::unique_ptr<std::unique_ptr<int[]>[]> map;
	RectanglesMappingAlgPreparation(rectangles, map, vecX, vecY);
	PersistentSegmentTree segTree(vecY, vecX, rectangles);
	for (Point2i& p : points) {
		std::cout << segTree.GetAnswer(p, vecX, vecY) << ' ';
	}
}
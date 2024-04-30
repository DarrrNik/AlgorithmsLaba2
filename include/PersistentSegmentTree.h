#pragma once
#include <vector>
#include <algorithm>
#include "Point2i.h"
#include "Node.h"
#include "RectanglesProblem.h"

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


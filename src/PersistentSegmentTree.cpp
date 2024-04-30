#include "PersistentSegmentTree.h"

PersistentSegmentTree::PersistentSegmentTree(const std::vector<int>& vecY, const std::vector<int>& vecX, std::vector<Rectangle>& rectangles) : heads(rectangles.size() * 2, nullptr)
{
	BuildPersistentSegmentTree(rectangles, vecX, vecY);
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

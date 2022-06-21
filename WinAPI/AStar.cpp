#include "Stdafx.h"
#include "AStar.h"
#include "Tile.h"

void AStar::init(vector<Tile*> vTile, int row, int col)
{
	mvTile = vTile;
	miStart = 0;
	miEnd = 0;
	miRowMax = row;
	miColMax = col;
}

void AStar::release()
{
	for (int i = 0; i < mvNode.size(); i++) {
		SAFE_DELETE(mvNode[i]);
	}
}

void AStar::Algorithm(int start, int end)
{
	for (auto iter : mvTile) {
		NODE* node = new NODE;
		node->type = iter->GetType();
		node->parent = nullptr;
		node->f = node->g = node->h = 0;
		node->index = iter->GetIndex();
		node->row = iter->GetRow();
		node->col = iter->GetCol();
		mvNode.push_back(node);
	}
	miStart = start;
	miEnd = end;

	mvOpenList.push_back(mvNode[miStart]);
	while (true)
	{
		if (SubOpenList()) {
			FindPath(mvNode[miEnd]);
			break;
		}
		FindAdjacentNode(mvNode[mvCloseList.back()]);
		sort(mvOpenList.begin(), mvOpenList.end(), Compare());
	}
}

void AStar::Algorithm(set<int> range, int start, int end)
{
	for (auto iter : mvTile) {
		NODE* node = new NODE;
		node->type = iter->GetType();
		node->parent = nullptr;
		node->f = node->g = node->h = 0;
		node->index = iter->GetIndex();
		node->row = iter->GetRow();
		node->col = iter->GetCol();
		mvNode.push_back(node);
	}
	miStart = start;
	miEnd = end;

	mvOpenList.push_back(mvNode[miStart]);
	while (true)
	{
		if (SubOpenList()) {
			FindPath(mvNode[miEnd]);
			break;
		}
		FindAdjacentNode(mvNode[mvCloseList.back()]);
		sort(mvOpenList.begin(), mvOpenList.end(), Compare());
	}
	if(range.find(miEnd) == range.end()) SubPath(range);
}

void AStar::AddOpenList(NODE* prevNode, int index)
{
	bool recalculateG = true;
	for (auto iter = mvOpenList.begin(); iter != mvOpenList.end(); ++iter) {
		if ((*iter)->index == index) {
			if (CompareG(prevNode, mvNode[index])) {
				recalculateG = false;
				mvOpenList.erase(iter);
				break;
			}
			else return;
		}
	}
	mvNode[index]->parent = prevNode;
	if (recalculateG) G(mvNode[index]);
	H(mvNode[index]);
	F(mvNode[index]);
	mvOpenList.push_back(mvNode[index]);
	msTile.insert(index);
}

bool AStar::SubOpenList()
{
	PAIR_INT min = make_pair(mvOpenList.front()->f, mvOpenList.front()->index);
	for (auto iter = mvOpenList.begin() + 1; iter != mvOpenList.end(); ++iter) {
		if ((*iter)->f > min.first) break;
		else {
			min.first = (*iter)->f;
			min.second = (*iter)->index;
		}
	}
	mvCloseList.push_back(min.second);
	for (auto iter = mvOpenList.begin(); iter != mvOpenList.end();) {
		if ((*iter)->index == min.second) {
			iter = mvOpenList.erase(iter);
			break;
		}
		else ++iter;
	}
	if (min.second == miEnd) return true;
	return false;
}

void AStar::FindAdjacentNode(NODE* node)
{
	int row = node->row;
	int col = node->col;
	int index = node->index;

	int left = index - 1;
	int right = index + 1;
	int up = index - miRowMax;
	int down = index + miRowMax;

	if (row - 1 >= 0 && left >= 0) {
		if (mvNode[left]->type == eObjectType::TILE && find(mvCloseList.begin(), mvCloseList.end(), left) == mvCloseList.end()) {
			AddOpenList(node, left);
		}
	}
	if (row + 1 < miRowMax && right < miRowMax * miColMax) {
		if (mvNode[right]->type == eObjectType::TILE && find(mvCloseList.begin(), mvCloseList.end(), right) == mvCloseList.end()) {
			AddOpenList(node, right);
		}
	}
	if (col - 1 >= 0 && up >= 0) {
		if (mvNode[up]->type == eObjectType::TILE && find(mvCloseList.begin(), mvCloseList.end(), up) == mvCloseList.end()) {
			AddOpenList(node, up);
		}
	}
	if (col + 1 < miColMax && down < miRowMax * miColMax) {
		if (mvNode[down]->type == eObjectType::TILE && find(mvCloseList.begin(), mvCloseList.end(), down) == mvCloseList.end()) {
			AddOpenList(node, down);
		}
	}
}

void AStar::FindPath(NODE* node)
{
	mqPath.push_front(node->index);
	if (node->parent == nullptr) return;
	else FindPath(node->parent);
}

void AStar::SubPath(set<int> range)
{
	for (auto iter = mqPath.end() - 1; iter != mqPath.begin() - 1; --iter) {
		if (range.find(*iter) != range.end()) {
			mqPath.erase(iter, mqPath.end());
			break;
		}
	}
}

void AStar::G(NODE* node)
{
	node->g = node->parent->g + 1;
}

void AStar::H(NODE* node)
{
	node->h = ManhattanDistance(PointMake(node->row, node->col),
								PointMake(mvNode[miEnd]->row, mvNode[miEnd]->col));
}

void AStar::F(NODE* node)
{
	node->f = node->g + node->h;
}

bool AStar::CompareG(NODE* prevNode, NODE* node)
{
	int currG = prevNode->g + 1;
	if (currG < node->g) {
		node->g = currG;
		return true;
	}
	else return false;
}

int AStar::ManhattanDistance(POINT p, POINT q)
{
	return abs(p.x - q.x) + abs(p.y - q.y);
}

void AStar::ClearPath()
{
	this->release();
	mvNode.clear();
	mvOpenList.clear();
	mvCloseList.clear();
	mqPath.clear();
	msTile.clear();
}

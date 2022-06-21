#pragma once

struct Compare
{
	bool operator()(NODE* n1, NODE* n2){
		return n1->f < n2->f;
	}
};

class AStar
{
private:
	vector<Tile*> mvTile;
	vector<NODE*> mvNode;
	vector<NODE*> mvOpenList;
	vector<int> mvCloseList;
	deque<int> mqPath;
	set<int> msTile;

	int miStart;
	int miEnd;
	int miRowMax;
	int miColMax;
public:
	void init(vector<Tile*> vTile, int row, int col);
	void release();

	deque<int> GetPath() { return mqPath; }
	set<int> GetTile() { return msTile; }

	void SetPath(deque<int> path) { mqPath = path; }

	void Algorithm(int start, int end);
	void Algorithm(set<int> range, int start, int end);
	void AddOpenList(NODE* prevNode, int nextIndex);
	bool SubOpenList();
	void FindAdjacentNode(NODE* node);
	void FindPath(NODE* node);
	void SubPath(set<int> range);

	void G(NODE* node);
	void H(NODE* node);
	void F(NODE* node);
	bool CompareG(NODE* prevNode, NODE* node);
	int ManhattanDistance(POINT p, POINT q);

	void ClearPath();

	AStar() {}
	~AStar() {}
};


#include <vector>
class BranchAndBoundNode
{
public:
	std::vector<int> path;
	int** reducedMatrix;
	int cost;
	int cityNum;
	int currentNode;
public:
	BranchAndBoundNode(int** reducedMatrix, std::vector<int> path, int cost, int currentNode, int cityNum);
	~BranchAndBoundNode();
	int** getMatrix();
	void disablePaths();
	int getCost() const;
	std::vector<int> getPath();
	void copyMatrix(int** matrix);
	int getCurrentNode();
};


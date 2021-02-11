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
	int** GetMatrix();
	void DisablePaths();
	int GetCost() const;
	std::vector<int> GetPath();
	void CopyMatrix(int** matrix);
	int GetCurrentNode();
};


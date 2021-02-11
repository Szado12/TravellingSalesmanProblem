#include "TSPBranchAndBound.h"

/// <summary>
/// Function comapres 2 Branch And Bound Nodes
/// </summary>
struct comp {
	bool operator()(const BranchAndBoundNode* lhs, const BranchAndBoundNode* rhs) const
	{
		return lhs->GetCost() > rhs->GetCost();
	}
};

/// <summary>
/// Constructor with parameters
/// </summary>
/// <param name="arrayGraph"></param>
/// <param name="cityNum"></param>
TSPBranchAndBound::TSPBranchAndBound(int** arrayGraph, int cityNum)
{
	this->cityNum = cityNum;
	this->arrayGraph = arrayGraph;
	this->topCost = INT_MAX;
}
/// <summary>
/// Branch and Bound algorithm with breadth first searching method
/// </summary>
void TSPBranchAndBound::CalculatePath()
{
	std::priority_queue<BranchAndBoundNode*, std::vector<BranchAndBoundNode*>, comp> queue;
	int** reducedMatrix = new int* [cityNum];
	for(int i=0;i<this->cityNum;i++)
		reducedMatrix[i] = new int[cityNum];

	CopyMatrices(reducedMatrix, this->arrayGraph);
	std::vector<int> startPath;
	int cost = ReduceMatrix(reducedMatrix);
	BranchAndBoundNode* node = new BranchAndBoundNode(reducedMatrix, startPath, cost, 0, this->cityNum);
	queue.push(node);
	int counter = 0;
	while (!queue.empty()) {
		BranchAndBoundNode* newNode = queue.top();
		queue.pop();
		if (newNode->GetCost() < this->topCost) {
			if (newNode->GetPath().size() == this->cityNum) {
				this->topCost = newNode->GetCost();
				this->path = newNode->GetPath();
			}
			else {
				reducedMatrix = newNode->GetMatrix();
				cost = newNode->GetCost();
				cost += ReduceMatrix(reducedMatrix);
				int currentNode = newNode->GetCurrentNode();
				for (int i = 0; i < this->cityNum; i++) {
					if (reducedMatrix[currentNode][i] > -1 and i!=currentNode and cost+reducedMatrix[currentNode][i]<this->topCost)
					{
						try {
							BranchAndBoundNode* nextNode = new BranchAndBoundNode(reducedMatrix, newNode->GetPath(), cost+ reducedMatrix[currentNode][i], i, this->cityNum);
							queue.push(nextNode);
						}
						catch (const std::exception&) {
							printf("Allocating memory failed");
							break;
						}
					}
				}
			}
		}
		delete newNode;
	}
	this->distance = this->topCost;
}
/// <summary>
/// Function copies matrix of graph
/// </summary>
/// <param name="matrix1"></param>
/// <param name="matrix2"></param>
void TSPBranchAndBound::CopyMatrices(int** matrix1, int** matrix2)
{
	for (int i = 0; i < this->cityNum; i++)
		for (int j = 0; j < this->cityNum; j++)
			matrix1[i][j] = matrix2[i][j];
}


/// <summary>
/// Function returns arrays of minimum values in each row
/// </summary>
/// <param name="arrayGraph"></param>
/// <returns></returns>
int* TSPBranchAndBound::FindMinInRows(int** arrayGraph)
{
	int* minRow = new int[this->cityNum];
	for (int i = 0; i < this->cityNum; i++) {
		minRow[i] = INT_MAX;
		for (int j = 0; j < this->cityNum; j++) {
			if (minRow[i] > arrayGraph[i][j] and i != j and arrayGraph[i][j] >= 0)
				minRow[i] = arrayGraph[i][j];
		}
		if (minRow[i] == INT_MAX)
			minRow[i] = 0;
	}
	return minRow;
}
/// <summary>
/// Function returns arrays of minimum values in each column
/// </summary>
/// <param name="arrayGraph"></param>
/// <returns></returns>
int* TSPBranchAndBound::FindMinInCols(int** arrayGraph)
{
	int* minCol = new int[this->cityNum];
	for (int i = 0; i < this->cityNum; i++) {
		minCol[i] = INT_MAX;
		for (int j = 0; j < this->cityNum; j++) {
			if (minCol[i] > arrayGraph[j][i] and i != j and arrayGraph[j][i] >= 0)
				minCol[i] = arrayGraph[j][i];
		}
		if (minCol[i] == INT_MAX)
			minCol[i] = 0;
	}
	return minCol;
}
/// <summary>
/// Function reduces matrix
/// </summary>
/// <param name="arrayGraph"></param>
/// <returns></returns>
int TSPBranchAndBound::ReduceMatrix(int** arrayGraph)
{
	int costOfRed = 0;
	int* min = FindMinInRows(arrayGraph);
	for (int i = 0; i < this->cityNum; i++) {
		costOfRed += min[i];
		for (int j = 0; j < this->cityNum; j++)
			arrayGraph[i][j] -= min[i];
	}
	min = FindMinInCols(arrayGraph);
	for (int i = 0; i < this->cityNum; i++) {
		costOfRed += min[i];
		for (int j = 0; j < this->cityNum; j++)
			arrayGraph[j][i] -= min[i];
	}
	return costOfRed;
}


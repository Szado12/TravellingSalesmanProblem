#include "TSPBranchAndBound.h"


struct comp {
	bool operator()(const BranchAndBoundNode* lhs, const BranchAndBoundNode* rhs) const
	{
		return lhs->getCost() > rhs->getCost();
	}
};


TSPBranchAndBound::TSPBranchAndBound(int** arrayGraph, int cityNum)
{
	this->cityNum = cityNum;
	this->arrayGraph = arrayGraph;
	this->topCost = INT_MAX;
}

void TSPBranchAndBound::calculatePath()
{
	std::priority_queue<BranchAndBoundNode*, std::vector<BranchAndBoundNode*>, comp> queue;
	int** reducedMatrix = new int* [cityNum];
	for(int i=0;i<this->cityNum;i++)
		reducedMatrix[i] = new int[cityNum];

	copyMatrices(reducedMatrix, this->arrayGraph);
	std::vector<int> startPath;
	int cost = reduceMatrix(reducedMatrix);
	BranchAndBoundNode* node = new BranchAndBoundNode(reducedMatrix, startPath, cost, 0, this->cityNum);
	queue.push(node);
	int counter = 0;
	while (!queue.empty()) {
		BranchAndBoundNode* newNode = queue.top();
		queue.pop();
		if (newNode->getCost() < this->topCost) {
			if (newNode->getPath().size() == this->cityNum) {
				this->topCost = newNode->getCost();
				this->path = newNode->getPath();
			}
			else {
				reducedMatrix = newNode->getMatrix();
				cost = newNode->getCost();
				cost += reduceMatrix(reducedMatrix);
				int currentNode = newNode->getCurrentNode();
				for (int i = 0; i < this->cityNum; i++) {
					if (reducedMatrix[currentNode][i] > -1 and i!=currentNode and cost+reducedMatrix[currentNode][i]<this->topCost)
					{
						try {
							BranchAndBoundNode* nextNode = new BranchAndBoundNode(reducedMatrix, newNode->getPath(), cost+ reducedMatrix[currentNode][i], i, this->cityNum);
							queue.push(nextNode);
						}
						catch (const std::exception&) {
							printf("Allocating memeory failed");
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

void TSPBranchAndBound::copyMatrices(int** matrix1, int** matrix2)
{
	for (int i = 0; i < this->cityNum; i++)
		for (int j = 0; j < this->cityNum; j++)
			matrix1[i][j] = matrix2[i][j];
}



int* TSPBranchAndBound::findMinInRows(int** arrayGraph)
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

int* TSPBranchAndBound::findMinInCols(int** arrayGraph)
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

int TSPBranchAndBound::reduceMatrix(int** arrayGraph)
{
	int costOfRed = 0;
	int* min = findMinInRows(arrayGraph);
	for (int i = 0; i < this->cityNum; i++) {
		costOfRed += min[i];
		for (int j = 0; j < this->cityNum; j++)
			arrayGraph[i][j] -= min[i];
	}
	min = findMinInCols(arrayGraph);
	for (int i = 0; i < this->cityNum; i++) {
		costOfRed += min[i];
		for (int j = 0; j < this->cityNum; j++)
			arrayGraph[j][i] -= min[i];
	}
	return costOfRed;
}


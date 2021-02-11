#include "BranchAndBoundNode.h"

BranchAndBoundNode::BranchAndBoundNode(int** reducedMatrix, std::vector<int> path, int cost, int currentNode, int cityNum)
{
	this->path = path;
	this->cost = cost;
	this->cityNum = cityNum;
	this->currentNode = currentNode;
	this->reducedMatrix = new int* [this->cityNum];
	for (int i = 0; i < this->cityNum; i++)
		this->reducedMatrix[i] = new int[this->cityNum];
	this->CopyMatrix(reducedMatrix);
	if (this->path.size() > 0)
		this->DisablePaths();
	this->path.push_back(currentNode);
}
BranchAndBoundNode::~BranchAndBoundNode() {
	for (int i = 0; i < this->cityNum; i++)
		delete[] this->reducedMatrix[i];
	delete[] this->reducedMatrix;
}

int** BranchAndBoundNode::GetMatrix()
{
	return this->reducedMatrix;
}

void BranchAndBoundNode::DisablePaths()
{
	int lastNode = this->path.back();
	for (int i = 0; i < cityNum; i++) {
		this->reducedMatrix[i][this->currentNode] = -1;
		this->reducedMatrix[lastNode][i] = -1;
		if (this->path.size() > i)
			this->reducedMatrix[this->currentNode][this->path[i]] = -1;
	}
}

int BranchAndBoundNode::GetCost() const
{
	return this->cost;
}

std::vector<int> BranchAndBoundNode::GetPath()
{
	return this->path;
}

void BranchAndBoundNode::CopyMatrix(int** matrix)
{
	for (int i = 0; i < this->cityNum; i++)
		for (int j = 0; j < this->cityNum; j++)
			this->reducedMatrix[i][j] = matrix[i][j];
}

int BranchAndBoundNode::GetCurrentNode()
{
	return this->currentNode;
}

#include <queue>
#include "BranchAndBoundNode.h"
#include "TSPAlgorithm.h"
class TSPBranchAndBound : public TSPAlgorithm
{
private:
	int topCost;
	
public:
	TSPBranchAndBound(int** arrayGraph, int cityNum);
	void calculatePath();
	void copyMatrices(int** matrix1, int** matrix2);
	int* findMinInRows(int** arrayGraph);
	int* findMinInCols(int** arrayGraph);
	int reduceMatrix(int** arrayGraph);
};


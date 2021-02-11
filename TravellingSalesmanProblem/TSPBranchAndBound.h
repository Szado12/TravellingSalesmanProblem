#include <queue>
#include "BranchAndBoundNode.h"
#include "TSPAlgorithm.h"
class TSPBranchAndBound : public TSPAlgorithm
{
private:
	int topCost;
	
public:
	TSPBranchAndBound(int** arrayGraph, int cityNum);
	void CalculatePath();
	void CopyMatrices(int** matrix1, int** matrix2);
	int* FindMinInRows(int** arrayGraph);
	int* FindMinInCols(int** arrayGraph);
	int ReduceMatrix(int** arrayGraph);
};


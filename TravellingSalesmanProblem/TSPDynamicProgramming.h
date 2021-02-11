#include <math.h>
#include "TSPAlgorithm.h"
class TSPDynamicProgramming : public TSPAlgorithm
{
	
private:
	int** memArray;
	int maskMax;
public:
	TSPDynamicProgramming(int** arrayGraph, int cityNum);
	int DynamicProgramming(int mask, int pos);
	void CalculatePath();
	void CreatePath();
	int MaskToPos(int mask1, int mask2);
};


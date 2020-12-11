#include <math.h>
#include "TSPAlgorithm.h"
class TSPDynamicProgramming : public TSPAlgorithm
{
	
private:
	int** memArray;
	int maskMax;
public:
	TSPDynamicProgramming(int** arrayGraph, int cityNum);
	int dynamicProgramming(int mask, int pos);
	void calculatePath();
	void createPath();

	int maskToPos(int mask1, int mask2);
};


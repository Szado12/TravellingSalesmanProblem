#include "TSPDynamicProgramming.h"

TSPDynamicProgramming::TSPDynamicProgramming(int** arrayGraph, int cityNum)
{
	this->arrayGraph = arrayGraph;
	this->cityNum = cityNum;
	this->maskMax = (1 << cityNum - 1) - 1;
}

int TSPDynamicProgramming::dynamicProgramming(int mask, int pos)
{
	int distance = INT_MAX;
	if (mask == this->maskMax) {
		memArray[mask][pos] = this->arrayGraph[pos][0];
		return this->arrayGraph[pos][0];
	}
	if (memArray[mask][pos] == -1) {
		for (int i = 1; i < this->cityNum; i++)
			if ((mask & (1 << i - 1)) == 0) {
				int newDistance = this->arrayGraph[pos][i] + this->dynamicProgramming(mask | (1 << i - 1), i);
				if (newDistance < distance) {
					distance = newDistance;
					if (pos == 0)
						memArray[mask][1] = mask | (1 << i - 1);
					else
						memArray[mask][0] = mask | (1 << i - 1);
				}
			}
		memArray[mask][pos] = distance;
	}
	return memArray[mask][pos];
}

void TSPDynamicProgramming::calculatePath()
{
	try {
		int N2 = int(pow(2, this->cityNum - 1));
		this->memArray = new int* [N2];
		for (int i = 0; i < N2; i++)
			this->memArray[i] = new int[this->cityNum];
		for (int i = 0; i < N2; i++)
			for (int j = 0; j < this->cityNum; j++)
				this->memArray[i][j] = -1;
		this->distance = this->dynamicProgramming(0, 0);
		this->createPath();
		for (int i = 0; i < N2; i++)
			delete[] memArray[i];
		delete[] memArray;
	}
	catch (const std::bad_alloc) {
		printf("B³¹d alkowania pamiêci");
	}
}

void TSPDynamicProgramming::createPath()
{
	int x = memArray[0][1];
	int y = 0;
	this->path.push_back(0);
	for (int i = 1; i < this->cityNum; i++) {
		this->path.push_back(this->maskToPos(x, y));
		y = x;
		x = memArray[x][0];
	}
}
int TSPDynamicProgramming::maskToPos(int mask1, int mask2) {
	return (log2(abs(mask1 - mask2)) + 1);
}


#include "TSPDynamicProgramming.h"

/// <summary>
/// Constructor with parameters
/// </summary>
/// <param name="arrayGraph"></param>
/// <param name="cityNum"></param>
TSPDynamicProgramming::TSPDynamicProgramming(int** arrayGraph, int cityNum)
{
	this->arrayGraph = arrayGraph;
	this->cityNum = cityNum;
	this->maskMax = (1 << cityNum - 1) - 1;
}
/// <summary>
/// Functions calculate best solution using recursive and solving sub-problems.
/// </summary>
/// <param name="mask"></param>
/// <param name="pos"></param>
/// <returns></returns>
int TSPDynamicProgramming::DynamicProgramming(int mask, int pos)
{
	int distance = INT_MAX;
	if (mask == this->maskMax) {
		memArray[mask][pos] = this->arrayGraph[pos][0];
		return this->arrayGraph[pos][0];
	}
	if (memArray[mask][pos] == -1) {
		for (int i = 1; i < this->cityNum; i++)
			if ((mask & (1 << i - 1)) == 0) {
				int newDistance = this->arrayGraph[pos][i] + this->DynamicProgramming(mask | (1 << i - 1), i);
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
/// <summary>
/// Function creates array for DP and starts DP algortihm.
/// </summary>
void TSPDynamicProgramming::CalculatePath()
{
	try {
		int N2 = int(pow(2, this->cityNum - 1));
		this->memArray = new int* [N2];
		for (int i = 0; i < N2; i++)
			this->memArray[i] = new int[this->cityNum];
		for (int i = 0; i < N2; i++)
			for (int j = 0; j < this->cityNum; j++)
				this->memArray[i][j] = -1;
		this->distance = this->DynamicProgramming(0, 0);
		this->CreatePath();
		for (int i = 0; i < N2; i++)
			delete[] memArray[i];
		delete[] memArray;
	}
	catch (const std::bad_alloc) {
		printf("Allocating memeory failed");
	}
}
/// <summary>
/// Function creates path from masks
/// </summary>
void TSPDynamicProgramming::CreatePath()
{
	int x = memArray[0][1];
	int y = 0;
	this->path.push_back(0);
	for (int i = 1; i < this->cityNum; i++) {
		this->path.push_back(this->MaskToPos(x, y));
		y = x;
		x = memArray[x][0];
	}
}
/// <summary>
/// Function returns postion of diffrence in masks
/// </summary>
/// <param name="mask1"></param>
/// <param name="mask2"></param>
/// <returns></returns>
int TSPDynamicProgramming::MaskToPos(int mask1, int mask2) {
	return (log2(abs(mask1 - mask2)) + 1);
}


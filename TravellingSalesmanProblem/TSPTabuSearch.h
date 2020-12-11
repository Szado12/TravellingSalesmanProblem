#include "TSPMetaheuristicAlgorithm.h"

class TSPTabuSearch : public TSPMetaheuristicAlgorithm
{
	int **tabuList;
	std::vector<int> currentPath;
	int time;
	typedef std::vector<int>(TSPTabuSearch::*func)(int x, int y, std::vector<int> vector);
	TSPTabuSearch::func findNeigbour;
	int type;
public:
	TSPTabuSearch(int** arrayGraph, int cityNum, int second,int type);
	void restart(std::vector<int>* vector);
	void search();
	std::vector<int> findPathSwap(int x, int y, std::vector<int> currentPath);
	std::vector<int> findPathReverse(int x, int y, std::vector<int> currentPath);
	std::vector<int> findPathInsert(int x, int y, std::vector<int> currentPath);
	void untabu();
	void clearTabu();
};


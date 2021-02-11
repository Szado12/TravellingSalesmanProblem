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
	void Restart();
	void TabuSearch();
	std::vector<int> FindPathSwap(int x, int y, std::vector<int> currentPath);
	std::vector<int> FindPathReverse(int x, int y, std::vector<int> currentPath);
	std::vector<int> FindPathInsert(int x, int y, std::vector<int> currentPath);
	void Untabu();
	void ClearTabu();
};


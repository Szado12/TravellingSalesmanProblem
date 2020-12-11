#include <vector>

class Graph
{
private:
	std::vector<int> path;
	int distance;
	int** arrayGraph;
	int cityNum;
	double time;
public:
	Graph(int cityNum);
	void generateGraph();
	void loadGraph(int i, int j, int value);
	void printGraph();
	void dynamicPrograming();
	void branchAndBound();
	void bruteForce();
	void printPath();
	void printHeuresticPath();
	void simulatedAnnealing(int time, double coolingValue);
	void tabuSearch(int time, int type);
};


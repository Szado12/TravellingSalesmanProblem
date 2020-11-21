#include <vector>

class Graph
{
private:
	std::vector<int> path;
	int distance;
	int** arrayGraph;
	int cityNum;
public:
	Graph(int cityNum);
	void generateGraph();
	void loadGraph();
	void printGraph();
	void dynamicPrograming();
	void branchAndBound();
	void bruteForce();
	void printPath();
};


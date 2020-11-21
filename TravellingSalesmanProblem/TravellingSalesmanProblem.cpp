#include <iostream>
#include "Graph.h"
int main()
{
    Graph* graph = new Graph(7);
    graph->generateGraph();
    graph->printGraph();
    graph->bruteForce();
    graph->printPath();
}
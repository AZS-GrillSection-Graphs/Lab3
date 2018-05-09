#include <iostream>
#include "SimpleGraph.h"
#include "RandomSimpleConsistentGraph.h"

int main() {
    srand(time(0));

    RandomSimpleConsistentGraph graph;
    graph.Print();
    graph.ConvertGraph();
    graph.DrawGraph();

    return 0;
}
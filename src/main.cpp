#include <iostream>
#include <RandomSimpleConsistentGraph.h>

int main() {
    RandomSimpleConsistentGraph randomGraph;

    randomGraph.Print();
    randomGraph.DijkstraWithPrint(0);
    randomGraph.PrintCostMatrix();

    return 0;
}
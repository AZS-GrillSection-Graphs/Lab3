#include <iostream>
#include <RandomSimpleConsistentGraph.h>

int main() {
    RandomSimpleConsistentGraph randomGraph;

    randomGraph.Print();
//    randomGraph.DijkstraWithPrint(1);
//    randomGraph.PrintCostMatrix();
//    std::cout << "The center of graph is: " << randomGraph.FindGraphCenter() << std::endl;
//    std::cout << "The minimax center of graph is: " << randomGraph.FindMinimaxGraphCenter() << std::endl;
    randomGraph.PrimWithPrint(0);

    return 0;
}
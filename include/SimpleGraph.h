#ifndef GRAPHS2_SIMPLEGRAPH_H
#define GRAPHS2_SIMPLEGRAPH_H

#include <string>
#include <stack>
#include "Graph.h"

class SimpleGraph : public Graph{
public:
    explicit SimpleGraph(std::string  numberSeries);
    static bool IsGraphicSeries(std::string stringToCheck);
    void DoesHamiltonCycleExist() const;

private:
    static std::vector<int> getNumbers(const std::string numberSeries);
    void ConvertFromNumberSeries(std::vector<int> &vertexLinks);
    void Hamilton_R(const int verticesNumber, int neighbourIndex, std::vector<bool> &visited, std::stack<int> &vertices) const;
    void PrintStack(std::stack <int> & stack) const;
};


#endif //GRAPHS2_SIMPLEGRAPH_H

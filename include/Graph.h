#ifndef GRAPHS2_GRAPH_H
#define GRAPHS2_GRAPH_H

#include <string>
#include "AdjacencyList.h"


class Graph
{
public:
    explicit Graph(const char * inputFileName);
    explicit Graph(GraphRepresentation * inputGraphReprezentation) : m_graphRepr(inputGraphReprezentation) {}
    explicit Graph() {};
    ~Graph();
    void Print() const;
    void ConvertGraph() const;
    void SaveToFile(const char *fileName) const;
    void RandomizeGraph();
    void RandomizeGraph(const int edgeStart, const int edgeEnd);
    int NumberOfComponents() const;
    Graph & BiggestComponent() const;
    void DrawGraph() const;

protected:
    GraphRepresentation * m_graphRepr;
};

#endif

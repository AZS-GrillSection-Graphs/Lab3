//
// Created by os8 on 10.05.18.
//

#ifndef GRAPHS3_NEWSTRUCTURE_ADJACENCYMATRIX_H
#define GRAPHS3_NEWSTRUCTURE_ADJACENCYMATRIX_H

#include <vector>

class AdjacencyMatrix {
public:
    AdjacencyMatrix(const int numberOfVerices, const int numberOfEdges);

    void Print() const;
    bool DoesEdgeExist(const int firstVertex, const int secondVertex) const;
    int GetNumberOfVertices() const {return m_matrix.size();}
    int GetIndexOfEdge(const int firstVertex, const int secondVertex) const;

    void MakeEdge(const int firstVertex, const int secondVertex);

private:
    std::vector<std::vector<int>> m_matrix;

    int FindNotConnectedEdge() const;

};


#endif //GRAPHS3_NEWSTRUCTURE_ADJACENCYMATRIX_H

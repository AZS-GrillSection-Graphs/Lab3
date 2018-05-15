#ifndef GRAPHS3_NEWSTRUCTURE_ADJACENCYMATRIX_H
#define GRAPHS3_NEWSTRUCTURE_ADJACENCYMATRIX_H

#include <vector>

class IncidenceMatrix {
public:
    IncidenceMatrix(const int numberOfVerices, const int numberOfEdges);

    void Print() const;
    void SaveToFile(const char *fileName) const;
    bool DoesEdgeExist(const int firstVertex, const int secondVertex) const;
    int GetNumberOfVertices() const {return m_matrix.size();}
    int GetIndexOfEdge(const int firstVertex, const int secondVertex) const;

    void RandomizeEdges();
    void MakeEdge(const int firstVertex, const int secondVertex);
    void ResetMatrix();

    std::vector<std::vector<int>> CopyOfMatrix() const { return m_matrix;}
    int* GetConnectedVerticesBy(const int edgeNumber) const;

private:
    std::vector<std::vector<int>> m_matrix;

    int FindNotConnectedEdge() const;
    int GetStartOfEdge(int firstEdge) const;
    int GetEndOfEdge(int firstEdge, int startOfFirstEdge) const;
};


#endif //GRAPHS3_NEWSTRUCTURE_ADJACENCYMATRIX_H

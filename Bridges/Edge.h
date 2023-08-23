#ifndef _EDGE_H_
#define _EDGE_H_
#include <iostream>
#include <string>
#include "myList.h"
class Edge
{
protected:
	std::string edgeType;
	LinkedList<Edge*>::Node* pNDEdgeMutual;
	bool marked;
	int outVertex;
public:

	//C'tor
	Edge(const int out) : outVertex(out), edgeType("none"), marked(false) {};
	
	//D'tor
	~Edge() { if (pNDEdgeMutual) { delete pNDEdgeMutual; pNDEdgeMutual = nullptr; } }
	//get and set edge type - for DFS
	void setEdgeType(std::string eType) { this->edgeType = eType; };
	std::string getEdgeType() const { return this->edgeType; };

	//get out vertex
	int getOutVertex() const { return this->outVertex; };

	//get and set edge mutual pointer
	void setEdgeMutualPointer(LinkedList<Edge*>::Node* pMutualEdge) { this->pNDEdgeMutual = pMutualEdge; };
	LinkedList<Edge*>::Node* getEdgeMutualPointer() { return this->pNDEdgeMutual; };

	//get and set edge mark - for knowing if we visit this edge by the mutual pointer
	void setEdgeMark(bool m) { this->marked = m; };
	bool getEdgeMark() { return this->marked; };

};
#endif
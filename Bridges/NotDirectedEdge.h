#ifndef _NOT_DIR_EDGE_H_
#define _NOT_DIR_EDGE_H_
#include <iostream>
#include <string>
#include "Edge.h"

class NotDirectedEdge : public Edge
{
	std::list< NotDirectedEdge>::iterator pNDEdgeMutual;
	bool marked;
public:
	
	//c'tor
	NotDirectedEdge(const int secV) : Edge(secV), marked(false) {};

	//get and set edge mutual pointer
	void setEdgeMutualPointer(std::list< NotDirectedEdge>::iterator pMutualEdge) { this->pNDEdgeMutual = pMutualEdge; };
	std::list< NotDirectedEdge>::iterator getEdgeMutualPointer() { return this->pNDEdgeMutual; };

	//get and set edge mark - for knowing if we visit this edge by the mutual pointer
	void setEdgeMark(bool m) { this->marked = m; };
	bool getEdgeMark() { return this->marked; };
};
#endif
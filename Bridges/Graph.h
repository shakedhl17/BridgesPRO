#ifndef _GRAPH_H
#define _GRAPH_H

#include <iostream>
#include <vector>
#include "Vertex.h"
#include "Edge.h"


class Graph
{
protected:
	int VNumber, Enumber;
	std::vector<int> parents;
	std::list<int> endVisit;
public:
	virtual void AddEdge(int v, int u) =0;
	virtual void DeleteEdge(int v, int u)=0;
	virtual std::list<int> getEndList() const = 0;

	const int getVNumber() { return this->VNumber; };
};
#endif

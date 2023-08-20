#ifndef _EDGE_H_
#define _EDGE_H_
#include <iostream>
#include <string>

class Edge
{
protected:
	std::string edgeType;
	int outVertex;
public:

	Edge(const int out) : outVertex(out), edgeType("none") {};

	//get and set edge type - for DFS
	void setEdgeType(std::string eType) { this->edgeType = eType; };
	std::string getEdgeType() const { return this->edgeType; };

	//get out vertex
	int getOutVertex() const { return this->outVertex; };
};
#endif
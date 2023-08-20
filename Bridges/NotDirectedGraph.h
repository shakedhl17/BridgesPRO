#ifndef _NOT_DIR_GRAPH_H
#define _NOT_DIR_GRAPH_H

#include <list>
#include "Graph.h"
#include "NotDirectedEdge.h"

class NotDirectedGraph : public Graph
{
	std::vector<Vertex> vertices;
	std::vector<std::list<NotDirectedEdge>> lstOfNeighborhods;
public:
	NotDirectedGraph* MakeGraph(const int n);
	bool AreNeighbors(int v, int u) const;
	void AddEdge(int v, int u);
	void DeleteEdge(int v, int u);
};
#endif

 

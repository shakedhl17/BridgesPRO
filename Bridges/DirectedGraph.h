#ifndef _DIR_GRAPH_H
#define _DIR_GRAPH_H

#include <list>
#include "Graph.h"

class DirectedGraph: public Graph
{
	std::vector<Vertex*> vertices;
	std::vector<std::list<Edge*>> edges;
public:

	//c'tor & d'tor
	DirectedGraph(const int n);
	~DirectedGraph();
	
	bool AreVPointsToU(int v, int u) const;
	void AddEdge(int v, int u);
	void DeleteEdge(int v, int u);

	void DFS();
	void DFSByMainLoop(vector<int> mainLoop);
	void Visit(int v, int currRoot);
	bool isParent(const int currV,const int suspectParent) const;

	std::vector<Vertex*>& getVertices();
	std::list<int> getEndList() const;
	const int getVNumber() { return this->VNumber; };
	void makeTransposeGraph(DirectedGraph& g);

};
#endif
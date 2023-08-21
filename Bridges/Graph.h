#ifndef _GRAPH_H
#define _GRAPH_H

#include <iostream>
#include "Vertex.h"
#include "Edge.h"
#include "myList.h"


class Graph
{
	int VNumber, Enumber;
	int* parents;
	LinkedList<int> endVisit;
	Vertex** vertices;
	LinkedList<Edge*>** lstOfNeighborhods;
	bool isDirected;

public:
	Graph(const int n,bool isDir);
	void AddEdge(int v, int u);
	void DeleteEdge(int v, int u);
	LinkedList<int> getEndList() const;
	const int getVNumber() { return this->VNumber; };

	bool AreNeighbors(int v, int u) const;
	void DFS();
	void VisitNotDirectedGraph(int v);
	void VisitDirectedGraph(int v, int currRoot);
	bool isParent(const int currV, const int suspectParent) const;
	Vertex** getVertices();


	void DFSByMainLoop(LinkedList<int> mainLoop);
	void makeTransposeGraph(Graph& g);
	void printBridges() const;
};

#endif

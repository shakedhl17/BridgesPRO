#include "DirectedGraph.h"
using namespace std;

//c'tor
DirectedGraph::DirectedGraph(const int n)
{
	this->VNumber = n;
	this->Enumber = 0;

	//set the vertices in the vertices vector
	for (int i = 0; i < this->VNumber; i++)
	{
		Vertex* tmpV = new Vertex(i);
		this->vertices.push_back(tmpV);
	}
	
	// preparing the neighbors vertices lists
	this->edges.resize(this->VNumber);
}

// return if v is a neighbor of u
bool DirectedGraph::AreVPointsToU(int v, int u) const
{
	if (!this->edges[v].empty())
	{
		list<Edge*>::const_iterator findIter = this->edges[v].begin();
		list<Edge*>::const_iterator endIter = this->edges[v].end();
		while (findIter != endIter)
		{
			if ((*findIter)->getOutVertex() == u)
				return true;
			++findIter;
		}
	}
	return false;
}

//add the given edge to the edges structor
void DirectedGraph::AddEdge(int v, int u)
{
	this->Enumber++;
	Edge* tmp = new Edge(u);
	this->edges[v].push_back(tmp);
}

//this function is deleting the given edge
void DirectedGraph::DeleteEdge(int v, int u)
{
	list<Edge*>::const_iterator findIter = this->edges[v].begin();
	while (findIter != this->edges[v].end())
	{
		if ((*findIter)->getOutVertex() == u)
		{
			this->edges[v].remove((*findIter));
			delete (*findIter);
			break;
		}
		++findIter;
	}
	this->Enumber--;
}

void DirectedGraph::DFS()
{
	vector<Vertex*>::iterator vItr = this->vertices.begin();
	vector<Vertex*>::iterator vItrEnd = this->vertices.end();
	while (vItr != vItrEnd)
	{
		(*vItr)->setVertexColor("white");
		++vItr;
	}

	vItr = this->vertices.begin();

	while (vItr != this->vertices.end())
	{
		if ((*vItr)->getVertexColor() == "white")
			this->Visit((*vItr)->getVertexNum(), (*vItr)->getVertexNum());
		++vItr;
	}

}

void DirectedGraph::DFSByMainLoop(vector<int> mainLoop)
{
	vector<Vertex*>::iterator vItr = this->vertices.begin();

	while (vItr != this->vertices.end())
	{
		(*vItr)->setVertexColor("white");
		++vItr;
	}

	vector<int>::const_iterator itr = mainLoop.begin();
	vector<int>::const_iterator itrEnd = mainLoop.end();
	while (itr != itrEnd)
	{
		if (this->vertices[(*itr)]->getVertexColor() == "white")
			this->Visit(this->vertices[(*itr)]->getVertexNum(), this->vertices[(*itr)]->getVertexNum());
		++itr;
	}
}

//This function is the visit function in the DFS algoritem
void DirectedGraph::Visit(int v, int currRoot)
{
	//set the v parent to currRoot
	this->parents[v] = currRoot;

	//set the currRoot to be v
	currRoot = v;

	//set the current vertex (v) to be type gray
	this->vertices[v]->setVertexColor("gray");

	//set the iterators of the v  neighbors list
	list<Edge*>::iterator vNeighborsItr = this->edges[v].begin();
	list<Edge*>::iterator vNeighborsItrEnd = this->edges[v].end();

	//run on the v neighbors list 
	while (vNeighborsItr != vNeighborsItrEnd)
	{
		//checks the curr v neighbor type and handle for each case
		if (this->vertices[(*vNeighborsItr)->getOutVertex()]->getVertexColor() == "white")
		{
			(*vNeighborsItr)->setEdgeType("treeArc");
			this->Visit((*vNeighborsItr)->getOutVertex(), currRoot);
		}
		else if (this->vertices[(*vNeighborsItr)->getOutVertex()]->getVertexColor() == "gray")
			(*vNeighborsItr)->setEdgeType("backArc");
		else if (isParent(v, (*vNeighborsItr)->getOutVertex()))
			(*vNeighborsItr)->setEdgeType("forwardArc");
		else
			(*vNeighborsItr)->setEdgeType("crossArc");

		++vNeighborsItr;
	}

	this->vertices[v]->setVertexColor("black");

	//add the v to the end vertices list
	this->endVisit.push_back(v);
}

//get the end vertices list 
std::list<int> DirectedGraph::getEndList() const
{
	return this->endVisit;
}

//checks if in the parents vector are currV is a descendant of suspectParent
bool DirectedGraph::isParent(const int currV, const int suspectParent) const
{
	if (this->parents[currV] == suspectParent)
		return true;
	else if (this->parents[currV] == currV)
		return false;
	return isParent(this->parents[currV], suspectParent);
}

//get the vertices vector 
vector<Vertex*>& DirectedGraph::getVertices() 
{
	return this->vertices;
}

//create this directed-graph a traspose graph of the directed graph given - g
void DirectedGraph::makeTransposeGraph(DirectedGraph& g)
{
	for (int i = 0; i < g.VNumber; i++)
	{
		list<Edge*>::const_iterator eItr = g.edges[i].begin();
		list<Edge*>::const_iterator eItrEnd = g.edges[i].end();
		while (eItr != eItrEnd)
		{
			this->AddEdge((*eItr)->getOutVertex(), i);
			++eItr;
		}
		
	}
}

//d'tor
DirectedGraph::~DirectedGraph()
{
	// Delete Vertex objects
	for (Vertex* vertexPtr : vertices) {
		delete vertexPtr;
	}

	// Delete Edge objects
	for (std::list<Edge*>& edgeList : edges) {
		for (Edge* edgePtr : edgeList) {
			delete edgePtr;
		}
	}
}
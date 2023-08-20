#include "DirectedGraph.h"
using namespace std;

DirectedGraph::DirectedGraph(const int n)
{
	this->VNumber = n;
	this->Enumber = 0;
	this->vertices.resize(this->VNumber);
	this->edges.resize(this->VNumber);
}

bool DirectedGraph::AreVPointsToU(int v, int u) const
{
	if (!this->edges[v].empty())
	{
		list<Edge*>::const_iterator findIter = this->edges[v].begin();
		while (findIter != this->edges[v].end())
		{
			if ((*findIter)->getOutVertex() == u)
				return true;
			++findIter;
		}
	}
	return false;
}

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
	while (vItr != this->vertices.end())
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

	while (itr != mainLoop.end())
	{
		if ((*itr) == "white")
			this->Visit((*vItr)->getVertexNum(), (*vItr)->getVertexNum());
		++vItr;
	}

}


void DirectedGraph::Visit(int v, int currRoot)
{
	this->parents[v] = currRoot;
	currRoot = v;
	this->vertices[v]->setVertexColor("gray");

	list<Edge*>::iterator vNeighborsItr = this->edges[v].begin();
	list<Edge*>::iterator vNeighborsItrEnd = this->edges[v].end();
	while (vNeighborsItr != vNeighborsItrEnd)
	{
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
	this->endVisit.push_back(v);
}

std::vector<int> DirectedGraph::getEndList() const
{
	return this->endVisit;
}


bool DirectedGraph::isParent(const int currV, const int suspectParent) const
{
	if (this->parents[currV] == suspectParent)
		return true;
	else if (this->parents[currV] == currV)
		return false;
	return isParent(this->parents[currV], suspectParent);
}

vector<Vertex*>& DirectedGraph::getVertices() 
{
	return this->vertices;
}

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
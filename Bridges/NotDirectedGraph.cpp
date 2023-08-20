#include "NotDirectedGraph.h"
#include <algorithm>
using namespace std;

NotDirectedGraph* NotDirectedGraph::MakeGraph(const int n)
{
	this->VNumber = n;
	this->Enumber = 0;

	//set the vertices in the vertices vector
	for (int i = 0; i < this->VNumber; i++)
	{
		Vertex* tmpV = new Vertex(i + 1);
		this->vertices.push_back(tmpV);
	}

	this->lstOfNeighborhods.resize(this->VNumber);
	return this;
}

bool NotDirectedGraph::AreNeighbors(int v, int u) const
{
	list<NotDirectedEdge*> vNeighbors = this->lstOfNeighborhods[v-1];
	list<NotDirectedEdge*>::iterator findIter = vNeighbors.begin();
	list<NotDirectedEdge*>::iterator endIter = vNeighbors.end();
	while (findIter != endIter)
		if ((*findIter)->getOutVertex() == u-1)
			return true;
	return false;
}

void NotDirectedGraph::AddEdge(int v, int u)
{
	if (!this->AreNeighbors(v, u))
	{
		// create the new edges for each vertices in the list of neighborhods
		NotDirectedEdge* newVEdge = new NotDirectedEdge(u-1);
		NotDirectedEdge* newUEdge = new NotDirectedEdge(v-1);

		//adding the edges to the list of neighborhods
		this->lstOfNeighborhods[v-1].push_back(newVEdge);
		this->lstOfNeighborhods[u-1].push_back(newUEdge);

		newVEdge->setEdgeMutualPointer(prev(this->lstOfNeighborhods[u-1].end()));
		newUEdge->setEdgeMutualPointer(prev(this->lstOfNeighborhods[v-1].end()));

		//incrieasing the edges number;
		this->Enumber++;
	}
}

void NotDirectedGraph::DeleteEdge(int v, int u)
{
	if (this->AreNeighbors(v, u))
	{
		//set a pointer to the mutual edge
		list<NotDirectedEdge*>::iterator pMutual;

		//set the v and u Neighbors lists
		list<NotDirectedEdge*> vNeighbors = this->lstOfNeighborhods[v-1];
		list<NotDirectedEdge*> uNeighbors = this->lstOfNeighborhods[u-1];

		//set the v Neighbors list itrator
		list<NotDirectedEdge*>::iterator findIter = vNeighbors.begin();
		list<NotDirectedEdge*>::iterator endIter = vNeighbors.end();

		//run on the v Neighbors list to remove the (v,u) edge
		while (findIter != endIter)
		{
			if ((*findIter)->getOutVertex() == u-1)
			{
				pMutual = (*findIter)->getEdgeMutualPointer();
				uNeighbors.erase(pMutual);
				vNeighbors.erase(findIter);
				delete (*pMutual);
				delete (*findIter);
			}
			++findIter;
		}
		//reduce the edges number;
		this->Enumber--;
	}
}

void NotDirectedGraph::DFS()
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
			this->Visit((*vItr)->getVertexNum() - 1, (*vItr)->getVertexNum() - 1);
		++vItr;
	}

}

//This function is the visit function in the DFS algoritem
void NotDirectedGraph::Visit(int v, int currRoot)
{
	//set the v parent to currRoot
	this->parents[v] = currRoot;

	//set the currRoot to be v
	currRoot = v;

	//set the current vertex (v) to be type gray
	this->vertices[v]->setVertexColor("gray");

	//set the iterators of the v  neighbors list
	list<NotDirectedEdge*>::iterator vNeighborsItr = this->lstOfNeighborhods[v].begin();
	list<NotDirectedEdge*>::iterator vNeighborsItrEnd = this->lstOfNeighborhods[v].end();
	list<NotDirectedEdge*>::iterator pMutual;

	//run on the v neighbors list 
	while (vNeighborsItr != vNeighborsItrEnd)
	{
		list<NotDirectedEdge*> uNeighbors = this->lstOfNeighborhods[(*vNeighborsItr)->getOutVertex()];
		pMutual = (*vNeighborsItr)->getEdgeMutualPointer();
		uNeighbors.erase(pMutual);
		delete (*pMutual);

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

//checks if in the parents vector are currV is a descendant of suspectParent
bool NotDirectedGraph::isParent(const int currV, const int suspectParent) const
{
	if (this->parents[currV] == suspectParent)
		return true;
	else if (this->parents[currV] == currV)
		return false;
	return isParent(this->parents[currV], suspectParent);
}



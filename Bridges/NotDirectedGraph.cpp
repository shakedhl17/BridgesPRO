#include "NotDirectedGraph.h"
#include <algorithm>
using namespace std;

NotDirectedGraph* NotDirectedGraph::MakeGraph(const int n)
{
	this->VNumber = n;
	//this->vertices.resize(this->VNumber);
	this->lstOfNeighborhods.resize(this->VNumber);
	return this;
}

bool NotDirectedGraph::AreNeighbors(int v, int u) const
{
	list<NotDirectedEdge> vNeighbors = this->lstOfNeighborhods[v];
	list<NotDirectedEdge>::iterator findIter = vNeighbors.begin();
	while (findIter != vNeighbors.end())
		if ((*findIter).getOutVertex() == u)
			return true;
	return false;
}

void NotDirectedGraph::AddEdge(int v, int u)
{
	if (!this->AreNeighbors(v, u))
	{
		// create the new edges for each vertices in the list of neighborhods
		NotDirectedEdge* newVEdge = new NotDirectedEdge(u);
		NotDirectedEdge* newUEdge = new NotDirectedEdge(v);

		//adding the edges to the list of neighborhods
		this->lstOfNeighborhods[v].push_back(*newVEdge);
		this->lstOfNeighborhods[u].push_back(*newUEdge);

		newVEdge->setEdgeMutualPointer(prev(this->lstOfNeighborhods[u].end()));
		newUEdge->setEdgeMutualPointer(prev(this->lstOfNeighborhods[v].end()));

		//incrieasing the edges number;
		this->Enumber++;
	}
}

void NotDirectedGraph::DeleteEdge(int v, int u)
{
	if (this->AreNeighbors(v, u))
	{
		//set a flag that the edge found
		bool found = false;

		//set a pointer to the mutual edge
		list<NotDirectedEdge>::iterator pMutual;

		//set the v and u Neighbors lists
		list<NotDirectedEdge> vNeighbors = this->lstOfNeighborhods[v];
		list<NotDirectedEdge> uNeighbors = this->lstOfNeighborhods[u];

		//set the v Neighbors list itrator
		list<NotDirectedEdge>::iterator findIter = vNeighbors.begin();

		//run on the v Neighbors list to remove the (v,u) edge
		while (!found && findIter != vNeighbors.end())
		{
			if ((*findIter).getOutVertex() == u)
			{
				pMutual = (*findIter).getEdgeMutualPointer();
				uNeighbors.erase(pMutual);
				vNeighbors.erase(findIter);
				found = true;
			}
			++findIter;
		}
		//reduce the edges number;
		this->Enumber--;
	}
}
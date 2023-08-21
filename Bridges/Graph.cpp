#include "Graph.h"
using namespace std;

Graph::Graph(const int n, bool isDir)
{
	this->isDirected = isDir;
	this->VNumber = n;
	this->vertices = new Vertex * [this->VNumber];
	this->parents = new int [this->VNumber];
	this->Enumber = 0;

	//set the vertices in the vertices vector
	for (int i = 0; i < this->VNumber; i++)
	{
		Vertex* tmpV = new Vertex(i + 1);
		this->vertices[i] = tmpV;
	}

	for (int i = 0; i < this->VNumber; i++)
	{
		LinkedList<Edge*>* tmpV = new LinkedList<Edge*>();
		this->lstOfNeighborhods[i] = tmpV;
	}
}

bool Graph::AreNeighbors(int v, int u) const
{
	LinkedList<Edge*>::Node* currNode = this->lstOfNeighborhods[v - 1]->getHead();
	while (currNode->next != nullptr)
	{
		if (currNode->data->getOutVertex() == u - 1)
			return true;
		currNode = currNode->next;
	}
	return false;
}

void Graph::AddEdge(int v, int u)
{
	if (!this->AreNeighbors(v, u))
	{
		v--;
		u--;
		//incrieasing the edges number;
		this->Enumber++;

		if (this->isDirected)
		{
			this->Enumber++;
			Edge* tmp = new Edge(u);
			this->lstOfNeighborhods[v]->pushFront(tmp);
		}
		else
		{
			// create the new edges for each vertices in the list of neighborhods
			Edge* newVEdge = new Edge(u);
			Edge* newUEdge = new Edge(v);

			//adding the edges to the list of neighborhods
			this->lstOfNeighborhods[v]->pushFront(newVEdge);
			this->lstOfNeighborhods[u]->pushFront(newUEdge);

			newVEdge->setEdgeMutualPointer(this->lstOfNeighborhods[u]->getHead());
			newUEdge->setEdgeMutualPointer(this->lstOfNeighborhods[u]->getHead());

		}
	}
}

void Graph::DeleteEdge(int v, int u)
{
	if (this->AreNeighbors(v, u))
	{
		//reduce the edges number
		this->Enumber--;
		LinkedList<Edge*>::Node* currNode = this->lstOfNeighborhods[v - 1]->getHead();
		while (currNode->next != nullptr)
		{
			if (currNode->data->getOutVertex() == u - 1)
			{
				if (!this->isDirected)
					this->lstOfNeighborhods[u - 1]->remove(currNode->data->getEdgeMutualPointer());
				this->lstOfNeighborhods[v - 1]->remove(currNode);
				break;
			}
			currNode = currNode->next;
		}

	}
}

void Graph::DFS()
{
	for (int i = 0; i < this->VNumber; i++)
		this->vertices[i]->setVertexColor("white");

	for (int i = 0; i < this->VNumber; i++)
		if (this->vertices[i]->getVertexColor() == "white")
			this->VisitDirectedGraph(i,i);
	if(!this->isDirected)
		this->isDirected = true;
}

void Graph::DFSByMainLoop(LinkedList<int> mainLoop)
{
	for (int i = 0; i < this->VNumber; i++)
		this->vertices[i]->setVertexColor("white");
	
	LinkedList<int>::Node* currNode = mainLoop.getHead();
	while(currNode->next!= nullptr)
		if (this->vertices[currNode->data]->getVertexColor() == "white")
			this->VisitDirectedGraph(currNode->data, currNode->data);

	if (!this->isDirected)
		this->isDirected = true;
}

//This function is the visit function in the DFS algoritem
void Graph::VisitNotDirectedGraph(int v)
{
	//set the current vertex (v) to be type gray
	this->vertices[v]->setVertexColor("gray");
	LinkedList<Edge*>::Node* currNode = this->lstOfNeighborhods[v - 1]->getHead();
	while (currNode->next != nullptr)
	{
		if (currNode->data->getEdgeMark() == false)
		{
			currNode->data->getEdgeMutualPointer()->data->setEdgeMark(true);

			//checks the curr v neighbor type and handle for each case
			if (this->vertices[currNode->data->getOutVertex()]->getVertexColor() == "white")
			{
				currNode->data->setEdgeType("treeArc");
				this->VisitNotDirectedGraph(currNode->data->getOutVertex());
			}
			else if (this->vertices[currNode->data->getOutVertex()]->getVertexColor() == "gray")
				currNode->data->setEdgeType("backArc");
		}
		currNode = currNode->next;
	}
	
	this->vertices[v]->setVertexColor("black");

	//add the v to the end vertices list
	this->endVisit.pushFront(v);
}

//This function is the visit function in the DFS algoritem
void Graph::VisitDirectedGraph(int v, int currRoot)
{
	//set the v parent to currRoot
	this->parents[v] = currRoot;

	//set the currRoot to be v
	currRoot = v;

	//set the current vertex (v) to be type gray
	this->vertices[v]->setVertexColor("gray");
	LinkedList<Edge*>::Node* currNode = this->lstOfNeighborhods[v - 1]->getHead();
	while (currNode->next != nullptr)
	{
		if (!this->isDirected)
		{
			this->lstOfNeighborhods[currNode->data->getOutVertex()]->remove(currNode->data->getEdgeMutualPointer());
		}
		//checks the curr v neighbor type and handle for each case
		if (this->vertices[currNode->data->getOutVertex()]->getVertexColor() == "white")
		{
			currNode->data->setEdgeType("treeArc");
			this->VisitDirectedGraph(currNode->data->getOutVertex(), currRoot);
		}
		else if (this->vertices[currNode->data->getOutVertex()]->getVertexColor() == "gray")
			currNode->data->setEdgeType("backArc");
		else if (isParent(v, currNode->data->getOutVertex()))
			currNode->data->setEdgeType("forwardArc");
		else
			currNode->data->setEdgeType("crossArc");

		currNode = currNode->next;
	}

	this->vertices[v]->setVertexColor("black");

	//add the v to the end vertices list
	this->endVisit.pushFront(v);
}

//checks if in the parents vector are currV is a descendant of suspectParent
bool Graph::isParent(const int currV, const int suspectParent) const
{
	if (this->parents[currV] == suspectParent)
		return true;
	else if (this->parents[currV] == currV)
		return false;
	return isParent(this->parents[currV], suspectParent);
}

LinkedList<int> Graph::getEndList() const
{
	return this->endVisit;
}

//get the vertices vector 
Vertex** Graph::getVertices()
{
	return this->vertices;
}

//create this directed-graph a traspose graph of the directed graph given - g
void Graph::makeTransposeGraph(Graph& g)
{
	for (int i = 0; i < g.VNumber; i++)
	{
		LinkedList<Edge*>::Node* currNode = this->lstOfNeighborhods[i]->getHead();
		while (currNode->next!=nullptr)
		{
			this->AddEdge(currNode->data->getOutVertex(), i);
			currNode = currNode->next;
		}

	}
}


void Graph::printBridges() const
{
	for (int i = 0; i < this->VNumber; i++)
	{
		LinkedList<Edge*>::Node* currNode = this->lstOfNeighborhods[i]->getHead();
		while (currNode->next != nullptr)
		{
			if (currNode->data->getEdgeType() == "crossArc")
				cout << i + 1 << currNode->data->getOutVertex() + 1;
			currNode = currNode->next;
		} 
	}
};

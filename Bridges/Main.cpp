#include "Utils.h"
using namespace std;

int main()
{
	int n = getVerticesNum();
	DirectedGraph g(n);
	int m = getEdgesNum();
	for (int i = 0; i < m; i++)
		getEdges(g);
	if (isGraphStronglyConnected(g))
		printBridgesInDirGraph(g);
}

int getVerticesNum()
{
	int vNum;
	cin >> vNum;
	return vNum;
}

int getEdgesNum()
{
	int eNum;
	cin >> eNum;
	return eNum;
}

void getEdges(DirectedGraph& G)
{
	int inVNum, outVNum;
	cin >> inVNum;
	cin >> outVNum;
	G.AddEdge(inVNum, outVNum);
}

bool isGraphConnected(NotDirectedGraph& G)
{
	return true;
}

bool isGraphStronglyConnected(DirectedGraph& G)
{
	G.Visit(0, 0);
	std::vector<Vertex*> gVertices = G.getVertices();
	std::vector<Vertex*>::iterator gVItr = gVertices.begin();
	while (gVItr != gVertices.end())
	{
		if ((*gVItr)->getVertexColor() == "white")
			return false;
		++gVItr;
	}
	return true;
}

void printBridgesInDirGraph(DirectedGraph& G)
{
	G.DFS();
	list<int> endList = G.getEndList();
	DirectedGraph* GT = createGt(G);
	GT->DFSByMainLoop(endList);
	GT->printBridges();
	delete GT;
}

DirectedGraph* createGt(DirectedGraph& G)
{
	int vNum = G.getVNumber();
	DirectedGraph* Gt= new DirectedGraph(vNum);
	Gt->makeTransposeGraph(G);
	return Gt; 
}
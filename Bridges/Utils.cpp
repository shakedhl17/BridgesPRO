#include "Utils.h"
using namespace std;

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

void getEdges(Graph& G)
{
	int inVNum, outVNum;
	cin >> inVNum;
	cin >> outVNum;
	G.AddEdge(inVNum, outVNum);
}

bool isGraphConnected(Graph& G)
{
	G.VisitNotDirectedGraph(0);
	Vertex** gVertices = G.getVertices();
	int vNum = G.getVNumber();
	for (int i = 0; i < vNum; i++)
	{
		if (gVertices[i]->getVertexColor() == "white")
			return false;
	}
	return true;
}

void printBridges(Graph& G)
{
	//we will do a dfs that make g a directed graph
	G.DFS();
	LinkedList<int> endList = G.getEndList();
	Graph* GT = createGt(G);
	GT->DFSByMainLoop(endList);
	GT->printBridges();
}

Graph* createGt(Graph& G)
{
	int vNum = G.getVNumber();
	Graph* Gt = new Graph(vNum, true);
	Gt->makeTransposeGraph(G);
	return Gt;
}
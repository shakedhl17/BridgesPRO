#include "Utils.h"
using namespace std;

int main()
{

}

int getVerticesNum()
{
	int vNum;
	cout << "Type in the vertices number: ";
	cin >> vNum;
	return vNum;
}

int getEdgesNum()
{
	int eNum;
	cout << "Type in the edges number: ";
	cin >> eNum;
	return eNum;
}

void getEdges(DirectedGraph& G)
{
	int inVNum, outVNum;
	cout << "Type in the edge in vertex number: ";
	cin >> inVNum;
	cout << "Type in the edge out vertex number: ";
	cin >> outVNum;
	G.AddEdge(inVNum, outVNum);
}

bool isGraphConnected(NotDirectedGraph& G)
{
	return true;
}

bool isGraphStronglyConnected(DirectedGraph& G)
{
	G.DFS(0);
	std::vector<Vertex*> gVertices = G.getVertices();
	std::vector<Vertex*>::iterator gVItr = gVertices.begin();
	while (gVItr != gVertices.end())
	{
		if ((*gVItr)->getVertexColor() == "white")
			return false;
	}
	return true;
}

void printBridgesInDirGraph(DirectedGraph& G)
{
	G.DFS(0);
	vector<int> endList = G.getEndList();

}

DirectedGraph& createGt(vector<int> endlist, DirectedGraph& G)
{
	int vNum = G.getVNumber();
	DirectedGraph Gt(vNum);
	Gt.makeTransposeGraph(G);

}
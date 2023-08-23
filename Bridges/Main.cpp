#include "Utils.h"
using namespace std;

int main()
{
	int n = getVerticesNum();
	Graph g(n,false);
	int m = getEdgesNum();

	for (int i = 0; i < m; i++)
		getEdges(g);
	if (isGraphConnected(g))
		printBridges(g);
	else
		cout << "Graph is not connected";

}

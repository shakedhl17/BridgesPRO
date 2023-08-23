#pragma once
#include <iostream>
#include <stdlib.h>
#include "Graph.h"
#include "myList.h"

int getVerticesNum(); // get the number of vercies from the user
int getEdgesNum(); // get the number of edges from the user
void getEdges(Graph& G); // get the edges from the user
bool isGraphConnected(Graph& G); //check if the un-directed graph is connectd
Graph* createGt(Graph& G); // create a traspose fraph of g
void printBridges(Graph& G); //prints the bridges in the directed graph

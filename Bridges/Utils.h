#pragma once
#include <iostream>
#include <stdlib.h>
#include "DirectedGraph.h"
#include "NotDirectedGraph.h"

int getVerticesNum(); // get the number of vercies from the user
int getEdgesNum(); // get the number of edges from the user
void getEdges(DirectedGraph& G); // get the edges from the user
bool isGraphConnected(NotDirectedGraph& G); //check if the un-directed graph is connectd
bool isGraphStronglyConnected(DirectedGraph& G); //check if the directed graph is connectd
void printBridgesInDirGraph(DirectedGraph& G); //prints the bridges in the directed graph
DirectedGraph* createGt(DirectedGraph& G);

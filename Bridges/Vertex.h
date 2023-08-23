#ifndef _VERTEX_H
#define _VERTEX_H

#include <iostream>
#include <string>

class Vertex
{
	int vNum;
	std::string vColor;

public:
	//C'tor
	Vertex(int v) : vNum(v), vColor("white") {};
	
	//Setting the vertex color
	void setVertexColor(std::string color) { this->vColor = color; };

	//Getting the vertex color
	std::string getVertexColor() const { return this->vColor; };

	//Getting the vertex number
	int getVertexNum() const { return this->vNum; };
};
#endif
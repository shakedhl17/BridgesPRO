#ifndef _VERTEX_H
#define _VERTEX_H

#include <iostream>
#include <string>

class Vertex
{
	int vNum;
	std::string vColor;

public:
	Vertex(int v) : vNum(v), vColor("white") {};
	void setVertexColor(std::string color) { this->vColor = color; };
	std::string getVertexColor() const { return this->vColor; };
	int getVertexNum() const { return this->vNum; };
};
#endif
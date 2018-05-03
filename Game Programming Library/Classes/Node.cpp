#include "Node.h"

using namespace GPL;

void Node::SetX(const int x)
{
	this->x = x;
}

int Node::GetX() const
{
	return this->x;
}

void Node::SetY(const int y)
{
	this->y = y;
}

int Node::GetY() const
{
	return this->y;
}

void Node::SetG(const int g)
{
	this->g = g;
}

int Node::GetG() const
{
	return this->g;
}

void Node::SetH(const int h)
{
	this->h = h;
}

int Node::GetH() const
{
	return this->h;
}

int Node::GetF() const
{
	return (this->g + this->h);
}

void Node::SetWalkable(const bool walkable)
{
	this->walkable = walkable;
}

bool Node::GetWalkable() const
{
	return this->walkable;
}

void Node::SetNodeParent(const Node& node_parent)
{
	this->node_parent = &node_parent;
}

const Node& Node::GetNodeParent() const
{
	return *this->node_parent;
}
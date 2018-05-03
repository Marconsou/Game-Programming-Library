#ifndef NODE_H
#define NODE_H

#include "BuildDLL.h"

namespace GPL
{
	class Node
	{
	public:
		GPL_DLL void SetX(const int x);
		GPL_DLL int GetX() const;
		GPL_DLL void SetY(const int y);
		GPL_DLL int GetY() const;
		GPL_DLL void SetG(const int g);
		GPL_DLL int GetG() const;
		GPL_DLL void SetH(const int h);
		GPL_DLL int GetH() const;
		GPL_DLL int GetF() const;
		GPL_DLL void SetWalkable(const bool walkable);
		GPL_DLL bool GetWalkable() const;
		GPL_DLL void SetNodeParent(const Node& node_parent);
		GPL_DLL const Node& GetNodeParent() const;
	private:
		int x{};
		int y{};
		int g{};
		int h{};
		bool walkable{};
		const Node* node_parent{};
		Node& operator=(const Node&) = delete;
	};
}

#endif
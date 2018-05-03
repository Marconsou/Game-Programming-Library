#ifndef PATHFIND_H
#define PATHFIND_H

#include <algorithm>
#include <vector>
#include "Node.h"
#include "Rect.h"

namespace GPL
{
	enum class Movement
	{
		None,
		Left,
		Right,
		Up,
		Down,
		Done,
	};

	class Pathfind
	{
	public:
		GPL_DLL Pathfind() = default;
		GPL_DLL void SetCameraIndex(const int index_x,const int index_y,const int index_w,const int index_h);
		GPL_DLL void SetNodeInitial(const int index_x,const int index_y);
		GPL_DLL const Node& GetNodeInitial() const;
		GPL_DLL void SetNodeFinal(const int index_x,const int index_y);
		GPL_DLL const Node& GetNodeFinal() const;
		GPL_DLL const Node& GetNode(const int index_x,const int index_y) const;
		GPL_DLL const Node& GetCurrentNodeMovement() const;
		GPL_DLL bool SetNodeWalkable(const int index_x,const int index_y,const bool walkable);
		GPL_DLL int GetNodeTotalX() const;
		GPL_DLL int GetNodeTotalY() const;
		GPL_DLL Movement GetHorizontalMovement() const;
		GPL_DLL Movement GetVerticalMovement() const;
		GPL_DLL const std::vector<const Node*>& GetPath() const;
		GPL_DLL void CreateGridNodeMap(const int node_total_x,const int node_total_y,const int node_distance);
		GPL_DLL bool FindPath(const bool ignore_node_final_check = false);
		GPL_DLL void MovementNodeByNode(const int current_object_x,const int current_object_y,const int movement_speed);
		GPL_DLL void Clear();
	private:
		int node_distance{};
		int current_node_movement_index{-1};
		const int orthogonal_cost{10};
		const int diagonal_cost{static_cast<int>(orthogonal_cost * 1.4f)};
		Movement horizontal_movement{};
		Movement vertical_movement{};
		Rect<int> camera_index;
		const Node* node_initial{};
		const Node* node_final{};
		const Node* last_node_final{};
		std::vector<const Node*> open_list;
		std::vector<const Node*> closed_list;
		std::vector<const Node*> path;
		std::vector<std::vector<Node>> node_map;
		Pathfind(const Pathfind&) = delete;
		Pathfind& operator=(const Pathfind&) = delete;
		void ReconstructPath();
		bool ValidateIndex(const int index_x,const int index_y) const;
		int DistanceBetweenPositions(const int position_a,const int position_b) const;
		int DistanceBetweenNodes(const Node& node_a,const Node& node_b) const;
		int CalculateH(const Node& node) const;
		bool OpenListContainsNode(const Node& node) const;
		bool ClosedListContainsNode(const Node& node) const;
		const Node& SearchForNodeLowestH() const;
		bool CheckForDiagonalRestrictions(const Node& current_node,const Node& neighbor_node) const;
	};
}

#endif
#include "Pathfind.h"

using namespace std;
using namespace GPL;

void Pathfind::SetCameraIndex(const int index_x,const int index_y,const int index_w,const int index_h)
{
	this->camera_index.SetPosition(index_x,index_y);
	this->camera_index.SetSize(index_w,index_h);
}

void Pathfind::SetNodeInitial(const int index_x,const int index_y)
{
	this->node_initial = &this->node_map[index_x][index_y];
}

const Node& Pathfind::GetNodeInitial() const
{
	return *this->node_initial;
}

void Pathfind::SetNodeFinal(const int index_x,const int index_y)
{
	//Verificar antes se Node Final vai ser modificado (Performance pode cair ao resetar o valor)
	if (this->node_final != &this->node_map[index_x][index_y])
		this->last_node_final = nullptr;
	this->node_final = &this->node_map[index_x][index_y];
}

const Node& Pathfind::GetNodeFinal() const
{
	return *this->node_final;
}

const Node& Pathfind::GetNode(const int index_x,const int index_y) const
{
	return this->node_map[index_x][index_y];
}

const Node& Pathfind::GetCurrentNodeMovement() const
{
	//Se tiver no meio da movimentação
	if (this->current_node_movement_index >= 0)
		return *this->path[this->current_node_movement_index];

	//Caso contrário retornar o Node inicial que é onde se encontra o objeto móvel
	return *this->node_initial;
}

bool Pathfind::SetNodeWalkable(const int index_x,const int index_y,const bool walkable)
{
	Node& node = this->node_map[index_x][index_y];

	node.SetWalkable(walkable);

	//Caso o Node estiver no caminho já calculado, deverá recalcular um outro caminho
	if (!walkable)
	{
		for (size_t i = 0; i < this->path.size(); i++)
		{
			if (this->path[i] == &node)
				return this->FindPath(true);
		}
	}
	return false;
}

int Pathfind::GetNodeTotalX() const
{
	return this->node_map.size();
}

int Pathfind::GetNodeTotalY() const
{
	return this->node_map[0].size();
}

Movement Pathfind::GetHorizontalMovement() const
{
	return this->horizontal_movement;
}

Movement Pathfind::GetVerticalMovement() const
{
	return this->vertical_movement;
}

const vector<const Node*>& Pathfind::GetPath() const
{
	return this->path;
}

void Pathfind::CreateGridNodeMap(const int node_total_x,const int node_total_y,const int node_distance)
{
	//Distância entre os Nodes
	this->node_distance = node_distance;

	//Criando o mapa de Nodes
	this->node_map.resize(node_total_x,vector<Node>(node_total_y));

	//Os Nodes são centralizados
	const int center_position = node_distance / 2;

	for (int y = 0; y < node_total_y; y++)
	{
		for (int x = 0; x < node_total_x; x++)
		{
			Node& iterator = this->node_map[x][y];

			iterator.SetX(center_position + (x * node_distance));
			iterator.SetY(center_position + (y * node_distance));
			iterator.SetWalkable(true);
		}
	}

	//Inicialização dos principais Nodes
	const int last_index_x = node_total_x - 1;
	const int last_index_y = node_total_y - 1;
	this->SetNodeInitial(0,0);
	this->SetNodeFinal(last_index_x,last_index_y);
	this->SetCameraIndex(0,0,last_index_x,last_index_y);
}

bool Pathfind::FindPath(const bool ignore_node_final_check)
{
	//http://www.policyalmanac.org/games/aStarTutorial.htm
	//http://en.wikipedia.org/wiki/A*_search_algorithm
	//Algoritmo implementado daqui com algumas adições:
	//1 >> Restrições nas diagonais com base na situação.
	//2 >> Caso o Node final não for passável, colocar o Node final como o Node mais próximo (do final->inicial) passável, com base no menor Node H
	//3 >> Adicionar o conceito de câmera, para que seja executado o algoritmo em parte do mapa.
	//4 >> Além de encontrar o caminho mais curto, fazer o movimento do início até o fim.
	//5 >> Quando for alterar para um Node não passável, se já tiver um caminho já calculado, encontrar um novo caminho.

	//Se for o mesmo Node final ou simplesmente ignorar isto
	const bool same_last_node_final = (this->last_node_final == this->node_final) || ((!this->path.empty()) && (this->last_node_final == this->path.back()));
	if ((!same_last_node_final) || (ignore_node_final_check))
	{
		//Se o Node inicial já não for o próprio Node final
		if (this->node_initial != this->node_final)
		{
			//Limpar as listas
			this->open_list.clear();
			this->closed_list.clear();

			//Atualizar o valor inicial do Node inicial
			const int node_initial_index_x = this->node_initial->GetX() / this->node_distance;
			const int node_initial_index_y = this->node_initial->GetY() / this->node_distance;
			this->node_map[node_initial_index_x][node_initial_index_y].SetG(0);
			this->node_map[node_initial_index_x][node_initial_index_y].SetH(this->CalculateH(*this->node_initial));

			//Adicionar o Node inicial
			this->open_list.push_back(this->node_initial);

			//Enquanto tiver Nodes na Open List
			while (!this->open_list.empty())
			{
				//Open List já ordenada pegando o Node pelo menor custo F
				const Node& current_node = *this->open_list.back();

				//Se já achou o Node final
				if (&current_node == this->node_final)
				{
					//Reconstruir o caminho do início até o final
					this->ReconstructPath();
					return true;
				}

				//Passando o Node da Open List para Closed List
				this->closed_list.push_back(&current_node);
				this->open_list.pop_back();

				//Índices do Node atual que está sendo verificado
				const int current_index_x = current_node.GetX() / this->node_distance;
				const int current_index_y = current_node.GetY() / this->node_distance;

				//Verificar os Nodes vizinhos do Node atual
				for (int y = current_index_y - 1; y <= current_index_y + 1; y++)
				{
					for (int x = current_index_x - 1; x <= current_index_x + 1; x++)
					{
						//Se não for ele mesmo
						const bool is_not_itself = (x != current_index_x) || (y != current_index_y);

						//Se for um Node válido e não for ele mesmo
						if ((this->ValidateIndex(x,y)) && (is_not_itself))
						{
							//Node vizinho
							Node& neighbor_node = this->node_map[x][y];

							//Se o Node for passável, não tiver passagem de diagonais entre algum vizinho não passável e não já estar na Closed List
							if ((neighbor_node.GetWalkable()) && (CheckForDiagonalRestrictions(current_node,neighbor_node)) && (!this->ClosedListContainsNode(neighbor_node)))
							{
								//Distância do início até o Node vizinho através do Node atual
								const int tentative_g = current_node.GetG() + this->DistanceBetweenNodes(current_node,neighbor_node);

								//Node vizinho não está na Open List
								const bool neighbor_node_is_not_in_open_list = !this->OpenListContainsNode(neighbor_node);

								//Se não estiver na Open List ou o valor de tentativa de G é melhor (menor) passando pelo Node atual, do que o valor G pré-calculado do próprio Node vizinho
								if ((neighbor_node_is_not_in_open_list) || (tentative_g <= neighbor_node.GetG()))
								{
									//Atualizar os valores do Node vizinho, para quando ele for o Node atual, já estar com seus valores atualizados
									neighbor_node.SetNodeParent(current_node);
									neighbor_node.SetG(tentative_g);
									neighbor_node.SetH(this->CalculateH(neighbor_node));

									//Adicionar o Node vizinho na Open List e ordená-la por F
									if (neighbor_node_is_not_in_open_list)
									{
										static const auto sort_f_cost = [](const Node* node_a,const Node* node_b) -> bool { return (node_a->GetF() > node_b->GetF()); };
										this->open_list.push_back(&neighbor_node);
										sort(this->open_list.begin(),this->open_list.end(),sort_f_cost);
									}
								}
							}
						}
					}
				}
			}

			//Não encontrou o caminho, encontrar o mais próximo possível
			this->last_node_final = this->node_final;

			//Node com menor custo H por causa do atual Node final ser ilhado ou não passável
			this->node_final = &this->SearchForNodeLowestH();
			this->ReconstructPath();
			return true;
		}
	}

	//Não foi processado nada
	return false;
}

void Pathfind::ReconstructPath()
{
	//Começando pelo Node final
	const Node* current_node = this->node_final;

	//Limpar dados
	this->Clear();

	//Até chegar no Node inicial
	while (current_node != this->node_initial)
	{
		this->path.push_back(current_node);
		current_node = &current_node->GetNodeParent();
	}

	if (!this->path.empty())
	{
		//Revertendo para inicial->final
		reverse(this->path.begin(),this->path.end());
		this->current_node_movement_index = 0;
		this->node_initial = this->path[this->current_node_movement_index];
	}
}

bool Pathfind::ValidateIndex(const int index_x,const int index_y) const
{
	return ((index_x >= this->camera_index.GetPosition().GetX()) && (index_x <= this->camera_index.GetSize().GetX())) &&
		((index_y >= this->camera_index.GetPosition().GetY()) && (index_y <= this->camera_index.GetSize().GetY()));
}

int Pathfind::DistanceBetweenPositions(const int position_a,const int position_b) const
{
	return abs(position_a - position_b);
}

int Pathfind::DistanceBetweenNodes(const Node& node_a,const Node& node_b) const
{
	//http://www.policyalmanac.org/games/heuristics.htm
	const int distance_x = this->DistanceBetweenPositions(node_a.GetX(),node_b.GetX());
	const int distance_y = this->DistanceBetweenPositions(node_a.GetY(),node_b.GetY());

	if (distance_x > distance_y)
		return (this->diagonal_cost * distance_y) + (this->orthogonal_cost * (distance_x - distance_y));
	else
		return (this->diagonal_cost * distance_x) + (this->orthogonal_cost * (distance_y - distance_x));
}

int Pathfind::CalculateH(const Node& node) const
{
	//Cálculo da heurística deve ser ortogonal
	const int distance_x = this->DistanceBetweenPositions(node.GetX(),this->node_final->GetX());
	const int distance_y = this->DistanceBetweenPositions(node.GetY(),this->node_final->GetY());

	return (this->orthogonal_cost * (distance_x + distance_y));
}

bool Pathfind::OpenListContainsNode(const Node& node) const
{
	for (vector<const Node*>::const_iterator iterator = this->open_list.begin(); iterator != this->open_list.end(); iterator++)
	{
		if ((*iterator) == &node)
			return true;
	}
	return false;
}

bool Pathfind::ClosedListContainsNode(const Node& node) const
{
	for (vector<const Node*>::const_iterator iterator = this->closed_list.begin(); iterator != this->closed_list.end(); iterator++)
	{
		if ((*iterator) == &node)
			return true;
	}
	return false;
}

const Node& Pathfind::SearchForNodeLowestH() const
{
	const Node* node = this->closed_list.back();
	for (vector<const Node*>::const_iterator iterator = this->closed_list.begin(); iterator != this->closed_list.end(); iterator++)
	{
		if ((*iterator)->GetH() < node->GetH())
			node = (*iterator);
	}
	return *node;
}

bool Pathfind::CheckForDiagonalRestrictions(const Node& current_node,const Node& neighbor_node) const
{
	const int current_index_x = current_node.GetX() / this->node_distance;
	const int current_index_y = current_node.GetY() / this->node_distance;

	const int relative_index_x = (neighbor_node.GetX() - current_node.GetX()) / this->node_distance;
	const int relative_index_y = (neighbor_node.GetY() - current_node.GetY()) / this->node_distance;

	const bool left_top = (relative_index_x == -1) && (relative_index_y == -1);
	const bool right_top = (relative_index_x == 1) && (relative_index_y == -1);
	const bool left_bottom = (relative_index_x == -1) && (relative_index_y == 1);
	const bool right_bottom = (relative_index_x == 1) && (relative_index_y == 1);

	const Node* node_left = ((this->ValidateIndex(current_index_x - 1,current_index_y)) ? (&this->node_map[current_index_x - 1][current_index_y]) : (nullptr));
	const Node* node_right = ((this->ValidateIndex(current_index_x + 1,current_index_y)) ? (&this->node_map[current_index_x + 1][current_index_y]) : (nullptr));
	const Node* node_top = ((this->ValidateIndex(current_index_x,current_index_y - 1)) ? (&this->node_map[current_index_x][current_index_y - 1]) : (nullptr));
	const Node* node_bottom = ((this->ValidateIndex(current_index_x,current_index_y + 1)) ? (&this->node_map[current_index_x][current_index_y + 1]) : (nullptr));

	if (left_top)
	{
		//[N][X][ ]
		//[X][C][ ]
		//[ ][ ][ ]
		if ((!node_left->GetWalkable()) || (!node_top->GetWalkable()))
			return false;
	}

	else if (right_top)
	{
		//[ ][X][N]
		//[ ][C][X]
		//[ ][ ][ ]
		if ((!node_right->GetWalkable()) || (!node_top->GetWalkable()))
			return false;
	}

	else if (left_bottom)
	{
		//[ ][ ][ ]
		//[X][C][ ]
		//[N][X][ ]
		if ((!node_left->GetWalkable()) || (!node_bottom->GetWalkable()))
			return false;
	}

	else if (right_bottom)
	{
		//[ ][ ][ ]
		//[ ][C][X]
		//[ ][X][N]
		if ((!node_right->GetWalkable()) || (!node_bottom->GetWalkable()))
			return false;
	}

	return true;
}

void Pathfind::MovementNodeByNode(const int current_object_x,const int current_object_y,const int movement_speed)
{
	//Movimento completado no Node atual do movimento
	if ((this->horizontal_movement == Movement::Done) && (this->vertical_movement == Movement::Done))
	{
		//Incrementando para passar para o próximo Node
		this->current_node_movement_index++;

		//Ja chegou ao último Node do caminho então parar o processo
		if (this->current_node_movement_index == this->path.size())
			this->Clear();
	}
	//A verificação acima deve ser feita antes aqui pois deve-se deixar o loop correr uma vez com base nos resultados abaixo

	//Verificando se ha algum caminho para ser percorrido
	const Node* current_node_movement = ((this->path.empty()) ? this->node_initial : this->path[this->current_node_movement_index]);
	if (current_node_movement)
	{
		//Verificando se ja está no ponto final do Node atual com base na velocidade
		if ((current_object_x <= current_node_movement->GetX() + movement_speed) && (current_object_x >= current_node_movement->GetX() - movement_speed))
			this->horizontal_movement = Movement::Done;

		//Objeto está a direita do Node atual
		else if (current_object_x > current_node_movement->GetX())
			this->horizontal_movement = Movement::Left;

		//Objeto está a esquerda do Node atual
		else if (current_object_x < current_node_movement->GetX())
			this->horizontal_movement = Movement::Right;

		//Verificando se ja está no ponto final do Node atual com base na velocidade
		if ((current_object_y <= current_node_movement->GetY() + movement_speed) && (current_object_y >= current_node_movement->GetY() - movement_speed))
			this->vertical_movement = Movement::Done;

		//Objeto está abaixo do Node atual
		else if (current_object_y > current_node_movement->GetY())
			this->vertical_movement = Movement::Up;

		//Objeto está acima do Node atual
		else if (current_object_y < current_node_movement->GetY())
			this->vertical_movement = Movement::Down;

		//Atualizar o Node inicial com base no movimento, fazendo com que sempre o Node alvo (em direção) seja o Node inicial
		int index_x = current_object_x / this->node_distance;
		int index_y = current_object_y / this->node_distance;

		if (this->horizontal_movement == Movement::Right)
			index_x = (current_object_x + (this->node_distance / 2) + 1) / this->node_distance;

		else if (this->horizontal_movement == Movement::Left)
			index_x = (current_object_x - (this->node_distance / 2) - 1) / this->node_distance;

		if (this->vertical_movement == Movement::Down)
			index_y = (current_object_y + (this->node_distance / 2) + 1) / this->node_distance;

		else if (this->vertical_movement == Movement::Up)
			index_y = (current_object_y - (this->node_distance / 2) - 1) / this->node_distance;

		this->SetNodeInitial(index_x,index_y);
	}
}

void Pathfind::Clear()
{
	this->path.clear();
	this->current_node_movement_index = -1;
	this->horizontal_movement = Movement::None;
	this->vertical_movement = Movement::None;
}
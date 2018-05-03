#ifndef CHARACTER_H
#define CHARACTER_H

#include "Quantity.h"
#include "Interval.h"
#include "Pathfind.h"
#include "Sprite.h"
#include "MapObject.h"

namespace RPG
{
	class Character : public GPL::MapObject
	{
	private:
		//Velocidade para alterar a posição X
		float velocity_x;

		//Velocidade para alterar a posição Y
		float velocity_y;

		//Velocidade do movimento
		float movement_speed;

		//Para qual direção o personagem está virado
		float direction;

		//Sprite do personagem
		GPL::Sprite character_sprite;

		//Sprite da sombra do personagem
		GPL::Sprite character_shadow_sprite;

		//Índice de cada passo
		GPL::Quantity walk_index;

		//Temporizado do controle de índices e dar a impressão de movimento
		GPL::Interval movement_timer;

		//Temporizador para atualizar a posição do personagem com base na velocidade
		GPL::Interval velocity_timer;

		//Encontrar o melhor caminho para chegar no objetivo
		GPL::Pathfind pathfind;

		//Bloquear movimentos do personagem
		bool lock_move;

		//Está se movendo para esquerda
		bool moving_left;

		//Está se movendo para direita
		bool moving_right;

		//Está se movendo para cima
		bool moving_up;

		//Está se movendo para baixo
		bool moving_down;

		//Habilitar o uso de Pathfind
		bool enable_pathfind;

		//Fazer o movimento pelo Pathfind
		void PathfindMovement();

		//Resetar valores
		void Reset();

		//Alterar Gray Scale
		virtual void SetGrayScale(const bool gray_scale);
	public:
		//Construtor
		Character(const bool enable_action_tooltip = true,const bool ignore_any_mouse_interaction = false);

		//Alterar Character Texture
		void SetCharacterTexture(const GPL::Texture& texture);

		//Pegar Character Texture
		const GPL::Texture& GetCharacterTexture() const;

		//Alterar Character Shadow Texture
		void SetCharacterShadowTexture(const GPL::Texture& texture);

		//Alterar Pathfind Node Walkable
		void SetPathfindNodeWalkable(const int index_x,const int index_y,const bool walkable);

		//Alterar Pathfind Node Initial
		void SetPathfindNodeInitial(const int index_x,const int index_y);

		//Alterar Pathfind Node Final
		void SetPathfindNodeFinal(const int index_x,const int index_y);

		//Alterar Pathfind Camera Index
		void SetPathfindCameraIndex(const int index_x,const int index_y,const int index_w,const int index_h);

		//Criar mapa de Nodes para o Pathfind
		void CreatePathfindGridNodeMap(const int node_total_x,const int node_total_y,const float node_distance);

		//Limpar dados do Pathfind
		void ClearPathfind();

		//Calcular e encontrar o caminho final
		bool FindPath();

		//Habilitar Pathfind
		void EnablePathfind();

		//Desabilitar Pathfind
		void DisablePathfind();

		//Mover para esquerda
		void MoveLeft();

		//Mover para direita
		void MoveRight();

		//Mover para cima
		void MoveUp();

		//Mover para baixo
		void MoveDown();

		//Parar personagem
		void Stop();

		//Verificar se está virado para esquerda
		bool IsFacingLeft() const;

		//Verificar se está virado para direita
		bool IsFacingRight() const;

		//Verificar se está virado para cima
		bool IsFacingUp() const;

		//Verificar se está virado para baixo
		bool IsFacingDown() const;

		//Verificar se os movimentos estão bloqueados
		bool IsMovementLocked() const;

		//Sem alterar posição no movimento
		void NoMovementSpeed();

		//Movimento lento
		void MovementSpeedSlow();

		//Movimento normal
		void MovementSpeedNormal();

		//Movimento rapido
		void MovementSpeedFast();

		//Pegar Action Position X
		virtual float GetActionPositionX() const;

		//Pegar Action Position Y
		virtual float GetActionPositionY() const;

		//Pegar Move To Position X
		virtual float GetMoveToPositionX(const MapObject& map_object) const;

		//Pegar Move To Position Y
		virtual float GetMoveToPositionY(const MapObject& map_object) const;

		//Virar para esquerda
		virtual void TurnLeft();

		//Virar para direita
		virtual void TurnRight();

		//Virar para cima
		virtual void TurnUp();

		//Virar para baixo
		virtual void TurnDown();

		//Verificar se está movendo
		virtual bool IsMoving() const;

		//Bloquear movimentos
		virtual void LockMovement();

		//Desbloquear movimentos
		virtual void UnlockMovement();

		//Atualizar dados de relacionados aos movimentos
		virtual void UpdateMovement(const GPL::Timer& timer);

		//Atualizar dados do objeto
		virtual void Update(const GPL::Timer& timer);

		//Mostrar o objeto
		virtual void Show(GPL::Video& video,const GPL::Timer& timer);
	};
}

#endif
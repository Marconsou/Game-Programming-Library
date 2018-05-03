#include "Character.h"

using namespace std;
using namespace GPL;
using namespace RPG;

Character::Character(const bool enable_action_tooltip,const bool ignore_any_mouse_interaction) :
	MapObject(64.0f,96.0f,64.0f * 3.0f,64.0f * 3.0f,enable_action_tooltip,ignore_any_mouse_interaction),
	velocity_x(0.0f),
	velocity_y(0.0f),
	movement_speed(0.0f),
	direction(0.0f),
	walk_index(0,4),
	velocity_timer(0.015f),
	lock_move(false),
	moving_left(false),
	moving_right(false),
	moving_up(false),
	moving_down(false),
	enable_pathfind(true)
{
	this->character_sprite.SetSize(this->GetW(),this->GetH());
	this->character_shadow_sprite.SetSize(this->GetW(),this->GetH() / 3.0f);
	this->MovementSpeedNormal();
}

float Character::GetActionPositionX() const
{
	return (this->GetX() + (this->GetW() / 2.0f));
}

float Character::GetActionPositionY() const
{
	return (this->GetY() + this->GetH() - 14.0f);
}

float Character::GetMoveToPositionX(const MapObject& map_object) const
{
	return this->GetMoveToPositionBase(&MapObject::GetActionPositionX,map_object,64.0f);
}

float Character::GetMoveToPositionY(const MapObject& map_object) const
{
	return this->GetMoveToPositionBase(&MapObject::GetActionPositionY,map_object,64.0f);
}

void Character::SetGrayScale(const bool gray_scale)
{
	this->character_sprite.SetGrayScale(gray_scale);
	this->character_shadow_sprite.SetGrayScale(gray_scale);
}

void Character::SetCharacterTexture(const Texture& texture)
{
	this->character_sprite.SetTexture(texture);
}

const Texture& Character::GetCharacterTexture() const
{
	return this->character_sprite.GetTexture();
}

void Character::SetCharacterShadowTexture(const Texture& texture)
{
	this->character_shadow_sprite.SetTexture(texture);
}

void Character::SetPathfindNodeWalkable(const int index_x,const int index_y,const bool walkable)
{
	this->pathfind.SetNodeWalkable(index_x,index_y,walkable);
}

void Character::SetPathfindNodeInitial(const int index_x,const int index_y)
{
	this->pathfind.SetNodeInitial(index_x,index_y);
}

void Character::SetPathfindNodeFinal(const int index_x,const int index_y)
{
	this->pathfind.SetNodeFinal(index_x,index_y);
}

void Character::SetPathfindCameraIndex(const int index_x,const int index_y,const int index_w,const int index_h)
{
	this->pathfind.SetCameraIndex(index_x,index_y,index_w,index_h);
}

void Character::CreatePathfindGridNodeMap(const int node_total_x,const int node_total_y,const float node_distance)
{
	this->pathfind.CreateGridNodeMap(node_total_x,node_total_y,static_cast<int>(node_distance));
}

void Character::ClearPathfind()
{
	this->pathfind.Clear();
}

bool Character::FindPath()
{
	if (this->enable_pathfind)
		return this->pathfind.FindPath();
	return false;
}

void Character::EnablePathfind()
{
	this->enable_pathfind = true;
}

void Character::DisablePathfind()
{
	this->enable_pathfind = false;
}

void Character::MoveLeft()
{
	if (!this->lock_move)
	{
		this->velocity_x -= this->movement_speed;
		this->moving_left = true;
		this->TurnLeft();
	}
}

void Character::MoveRight()
{
	if (!this->lock_move)
	{
		this->velocity_x += this->movement_speed;
		this->moving_right = true;
		this->TurnRight();
	}
}

void Character::MoveUp()
{
	if (!this->lock_move)
	{
		this->velocity_y -= this->movement_speed;
		this->moving_up = true;
		this->TurnUp();
	}
}

void Character::MoveDown()
{
	if (!this->lock_move)
	{
		this->velocity_y += this->movement_speed;
		this->moving_down = true;
		this->TurnDown();
	}
}

void Character::Stop()
{
	this->walk_index.SetCurrent(0);
	this->Reset();
}

bool Character::IsFacingLeft() const
{
	return (this->direction == this->GetH());
}

bool Character::IsFacingRight() const
{
	return (this->direction == this->GetH() * 2.0f);
}

bool Character::IsFacingUp() const
{
	return (this->direction == this->GetH() * 3.0f);
}

bool Character::IsFacingDown() const
{
	return (this->direction == 0.0f);
}

void Character::TurnLeft()
{
	this->direction = this->GetH();
}

void Character::TurnRight()
{
	this->direction = this->GetH() * 2.0f;
}

void Character::TurnUp()
{
	this->direction = this->GetH() * 3.0f;
}

void Character::TurnDown()
{
	this->direction = 0.0f;
}

bool Character::IsMoving() const
{
	return ((this->moving_left) || (this->moving_right) || (this->moving_up) || (this->moving_down));
}

bool Character::IsMovementLocked() const
{
	return this->lock_move;
}

void Character::NoMovementSpeed()
{
	this->movement_speed = 0.0f;
}

void Character::MovementSpeedSlow()
{
	this->movement_speed = 2.5f;
	this->movement_timer.SetInterval(0.200f);
}

void Character::MovementSpeedNormal()
{
	this->movement_speed = 5.0f;
	this->movement_timer.SetInterval(0.100f);
}

void Character::MovementSpeedFast()
{
	this->movement_speed = 10.0f;
	this->movement_timer.SetInterval(0.050f);
}

void Character::LockMovement()
{
	this->lock_move = true;
	this->pathfind.Clear();
	this->Reset();
}

void Character::UnlockMovement()
{
	this->lock_move = false;
}

void Character::PathfindMovement()
{
	const float action_position_x = this->GetActionPositionX();
	const float action_position_y = this->GetActionPositionY();

	//Fazer o movimento passo a passo
	this->pathfind.MovementNodeByNode(static_cast<int>(action_position_x),static_cast<int>(action_position_y),static_cast<int>(this->movement_speed));

	//Movimento pela horizontal
	const Movement horizontal_movement = this->pathfind.GetHorizontalMovement();

	//Right
	if (horizontal_movement == Movement::Right)
		this->MoveRight();

	//Left
	else if (horizontal_movement == Movement::Left)
		this->MoveLeft();

	//Done
	else if (horizontal_movement == Movement::Done)
	{
		//Centralizar o personagem no Node atual quando não estiver se movendo com base na posição base
		const float center_x = action_position_x - this->GetX();
		this->SetX(this->pathfind.GetCurrentNodeMovement().GetX() - center_x);
	}

	//Movimento pela vertical
	const Movement vertical_movement = this->pathfind.GetVerticalMovement();

	//Up
	if (vertical_movement == Movement::Up)
		this->MoveUp();

	//Down
	else if (vertical_movement == Movement::Down)
		this->MoveDown();

	//Done
	else if (vertical_movement == Movement::Done)
	{
		//Centralizar o personagem no Node atual quando não estiver se movendo com base na posição base
		const float center_y = action_position_y - this->GetY();
		this->SetY(this->pathfind.GetCurrentNodeMovement().GetY() - center_y);
	}
}

void Character::UpdateMovement(const Timer& timer)
{
	//Movimento pelo Pathfind se habilitado
	if (this->enable_pathfind)
		this->PathfindMovement();

	//Personagem dando impressão de movimento
	if (this->IsMoving())
	{
		if (this->movement_timer.Action(timer))
			this->walk_index.Next();
	}
	else
		this->Stop();

	//Atualizar a posição com base na velocidade
	if (this->velocity_timer.Action(timer))
	{
		//Mudando a posição com base na velocidade adquirida
		this->SetX(this->GetX() + this->velocity_x);
		this->SetY(this->GetY() + this->velocity_y);
	}

	//Área de interação do personagem centralizado
	this->GetInteractionArea().SetPosition(this->GetActionPositionX(),this->GetActionPositionY(),true);
}

void Character::Update(const Timer& timer)
{
	//Atualizando as posições do personagem baseado na câmera, mas sem de fato alterar as dimensões do objeto (somente o Sprite)
	const float x = this->GetX() - this->GetCameraX();
	const float y = this->GetY() - this->GetCameraY();

	//Posição da textura do personagem
	this->character_sprite.SetTexturePosition(this->GetW() * this->walk_index.GetCurrent(),this->direction);

	//Posição do personagem
	this->character_sprite.SetPosition(x,y);

	//Posição da sombra do personagem
	if (&this->character_shadow_sprite.GetTexture())
		this->character_shadow_sprite.SetPosition(this->character_sprite.GetX(),this->character_sprite.GetY() + this->character_sprite.GetH() - this->character_shadow_sprite.GetH() + 8.0f);
}

void Character::Show(Video& video,const Timer& timer)
{
	//Mostrar sombra do personagem
	if (&this->character_shadow_sprite.GetTexture())
		this->character_shadow_sprite.Show(video);

	//Mostrar personagem
	this->character_sprite.Show(video);

	//Resetando valores para o próximo loop
	this->Reset();
}

void Character::Reset()
{
	this->velocity_x = 0.0f;
	this->velocity_y = 0.0f;
	this->moving_left = false;
	this->moving_right = false;
	this->moving_up = false;
	this->moving_down = false;
}
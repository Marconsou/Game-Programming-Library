#include "SkillButton.h"

using namespace std;
using namespace GPL;
using namespace RPG;

SkillButton::SkillButton() :
	skill(nullptr)
{
	this->SetButton(0.0f,0.0f,32.0f,32.0f);
}

void SkillButton::SetSkill(Skill& skill,const Texture& texture,const int skill_index)
{
	this->skill = &skill;

	const int quantity_w = static_cast<int>(texture.GetWidth() / this->GetW());

	const float texture_position_x = (skill_index % quantity_w) * this->GetW();
	const float texture_position_y = (skill_index / quantity_w) * this->GetH();

	//Atualizar o botão
	this->SetButton(texture,this->GetW(),this->GetH(),texture_position_x,texture_position_y);
}

Skill& SkillButton::GetSkill()
{
	return *this->skill;
}
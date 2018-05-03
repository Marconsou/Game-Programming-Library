#include "ClassSelector.h"

using namespace std;
using namespace GPL;
using namespace RPG;

ClassSelector::ClassSelector() :
	selected(false),
	base_texture_id(0)
{

}

void ClassSelector::SetPosition(const float x,const float y,const bool centralize)
{
	//Posição do botão
	Button::SetPosition(x,y,centralize);

	//Alterar posição de todos os avatares
	for (size_t i = 0; i < this->avatars.size(); i++)
		this->avatars[i]->SetPosition(x,y,centralize);
}

void ClassSelector::SetSelected(const bool selected)
{
	this->selected = selected;
}

int ClassSelector::GetTextureID() const
{
	return (this->base_texture_id + this->avatar_quantity.GetCurrent());
}

void ClassSelector::PreviousAvatar()
{
	this->avatar_quantity.Previous();
}

void ClassSelector::NextAvatar()
{
	this->avatar_quantity.Next();
}

void ClassSelector::SetClassSelector(const Video& video,const int base_texture_id,const size_t avatar_total)
{
	this->base_texture_id = base_texture_id;

	//Quantidade de avatares
	this->avatar_quantity.SetTotal(avatar_total);

	//Texturas dos avatares
	for (size_t i = 0; i < avatar_total; i++)
	{
		//Adicionando Character
		this->avatars.push_back(make_unique<Character>());

		//Último adicionado
		Character& character = *this->avatars.back().get();

		//Textura que será utilizada
		character.SetCharacterTexture(video.GetTexture(this->base_texture_id + i));

		//Velocidade do movimento
		character.NoMovementSpeed();
	}

	//Botão
	this->SetButton(0.0f,0.0f,this->avatars.back()->GetW(),this->avatars.back()->GetH());
}

bool ClassSelector::Show(const Input& input,Video& video,const Timer& timer)
{
	const bool show_tooltip = Button::Show(input,video,timer);

	//Personagem selecionado
	Character& character = *this->avatars[this->avatar_quantity.GetCurrent()].get();

	//Personagem fará o movimento para baixo se está selecionado
	if (this->selected)
		character.MoveDown();

	//Atualizar e mostrar o personagem
	character.UpdateMovement(timer);
	character.Update(timer);
	character.Show(video,timer);

	return show_tooltip;
}
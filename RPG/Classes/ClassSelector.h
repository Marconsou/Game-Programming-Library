#ifndef CLASSSELECTOR_H
#define CLASSSELECTOR_H

#include "Button.h"
#include "Character.h"

namespace RPG
{
	class ClassSelector : public GPL::Button
	{
	private:
		//Se está selecionado
		bool selected;

		//ID da textura base da classe
		int base_texture_id;

		//Quantidade de avatares
		GPL::Quantity avatar_quantity;

		//Personagem se movendo
		std::vector<std::unique_ptr<Character>> avatars;

		//Mostrar o controle
		bool Show(const GPL::Input& input,GPL::Video& video,const GPL::Timer& timer) override;
	public:
		//Construtor
		ClassSelector();

		//Alterar Selected
		void SetSelected(const bool selected);

		//Pegar Texture ID
		int GetTextureID() const;

		//Avatar anterior
		void PreviousAvatar();

		//Avatar posterior
		void NextAvatar();

		//Alterar Class Selector
		void SetClassSelector(const GPL::Video& video,const int base_texture_id,const std::size_t avatar_total = 5);

		//Alterar Position
		virtual void SetPosition(const float x,const float y,const bool centralize = false);
	};
}

#endif
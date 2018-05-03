#ifndef CHARACTERSTATSPAGE_H
#define CHARACTERSTATSPAGE_H

#include "Label.h"
#include "Menu.h"

namespace RPG
{
	class CharacterStatsPage : public Menu
	{
	private:
		//Referência da posição do Menu
		const GPL::Point2D<float>& position;
	protected:
		//Pegar X
		float GetX();

		//Pegar Y
		float GetY();

		//Alterar Stats Label
		void SetStatsLabel(int& index,const float x,float& y,const std::string& label,const GPL::Color& label_color = GPL::Color::Yellow,const bool double_line_skip = false);

		//Alterar Stats Label
		void SetStatsLabel(int& index,const float x,float& y,const std::string& label,const std::string& value,const GPL::Color& label_color = GPL::Color::Yellow,const GPL::Color& value_color = GPL::Color::White,const bool double_line_skip = false);

		//Pegar Stat Label
		const GPL::Label& GetStatsLabel(const int index) const;

		//Adicionar Stats Label na lista de controles
		void AddStatsLabelControl(const int index);

		//Nova linha de texto para o ToolTip para o Label do índice
		void NewToolTipTextLine(int& index,const std::string& string_text,const GPL::Color& color = GPL::Color::White,const GPL::ToolTipTextAlign text_align = GPL::ToolTipTextAlign::Left);

		//Adicionar texto na última linha para o ToolTip do Label do índice
		void AddToolTipTextLine(int& index,const std::string& string_text,const GPL::Color& color = GPL::Color::White);
	public:
		//Construtor
		CharacterStatsPage(const GPL::Point2D<float>& position,const size_t size);

		//Destrutor
		virtual ~CharacterStatsPage() = 0 {};
	};
}

#endif
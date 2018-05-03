#include "TextDynamicWave.h"

using namespace std;
using namespace GPL;

void TextDynamicWave::SetPosition(const float x,const float y,const bool centralize)
{
	TextDynamic::SetPosition(x,y,centralize);
}

void TextDynamicWave::SetTextDynamic(const Font& font,const string& string_text,const Color& color)
{
	//Resetando os valores do texto dinâmico
	this->Clear();

	//Tamanho
	Point2D<float> size = Text::TextSize(font,string_text);
	this->GetRect().SetSize(size.GetX(),size.GetY());

	this->text_dynamic.clear();
	for (size_t i = 0; i < string_text.size(); i++)
		this->text_dynamic.push_back(make_unique<Text>(font,string(1,string_text[i]),color));
}

bool TextDynamicWave::Play(const bool force_replay)
{
	if (TextDynamic::Play(force_replay))
	{
		Text& text = *this->text_dynamic.front();
		float last_char_width = 0;
		float total_width = 0;
		const int size = this->text_dynamic.size();
		for (int i = 0; i < size; i++)
		{
			this->enable.push_back(false);
			this->revert.push_back(false);
			this->end.push_back(false);
			this->speed.push_back(1.0f);
			this->show_timer.push_back(make_unique<Interval>(0.01f));

			//Posição de cada caractere com base na largura do anterior
			total_width += last_char_width;
			this->relative_position.push_back(Point2D<float>(total_width,0));
			this->text_dynamic[i]->SetPosition(total_width,0.0f);

			//Espaço de cada caractere
			last_char_width = this->text_dynamic[i]->GetW();
		}

		//Habilitando o primeiro caractere
		if (size > 0)
			this->enable[0] = true;

		return true;
	}
	return false;
}

bool TextDynamicWave::Show(Video& video,const Timer& timer)
{
	//Mostrar o Text Dynamic
	if (this->GetPlaying())
	{
		//Posição inicial
		const float x = this->GetRect().GetPosition().GetX();
		const float y = this->GetRect().GetPosition().GetY();

		//Atualizando os valores que marcam a posição de reversão e chamado do próximo caracter
		this->revert_y = y - (this->GetH() / 3);
		this->call_next_y = ((y - this->revert_y) / 2) + this->revert_y;

		const size_t size = this->text_dynamic.size();
		for (size_t i = 0; i < size; i++)
		{
			Text& iterator = *this->text_dynamic[i];

			iterator.SetPosition(x + this->relative_position[i].GetX(),y + this->relative_position[i].GetY());

			//Temporizador de cada caractere do texto dinâmico
			if ((this->show_timer[i]->Action(timer)) && (this->enable[i]))
			{
				//Muda incremento<->decremento
				const float wave_speed = 1.0f;
				if (this->revert[i])
					this->speed[i] -= wave_speed;
				else
					this->speed[i] += wave_speed;

				//Atualizando a posição Y
				this->relative_position[i].SetY(this->relative_position[i].GetY() - this->speed[i]);
				const float updated_y = y + this->relative_position[i].GetY();

				//Se Y alcançar o seu limite, então é revertido a direção (Queda)
				if ((updated_y <= this->revert_y) && (!this->revert[i]))
					this->revert[i] = true;

				//Se Y alcancar a posição inicial novamente então para de cair
				else if ((updated_y >= y) && (this->revert[i]))
				{
					this->enable[i] = false;
					this->revert[i] = false;
					this->end[i] = true;
					this->speed[i] = 0.0f;
				}

				//Se Y alcancar a posição para chamar o próximo caractere então este começa a se mover
				if (updated_y <= this->call_next_y)
				{
					//Se não for o último caractere
					if (i != size - 1)
						this->enable[i + 1] = true;
				}
			}
		}

		//Último caractere do texto dinâmico chega ao fim do movemento, começar a reduzir a transparência
		if (size > 0)
		{
			if (this->end[size - 1])
			{
				if (this->alpha_timer.Action(timer))
				{
					for (size_t i = 0; i < size; i++)
						this->text_dynamic[i]->SetAlpha(this->text_dynamic[i]->GetAlpha() - 0.040f);

					if (this->text_dynamic.back()->GetAlpha() < 0.0f)
						this->SetPlaying(false);
				}
			}
		}

		//Mostrando o texto
		if (this->GetPlaying())
		{
			for (size_t i = 0; i < this->text_dynamic.size(); i++)
				this->text_dynamic[i]->Show(video);
		}
	}
	return this->GetPlaying();
}

void TextDynamicWave::Clear()
{
	this->SetPlaying(false);

	for (size_t i = 0; i < this->text_dynamic.size(); i++)
	{
		Text& iterator = *this->text_dynamic[i];

		//Alpha
		iterator.SetAlpha(1.0f);

		//Scale
		iterator.SetScaleX(1.0f);
		iterator.SetScaleY(1.0f);
	}

	this->enable.clear();
	this->revert.clear();
	this->end.clear();
	this->speed.clear();
	this->relative_position.clear();
	this->show_timer.clear();
}
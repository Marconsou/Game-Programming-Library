#include "DialogueBox.h"

using namespace std;
using namespace GPL;

DialogueBox::DialogueBox() :
	center_next_loop(false),
	opening_dialogue_box(true),
	closing_dialogue_box(false),
	width_reach_limit(false),
	last_option_selected_index(-1),
	text_lines_per_paragraph(0),
	current_paragraph_index(0),
	current_option_index(0),
	character_timer(0.0f),
	show_option_timer(0.015f),
	window_resize_timer(0.015f),
	cursor(PrimitiveType::TriangleList,2,6)
{
	this->cursor.SetVertexColor(0,Color::Black);
	this->cursor.SetVertexColor(1,Color::Black);
	this->cursor.SetVertexColor(2,Color::Black);
	this->cursor.SetVertexColor(3,Color::White);
	this->cursor.SetVertexColor(4,Color::White);
	this->cursor.SetVertexColor(5,Color::White);

	this->AddEventOnKeyDown(&DialogueBox::OnKeyDown,*this);
	this->AddEventOnMouseDown(&DialogueBox::OnMouseDown,*this);
}

void DialogueBox::RectUpdate()
{
	//Control
	this->GetRect().SetSize(this->window.GetW(),this->window.GetH());
}

void DialogueBox::SetPosition(const float x,const float y,const bool centralize)
{
	this->center_next_loop = centralize;
	this->RectUpdate();
	Control::SetPosition(x,y,centralize);
	this->window.SetPosition(x,y,centralize);
}

void DialogueBox::SetDialogueBox(const Font& font,const size_t text_lines_per_paragraph,const float text_area_width,const float text_area_padding_x,const float text_area_padding_y,const float text_speed_interval,const string& title_text,const Color& color)
{
	//Limpar tudo antes
	this->Clear();

	//Quantidade de linhas de texto por parágrafo
	this->text_lines_per_paragraph = text_lines_per_paragraph;

	//Text Speed
	this->character_timer.SetInterval(text_speed_interval);

	//Title
	this->title.SetText(font,title_text,color);

	//Text Area
	this->text_area.SetPosition(text_area_padding_x,text_area_padding_y);
	this->text_area.SetSize(text_area_width,(((this->title.GetValidCharacterTotal() > 0) ? 1.0f : 0.0f) * this->title.GetH()) + (text_lines_per_paragraph * this->title.GetH()));
}

void DialogueBox::SetWindowCurrentBackground(const int current_background)
{
	this->window.SetCurrentBackground(current_background);
}

void DialogueBox::SetWindowShowBorder(const bool show_border)
{
	this->window.SetShowBorder(show_border);
}

void DialogueBox::SetWindow(const float edge_distance)
{
	this->window.SetWindow(0,0,edge_distance);
	this->RectUpdate();
}

void DialogueBox::SetWindow(const Color& color_left_top,const Color& color_right_top,const Color& color_left_bottom,const Color& color_right_bottom,const float edge_distance)
{
	this->window.SetWindow(0,0,color_left_top,color_right_top,color_left_bottom,color_right_bottom,edge_distance);
	this->RectUpdate();
}

void DialogueBox::SetOptionText(const int index,const string& string_text,const Color& color)
{
	this->options[index]->option.AddButtonText(string_text,color,true);
}

int DialogueBox::GetOptionsTotal() const
{
	return this->options.size();
}

void DialogueBox::AddControl()
{
	//Resetar valores
	this->Reset();

	//Window
	this->window.AddControl();

	//DialogueBox
	Control::AddControl();

	//Ganhar o foco
	this->GainFocus(true);
}

void DialogueBox::RemoveControl()
{
	//Window
	this->window.RemoveControl();

	//DialogueBox
	Control::RemoveControl();

	//Retroceder para o início
	this->Reset();
}

void DialogueBox::Reset()
{
	this->opening_dialogue_box = true;
	this->closing_dialogue_box = false;
	this->width_reach_limit = false;
	this->last_option_selected_index = -1;
	this->current_paragraph_index = 0;
	this->current_option_index = 0;

	for (size_t i = 0; i < this->paragraphs.size(); i++)
	{
		Paragraph& paragraph = *this->paragraphs[i];

		paragraph.current_text_line_index = 0;

		for (size_t j = 0; j < paragraph.text_lines.size(); j++)
			paragraph.text_lines[j]->current_character_index = 0;
	}
}

void DialogueBox::Clear()
{
	this->Reset();
	this->title.Clear();
	this->paragraphs.clear();
	this->options.clear();
}

void DialogueBox::NewTextLine(const string& string_text,const Color& color)
{
	//Remover espaços do início
	string trimmed_string_text(string_text);
	trimmed_string_text.erase(trimmed_string_text.begin(),find_if(trimmed_string_text.begin(),trimmed_string_text.end(),not1(ptr_fun<int,int>(isspace))));

	this->paragraphs.back()->text_lines.push_back(make_unique<TextLine>(this->title.GetFont(),trimmed_string_text,color));
}

void DialogueBox::NewParagraph(const string& string_text,const Color& color)
{
	this->paragraphs.push_back(make_unique<Paragraph>());
	this->NewTextLine(string_text,color);
}

void DialogueBox::SplitString(const string& string_text,vector<string>& splitted_string_texts)
{
	//Dividir de strings
	stringstream splitter(string_text);

	do
	{
		string buffer;
		splitter >> buffer;

		if (!buffer.empty())
		{
			//Se não for o primeiro texto
			if (!splitted_string_texts.empty())
				splitted_string_texts.push_back(" " + buffer);
			else
				splitted_string_texts.push_back(buffer);
		}
	} while (splitter);

	//Se tiver texto
	if (!string_text.empty())
	{
		//Se a string original tiver espaço no início, adicionar espaço na primeira string dividida, porque o stringstream remove
		const char first_character = string_text.front();
		if (Font::IsCharacterSpace(first_character))
			splitted_string_texts.front().insert(0,&first_character,1);

		//Se a string original tiver espaço no final, adicionar espaço na última string dividida, porque o stringstream remove
		const char last_character = string_text.back();
		if (Font::IsCharacterSpace(last_character))
			splitted_string_texts.back().push_back(last_character);
	}
}

void DialogueBox::AddText(const string& string_text,const Color& color)
{
	//Strings divididas
	vector<string> splitted_string_texts;
	SplitString(string_text,splitted_string_texts);

	for (size_t i = 0; i < splitted_string_texts.size(); i++)
	{
		string& iterator = splitted_string_texts[i];

		//Tem algum parágrafo
		if (!this->paragraphs.empty())
		{
			Paragraph& last_paragraph = *this->paragraphs.back();

			TextLine& last_text_line = *last_paragraph.text_lines.back();

			const float new_width = last_text_line.text.GetW() + Text::TextSize(this->title.GetFont(),iterator).GetX();

			//O texto cabe neste linha
			if (new_width < this->text_area.GetSize().GetX())
			{
				//Adicionar texto na mesma linha de texto
				last_text_line.text.AddText(iterator,color);
			}
			else
			{
				//O último parágrafo já está lotado de linhas de texto
				if (last_paragraph.text_lines.size() == this->text_lines_per_paragraph)
					this->NewParagraph(iterator,color);
				else
					this->NewTextLine(iterator,color);
			}
		}
		else
			this->NewParagraph(iterator,color);
	}
}

void DialogueBox::AddOption(const string& string_text,const Color& color,const float tab_space_x,const Color& cursor_text_color)
{
	this->options.push_back(make_unique<Option>(tab_space_x));

	Button& option = this->options.back()->option;

	option.SetButton(this->title.GetFont(),string_text,color,cursor_text_color);
	option.AddEventOnClick(&DialogueBox::OptionOnClick,*this);
}

void DialogueBox::AddOptionText(const string& string_text,const Color& color)
{
	this->options.back()->option.AddButtonText(string_text,color);
}

void DialogueBox::AddOptionKeyShortcut(const int index,const KeyboardKey keyboard_key_shortcut)
{
	this->options[index]->option.SetKeyboardKeyShortcut(keyboard_key_shortcut);
}

bool DialogueBox::IsLastParagraph() const
{
	return ((this->paragraphs.empty()) || (this->current_paragraph_index == this->paragraphs.size() - 1));
}

bool DialogueBox::IsLastTextLine(const Paragraph& paragraph) const
{
	return (paragraph.current_text_line_index == paragraph.text_lines.size() - 1);
}

bool DialogueBox::IsLastCharacter(const TextLine& text_line) const
{
	return (text_line.current_character_index == text_line.text.GetValidCharacterTotal());
}

void DialogueBox::NextParagraph()
{
	//Passando para o próximo parágrafo e evitar ultrapassar o índice
	this->current_paragraph_index = min(++this->current_paragraph_index,this->paragraphs.size() - 1);
}

void DialogueBox::NextTextLine()
{
	//Parágrafo atual
	Paragraph& paragraph = *this->paragraphs[this->current_paragraph_index];

	//Passando para a próxima linha de texto e evitar ultrapassar o índice
	paragraph.current_text_line_index = min(++paragraph.current_text_line_index,paragraph.text_lines.size() - 1);
}

void DialogueBox::NextCharacter()
{
	//Parágrafo atual
	Paragraph& paragraph = *this->paragraphs[this->current_paragraph_index];

	//Linha de texto atual
	TextLine& text_line = *paragraph.text_lines[paragraph.current_text_line_index];

	//Passando para o próximo caractere e evitar ultrapassar o índice
	text_line.current_character_index = min(++text_line.current_character_index,text_line.text.GetValidCharacterTotal());
}

void DialogueBox::SnapshotParagraph()
{
	if (!this->paragraphs.empty())
	{
		//Parágrafo atual
		Paragraph& paragraph = *this->paragraphs[this->current_paragraph_index];

		for (size_t i = 0; i < paragraph.text_lines.size(); i++)
		{
			TextLine& iterator = *paragraph.text_lines[i];

			iterator.current_character_index = iterator.text.GetValidCharacterTotal();
		}
	}
}

void DialogueBox::Interaction()
{
	//Só poderá interagir se não já estiver abrindo/fechando o DialogueBox
	if ((!this->opening_dialogue_box) && (!this->closing_dialogue_box))
	{
		//Último caractere do parágrafo atual mostrado
		if ((!this->paragraphs.empty()) && (this->IsLastCharacter(*this->paragraphs[this->current_paragraph_index]->text_lines.back())))
		{
			//Passar para o próximo para parágrafo
			this->NextParagraph();

			//Verificar se chegou ao final
			if (this->IsLastCharacter(*this->paragraphs.back()->text_lines.back()))
			{
				//Se não tiver opções já poderá fechar o DialogueBox
				if (this->options.empty())
					this->Close();
			}
		}
		else
		{
			//Mostrar todo o texto do parágrafo atual instantâneamente
			this->SnapshotParagraph();
		}
	}
}

void DialogueBox::Close()
{
	this->closing_dialogue_box = true;

	//Salvando a janela no estado atual
	this->closing_window_inner_border_quantity.SetX(this->window.GetInnerBlockQuantityW());
	this->closing_window_inner_border_quantity.SetY(this->window.GetInnerBlockQuantityH());

	//Se tiver opções
	if (!this->options.empty())
	{
		//Remover todas de uma vez
		for (size_t i = 0; i < this->options.size(); i++)
			this->options[i]->option.RemoveControl();
	}
}

bool DialogueBox::IsAlmostClosed()
{
	//Desta forma está mostrando o mínimo da janela
	return ((!this->opening_dialogue_box) && (this->window.GetInnerBlockQuantityW() == 0) && (this->window.GetInnerBlockQuantityH() == 0));
}

void DialogueBox::AddOptionsDynamically(const Timer& timer)
{
	if (!this->options.empty())
	{
		//Se não estiver abrindo/fechando o DialogueBox
		if ((!this->opening_dialogue_box) && (!this->closing_dialogue_box))
		{
			//O último dos últimos caracteres foi mostrado
			if ((this->paragraphs.empty()) || (this->IsLastCharacter(*this->paragraphs.back()->text_lines.back())))
			{
				//Se já não chegou no último
				if (this->current_option_index < this->options.size())
				{
					//Tempo de mostrar uma opção
					if (this->show_option_timer.Action(timer))
					{
						//Adicionando as opções para serem mostradas
						this->options[this->current_option_index]->option.AddControl();
						this->current_option_index++;
					}
				}
			}
		}
	}
}

void DialogueBox::UpdatePositions()
{
	const float x = this->GetX() + this->text_area.GetPosition().GetX();
	float y = this->GetY() + this->text_area.GetPosition().GetY();

	//Title
	if (this->title.GetValidCharacterTotal() > 0)
	{
		this->title.SetPosition(x,y);
		y += this->title.GetH();
	}

	//Text Lines
	if (!this->paragraphs.empty())
	{
		Paragraph& paragraph = *this->paragraphs[this->current_paragraph_index];

		for (size_t i = 0; i < paragraph.text_lines.size(); i++)
		{
			Text& iterator = paragraph.text_lines[i]->text;

			iterator.SetPosition(x,y);
			y += iterator.GetH();
		}
	}

	//Se tiver opção
	if (!this->options.empty())
	{
		//Atualizar as posições das opções que já estão sendo mostradas
		for (size_t i = 0; i < this->current_option_index; i++)
		{
			Option& iterator = *this->options[i].get();

			//Com espaçamento específico para a opção
			iterator.option.SetPosition(x + iterator.tab_space_x,y);

			//Adicionar 1.0f para evitar conflito entre as opções
			y += iterator.option.GetH() + 1.0f;
		}
	}
}

float DialogueBox::EstimateTotalHeight() const
{
	float total_height = this->GetY() + this->text_area.GetPosition().GetY();

	//Title
	if (this->title.GetValidCharacterTotal() > 0)
		total_height += this->title.GetH();

	//Text Lines
	if (!this->paragraphs.empty())
	{
		const Paragraph& paragraph = *this->paragraphs[this->current_paragraph_index];

		for (size_t i = 0; i < paragraph.text_lines.size(); i++)
			total_height += paragraph.text_lines[i]->text.GetH();
	}

	//Options
	if (!this->options.empty())
	{
		for (size_t i = 0; i < this->current_option_index; i++)
		{
			//Adicionar 1.0f para evitar conflito entre as opções
			total_height += this->options[i]->option.GetH() + 1.0f;
		}
	}

	return total_height;
}

void DialogueBox::AutoSizeWindow(const Timer& timer)
{
	const float y = this->EstimateTotalHeight();
	int final_window_inner_border_w = this->window.GetInnerBlockQuantityW();
	int final_window_inner_border_h = this->window.GetInnerBlockQuantityH();

	//Se tiver abrindo o DialogueBox
	if (this->opening_dialogue_box)
	{
		if (this->window_resize_timer.Action(timer))
		{
			//Aumentar a largura até o tamanho limite da área de texto
			const int quantity_w = static_cast<int>((this->text_area.GetPosition().GetX() + this->text_area.GetSize().GetX()) / Window::GetBlockSize());
			if (final_window_inner_border_w < quantity_w)
				final_window_inner_border_w++;

			//Depois quando chegar no limite da largura, aumentar a altura
			else
			{
				this->width_reach_limit = true;

				//Se tiver título, somar sua altura
				float total_height = this->text_area.GetPosition().GetY() + ((this->title.GetValidCharacterTotal() > 0) ? this->title.GetH() : 0.0f);

				//Somar a altura de cada linha de texto do primeiro parágrafo
				if (!this->paragraphs.empty())
				{
					for (size_t i = 0; i < this->paragraphs.front()->text_lines.size(); i++)
						total_height += this->paragraphs.front()->text_lines[i]->text.GetH();
				}

				//Aumentar a altura até o tamanho limite pela quantidade de linhas de textos incluíndo o título se tiver
				const int quantity_h = static_cast<int>(total_height / Window::GetBlockSize()) - 1;
				if (final_window_inner_border_h < quantity_h)
					final_window_inner_border_h++;

				//Já aumentou a largura e altura até certo ponto
				else
					this->opening_dialogue_box = false;
			}
		}
	}
	else
	{
		//Se tiver fechando o DialogueBox
		if (this->closing_dialogue_box)
		{
			if (this->window_resize_timer.Action(timer))
			{
				//Diminuir a altura primeiro
				if (this->closing_window_inner_border_quantity.GetY() > 0)
					this->closing_window_inner_border_quantity.SetY(max(this->closing_window_inner_border_quantity.GetY() - 1,0));

				//Depois quando a altura acabar, diminuir a largura
				else if (this->closing_window_inner_border_quantity.GetY() == 0)
					this->closing_window_inner_border_quantity.SetX(max(this->closing_window_inner_border_quantity.GetX() - 1,0));
			}

			final_window_inner_border_w = this->closing_window_inner_border_quantity.GetX();
			final_window_inner_border_h = this->closing_window_inner_border_quantity.GetY();
		}
		else
		{
			const float total_height = abs(y - this->GetY());
			const int quantity_h = static_cast<int>(total_height / Window::GetBlockSize()) - 1;
			final_window_inner_border_h = quantity_h;
		}
	}

	//Atualizar tamanho da janela
	this->window.SetInnerBlockQuantity(final_window_inner_border_w,final_window_inner_border_h);

	//Centralização necessária pois o tamanho já mudou dinamicamente
	if (this->center_next_loop)
	{
		this->SetPosition(this->GetX() + (this->GetW() / 2.0f),this->GetY() + (this->GetH() / 2.0f),true);
		this->center_next_loop = false;
	}
}

void DialogueBox::Update(const Input& input,const Timer& timer)
{
	//Se estiver habilitado e não estiver abrindo/fechando o DialogueBox
	if ((this->GetEnabled()) && (!this->opening_dialogue_box) && (!this->closing_dialogue_box))
	{
		//Se for instantâneo
		if (this->character_timer.GetInterval() == 0.0f)
			this->SnapshotParagraph();
		else
		{
			//Tempo para os caracteres
			if (this->character_timer.Action(timer))
			{
				//Parágrafo atual
				if (!this->paragraphs.empty())
				{
					Paragraph& paragraph = *this->paragraphs[this->current_paragraph_index];

					//Passar para o próximo caractere
					this->NextCharacter();

					//Verificar se chegou no último caractere do texto atual
					if (this->IsLastCharacter(*paragraph.text_lines[paragraph.current_text_line_index]))
					{
						//Passar para a próxima linha de texto
						this->NextTextLine();
					}
				}
			}
		}
	}

	//Se o Dialogue Box estiver finalizado/fechado
	if (!this->IsAlmostClosed())
	{
		//Adicionar opções dinamicamente
		this->AddOptionsDynamically(timer);

		//Mudar o tamanho da janela
		this->AutoSizeWindow(timer);

		//Atualizar as posições
		this->UpdatePositions();
	}
	else
	{
		//Remover primeiro a janela
		if (!this->window.IsRemoved())
			this->window.RemoveControl();

		//Depois remover o resto do DialogueBox
		else
		{
			//DialogueBox
			Control::RemoveControl();

			//On Option Selected
			this->CheckForOnOptionSelected();
		}
	}
}

void DialogueBox::ShowCursor(Video& video,const Timer& timer)
{
	static Interval cursor_timer(0.5f,timer);
	static bool show_cursor = true;
	if (this->GetEnabled())
	{
		if (cursor_timer.Action(timer))
			show_cursor = !show_cursor;
	}

	//Mostrar cursor
	if (show_cursor)
	{
		//Se não último parágrafo e o último caractere já foi mostrado
		if ((!this->IsLastParagraph()) && ((!this->paragraphs.empty()) && this->IsLastCharacter(*this->paragraphs[this->current_paragraph_index]->text_lines.back())))
		{
			const float size = 10.0f;
			const float space = 1.0f;

			const float x = this->GetX() + this->text_area.GetPosition().GetX() + this->text_area.GetSize().GetX();
			const float y = this->GetY() + this->text_area.GetPosition().GetY() + this->text_area.GetSize().GetY();

			const float x_1 = x;
			const float y_1 = y;

			const float x_2 = x_1 + size;
			const float y_2 = y_1 + size;

			const float x_3 = x_2 - (size / 2.0f);

			this->cursor.SetVertexPosition(0,x_1 + space,y_1 + space);
			this->cursor.SetVertexPosition(1,x_2 + space,y_1 + space);
			this->cursor.SetVertexPosition(2,x_3 + space,y_2 + space);

			this->cursor.SetVertexPosition(3,x_1,y_1);
			this->cursor.SetVertexPosition(4,x_2,y_1);
			this->cursor.SetVertexPosition(5,x_3,y_2);

			video.Draw(this->cursor);
		}
	}
}

void DialogueBox::Show(Video& video,Text& text,const int index)
{
	//Considera-se o texto com mais espaços para garantir que ele será exibido até 1 bloco da janela a mais em relação à sua altura quando abrir/fechar o DialogueBox
	if (((!this->opening_dialogue_box) && (!this->closing_dialogue_box)) || (text.GetY() + text.GetH() + Window::GetBlockSize() < this->window.GetY() + this->window.GetH()))
		text.Show(video,index);
}

bool DialogueBox::Show(const Input& input,Video& video,const Timer& timer)
{
	//Começar a mostrar depois que chegar no limite da largura
	if (this->width_reach_limit)
	{
		//Title
		if (this->title.GetValidCharacterTotal() > 0)
			this->Show(video,this->title,-1);

		//Text Lines
		if (!this->paragraphs.empty())
		{
			Paragraph& paragraph = *this->paragraphs[this->current_paragraph_index];

			for (size_t i = 0; i < paragraph.text_lines.size(); i++)
				this->Show(video,paragraph.text_lines[i]->text,paragraph.text_lines[i]->current_character_index);
		}

		//Cursor
		this->ShowCursor(video,timer);
	}

	return false;
}

void DialogueBox::CheckForOnOptionSelected()
{
	//Se foi selecionado alguma opção
	if (this->last_option_selected_index != -1)
	{
		const Option& option = *this->options[this->last_option_selected_index].get();
		
		//Resetar valor
		const int last_option_selected_index = this->last_option_selected_index;
		this->last_option_selected_index = -1;

		//Evento On Option Selected
		option.on_option_selected(option.option,last_option_selected_index);
	}
}

void DialogueBox::OnEnabledChanged(const Control& control)
{
	const bool change = !this->GetEnabled();

	//Window
	this->window.SetEnabled(this->GetEnabled());

	//Title
	this->title.SetGrayScale(change);

	//Cursor
	this->cursor.SetGrayScale(change);

	//Buttons
	for (size_t i = 0; i < this->options.size(); i++)
		this->options[i]->option.SetEnabled(this->GetEnabled());

	//Texts
	Paragraph& paragraph = *this->paragraphs[this->current_paragraph_index];
	for (size_t j = 0; j < paragraph.text_lines.size(); j++)
		paragraph.text_lines[j]->text.SetGrayScale(change);
}

void DialogueBox::OptionOnClick(const Control& control)
{
	//Buscar qual opção foi selecionada para atualizar o índice abaixo
	for (size_t i = 0; i < this->options.size(); i++)
	{
		if (&control == &this->options[i]->option)
		{
			this->last_option_selected_index = i;
			break;
		}
	}

	//Começar a fechar
	this->Close();
}

void DialogueBox::OnKeyDown(const Control& control,const KeyboardKey keyboard_key)
{
	if ((keyboard_key == KeyboardKey::Space) || (keyboard_key == KeyboardKey::Esc) || (keyboard_key == KeyboardKey::Enter))
		this->Interaction();
}

void DialogueBox::OnMouseDown(const Control& control,const MouseButton mouse_button,const float mouse_x,const float mouse_y)
{
	this->Interaction();
}
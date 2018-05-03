#include "MessageLog.h"

using namespace std;
using namespace GPL;

MessageLog::MessageLog() :
font(nullptr),
orientation{},
	message_life_time_ms(0.0f)
{
}

float MessageLog::GetX() const
{
	return this->position.GetX();
}

float MessageLog::GetY() const
{
	return this->position.GetY();
}

void MessageLog::SetPosition(const float x,const float y)
{
	this->position.SetX(x);
	this->position.SetY(y);
}

void MessageLog::SetMessageLog(const Font& font,const string& label_default_text,const Color& label_default_color,const float message_life_time_ms,const MessageLogOrientation orientation)
{
	this->Clear();
	this->font = &font;
	this->orientation = orientation;
	this->message_life_time_ms = message_life_time_ms;
	this->label_default_text = label_default_text;
	this->label_default_color = label_default_color;
}

void MessageLog::NewMessage(const Timer& timer,const string& message,const Color& color)
{
	//Nova linha
	this->text_lines.push_back(make_unique<TextLine>(1.0f,timer.CurrentTime()));
	TextLine& text_line = *this->text_lines.back();

	//Label
	text_line.message.SetText(*this->font,this->label_default_text,this->label_default_color);

	//Message
	text_line.message.AddText(message,color);
}

void MessageLog::AddMessage(const string& message,const Color& color)
{
	if (!this->text_lines.empty())
		this->text_lines.back()->message.AddText(message,color);
}

void MessageLog::ShowMessageLog(Video& video,const Timer& timer)
{
	for (size_t i = 0; i < this->text_lines.size(); i++)
	{
		TextLine& iterator = *this->text_lines[i];

		//Ação do Fade
		bool erased = false;
		if (timer.CurrentTime() >= (iterator.time + this->message_life_time_ms))
		{
			if (iterator.alpha_timer.Action(timer))
			{
				iterator.alpha = max(iterator.alpha -= 0.008f,0.0f);
				if (iterator.alpha == 0.0f)
				{
					this->text_lines.erase(this->text_lines.begin() + i);
					erased = true;
					i--;
				}
			}
		}

		//Se o texto não foi removido
		if (!erased)
		{
			//Orientação das mensagens
			const size_t last_index = this->text_lines.size() - i - 1;
			const float direction_y = (iterator.message.GetH() + 2.0f) * last_index;
			const float new_y = (this->orientation == MessageLogOrientation::Up) ? (this->position.GetY() - direction_y) : (this->orientation == MessageLogOrientation::Down) ? (this->position.GetY() + direction_y) : 0.0f;

			//Message
			iterator.message.SetPosition(this->position.GetX(),new_y);
			iterator.message.SetAlpha(iterator.alpha);
			iterator.message.Show(video);
		}
	}
}

void MessageLog::Clear()
{
	this->text_lines.clear();
}
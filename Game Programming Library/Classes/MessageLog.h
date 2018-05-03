#ifndef MESSAGELOG_H
#define MESSAGELOG_H

#include "Interval.h"
#include "Text.h"

namespace GPL
{
	enum class MessageLogOrientation
	{
		Down,
		Up,
	};

	class MessageLog
	{
	private:
		//Estrutura que representa a linha de textos
		struct TextLine
		{
			//Transparência de cada texto
			float alpha;

			//Tempo para poder começar a transparência
			float time;

			//Timer para transparência
			Interval alpha_timer;

			//Texto da mensagem
			Text message;

			//Construtor
			TextLine(const float alpha = 1.0f,const float time = 0.0f) :
				alpha(alpha),time(time),alpha_timer(0.015f) {}
		};

		//Fonte para ser usada em todos os textos
		const Font* font;

		//Orientação das mensagens
		MessageLogOrientation orientation;

		//Tempo de vida de cada mensagem
		float message_life_time_ms;

		//Posição da mensagem inicial
		Point2D<float> position;

		//Cor padrão para rótulo
		Color label_default_color;

		//Rótulo padrão para todas as mensagens
		std::string label_default_text;

		//Linhas com as mensagens e textos
		std::vector<std::unique_ptr<TextLine>> text_lines;
	public:
		//Construtor
		GPL_DLL MessageLog();

		//Pegar X
		GPL_DLL float GetX() const;

		//Pegar Y
		GPL_DLL float GetY() const;

		//Alterar Position
		GPL_DLL void SetPosition(const float x,const float y);

		//Alterar MessageLog
		GPL_DLL void SetMessageLog(const Font& font,const std::string& label_default_text,const Color& label_default_color,const float message_life_time_ms = 10.0f,const MessageLogOrientation orientation = MessageLogOrientation::Down);

		//Adicionar novo texto
		GPL_DLL void NewMessage(const Timer& timer,const std::string& message,const Color& color);

		//Adicionar texto para última mensagem criada
		GPL_DLL void AddMessage(const std::string& message,const Color& color);

		//Mostrar MessageLog
		GPL_DLL void ShowMessageLog(Video& video,const Timer& timer);

		//Limpar todas as mensagens
		GPL_DLL void Clear();
	};
}

#endif
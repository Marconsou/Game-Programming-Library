#ifndef TEXTDYNAMIC_H
#define TEXTDYNAMIC_H

#include <string>
#include "Rect.h"
#include "BuildDLL.h"

namespace GPL
{
	class Video;
	class Font;
	class Color;
	class Timer;

	class TextDynamic
	{
	public:
		GPL_DLL TextDynamic() = default;
		GPL_DLL virtual ~TextDynamic() = 0 {};
		GPL_DLL float GetX() const;
		GPL_DLL float GetY() const;
		GPL_DLL float GetW() const;
		GPL_DLL float GetH() const;
		GPL_DLL virtual void SetPosition(const float x,const float y,const bool centralize = false);
		GPL_DLL virtual void SetTextDynamic(const Font& font,const std::string& string_text,const Color& color) = 0;
		GPL_DLL virtual bool Play(const bool force_replay = true);
		GPL_DLL virtual bool Show(Video& video,const Timer& timer) = 0;
	protected:
		void SetPlaying(const bool playing);
		bool GetPlaying() const;
		Rect<float>& GetRect();
		virtual void Clear() = 0;
	private:
		bool playing{};
		Rect<float> rect;
		TextDynamic(const TextDynamic&) = delete;
		TextDynamic& operator=(const TextDynamic&) = delete;
	};
}

#endif
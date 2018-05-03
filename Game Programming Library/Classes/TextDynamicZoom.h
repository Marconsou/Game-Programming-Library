#ifndef TEXTDYNAMICZOOM_H
#define TEXTDYNAMICZOOM_H

#include "Interval.h"
#include "TextDynamic.h"
#include "Text.h"

namespace GPL
{
	class TextDynamicZoom : public TextDynamic
	{
	public:
		GPL_DLL void SetPosition(const float x,const float y,const bool centralize = false) override;
		GPL_DLL void SetTextDynamic(const Font& font,const std::string& string_text,const Color& color) override;
		GPL_DLL bool Play(const bool force_replay = true) override;
		GPL_DLL bool Show(Video& video,const Timer& timer) override;
	private:
		bool revert_scale{};
		float change_y{};
		Interval interval{0.015f};
		Interval scale_timer{0.015f};
		Text text_dynamic;
		GPL_DLL void Clear() override;
	};
}

#endif
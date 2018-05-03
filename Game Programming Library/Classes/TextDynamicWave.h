#ifndef TEXTDYNAMICWAVE_H
#define TEXTDYNAMICWAVE_H

#include "Interval.h"
#include "TextDynamic.h"
#include "Text.h"

namespace GPL
{
	class TextDynamicWave : public TextDynamic
	{
	public:
		GPL_DLL void SetPosition(const float x,const float y,const bool centralize = false) override;
		GPL_DLL void SetTextDynamic(const Font& font,const std::string& string_text,const Color& color) override;
		GPL_DLL bool Play(const bool force_replay = true) override;
		GPL_DLL bool Show(Video& video,const Timer& timer) override;
	private:
		float revert_y{};
		float call_next_y{};
		Interval alpha_timer{0.015f};
		std::vector<bool> enable;
		std::vector<bool> revert;
		std::vector<bool> end;
		std::vector<float> speed;
		std::vector<Point2D<float>> relative_position;
		std::vector<std::unique_ptr<Interval>> show_timer;
		std::vector<std::unique_ptr<Text>> text_dynamic;
		GPL_DLL void Clear() override;
	};
}

#endif
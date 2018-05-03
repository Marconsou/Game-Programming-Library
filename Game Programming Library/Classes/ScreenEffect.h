#ifndef SCREENEFFECT_H
#define SCREENEFFECT_H

#include "Interval.h"
#include "Video.h"

namespace GPL
{
	enum class ScreenEffectFadeMode
	{
		Slow,
		Normal,
		Fast,
	};

	class ScreenEffect
	{
	public:
		GPL_DLL ScreenEffect() = default;
		GPL_DLL void StartFadeInScreen(const ScreenEffectFadeMode screen_fade_mode);
		GPL_DLL void StartFadeOutScreen(const ScreenEffectFadeMode screen_fade_mode);
		GPL_DLL bool FadeInEnd() const;
		GPL_DLL bool FadeOutEnd() const;
		GPL_DLL void Show(Video& video,const Timer& timer);
	private:
		bool fading_in_screen{};
		bool fading_out_screen{};
		float alpha{1.0f};
		ScreenEffectFadeMode screen_fade_mode{ScreenEffectFadeMode::Normal};
		Model screen{PrimitiveType::TriangleStrip,2,4};
		ScreenEffect(const ScreenEffect&) = delete;
		ScreenEffect& operator=(const ScreenEffect&) = delete;
	};
}

#endif
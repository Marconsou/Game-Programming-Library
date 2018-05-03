#ifndef ANIMATIONFRAME_H
#define ANIMATIONFRAME_H

#include "Quantity.h"
#include "Interval.h"
#include "Sprite.h"

namespace GPL
{
	class AnimationFrame
	{
	public:
		GPL_DLL AnimationFrame() = default;
		GPL_DLL void SetTexture(const Texture& texture);
		GPL_DLL void SetX(const float x);
		GPL_DLL float GetX() const;
		GPL_DLL void SetY(const float y);
		GPL_DLL float GetY() const;
		GPL_DLL void SetPosition(const float x,const float y,const bool centralize = false);
		GPL_DLL float GetW() const;
		GPL_DLL float GetH() const;
		GPL_DLL void SetPause(const bool pause);
		GPL_DLL void SetGrayScale(const bool gray_scale);
		GPL_DLL void SetColor(const Color& color);
		GPL_DLL int GetCurrentFrame() const;
		GPL_DLL void SetAnimationFrame(const Timer& timer,const Texture& texture,const float frame_width,const float frame_height,const int frame_quantity,const float interval,const int pixel_gap = 0);
		GPL_DLL void EditInterval(const Timer& timer,const float interval);
		GPL_DLL void EditInterval(const Timer& timer,const int index,const float interval);
		GPL_DLL bool IsPlaying() const;
		GPL_DLL bool IsAtTheBeginning() const;
		GPL_DLL bool IsAtTheEnd() const;
		GPL_DLL void Play(const Timer& timer,const bool forward = true,const bool force_replay = true);
		GPL_DLL void Show(Video& video,const Timer& timer,const bool replay = false);
	private:
		bool playing{};
		bool pause{};
		bool forward{true};
		int pixel_gap{};
		Sprite sprite;
		Quantity frame_quantity{0,1,false};
		Interval animation_timer;
		std::vector<float> interval;
		AnimationFrame(const AnimationFrame&) = delete;
		AnimationFrame& operator=(const AnimationFrame&) = delete;
		void TimerIntervalUpdate(const Timer& timer,const float interval);
	};
}

#endif
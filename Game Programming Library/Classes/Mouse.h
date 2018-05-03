#ifndef MOUSE_H
#define MOUSE_H

#include "InputDevice.h"

namespace GPL
{
	enum class MouseButton
	{
		Unknown,
		Left,
		Right,
		Middle,
		XButton1,
		XButton2,
		Max,
	};

	class Mouse : public InputDevice<MouseButton>
	{
	public:
		Mouse();
		virtual ~Mouse() = 0 {};
		int GetX() const;
		int GetY() const;
		void SetMouseResolutionRatio(const float resolution_ratio_x,const float resolution_ratio_y);
		bool IsMouseWheelUp() const;
		bool IsMouseWheelDown() const;
		void ProcessInputEvents() override;
		virtual void SetMousePosition(const int x,const int y) = 0;
	protected:
		void MousePositionUpdate(const int x,const int y);
		void AddMouseWheelEventUp();
		void AddMouseWheelEventDown();
		void MapInputNames() override;
	private:
		enum class MouseWheel
		{
			None,
			Up,
			Down,
		};
		int x{};
		int y{};
		float resolution_ratio_x{1.0f};
		float resolution_ratio_y{1.0f};
		MouseWheel mouse_wheel;
		std::queue<MouseWheel> mouse_wheel_events;
		void ProcessMouseWheelEvents();
	};
}

#endif
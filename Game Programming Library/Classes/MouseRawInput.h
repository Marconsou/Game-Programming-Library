#ifndef MOUSERAWINPUT_H
#define MOUSERAWINPUT_H

#include <Windows.h>
#include "Log.h"
#include "Mouse.h"

namespace GPL
{
	class MouseRawInput : public Mouse
	{
	public:
		void RegisterMouseRawInput(const HWND& handle_window);
		void OnWMInput(const RAWMOUSE& raw_mouse);
		void SetMousePosition(const int x,const int y) override;
	private:
		std::vector<std::tuple<int,MouseButton>> ri_mouse_button;
		const HWND* pointer_handle_window{};
		POINT GetMousePosition() const;
		bool IsOutsideClientArea(const POINT& point) const;
		void MouseWheelUpdate(const RAWMOUSE& raw_mouse);
		void MouseButtonsUpdate(const RAWMOUSE& raw_mouse);
	};
}

#endif
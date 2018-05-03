#include "MouseRawInput.h"

using namespace std;
using namespace GPL;

void MouseRawInput::SetMousePosition(const int x,const int y)
{
	POINT point{x,y};
	if (!ClientToScreen(*this->pointer_handle_window,&point))
		Log::Error(__FUNCTION__,"ClientToScreen");

	if (!SetCursorPos(point.x,point.y))
		Log::Error(__FUNCTION__,"SetCursorPos");
}

void MouseRawInput::RegisterMouseRawInput(const HWND& handle_window)
{
	RAWINPUTDEVICE raw_input_device;
	raw_input_device.usUsagePage = 1;
	raw_input_device.usUsage = 2;
	raw_input_device.dwFlags = 0;
	raw_input_device.hwndTarget = handle_window;

	if (!RegisterRawInputDevices(&raw_input_device,1,sizeof(raw_input_device)))
		Log::Error(__FUNCTION__,"RegisterRawInputDevices");

	this->pointer_handle_window = &handle_window;

	this->ri_mouse_button.push_back(make_tuple(RI_MOUSE_LEFT_BUTTON_DOWN,MouseButton::Left));
	this->ri_mouse_button.push_back(make_tuple(RI_MOUSE_LEFT_BUTTON_UP,MouseButton::Left));
	this->ri_mouse_button.push_back(make_tuple(RI_MOUSE_RIGHT_BUTTON_DOWN,MouseButton::Right));
	this->ri_mouse_button.push_back(make_tuple(RI_MOUSE_RIGHT_BUTTON_UP,MouseButton::Right));
	this->ri_mouse_button.push_back(make_tuple(RI_MOUSE_MIDDLE_BUTTON_DOWN,MouseButton::Middle));
	this->ri_mouse_button.push_back(make_tuple(RI_MOUSE_MIDDLE_BUTTON_UP,MouseButton::Middle));
	this->ri_mouse_button.push_back(make_tuple(RI_MOUSE_BUTTON_4_DOWN,MouseButton::XButton1));
	this->ri_mouse_button.push_back(make_tuple(RI_MOUSE_BUTTON_4_UP,MouseButton::XButton1));
	this->ri_mouse_button.push_back(make_tuple(RI_MOUSE_BUTTON_5_DOWN,MouseButton::XButton2));
	this->ri_mouse_button.push_back(make_tuple(RI_MOUSE_BUTTON_5_UP,MouseButton::XButton2));
}

POINT MouseRawInput::GetMousePosition() const
{
	POINT point;
	if (!GetCursorPos(&point))
		Log::Error(__FUNCTION__,"GetCursorPos");

	if (!ScreenToClient(*this->pointer_handle_window,&point))
		Log::Error(__FUNCTION__,"ScreenToClient");

	return point;
}

bool MouseRawInput::IsOutsideClientArea(const POINT& point) const
{
	RECT rect;
	if (!GetClientRect(*this->pointer_handle_window,&rect))
		Log::Error(__FUNCTION__,"GetClientRect");

	return ((point.x < rect.left) || (point.x > rect.right) || (point.y < rect.top) || (point.y > rect.bottom));
}

void MouseRawInput::MouseWheelUpdate(const RAWMOUSE& raw_mouse)
{
	if (raw_mouse.usButtonFlags & RI_MOUSE_WHEEL)
	{
		const short mouse_wheel = static_cast<short>(raw_mouse.usButtonData);

		if (mouse_wheel > 0)
			this->AddMouseWheelEventUp();

		else if (mouse_wheel < 0)
			this->AddMouseWheelEventDown();
	}
}

void MouseRawInput::MouseButtonsUpdate(const RAWMOUSE& raw_mouse)
{
	for (size_t i = 0; i < this->ri_mouse_button.size(); i++)
	{
		const std::tuple<int,MouseButton>& iterator = this->ri_mouse_button[i];

		int raw_input_value = get<0>(iterator);

		if (raw_mouse.ulButtons & raw_input_value)
		{
			const MouseButton mouse_button = get<1>(iterator);

			const bool is_down = (i % 2 == 0);

			if (is_down)
				this->AddInputEventPressedOnce(mouse_button);
			else
				this->AddInputEventReleasedOnce(mouse_button);
		}
	}
}

void MouseRawInput::OnWMInput(const RAWMOUSE& raw_mouse)
{
	if (this->pointer_handle_window)
	{
		const POINT point = this->GetMousePosition();

		this->MousePositionUpdate(point.x,point.y);

		if (!this->IsOutsideClientArea(point))
		{
			this->MouseWheelUpdate(raw_mouse);
			this->MouseButtonsUpdate(raw_mouse);
		}
		else
			this->ResetInputStates();
	}
}
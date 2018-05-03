#include "Mouse.h"

using namespace std;
using namespace GPL;

Mouse::Mouse() :
InputDevice(static_cast<size_t>(MouseButton::Max)),
mouse_wheel{}
{
	this->MapInputNames();
}

int Mouse::GetX() const
{
	return static_cast<int>(this->x * this->resolution_ratio_x);
}

int Mouse::GetY() const
{
	return static_cast<int>(this->y * this->resolution_ratio_y);
}

void Mouse::SetMouseResolutionRatio(const float resolution_ratio_x,const float resolution_ratio_y)
{
	this->resolution_ratio_x = resolution_ratio_x;
	this->resolution_ratio_y = resolution_ratio_y;
}

void Mouse::MousePositionUpdate(const int x,const int y)
{
	this->x = x;
	this->y = y;
}

void Mouse::AddMouseWheelEventUp()
{
	this->mouse_wheel_events.push(MouseWheel::Up);
}

void Mouse::AddMouseWheelEventDown()
{
	this->mouse_wheel_events.push(MouseWheel::Down);
}

bool Mouse::IsMouseWheelUp() const
{
	return ((this->GetEnabled()) && (this->mouse_wheel == MouseWheel::Up));
}

bool Mouse::IsMouseWheelDown() const
{
	return ((this->GetEnabled()) && (this->mouse_wheel == MouseWheel::Down));
}

void Mouse::ProcessInputEvents()
{
	InputDevice::ProcessInputEvents();
	this->ProcessMouseWheelEvents();
}

void Mouse::ProcessMouseWheelEvents()
{
	queue<MouseWheel> new_mouse_wheel_events;

	while (!this->mouse_wheel_events.empty())
	{
		this->mouse_wheel = this->mouse_wheel_events.front();

		if ((this->IsMouseWheelUp()) || (this->IsMouseWheelDown()))
			new_mouse_wheel_events.push(MouseWheel::None);

		this->mouse_wheel_events.pop();
	}
	this->mouse_wheel_events = new_mouse_wheel_events;
}

void Mouse::MapInputNames()
{
	this->AddInputName(MouseButton::Unknown,"Unknown");
	this->AddInputName(MouseButton::Left,"Left");
	this->AddInputName(MouseButton::Right,"Right");
	this->AddInputName(MouseButton::Middle,"Middle");
	this->AddInputName(MouseButton::XButton1,"XButton-1");
	this->AddInputName(MouseButton::XButton2,"XButton-2");
}
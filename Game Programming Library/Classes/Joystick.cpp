#include "Joystick.h"

using namespace std;
using namespace GPL;

Joystick::Joystick() :
InputDevice(static_cast<size_t>(JoystickButton::Max)),
pov_horizontal{},
pov_vertical{}
{
	this->MapInputNames();
}

int Joystick::GetAxisRange() const
{
	return this->axis_range;
}

void Joystick::DataUpdate(const int x_axis,const int y_axis,const int z_axis,const int z_axis_rotation,const int pov,const bool right,const bool left,const bool up,const bool down)
{
	this->x_axis = x_axis;
	this->y_axis = y_axis;
	this->z_axis = z_axis;
	this->z_axis_rotation = z_axis_rotation;
	this->pov = pov;
	this->pov_horizontal = ((left) ? POVHorizontal::Left : (right) ? POVHorizontal::Right : POVHorizontal::None);
	this->pov_vertical = ((up) ? POVVertical::Up : (down) ? POVVertical::Down : POVVertical::None);
}

bool Joystick::IsJoystickXAxisUp() const
{
	return ((this->GetEnabled()) && (this->CheckDeadzone(this->x_axis) > 0));
}

bool Joystick::IsJoystickXAxisDown() const
{
	return ((this->GetEnabled()) && (this->CheckDeadzone(this->x_axis) < 0));
}

bool Joystick::IsJoystickYAxisUp() const
{
	return ((this->GetEnabled()) && (this->CheckDeadzone(this->y_axis) > 0));
}

bool Joystick::IsJoystickYAxisDown() const
{
	return ((this->GetEnabled()) && (this->CheckDeadzone(this->y_axis) < 0));
}

bool Joystick::IsJoystickZAxisUp() const
{
	return ((this->GetEnabled()) && (this->CheckDeadzone(this->z_axis) > 0));
}

bool Joystick::IsJoystickZAxisDown() const
{
	return ((this->GetEnabled()) && (this->CheckDeadzone(this->z_axis) < 0));
}

bool Joystick::IsJoystickZAxisRotationUp() const
{
	return ((this->GetEnabled()) && (this->CheckDeadzone(this->z_axis_rotation) > 0));
}

bool Joystick::IsJoystickZAxisRotationDown() const
{
	return ((this->GetEnabled()) && (this->CheckDeadzone(this->z_axis_rotation) < 0));
}

bool Joystick::IsJoystickPOVRight() const
{
	return ((this->GetEnabled()) && (this->pov_horizontal == POVHorizontal::Right));
}

bool Joystick::IsJoystickPOVLeft() const
{
	return ((this->GetEnabled()) && (this->pov_horizontal == POVHorizontal::Left));
}

bool Joystick::IsJoystickPOVUp() const
{
	return ((this->GetEnabled()) && (this->pov_vertical == POVVertical::Up));
}

bool Joystick::IsJoystickPOVDown() const
{
	return ((this->GetEnabled()) && (this->pov_vertical == POVVertical::Down));
}

int Joystick::CheckDeadzone(const int axis) const
{
	return (abs(axis) < this->deadzone ? 0 : axis);
}

void Joystick::MapInputNames()
{
	this->AddInputName(JoystickButton::Unknown,"Unknown");
	this->AddInputName(JoystickButton::Button01,"Button-01");
	this->AddInputName(JoystickButton::Button02,"Button-02");
	this->AddInputName(JoystickButton::Button03,"Button-03");
	this->AddInputName(JoystickButton::Button04,"Button-04");
	this->AddInputName(JoystickButton::Button05,"Button-05");
	this->AddInputName(JoystickButton::Button06,"Button-06");
	this->AddInputName(JoystickButton::Button07,"Button-07");
	this->AddInputName(JoystickButton::Button08,"Button-08");
	this->AddInputName(JoystickButton::Button09,"Button-09");
	this->AddInputName(JoystickButton::Button10,"Button-10");
	this->AddInputName(JoystickButton::Button11,"Button-11");
	this->AddInputName(JoystickButton::Button12,"Button-12");
	this->AddInputName(JoystickButton::Button13,"Button-13");
	this->AddInputName(JoystickButton::Button14,"Button-14");
	this->AddInputName(JoystickButton::Button15,"Button-15");
	this->AddInputName(JoystickButton::Button16,"Button-16");
}
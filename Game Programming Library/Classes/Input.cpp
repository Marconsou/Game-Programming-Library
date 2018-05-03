#include "Input.h"

using namespace std;
using namespace GPL;

Input::Input(unique_ptr<Keyboard>&& keyboard,unique_ptr<Mouse>&& mouse,unique_ptr<Joystick>&& joystick) :
keyboard(move(keyboard)),
mouse(move(mouse)),
joystick(move(joystick))
{

}

unique_ptr<Keyboard>& Input::GetKeyboard()
{
	return this->keyboard;
}

unique_ptr<Mouse>& Input::GetMouse()
{
	return this->mouse;
}

unique_ptr<Joystick>& Input::GetJoystick()
{
	return this->joystick;
}

const string& Input::GetKeyboardKeyName(const KeyboardKey keyboard_key) const
{
	return this->keyboard->GetInputName(keyboard_key);
}

const string& Input::GetMouseButtonName(const MouseButton mouse_button) const
{
	return this->mouse->GetInputName(mouse_button);
}

const string& Input::GetJoystickButtonName(const JoystickButton joystick_button) const
{
	return this->joystick->GetInputName(joystick_button);
}

size_t Input::GetLastCharacterTyped() const
{
	return this->keyboard->GetLastCharacterTyped();
}

int Input::GetMouseX() const
{
	return this->mouse->GetX();
}

int Input::GetMouseY() const
{
	return this->mouse->GetY();
}

void Input::SetMousePosition(const int x,const int y)
{
	this->mouse->SetMousePosition(x,y);
}

void Input::SetMouseResolutionRatio(const float resolution_ratio_x,const float resolution_ratio_y)
{
	this->mouse->SetMouseResolutionRatio(resolution_ratio_x,resolution_ratio_y);
}

void Input::ProcessInput()
{
	if (this->keyboard)
		this->keyboard->ProcessInputEvents();

	if (this->mouse)
		this->mouse->ProcessInputEvents();

	if (this->joystick)
		this->joystick->ProcessInputEvents();
}

void Input::ResetInputStates()
{
	if (this->keyboard)
		this->keyboard->ResetInputStates();

	if (this->mouse)
		this->mouse->ResetInputStates();

	if (this->joystick)
		this->joystick->ResetInputStates();
}

bool Input::IsKeyboardKeyPressed(const KeyboardKey keyboard_key) const
{
	return this->keyboard->IsInputPressed(keyboard_key);
}

bool Input::IsKeyboardKeyPressedOnce(const KeyboardKey keyboard_key) const
{
	return this->keyboard->IsInputPressedOnce(keyboard_key);
}

bool Input::IsKeyboardKeyReleasedOnce(const KeyboardKey keyboard_key) const
{
	return this->keyboard->IsInputReleasedOnce(keyboard_key);
}

KeyboardKey Input::IsAnyKeyboardKeyPressed() const
{
	return this->keyboard->IsAnyInputPressed();
}

KeyboardKey Input::IsAnyKeyboardKeyPressedOnce() const
{
	return this->keyboard->IsAnyInputPressedOnce();
}

bool Input::IsMouseButtonPressed(const MouseButton mouse_button) const
{
	return this->mouse->IsInputPressed(mouse_button);
}

bool Input::IsMouseButtonPressedOnce(const MouseButton mouse_button) const
{
	return this->mouse->IsInputPressedOnce(mouse_button);
}

bool Input::IsMouseButtonReleasedOnce(const MouseButton mouse_button) const
{
	return this->mouse->IsInputReleasedOnce(mouse_button);
}

MouseButton Input::IsAnyMouseButtonPressed() const
{
	return this->mouse->IsAnyInputPressed();
}

MouseButton Input::IsAnyMouseButtonPressedOnce() const
{
	return this->mouse->IsAnyInputPressedOnce();
}

bool Input::IsMouseWheelUp() const
{
	return this->mouse->IsMouseWheelUp();
}

bool Input::IsMouseWheelDown() const
{
	return this->mouse->IsMouseWheelDown();
}

bool Input::IsJoystickButtonPressed(const JoystickButton joystick_button) const
{
	return this->joystick->IsInputPressed(joystick_button);
}

bool Input::IsJoystickButtonPressedOnce(const JoystickButton joystick_button) const
{
	return this->joystick->IsInputPressedOnce(joystick_button);
}

bool Input::IsJoystickButtonReleasedOnce(const JoystickButton joystick_button) const
{
	return this->joystick->IsInputReleasedOnce(joystick_button);
}

JoystickButton Input::IsAnyJoystickButtonPressed() const
{
	return this->joystick->IsAnyInputPressed();
}

JoystickButton Input::IsAnyJoystickButtonPressedOnce() const
{
	return this->joystick->IsAnyInputPressedOnce();
}

bool Input::IsJoystickXAxisUp() const
{
	return this->joystick->IsJoystickXAxisUp();
}

bool Input::IsJoystickXAxisDown() const
{
	return this->joystick->IsJoystickXAxisDown();
}

bool Input::IsJoystickYAxisUp() const
{
	return this->joystick->IsJoystickYAxisUp();
}

bool Input::IsJoystickYAxisDown() const
{
	return this->joystick->IsJoystickYAxisDown();
}

bool Input::IsJoystickZAxisUp() const
{
	return this->joystick->IsJoystickZAxisUp();
}

bool Input::IsJoystickZAxisDown() const
{
	return this->joystick->IsJoystickZAxisDown();
}

bool Input::IsJoystickZAxisRotationUp() const
{
	return this->joystick->IsJoystickZAxisRotationUp();
}

bool Input::IsJoystickZAxisRotationDown() const
{
	return this->joystick->IsJoystickZAxisRotationDown();
}

bool Input::IsJoystickPOVRight() const
{
	return this->joystick->IsJoystickPOVRight();
}

bool Input::IsJoystickPOVLeft() const
{
	return this->joystick->IsJoystickPOVLeft();
}

bool Input::IsJoystickPOVUp() const
{
	return this->joystick->IsJoystickPOVUp();
}

bool Input::IsJoystickPOVDown() const
{
	return this->joystick->IsJoystickPOVDown();
}

bool Input::IsKeyboardKeyUnknown(const KeyboardKey keyboard_key)
{
	return (keyboard_key == KeyboardKey::Unknown);
}

bool Input::IsMouseButtonUnknown(const MouseButton mouse_button)
{
	return (mouse_button == MouseButton::Unknown);
}

bool Input::IsJoystickButtonUnknown(const JoystickButton joystick_button)
{
	return (joystick_button == JoystickButton::Unknown);
}
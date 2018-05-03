#ifndef INPUT_H
#define INPUT_H

#include <memory>
#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"
#include "BuildDLL.h"

namespace GPL
{
	class Input
	{
	public:
		Input(std::unique_ptr<Keyboard>&& keyboard,std::unique_ptr<Mouse>&& mouse,std::unique_ptr<Joystick>&& joystick);
		virtual ~Input() = 0 {};
		const std::string& GetKeyboardKeyName(const KeyboardKey keyboard_key) const;
		const std::string& GetMouseButtonName(const MouseButton mouse_button) const;
		const std::string& GetJoystickButtonName(const JoystickButton joystick_button) const;
		size_t GetLastCharacterTyped() const;
		GPL_DLL int GetMouseX() const;
		GPL_DLL int GetMouseY() const;
		GPL_DLL void SetMousePosition(const int x,const int y);
		void SetMouseResolutionRatio(const float resolution_ratio_x,const float resolution_ratio_y);
		void ProcessInput();
		void ResetInputStates();
		GPL_DLL bool IsKeyboardKeyPressed(const KeyboardKey keyboard_key) const;
		GPL_DLL bool IsKeyboardKeyPressedOnce(const KeyboardKey keyboard_key) const;
		GPL_DLL bool IsKeyboardKeyReleasedOnce(const KeyboardKey keyboard_key) const;
		GPL_DLL KeyboardKey IsAnyKeyboardKeyPressed() const;
		GPL_DLL KeyboardKey IsAnyKeyboardKeyPressedOnce() const;
		GPL_DLL bool IsMouseButtonPressed(const MouseButton mouse_button) const;
		GPL_DLL bool IsMouseButtonPressedOnce(const MouseButton mouse_button) const;
		GPL_DLL bool IsMouseButtonReleasedOnce(const MouseButton mouse_button) const;
		GPL_DLL MouseButton IsAnyMouseButtonPressed() const;
		GPL_DLL MouseButton IsAnyMouseButtonPressedOnce() const;
		GPL_DLL bool IsMouseWheelUp() const;
		GPL_DLL bool IsMouseWheelDown() const;
		GPL_DLL bool IsJoystickButtonPressed(const JoystickButton joystick_button) const;
		GPL_DLL bool IsJoystickButtonPressedOnce(const JoystickButton joystick_button) const;
		GPL_DLL bool IsJoystickButtonReleasedOnce(const JoystickButton joystick_button) const;
		GPL_DLL JoystickButton IsAnyJoystickButtonPressed() const;
		GPL_DLL JoystickButton IsAnyJoystickButtonPressedOnce() const;
		GPL_DLL bool IsJoystickXAxisUp() const;
		GPL_DLL bool IsJoystickXAxisDown() const;
		GPL_DLL bool IsJoystickYAxisUp() const;
		GPL_DLL bool IsJoystickYAxisDown() const;
		GPL_DLL bool IsJoystickZAxisUp() const;
		GPL_DLL bool IsJoystickZAxisDown() const;
		GPL_DLL bool IsJoystickZAxisRotationUp() const;
		GPL_DLL bool IsJoystickZAxisRotationDown() const;
		GPL_DLL bool IsJoystickPOVRight() const;
		GPL_DLL bool IsJoystickPOVLeft() const;
		GPL_DLL bool IsJoystickPOVUp() const;
		GPL_DLL bool IsJoystickPOVDown() const;
		GPL_DLL static bool IsKeyboardKeyUnknown(const KeyboardKey keyboard_key);
		GPL_DLL static bool IsMouseButtonUnknown(const MouseButton mouse_button);
		GPL_DLL static bool IsJoystickButtonUnknown(const JoystickButton joystick_button);
	protected:
		std::unique_ptr<Keyboard>& GetKeyboard();
		std::unique_ptr<Mouse>& GetMouse();
		std::unique_ptr<Joystick>& GetJoystick();
	private:
		std::unique_ptr<Keyboard> keyboard;
		std::unique_ptr<Mouse> mouse;
		std::unique_ptr<Joystick> joystick;
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;
	};
}

#endif
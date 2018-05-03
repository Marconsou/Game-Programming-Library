#ifndef JOYSTICKDIRECTINPUT_H
#define JOYSTICKDIRECTINPUT_H

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <atlbase.h>
#include "Log.h"
#include "Joystick.h"

namespace GPL
{
	class JoystickDirectInput : public Joystick
	{
	public:
		~JoystickDirectInput();
		void CreateJoystickDirectInput(const HWND& handle_window,const CComPtr<IDirectInput8>& direct_input);
		void Acquire() const;
		void PollDeviceState();
	protected:
		void ProcessInputEvents() override;
	private:
		enum class POV
		{
			None = -1,
			Up = 0,
			UpRight = 4500,
			Right = 9000,
			RightDown = 13500,
			Down = 18000,
			DownLeft = 22500,
			Left = 27000,
			LeftUp = 31500,
		};
		CComPtr<IDirectInputDevice8> direct_input_device_joystick;
		IDirectInput8* pointer_direct_input{};
		static BOOL CALLBACK DIEnumDevicesCallback(LPCDIDEVICEINSTANCE lpddi,LPVOID pvRef);
		static BOOL CALLBACK DIEnumDeviceObjectsCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi,LPVOID pvRef);
	};
}

#endif
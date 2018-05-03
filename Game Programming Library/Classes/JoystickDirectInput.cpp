#include "JoystickDirectInput.h"

using namespace std;
using namespace GPL;

JoystickDirectInput::~JoystickDirectInput()
{
	if (this->direct_input_device_joystick)
	{
		if (FAILED(this->direct_input_device_joystick->Unacquire()))
			Log::Warning(__FUNCTION__,"Unacquire");
	}
}

void JoystickDirectInput::Acquire() const
{
	if (this->direct_input_device_joystick)
		this->direct_input_device_joystick->Acquire();
}

void JoystickDirectInput::ProcessInputEvents()
{
	this->PollDeviceState();
	Joystick::ProcessInputEvents();
}

void JoystickDirectInput::CreateJoystickDirectInput(const HWND& handle_window,const CComPtr<IDirectInput8>& direct_input)
{
	//DirectInput já deve estar pelo menos criado
	if ((direct_input) && (!this->direct_input_device_joystick))
	{
		this->pointer_direct_input = direct_input;

		if (FAILED(this->pointer_direct_input->EnumDevices(DI8DEVCLASS_GAMECTRL,JoystickDirectInput::DIEnumDevicesCallback,this,DIEDFL_ATTACHEDONLY)))
			Log::Error(__FUNCTION__,"EnumDevices");

		//Existe a possibilidade do Joystick não estar plugado neste momento
		if (this->direct_input_device_joystick)
		{
			if (FAILED(this->direct_input_device_joystick->SetDataFormat(&c_dfDIJoystick2)))
				Log::Error(__FUNCTION__,"SetDataFormat");

			if (FAILED(this->direct_input_device_joystick->SetCooperativeLevel(handle_window,DISCL_EXCLUSIVE | DISCL_FOREGROUND)))
				Log::Error(__FUNCTION__,"SetCooperativeLevel");

			if (FAILED(this->direct_input_device_joystick->EnumObjects(JoystickDirectInput::DIEnumDeviceObjectsCallback,this,DIDFT_ALL)))
				Log::Error(__FUNCTION__,"EnumObjects");
		}
	}
}

BOOL CALLBACK JoystickDirectInput::DIEnumDevicesCallback(LPCDIDEVICEINSTANCE lpddi,LPVOID pvRef)
{
	JoystickDirectInput* joystick_direct_input = reinterpret_cast<JoystickDirectInput*>(pvRef);

	//Obter o primeiro Joystick
	if (FAILED(joystick_direct_input->pointer_direct_input->CreateDevice(lpddi->guidInstance,&joystick_direct_input->direct_input_device_joystick,nullptr)))
		return DIENUM_CONTINUE;

	return DIENUM_STOP;
}

BOOL CALLBACK JoystickDirectInput::DIEnumDeviceObjectsCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi,LPVOID pvRef)
{
	JoystickDirectInput* joystick_direct_input = reinterpret_cast<JoystickDirectInput*>(pvRef);

	//Para cada objeto Axis
	if (lpddoi->dwType & DIDFT_AXIS)
	{
		DIPROPRANGE di_prop_range;
		di_prop_range.diph.dwSize = sizeof(DIPROPRANGE);
		di_prop_range.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		di_prop_range.diph.dwHow = DIPH_BYID;
		di_prop_range.diph.dwObj = lpddoi->dwType;
		di_prop_range.lMin = -joystick_direct_input->GetAxisRange();
		di_prop_range.lMax = +joystick_direct_input->GetAxisRange();

		if (FAILED(joystick_direct_input->direct_input_device_joystick->SetProperty(DIPROP_RANGE,&di_prop_range.diph)))
			return DIENUM_STOP;
	}

	return DIENUM_CONTINUE;
}

void JoystickDirectInput::PollDeviceState()
{
	if (this->direct_input_device_joystick)
	{
		if (FAILED(this->direct_input_device_joystick->Poll()))
		{
			while (this->direct_input_device_joystick->Acquire() == DIERR_INPUTLOST) {}
		}

		DIJOYSTATE2 di_joystate_2;
		if (SUCCEEDED(this->direct_input_device_joystick->GetDeviceState(sizeof(DIJOYSTATE2),&di_joystate_2)))
		{
			static int last_pov = static_cast<int>(POV::None);

			const int x_axis = di_joystate_2.lX;
			const int y_axis = di_joystate_2.lY;
			const int z_axis = di_joystate_2.lZ;
			const int z_axis_rotation = di_joystate_2.lRz;
			int pov = di_joystate_2.rgdwPOV[0];

			//Desabilitar disparo contínuo dos direcionais
			if (pov == last_pov)
			{
				pov = static_cast<int>(POV::None);
			}
			else
			{
				last_pov = pov;
			}

			const bool up = ((pov == static_cast<int>(POV::LeftUp)) || (pov == static_cast<int>(POV::Up)) || (pov == static_cast<int>(POV::UpRight)));
			const bool right = ((pov == static_cast<int>(POV::UpRight)) || (pov == static_cast<int>(POV::Right)) || (pov == static_cast<int>(POV::RightDown)));
			const bool down = ((pov == static_cast<int>(POV::RightDown)) || (pov == static_cast<int>(POV::Down)) || (pov == static_cast<int>(POV::DownLeft)));
			const bool left = ((pov == static_cast<int>(POV::DownLeft)) || (pov == static_cast<int>(POV::Left)) || (pov == static_cast<int>(POV::LeftUp)));

			this->DataUpdate(x_axis,y_axis,z_axis,z_axis_rotation,pov,right,left,up,down);

			const int size = static_cast<size_t>(JoystickButton::Max) - 1;
			for (int i = 0; i < size; i++)
			{
				int button_pressed = (di_joystate_2.rgbButtons[i] & 0x80);
				JoystickButton joystick_button = static_cast<JoystickButton>(i + 1);

				if (button_pressed)
				{
					if ((this->IsInputStateReleased(joystick_button)) || (this->IsInputStateReleasedOnce(joystick_button)))
						this->AddInputEventPressedOnce(joystick_button);
				}
				else
				{
					if ((this->IsInputStatePressed(joystick_button)) || (this->IsInputStatePressedOnce(joystick_button)))
						this->AddInputEventReleasedOnce(joystick_button);
				}
			}
		}
	}
}
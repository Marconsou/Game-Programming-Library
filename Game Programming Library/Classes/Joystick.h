#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "InputDevice.h"

namespace GPL
{
	enum class JoystickButton
	{
		Unknown,
		Button01,
		Button02,
		Button03,
		Button04,
		Button05,
		Button06,
		Button07,
		Button08,
		Button09,
		Button10,
		Button11,
		Button12,
		Button13,
		Button14,
		Button15,
		Button16,
		Max,
	};

	class Joystick : public InputDevice<JoystickButton>
	{
	public:
		Joystick();
		virtual ~Joystick() = 0 {};
		bool IsJoystickXAxisUp() const;
		bool IsJoystickXAxisDown() const;
		bool IsJoystickYAxisUp() const;
		bool IsJoystickYAxisDown() const;
		bool IsJoystickZAxisUp() const;
		bool IsJoystickZAxisDown() const;
		bool IsJoystickZAxisRotationUp() const;
		bool IsJoystickZAxisRotationDown() const;
		bool IsJoystickPOVRight() const;
		bool IsJoystickPOVLeft() const;
		bool IsJoystickPOVUp() const;
		bool IsJoystickPOVDown() const;
	protected:
		int GetAxisRange() const;
		void DataUpdate(const int x_axis,const int y_axis,const int z_axis,const int z_axis_rotation,const int pov,const bool right,const bool left,const bool up,const bool down);
		void MapInputNames() override;
	private:
		enum class POVHorizontal
		{
			None,
			Right,
			Left,
		};
		enum class POVVertical
		{
			None,
			Up,
			Down,
		};
		int x_axis{};
		int y_axis{};
		int z_axis{};
		int z_axis_rotation{};
		int pov{};
		const int axis_range{1000};
		const int deadzone{static_cast<int>(axis_range * 0.2f)};
		POVHorizontal pov_horizontal;
		POVVertical pov_vertical;
		int CheckDeadzone(const int axis) const;
	};
}

#endif
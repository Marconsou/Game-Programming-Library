#ifndef CONTROL_H
#define CONTROL_H

#include "Rect.h"
#include "Signal.h"
#include "Input.h"

namespace GPL
{
	class Video;
	class Timer;

	class Control
	{
	public:
		GPL_DLL Control();
		GPL_DLL virtual ~Control();
		GPL_DLL void SetEnabled(const bool enabled);
		GPL_DLL bool GetEnabled() const;
		GPL_DLL void SetVisible(const bool visible);
		GPL_DLL bool GetVisible() const;
		GPL_DLL float GetX() const;
		GPL_DLL float GetY() const;
		GPL_DLL float GetW() const;
		GPL_DLL float GetH() const;
		GPL_DLL void EnableOnMouseClickRight();
		GPL_DLL void EnableOnMouseClickMiddle();
		GPL_DLL void DisableOnMouseClickRight();
		GPL_DLL void DisableOnMouseClickMiddle();
		GPL_DLL bool IsControlFocused();
		GPL_DLL bool IsRemoved() const;
		GPL_DLL void GainFocus(const bool focus);
		GPL_DLL void PerformClick();

		template<class Event,class Object>
		void AddEventOnClick(const Event& event,Object& object)
		{
			this->on_click.Add(event,object,std::placeholders::_1);
		}

		template<class Event,class Object>
		void AddEventOnEnter(const Event& event,Object& object)
		{
			this->on_enter.Add(event,object,std::placeholders::_1);
		}

		template<class Event,class Object>
		void AddEventOnLeave(const Event& event,Object& object)
		{
			this->on_leave.Add(event,object,std::placeholders::_1);
		}

		template<class Event,class Object>
		void AddEventOnEnabledChanged(const Event& event,Object& object)
		{
			this->on_enabled_changed.Add(event,object,std::placeholders::_1);
		}

		template<class Event,class Object>
		void AddEventOnMouseEnter(const Event& event,Object& object)
		{
			this->on_mouse_enter.Add(event,object,std::placeholders::_1);
		}

		template<class Event,class Object>
		void AddEventOnMouseHover(const Event& event,Object& object)
		{
			this->on_mouse_hover.Add(event,object,std::placeholders::_1);
		}

		template<class Event,class Object>
		void AddEventOnMouseLeave(const Event& event,Object& object)
		{
			this->on_mouse_leave.Add(event,object,std::placeholders::_1);
		}

		template<class Event,class Object>
		void AddEventOnRemove(const Event& event,Object& object)
		{
			this->on_remove.Add(event,object,std::placeholders::_1);
		}

		template<class Event,class Object>
		void AddEventOnKeyUp(const Event& event,Object& object)
		{
			this->on_key_up.Add(event,object,std::placeholders::_1,std::placeholders::_2);
		}

		template<class Event,class Object>
		void AddEventOnKeyDown(const Event& event,Object& object)
		{
			this->on_key_down.Add(event,object,std::placeholders::_1,std::placeholders::_2);
		}

		template<class Event,class Object>
		void AddEventOnMouseClick(const Event& event,Object& object)
		{
			this->on_mouse_click.Add(event,object,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
		}

		template<class Event,class Object>
		void AddEventOnMouseUp(const Event& event,Object& object)
		{
			this->on_mouse_up.Add(event,object,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
		}

		template<class Event,class Object>
		void AddEventOnMouseDown(const Event& event,Object& object)
		{
			this->on_mouse_down.Add(event,object,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
		}

		GPL_DLL virtual void SetPosition(const float x,const float y,const bool centralize = false);
		GPL_DLL virtual void AddControl();
		GPL_DLL virtual void RemoveControl();
		GPL_DLL static bool AnyControlFocused();
		GPL_DLL static bool AnyControlMouseHovered();
		GPL_DLL static void ProcessEvents(const Input& input,const Timer& timer);
		GPL_DLL static void ShowControls(const Input& input,Video& video,const Timer& timer);
	protected:
		GPL_DLL Rect<float>& GetRect();
		GPL_DLL bool GetMouseHover() const;
		GPL_DLL void SetDataUpdate(const bool data_update);
		GPL_DLL bool GetDataUpdate() const;

		template<typename Type>
		void CheckForDataUpdate(const Type& value_old,const Type& value_new)
		{
			if (value_old != value_new)
				this->data_update = true;
		}

		GPL_DLL virtual void CheckForSpecificEvents();
		static Control& GetControlFocused();
	private:
		using Event = Signal<void,Control&>;
		using KeyboardEvent = Signal<void,Control&,const KeyboardKey>;
		using MouseEvent = Signal<void,Control&,const MouseButton,const float,const float>;

		struct ControlState
		{
			Control* control{};
			bool copy_of_enabled{true};
			MouseButton mouse_button;
			KeyboardKey keyboard_key;
			ControlState(Control& control) :
				control(&control),
				keyboard_key(KeyboardKey::Unknown),
				mouse_button(MouseButton::Unknown) {}
			ControlState& operator=(const ControlState&) = delete;
		};

		bool enabled{true};
		bool visible{true};
		bool mouse_hover{};
		bool on_key_down_triggered{};
		bool on_mouse_down_triggered{};
		bool enable_on_mouse_click_right{};
		bool enable_on_mouse_click_middle{};
		bool data_update{true};
		Rect<float> rect;
		Event on_click;
		Event on_enter;
		Event on_leave;
		Event on_enabled_changed;
		Event on_mouse_enter;
		Event on_mouse_hover;
		Event on_mouse_leave;
		Event on_remove;
		KeyboardEvent on_key_up;
		KeyboardEvent on_key_down;
		MouseEvent on_mouse_click;
		MouseEvent on_mouse_up;
		MouseEvent on_mouse_down;
		static bool iterator_erased;
		static std::list<ControlState>::iterator iterator;
		static Control* control_focused;
		static const Control* control_mouse_hovered;
		static std::list<ControlState> control_states;
		Control(const Control&) = delete;
		Control& operator=(const Control&) = delete;
		bool CheckMouseClickAvailability(const MouseButton mouse_button) const;
		GPL_DLL virtual KeyboardKey GetKeyboardKeyShortcut() const;
		GPL_DLL virtual bool IsHighPriorityControl() const;
		GPL_DLL virtual void ShowAdditionalContent(const Input& input,Video& video,const Timer& timer);
		GPL_DLL virtual void Update(const Input& input,const Timer& timer);
		GPL_DLL virtual bool Show(const Input& input,Video& video,const Timer& timer) = 0;
		GPL_DLL virtual void OnEnabledChanged(const Control& control) = 0;
		static bool ControlGainFocus(Control& control);
		static bool ControlLoseFocus(Control& control);
		static void MouseHoverOnSomeControl(const Input& input);
		static bool CheckGainFocus(const MouseButton mouse_button_once,const bool skip_gain_focus_control);
		static void CheckLoseFocus(const MouseButton mouse_button_once);
		static void CheckOnEnabledChanged();
		static void CheckOnKeyUp(const KeyboardKey keyboard_key);
		static void CheckOnKeyDown(const KeyboardKey keyboard_key);
		static bool CheckOnMouseUp(const Input& input,const MouseButton mouse_button);
		static void CheckOnMouseDown(const Input& input,const MouseButton mouse_button);
		static void CheckOnMouseEnter();
		static void CheckOnMouseHover();
		static bool CheckOnClick(const Input& input,const bool on_mouse_up_triggered,const bool mouse_hover);
		static void CheckOnMouseClick(const Input& input,const bool on_mouse_up_triggered);
		static void CheckOnMouseLeave();
		static void CheckOnRemove(Control& control,const bool removing_from_destructor);
		static bool IsValidIterator();
	};
}

#endif
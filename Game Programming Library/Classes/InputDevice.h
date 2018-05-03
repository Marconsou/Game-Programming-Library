#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

#include <queue>
#include <unordered_map>

namespace GPL
{
	template<typename Type>
	class InputDevice
	{
	public:
		explicit InputDevice(const size_t input_state_size = 0) :
			input_states(input_state_size)	{}

		virtual ~InputDevice() = 0 {};

		const std::string& GetInputName(const Type id)
		{
			return this->input_name_map[id];
		}

		void EnableInput()
		{
			this->enabled = true;
		}

		void DisableInput()
		{
			this->enabled = false;
		}

		bool IsInputPressed(const Type input) const
		{
			return ((this->enabled) && (this->IsInputStatePressed(input) || this->IsInputStatePressedOnce(input)));
		}

		bool IsInputPressedOnce(const Type input) const
		{
			return ((this->enabled) && this->IsInputStatePressedOnce(input));
		}

		bool IsInputReleasedOnce(const Type input) const
		{
			return ((this->enabled) && this->IsInputStateReleasedOnce(input));
		}

		Type IsAnyInputPressed() const
		{
			Type input_state_index{};
			for (size_t i = 0; i < this->input_states.size(); i++)
			{
				const Type index = static_cast<Type>(i);
				if (this->IsInputStatePressed(index) || this->IsInputStatePressedOnce(index))
				{
					input_state_index = index;
					break;
				}
			}
			return input_state_index;
		}

		Type IsAnyInputPressedOnce() const
		{
			Type input_state_index{};
			for (size_t i = 0; i < this->input_states.size(); i++)
			{
				const Type index = static_cast<Type>(i);
				if (this->IsInputStatePressedOnce(index))
				{
					input_state_index = index;
					break;
				}
			}
			return input_state_index;
		}

		void ResetInputStates()
		{
			for (auto& iterator : this->input_states)
				iterator = InputState::Released;
		}

		virtual void ProcessInputEvents()
		{
			std::queue<std::tuple<Type,InputState>> new_input_events;

			while (!this->input_events.empty())
			{
				const std::tuple<Type,InputState>& input_event = this->input_events.front();

				Type input_type = std::get<0>(input_event);
				InputState input_state = std::get<1>(input_event);

				this->input_states[static_cast<size_t>(input_type)] = input_state;

				if (this->IsInputStatePressedOnce(input_type))
					new_input_events.push(std::make_tuple(input_type,InputState::Pressed));

				else if (this->IsInputStateReleasedOnce(input_type))
					new_input_events.push(std::make_tuple(input_type,InputState::Released));

				this->input_events.pop();
			}
			this->input_events = new_input_events;
		}
	protected:
		bool GetEnabled() const
		{
			return this->enabled;
		}

		void AddInputEventReleasedOnce(const Type input)
		{
			this->input_events.push(std::make_tuple(input,InputState::ReleasedOnce));
		}

		void AddInputEventPressedOnce(const Type input)
		{
			this->input_events.push(std::make_tuple(input,InputState::PressedOnce));
		}

		void AddInputName(const Type id,const std::string& value)
		{
			this->input_name_map.insert(std::pair<Type,std::string>(id,value));
		}

		bool IsInputStateReleased(const Type index) const
		{
			return (this->input_states[static_cast<size_t>(index)] == InputState::Released);
		}

		bool IsInputStateReleasedOnce(const Type index) const
		{
			return (this->input_states[static_cast<size_t>(index)] == InputState::ReleasedOnce);
		}

		bool IsInputStatePressed(const Type index) const
		{
			return (this->input_states[static_cast<size_t>(index)] == InputState::Pressed);
		}

		bool IsInputStatePressedOnce(const Type index) const
		{
			return (this->input_states[static_cast<size_t>(index)] == InputState::PressedOnce);
		}

		virtual void MapInputNames() = 0;
	private:
		enum class InputState
		{
			Released,
			ReleasedOnce,
			Pressed,
			PressedOnce,
		};
		bool enabled{true};
		std::vector<InputState> input_states;
		std::queue<std::tuple<Type,InputState>> input_events;
		std::unordered_map<Type,std::string> input_name_map;
		InputDevice(const InputDevice&) = delete;
		InputDevice& operator=(const InputDevice&) = delete;
	};
}

#endif
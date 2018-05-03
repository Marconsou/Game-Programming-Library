#ifndef APPLICATION_H
#define APPLICATION_H

#include "Signal.h"
#include "Input.h"

namespace GPL
{
	class Application
	{
	public:
		Application() = default;
		GPL_DLL virtual ~Application() = 0 {};
		GPL_DLL void SetShowCursor(const bool show_cursor);

		template<class Event,class Object> void AddEventOnActivating(const Event& event,Object& object)
		{ 
			this->on_activating.Add(event,object,std::placeholders::_1);
		}

		template<class Event,class Object> void AddEventOnInactivating(const Event& event,Object& object)
		{ 
			this->on_inactivating.Add(event,object,std::placeholders::_1);
		}

		GPL_DLL virtual void CreateApplication(std::unique_ptr<Input>& input,const std::string& title,const int application_width,const int application_height,const bool windowed,const int icon_id) = 0;
		GPL_DLL virtual void SetTitle(const std::string& title) const = 0;
		virtual bool IsActivated() const = 0;
		GPL_DLL virtual bool IsRunning() const = 0;
		GPL_DLL virtual void Quit() const = 0;
		virtual void ChangeApplicationSettings(const int application_width,const int application_height,const bool windowed,const int virtual_width,const int virtual_height) = 0;
		GPL_DLL virtual bool ProcessMessages() = 0;
	protected:
		bool GetShowCursor() const;
		void CheckApplicationState();
	private:
		bool show_cursor{};
		Signal<void,const Application&> on_activating;
		Signal<void,const Application&> on_inactivating;
		Application(const Application&) = delete;
		Application& operator=(const Application&) = delete;
	};
}

#endif
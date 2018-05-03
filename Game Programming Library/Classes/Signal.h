#ifndef SIGNAL_H
#define SIGNAL_H

#include <functional>
#include "SignalBase.h"

namespace GPL
{
	template<class Return,class... Args>
	class Signal : public SignalBase
	{
	private:
		using Slot = std::function<Return(Args...)>;
		std::list<Slot> callbacks;
	public:
		template<class Event,class Object,class... Placeholders> 
		void Add(const Event& event,Object& object,Placeholders... placeholders)
		{
			this->callbacks.push_back(std::bind(event,std::ref(object),placeholders...));
		}

		void Clear()
		{
			this->callbacks.clear();
		}

		void operator()(Args... args) const
		{
			if (!this->callbacks.empty())
				SignalBase::AddCurrentSignal(*this);

			for (auto& iterator = this->callbacks.begin(); iterator != this->callbacks.end(); /* iterator++ */)
			{
				auto& callback = *(iterator++);

				if (callback)
					callback(args...);

				//Se o próprio objeto foi removido durante as chamadas, parar a execução imediatamente
				if (!SignalBase::IsCurrentSignalAdded(*this))
					break;
			}

			SignalBase::RemoveCurrentSignal(*this);
		}
	};
}

#endif
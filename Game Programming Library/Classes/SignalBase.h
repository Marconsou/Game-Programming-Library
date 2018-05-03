#ifndef SIGNALBASE_H
#define SIGNALBASE_H

#include <list>
#include "BuildDLL.h"

namespace GPL
{
	class SignalBase
	{
	public:
		SignalBase() = default;
		virtual ~SignalBase() = 0
		{
			this->Remove();
		}
	protected:
		GPL_DLL static bool AddCurrentSignal(const SignalBase& current_signal);
		GPL_DLL static void RemoveCurrentSignal(const SignalBase& current_signal);
		GPL_DLL static bool IsCurrentSignalAdded(const SignalBase& current_signal);
	private:
		static std::list<const SignalBase*> current_signals;
		SignalBase(const SignalBase&) = delete;
		SignalBase& operator=(const SignalBase&) = delete;
		GPL_DLL void Remove() const;
	};
}

#endif
#include "SignalBase.h"

using namespace std;
using namespace GPL;

list<const SignalBase*> SignalBase::current_signals;

bool SignalBase::AddCurrentSignal(const SignalBase& current_signal)
{
	if (!SignalBase::IsCurrentSignalAdded(current_signal))
	{
		SignalBase::current_signals.push_back(&current_signal);
		return true;
	}
	return false;
}

void SignalBase::RemoveCurrentSignal(const SignalBase& current_signal)
{
	current_signal.Remove();
}

bool SignalBase::IsCurrentSignalAdded(const SignalBase& current_signal)
{
	return (find(SignalBase::current_signals.begin(),SignalBase::current_signals.end(),&current_signal) != SignalBase::current_signals.end());
}

void SignalBase::Remove() const
{
	SignalBase::current_signals.remove(this);
}
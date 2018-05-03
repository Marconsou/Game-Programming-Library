#include "Application.h"

using namespace GPL;

void Application::SetShowCursor(const bool show_cursor)
{
	this->show_cursor = show_cursor;
}

bool Application::GetShowCursor() const
{
	return this->show_cursor;
}

void Application::CheckApplicationState()
{
	static bool activating = true;
	static bool inactivating = true;

	if (this->IsActivated())
	{
		if (activating)
		{
			activating = false;
			inactivating = true;

			this->on_activating(*this);
		}
	}
	else
	{
		if (inactivating)
		{
			inactivating = false;
			activating = true;

			this->on_inactivating(*this);
		}
	}
}
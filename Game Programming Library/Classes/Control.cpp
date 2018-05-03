#include "Control.h"

using namespace std;
using namespace GPL;

bool Control::iterator_erased{};
list<Control::ControlState>::iterator Control::iterator;
Control* Control::control_focused{};
const Control* Control::control_mouse_hovered{};
list<Control::ControlState> Control::control_states;

Control::Control()
{
	this->AddEventOnEnabledChanged(&Control::OnEnabledChanged,*this);
}

Control::~Control()
{
	Control::CheckOnRemove(*this,true);
}

void Control::SetEnabled(const bool enabled)
{
	this->enabled = enabled;
}

bool Control::GetEnabled() const
{
	return this->enabled;
}

void Control::SetVisible(const bool visible)
{
	this->visible = visible;
}

bool Control::GetVisible() const
{
	return this->visible;
}

bool Control::GetMouseHover() const
{
	return this->mouse_hover;
}

void Control::SetDataUpdate(const bool data_update)
{
	this->data_update = data_update;
}

bool Control::GetDataUpdate() const
{
	return this->data_update;
}

float Control::GetX() const
{
	return this->rect.GetPosition().GetX();
}

float Control::GetY() const
{
	return this->rect.GetPosition().GetY();
}

void Control::SetPosition(const float x,const float y,const bool centralize)
{
	const float center_x = (centralize) ? (this->GetW() / 2.0f) : 0.0f;
	const float center_y = (centralize) ? (this->GetH() / 2.0f) : 0.0f;

	this->CheckForDataUpdate(this->GetX(),x - center_x);
	this->CheckForDataUpdate(this->GetY(),y - center_y);

	this->rect.SetPosition(x,y,centralize);
}

float Control::GetW() const
{
	return this->rect.GetSize().GetX();
}

float Control::GetH() const
{
	return this->rect.GetSize().GetY();
}

Rect<float>& Control::GetRect()
{
	return this->rect;
}

void Control::EnableOnMouseClickRight()
{
	this->enable_on_mouse_click_right = true;
}

void Control::EnableOnMouseClickMiddle()
{
	this->enable_on_mouse_click_middle = true;
}

void Control::DisableOnMouseClickRight()
{
	this->enable_on_mouse_click_right = false;
}

void Control::DisableOnMouseClickMiddle()
{
	this->enable_on_mouse_click_middle = false;
}

bool Control::CheckMouseClickAvailability(const MouseButton mouse_button) const
{
	return ((mouse_button == MouseButton::Left) ||
			((mouse_button == MouseButton::Right) && (this->enable_on_mouse_click_right)) ||
			((mouse_button == MouseButton::Middle) && (this->enable_on_mouse_click_middle)));
}

void Control::CheckForSpecificEvents()
{

}

KeyboardKey Control::GetKeyboardKeyShortcut() const
{
	return KeyboardKey::Unknown;
}

bool Control::IsHighPriorityControl() const
{
	return false;
}

void Control::ShowAdditionalContent(const Input& input,Video& video,const Timer& timer)
{

}

void Control::Update(const Input& input,const Timer& timer)
{

}

bool Control::AnyControlFocused()
{
	return (Control::control_focused != nullptr);
}

bool Control::AnyControlMouseHovered()
{
	return (Control::control_mouse_hovered != nullptr);
}

bool Control::IsControlFocused()
{
	return (this == Control::control_focused);
}

bool Control::IsRemoved() const
{
	for (list<ControlState>::const_iterator iterator = Control::control_states.begin(); iterator != Control::control_states.end(); iterator++)
	{
		//Verificar se já está na lista
		if (this == iterator->control)
			return false;
	}
	return true;
}

void Control::AddControl()
{
	bool skip = false;
	for (list<ControlState>::const_iterator iterator = Control::control_states.begin(); iterator != Control::control_states.end(); iterator++)
	{
		//Verificar se já está na lista
		if (this == iterator->control)
		{
			skip = true;
			break;
		}
	}

	//Se não precisar pular o controle então adicionar
	if (!skip)
		Control::control_states.push_back(ControlState(*this));
}

void Control::RemoveControl()
{
	Control::CheckOnRemove(*this,false);
}

void Control::GainFocus(const bool focus)
{
	//On Leave
	Control& control_losing_focus = ((!this->IsControlFocused() && (focus)) ? *Control::control_focused : *this);
	if (Control::ControlLoseFocus(control_losing_focus))
		control_losing_focus.on_leave(control_losing_focus);

	//On Enter
	if (focus)
	{
		if (Control::ControlGainFocus(*this))
			this->on_enter(*this);
	}
}

void Control::PerformClick()
{
	//Se estiver habilitado e visível
	if ((this->enabled) && (this->visible))
		this->on_click(*this);
}

Control& Control::GetControlFocused()
{
	return *Control::control_focused;
}

bool Control::ControlGainFocus(Control& control)
{
	//Se o controle com foco for nullptr ou outro controle e estiver habilitado e visível
	if ((!control.IsControlFocused()) && (control.enabled) && (control.visible))
	{
		Control::control_focused = &control;
		return true;
	}
	return false;
}

bool Control::ControlLoseFocus(Control& control)
{
	//Se o controle com foco for ele mesmo mas não for nullptr
	if ((control.IsControlFocused()) && (Control::control_focused))
	{
		Control::control_focused = nullptr;
		return true;
	}
	return false;
}

void Control::MouseHoverOnSomeControl(const Input& input)
{
	for (list<ControlState>::const_iterator iterator = Control::control_states.begin(); iterator != Control::control_states.end(); iterator++)
	{
		//Control
		const Control& control = *iterator->control;

		//Mouse Hover Control
		if (Rect<float>(control.GetX(),control.GetY(),control.GetW(),control.GetH()).PointInRect(static_cast<float>(input.GetMouseX()),static_cast<float>(input.GetMouseY())))
		{
			Control::control_mouse_hovered = &control;
			break;
		}
	}
}

bool Control::CheckGainFocus(const MouseButton mouse_button_once,const bool skip_gain_focus_control)
{
	if (Control::IsValidIterator())
	{
		Control& control = *Control::iterator->control;

		//Não poderá trocar com ele mesmo
		if (!control.IsControlFocused())
		{
			//Se algum clique do Mouse foi pressionado
			if (!Input::IsMouseButtonUnknown(mouse_button_once))
			{
				//Caso não tenha executado o ganho do foco em outros controles, somente um deve ganhar foco durante o processo
				if (!skip_gain_focus_control)
				{
					//OnLeave OnEnter
					control.GainFocus(true);

					//Evitar de executar mais de uma vez no processo para evitar vários disparos nos eventos OnEnter e OnLeave
					return true;
				}
			}
		}

		//Controle já está com foco no momento do clique, poderá pular os outros controles
		else
			return true;
	}

	//Nada ocorreu retorna o mesmo valor
	return skip_gain_focus_control;
}

void Control::CheckLoseFocus(const MouseButton mouse_button_once)
{
	if (Control::IsValidIterator())
	{
		Control& control = *Control::iterator->control;

		//Se clicou com o Mouse
		if (!Input::IsMouseButtonUnknown(mouse_button_once))
		{
			//Controle com foco vai perder, caso o Mouse esteja fora de qualquer outro controle
			if (!Control::control_mouse_hovered)
				control.GainFocus(false);
		}
	}
}

void Control::CheckOnEnabledChanged()
{
	if (Control::IsValidIterator())
	{
		ControlState& control_state = *Control::iterator;
		Control& control = *control_state.control;

		//On Enabled Changed
		if (control.enabled != control_state.copy_of_enabled)
		{
			control_state.copy_of_enabled = control.enabled;
			control.on_enabled_changed(control);

			//Caso o controle ficar desabilitado então perder o foco
			if (!control.enabled)
			{
				//On Leave
				control.GainFocus(false);
			}
		}
	}
}

void Control::CheckOnKeyUp(const KeyboardKey keyboard_key)
{
	if (Control::IsValidIterator())
	{
		const ControlState& control_state = *Control::iterator;
		Control& control = *control_state.control;

		//Executar somente se o controle tem o foco
		if (control.IsControlFocused())
		{
			//Se apertou alguma tecla antes mas agora soltou
			if (Input::IsKeyboardKeyUnknown(keyboard_key))
			{
				//Qual tecla foi apertada anteriormente
				if (!Input::IsKeyboardKeyUnknown(control_state.keyboard_key))
				{
					//Evento On Key Down deve ter sido executado antes
					if (control.on_key_down_triggered)
					{
						control.on_key_up(control,control_state.keyboard_key);
						control.on_key_down_triggered = false;
					}
				}
			}
		}
	}
}

void Control::CheckOnKeyDown(const KeyboardKey keyboard_key)
{
	if (Control::IsValidIterator())
	{
		const ControlState& control_state = *Control::iterator;
		Control& control = *control_state.control;

		//Executar somente se o controle tem o foco
		if (control.IsControlFocused())
		{
			//Se apertou alguma tecla antes
			if (!Input::IsKeyboardKeyUnknown(keyboard_key))
			{
				//Não teve nenhuma teclada anteriormente
				if (Input::IsKeyboardKeyUnknown(control_state.keyboard_key))
				{
					control.on_key_down(control,keyboard_key);
					control.on_key_down_triggered = true;
				}
			}
		}
	}
}

bool Control::CheckOnMouseUp(const Input& input,const MouseButton mouse_button)
{
	if (Control::IsValidIterator())
	{
		const ControlState& control_state = *Control::iterator;
		Control& control = *control_state.control;

		//Executar somente o controle da frente que tem o foco
		if (control.IsControlFocused())
		{
			//Se apertou algum clique antes mas agora soltou
			if (Input::IsMouseButtonUnknown(mouse_button))
			{
				//Qual clique foi apertado anteriormente
				if (!Input::IsMouseButtonUnknown(control_state.mouse_button))
				{
					//Evento On Mouse Down deve ter sido executado antes
					if (control.on_mouse_down_triggered)
					{
						//Verificar a disponibilidade de clique com o Mouse com base no qual foi pressionado
						if (control.CheckMouseClickAvailability(control_state.mouse_button))
						{
							control.on_mouse_up(control,control_state.mouse_button,static_cast<float>(input.GetMouseX()),static_cast<float>(input.GetMouseY()));
							control.on_mouse_down_triggered = false;
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

void Control::CheckOnMouseDown(const Input& input,const MouseButton mouse_button)
{
	if (Control::IsValidIterator())
	{
		const ControlState& control_state = *Control::iterator;
		Control& control = *control_state.control;

		//Executar somente o controle da frente que tem o foco
		if (control.IsControlFocused())
		{
			//Se apertou algum clique antes
			if (!Input::IsMouseButtonUnknown(mouse_button))
			{
				//Não deve ter nenhum clique anteriormente
				if (Input::IsMouseButtonUnknown(control_state.mouse_button))
				{
					//Verificar a disponibilidade de clique com o Mouse com base no qual foi pressionado
					if (control.CheckMouseClickAvailability(mouse_button))
					{
						control.on_mouse_down(control,mouse_button,static_cast<float>(input.GetMouseX()),static_cast<float>(input.GetMouseY()));
						control.on_mouse_down_triggered = true;
					}
				}
			}
		}
	}
}

void Control::CheckOnMouseEnter()
{
	if (Control::IsValidIterator())
	{
		Control& control = *Control::iterator->control;

		//Se anteriormente o Mouse não estava passando por cima do controle
		if (!control.mouse_hover)
			control.on_mouse_enter(control);
	}
}

void Control::CheckOnMouseHover()
{
	if (Control::IsValidIterator())
	{
		Control& control = *Control::iterator->control;

		control.on_mouse_hover(control);
	}
}

bool Control::CheckOnClick(const Input& input,const bool on_mouse_up_triggered,const bool mouse_hover)
{
	if (Control::IsValidIterator())
	{
		Control& control = *Control::iterator->control;

		const bool keyboard_on_click = ((!Input::IsKeyboardKeyUnknown(control.GetKeyboardKeyShortcut())) && (input.IsKeyboardKeyPressedOnce(control.GetKeyboardKeyShortcut())) && (!control.on_mouse_down_triggered));
		const bool mouse_on_click = ((on_mouse_up_triggered) && (mouse_hover));

		//Tecla de atalho do Keyboard foi apertada, mas o clique do Mouse não deve estar pressionado
		if ((keyboard_on_click) || (mouse_on_click))
		{
			control.on_click(control);
			return true;
		}
	}
	return false;
}

void Control::CheckOnMouseClick(const Input& input,const bool on_mouse_up_triggered)
{
	if (Control::IsValidIterator())
	{
		const ControlState& control_state = *Control::iterator;
		Control& control = *control_state.control;

		if (on_mouse_up_triggered)
		{
			//Verificar a disponibilidade de clique com o Mouse com base no qual foi pressionado
			if (control.CheckMouseClickAvailability(control_state.mouse_button))
				control.on_mouse_click(control,control_state.mouse_button,static_cast<float>(input.GetMouseX()),static_cast<float>(input.GetMouseY()));
		}
	}
}

void Control::CheckOnMouseLeave()
{
	if (Control::IsValidIterator())
	{
		Control& control = *Control::iterator->control;

		if (control.mouse_hover)
			control.on_mouse_leave(control);
	}
}

void Control::CheckOnRemove(Control& control,const bool removing_from_destructor)
{
	for (list<ControlState>::const_iterator iterator = Control::control_states.begin(); iterator != Control::control_states.end(); iterator++)
	{
		//Verificar se já está na lista
		if (&control == iterator->control)
		{
			//O controle deve apenas perder o foco caso for ele, não deve disparar o evento On Leave pelo destrutor
			if (removing_from_destructor)
				Control::ControlLoseFocus(control);
			else
				control.GainFocus(false);

			//On Remove
			control.on_remove(control);

			//Removendo da lista de Control States
			Control::iterator = Control::control_states.erase(iterator);
			Control::iterator_erased = true;
			break;
		}
	}
}

bool Control::IsValidIterator()
{
	return (Control::iterator != Control::control_states.end());
}

void Control::ProcessEvents(const Input& input,const Timer& timer)
{
	//Executar o ganho de foco de controle somente uma vez por processo
	bool skip_gain_focus_control = false;

	//Resetar valor
	Control::control_mouse_hovered = nullptr;

	//Verificar se o Mouse passa sobre algum controle
	Control::MouseHoverOnSomeControl(input);

	const KeyboardKey keyboard_key = input.IsAnyKeyboardKeyPressed();

	const MouseButton mouse_button = input.IsAnyMouseButtonPressed();

	const MouseButton mouse_button_once = input.IsAnyMouseButtonPressedOnce();

	bool skip_onclick_event = false;

	//Eventos principais, devem ser verificados em ordem inversa devido a ordem que são mostrados na tela
	for (Control::iterator = Control::control_states.end(); iterator != Control::control_states.begin(); /* empty */)
	{
		//Já começa a decremetar aqui pois o último elemento (end) não é o último elemento da lista
		if (!Control::iterator_erased)
			Control::iterator--;
		Control::iterator_erased = false;

		//Verificar se o iterator é valido para ser usado
		if (Control::IsValidIterator())
		{
			//Mouse Hover Control
			const bool mouse_hover = Control::iterator->control->rect.PointInRect(static_cast<float>(input.GetMouseX()),static_cast<float>(input.GetMouseY()));

			//On Enabled Changed
			Control::CheckOnEnabledChanged();

			//Se o controle estiver habilitado e visível
			if ((Control::IsValidIterator() && (iterator->control->enabled) && (iterator->control->visible)))
			{
				//On Key Up
				Control::CheckOnKeyUp(keyboard_key);

				//On Key Down
				Control::CheckOnKeyDown(keyboard_key);

				//On Mouse Up
				const bool on_mouse_up_triggered = Control::CheckOnMouseUp(input,mouse_button);

				//On Click
				if (!skip_onclick_event)
					skip_onclick_event = Control::CheckOnClick(input,on_mouse_up_triggered,mouse_hover);

				//Mouse sobre o controle
				if (mouse_hover)
				{
					//On Mouse Hover
					Control::CheckOnMouseHover();

					//On Mouse Enter
					Control::CheckOnMouseEnter();

					//Gain Focus (On Leave On Enter)
					skip_gain_focus_control = Control::CheckGainFocus(mouse_button_once,skip_gain_focus_control);

					//On Mouse Down
					Control::CheckOnMouseDown(input,mouse_button);

					//On Mouse Click
					Control::CheckOnMouseClick(input,on_mouse_up_triggered);
				}
				else
				{
					//On Mouse Leave
					Control::CheckOnMouseLeave();

					//Lose Focus (On Leave)
					Control::CheckLoseFocus(mouse_button_once);
				}

				//Verificar por eventos específicos do controle
				if (Control::IsValidIterator())
					iterator->control->CheckForSpecificEvents();
			}

			//Atualizar dados
			if (Control::IsValidIterator())
			{
				iterator->control->mouse_hover = mouse_hover;
				iterator->keyboard_key = keyboard_key;
				iterator->mouse_button = mouse_button;
			}
		}
	}
}

void Control::ShowControls(const Input& input,Video& video,const Timer& timer)
{
	//Conteúdo adicional
	Control* control_of_additional_content = nullptr;

	//Atualizar dados de todos os controles antes de mostrá-los
	for (list<ControlState>::const_iterator iterator = Control::control_states.begin(); iterator != Control::control_states.end(); /* empty */)
		(iterator++)->control->Update(input,timer);

	//Mostrar os controles na ordem que foram adicionados
	for (list<ControlState>::const_iterator iterator = Control::control_states.begin(); iterator != Control::control_states.end(); iterator++)
	{
		//Se tiver conteúdo adicional para mostrar
		if ((iterator->control->visible) && (iterator->control->Show(input,video,timer)))
			control_of_additional_content = iterator->control;
	}

	//Mostrar conteúdo adicional após renderizar todos os controles
	if (control_of_additional_content)
	{
		//Mostrando conteúdo adicional
		control_of_additional_content->ShowAdditionalContent(input,video,timer);

		//Se for um controle de alta prioridade
		if (control_of_additional_content->IsHighPriorityControl())
		{
			//Se não estiver já no final
			if (Control::control_states.back().control != control_of_additional_content)
			{
				//Achá-lo na lista
				for (list<ControlState>::const_iterator iterator = Control::control_states.begin(); iterator != Control::control_states.end(); iterator++)
				{
					//Colocá-lo no final e remover da posição atual
					if (iterator->control == control_of_additional_content)
					{
						ControlState copy_control = *iterator;
						Control::control_states.erase(iterator);
						Control::control_states.push_back(copy_control);
						break;
					}
				}
			}
		}
	}

	//Pegar o último caractere digitado para resetar o valor
	input.GetLastCharacterTyped();
}
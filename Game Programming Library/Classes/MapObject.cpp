#include "MapObject.h"

using namespace std;
using namespace GPL;

MapObject* MapObject::map_object_focused(nullptr);
MapObject* MapObject::map_object_mouse_hovered(nullptr);
MapObject* MapObject::map_object_interacted(nullptr);
list<MapObject::MapObjectState> MapObject::sorted_map_objects;

MapObject::MapObject(const float w,const float h,const float interaction_area_w,const float interaction_area_h,const bool enable_action_tooltip,const bool ignore_any_mouse_interaction) :
	enable_action_tooltip(enable_action_tooltip),
	ignore_any_mouse_interaction(ignore_any_mouse_interaction),
	show(true),
	interaction(nullptr),
	camera(nullptr),
	object_rect(0.0f,0.0f,w,h),
	interaction_area(0.0f,0.0f,interaction_area_w,interaction_area_h)
{

}

MapObject::~MapObject()
{
	//Resetar
	if (this == MapObject::map_object_focused)
		MapObject::map_object_focused = nullptr;

	//Resetar
	if (this == MapObject::map_object_mouse_hovered)
		MapObject::map_object_mouse_hovered = nullptr;

	//Resetar
	if (this == MapObject::map_object_interacted)
		MapObject::map_object_interacted = nullptr;

	//Remover da lista se o próprio objeto do mapa estiver nela
	MapObject::sorted_map_objects.erase(remove(MapObject::sorted_map_objects.begin(),MapObject::sorted_map_objects.end(),MapObjectState(*this)),MapObject::sorted_map_objects.end());
}

void MapObject::SetShow(const bool show)
{
	this->show = show;
}

void MapObject::SetInteraction(MapObject& interaction)
{
	if (&interaction != this)
		this->interaction = &interaction;
}

MapObject& MapObject::GetInteraction()
{
	return *this->interaction;
}

void MapObject::SetCamera(const Point2D<float>& camera)
{
	this->camera = &camera;
}

float MapObject::GetCameraX() const
{
	return this->camera ? this->camera->GetX() : 0.0f;
}

float MapObject::GetCameraY() const
{
	return this->camera ? this->camera->GetY() : 0.0f;
}

void MapObject::SetX(const float x)
{
	this->object_rect.GetPosition().SetX(x);
}

float MapObject::GetX() const
{
	return this->object_rect.GetPosition().GetX();
}

void MapObject::SetY(const float y)
{
	this->object_rect.GetPosition().SetY(y);
}

float MapObject::GetY() const
{
	return this->object_rect.GetPosition().GetY();
}

void MapObject::SetW(const float w)
{
	this->object_rect.GetSize().SetX(w);
}

float MapObject::GetW() const
{
	return this->object_rect.GetSize().GetX();
}

void MapObject::SetH(const float h)
{
	this->object_rect.GetSize().SetY(h);
}

float MapObject::GetH() const
{
	return this->object_rect.GetSize().GetY();
}

void MapObject::SetPosition(const float x,const float y,const bool centralize)
{
	this->object_rect.SetPosition(x,y,centralize);
}

Rect<float>& MapObject::GetInteractionArea()
{
	return this->interaction_area;
}

const Rect<float>& MapObject::GetInteractionArea() const
{
	return this->interaction_area;
}

float MapObject::GetDrawPoint() const
{
	//Não importa a câmera já que é um valor para ser usado na ordenação dos objetos do mapa
	return (this->GetY() + this->GetH());
}

float MapObject::GetMoveToPositionBase(const GetActionPositionMethod& GetActionPosition,const MapObject& map_object,const float add_value) const
{
	if ((map_object.*GetActionPosition)() < (this->*GetActionPosition)())
		return (this->*GetActionPosition)() - add_value;

	else if ((map_object.*GetActionPosition)() > (this->*GetActionPosition)())
		return (this->*GetActionPosition)() + add_value;

	else
		return (this->*GetActionPosition)();
}

void MapObject::SetActionToolTipText(const Font& font,const string& text,const Color& text_color,const float edge_distance,const string& additional_text,const Color& additional_text_color)
{
	//Se precisar atualizar o texto
	if (this->old_action_text != text)
	{
		this->action_tooltip.Clear();
		this->action_tooltip.SetToolTip(font,edge_distance);
		this->action_tooltip.NewTextLine(text,text_color);
		this->old_action_text = text;

		//Texto adicional na linha de baixo (fica melhor distribuído na tela) se precisar
		if (!additional_text.empty())
			this->action_tooltip.NewTextLine(additional_text,additional_text_color);
	}
}

void MapObject::ShowActionToolTip(Video& video)
{
	//Mostrar o texto da ação se necessário
	if (this->enable_action_tooltip)
	{
		//Atualizar os dados do ToolTip antes de mostrar
		this->action_tooltip.SetPosition(this->GetX() - this->GetCameraX() + (this->GetW() / 2.0f),this->GetY() - this->GetCameraY() + (this->GetH() / 2.0f),true);
		this->action_tooltip.ShowToolTip(video);
	}
}

bool MapObject::IsMouseHover(const Input& input) const
{
	//Se o Mouse estiver sobre o objeto considerando a câmera, não deve alterar as posições X e Y diretamente para evitar problemas com as posições
	return Rect<float>(this->GetX() - this->GetCameraX(),this->GetY() - this->GetCameraY(),this->GetW(),this->GetH()).PointInRect(static_cast<float>(input.GetMouseX()),static_cast<float>(input.GetMouseY()));
}

void MapObject::CheckForSpecificEvents()
{

}

bool MapObject::MovedToMoveToPositionOf(const MapObject& map_object) const
{
	return (map_object.GetMoveToPositionX(*this) == this->GetActionPositionX()) && (map_object.GetMoveToPositionY(*this) == this->GetActionPositionY());
}

float MapObject::GetActionPositionX() const
{
	return (this->GetX() + (this->GetW() / 2.0f));
}

float MapObject::GetActionPositionY() const
{
	return (this->GetY() + (this->GetH() / 2.0f));
}

float MapObject::GetMoveToPositionX(const MapObject& map_object) const
{
	return this->GetMoveToPositionBase(&MapObject::GetActionPositionX,map_object,0.0f);
}

float MapObject::GetMoveToPositionY(const MapObject& map_object) const
{
	return this->GetMoveToPositionBase(&MapObject::GetActionPositionY,map_object,0.0f);
}

void MapObject::SetPause(const bool pause)
{

}

void MapObject::SetGrayScale(const bool gray_scale)
{

}

void MapObject::TurnLeft()
{

}

void MapObject::TurnRight()
{

}

void MapObject::TurnUp()
{

}

void MapObject::TurnDown()
{

}

bool MapObject::IsMoving() const
{
	return false;
}

void MapObject::LockMovement()
{

}

void MapObject::UnlockMovement()
{

}

void MapObject::UpdateMovement(const Timer& timer)
{

}

void MapObject::TurnTo(MapObject& map_object)
{
	if (this->GetActionPositionX() < map_object.GetActionPositionX())
	{
		this->TurnRight();
		map_object.TurnLeft();
	}
	else if (this->GetActionPositionX() > map_object.GetActionPositionX())
	{
		this->TurnLeft();
		map_object.TurnRight();
	}

	if (this->GetActionPositionY() < map_object.GetActionPositionY())
	{
		this->TurnDown();
		map_object.TurnUp();
	}
	else if (this->GetActionPositionY() > map_object.GetActionPositionY())
	{
		this->TurnUp();
		map_object.TurnDown();
	}
}

bool MapObject::AddMapObject()
{
	//Verificar se o objeto do mapa não se encontra na lista para adicioná-lo
	if (find(MapObject::sorted_map_objects.begin(),MapObject::sorted_map_objects.end(),MapObjectState(*this)) == MapObject::sorted_map_objects.end())
	{
		MapObject::sorted_map_objects.push_back(MapObjectState(*this));
		return true;
	}
	return false;
}

void MapObject::RemoveAllEventsOnShow()
{ 
	this->on_show.Clear(); 
}

const MapObject* MapObject::GetMapObjectFocused()
{
	return MapObject::map_object_focused;
}

MapObject* MapObject::GetMapObjectInteracted()
{
	return MapObject::map_object_interacted;
}

void MapObject::ResetMapObjectInteracted()
{
	MapObject::map_object_interacted = nullptr;
}

void MapObject::CheckOnMouseHover(MapObject& map_object)
{
	MapObject::map_object_mouse_hovered = &map_object;
	map_object.on_mouse_hover(map_object);
}

void MapObject::CheckOnMouseLeftClick(MapObject& map_object)
{
	//Dar a chance de outros objetos do mapa receber o foco
	MapObject::map_object_focused = &map_object;
	map_object.on_mouse_left_click(map_object);
}

void MapObject::CheckOnInteraction(MapObject& map_object,MapObject& sub_map_object)
{
	//Se tiver nenhum objeto do mapa já está interagindo
	if (!MapObject::map_object_interacted)
	{
		//Objeto do map com o foco deve ser o mesmo que este e deve verificar se o outro objeto do mapa é o interagível
		if ((MapObject::map_object_focused == &map_object) && (&sub_map_object == map_object.interaction))
		{
			//Se o objeto que irá receber o foco pela interação estiver se movendo (nesse caso não tem jeito e pode intergir) ou esperar até o outro objeto do mapa entrar na posição para onde ele deve ser mover
			if ((map_object.IsMoving()) || (sub_map_object.MovedToMoveToPositionOf(map_object)))
			{
				MapObject::map_object_interacted = &map_object;
				map_object.on_interaction_event(map_object,sub_map_object);
				MapObject::map_object_focused = nullptr;
			}
		}
	}
}

void MapObject::CheckOnEnterInteractionArea(MapObject& map_object,MapObjectState& map_object_state,MapObject& sub_map_object)
{
	//Se o objeto do mapa já não havia entrado na área interação
	if (!map_object_state.MapObjectEnteredInteractionArea(sub_map_object))
	{
		map_object.on_enter_interaction_area_event(map_object,sub_map_object);

		//Adicionar na estrutura dos objetos do mapa que entraram
		map_object_state.AddEnteredMapObjectInteractionArea(sub_map_object);
	}
}

void MapObject::CheckOnLeaveInteractionArea(MapObject& map_object,MapObjectState& map_object_state,MapObject& sub_map_object)
{
	//Se o objeto do mapa já havia entrado na área interação
	if (map_object_state.MapObjectEnteredInteractionArea(sub_map_object))
	{
		map_object.on_leave_interaction_area_event(map_object,sub_map_object);

		//Remover da estrutura dos objetos do mapa que entraram
		map_object_state.RemoveEnteredMapObjectInteractionArea(sub_map_object);
	}
}

void MapObject::ProcessEvents(const Input& input,const Timer& timer,const bool skip_mouse_interaction)
{
	//Mouse foi clicado
	const bool mouse_button_left = input.IsMouseButtonPressed(MouseButton::Left);
	static bool last_mouse_button_left = mouse_button_left;

	//Começou a clicar agora em relação ao Loop anterior
	const bool starting_mouse_button_left_now = ((!last_mouse_button_left) && (mouse_button_left));

	//Resetar valores
	MapObject::map_object_mouse_hovered = nullptr;

	//Verificar todos os eventos de cada objeto do mapa
	for (list<MapObjectState>::iterator main_iterator = MapObject::sorted_map_objects.begin(); main_iterator != MapObject::sorted_map_objects.end(); main_iterator++)
	{
		//Map Object State
		MapObjectState& map_object_state = *main_iterator;

		//Map Object
		MapObject& map_object = *map_object_state.map_object;

		//Atualizar dados de relacionados aos movimentos
		map_object.UpdateMovement(timer);

		//Se não precisar ignorar o evento com Mouse sobre o objeto do mapa ou tiver que evitar pois alguma interação já poderá estar ocorrendo
		if ((!map_object.ignore_any_mouse_interaction) && (!skip_mouse_interaction))
		{
			//Mouse sobre o objeto do mapa
			if (map_object.IsMouseHover(input))
			{
				//On Mouse Hover
				MapObject::CheckOnMouseHover(map_object);

				//Começou a clicar agora em relação ao Loop anterior
				if (starting_mouse_button_left_now)
				{
					//On Mouse Left Click
					MapObject::CheckOnMouseLeftClick(map_object);
				}
			}
		}

		//Eventos que envolvem outros objetos do mapa
		for (list<MapObjectState>::const_iterator sub_iterator = MapObject::sorted_map_objects.begin(); sub_iterator != MapObject::sorted_map_objects.end(); sub_iterator++)
		{
			//Sub Map Object
			MapObject& sub_map_object = *sub_iterator->map_object;

			//Se não for ele mesmo
			if (&map_object != &sub_map_object)
			{
				//Se está dentro da área de interação
				if (map_object.interaction_area.PointInRect(sub_map_object.GetActionPositionX(),sub_map_object.GetActionPositionY()))
				{
					//On Interaction
					MapObject::CheckOnInteraction(map_object,sub_map_object);

					//On Enter Interaction Area
					MapObject::CheckOnEnterInteractionArea(map_object,map_object_state,sub_map_object);
				}
				else
				{
					//On Leave Interaction Area
					MapObject::CheckOnLeaveInteractionArea(map_object,map_object_state,sub_map_object);
				}
			}
		}

		//Verificar por eventos específicos do objeto do mapa
		map_object.CheckForSpecificEvents();
	}

	//Se o Mouse não tiver por cima de nenhum objeto e for dar um novo clique, ou seja, clicar fora de qualquer objeto do mapa
	if (((!MapObject::map_object_mouse_hovered) && (starting_mouse_button_left_now)))
		MapObject::map_object_focused = nullptr;

	//Ordenando os objetos do mapa
	static const auto sort_y_top_to_bottom = [](const MapObjectState& map_object_state_a,const MapObjectState& map_object_state_b) -> bool { return (map_object_state_a.map_object->GetDrawPoint() < map_object_state_b.map_object->GetDrawPoint()); };
	MapObject::sorted_map_objects.sort(sort_y_top_to_bottom);

	//Atualizando para o próximo Loop
	last_mouse_button_left = mouse_button_left;
}

void MapObject::ShowMapObjectsSorted(Video& video,const Timer& timer)
{
	//Mostrar todos os objetos do mapa já ordenados
	for (list<MapObjectState>::const_iterator iterator = MapObject::sorted_map_objects.begin(); iterator != MapObject::sorted_map_objects.end(); iterator++)
	{
		MapObject& map_object = *iterator->map_object;

		//Mostrar o objeto do mapa quando possível
		if (map_object.show)
			map_object.Show(video,timer);

		//Evento On Show
		map_object.on_show(map_object);
	}
}

void MapObject::ShowMapObjectActionToolTip(Video& video)
{
	//Se tiver nenhum objeto do mapa interagindo
	if (!MapObject::map_object_interacted)
	{
		//Mostrar o texto de ação de interação por cima de um objeto que foi clicado com o Mouse e recebeu o foco
		if (MapObject::map_object_focused)
			MapObject::map_object_focused->ShowActionToolTip(video);

		//Mostrar o texto de ação de interação por cima de um objeto que foi passado o Mouse
		else if (MapObject::map_object_mouse_hovered)
			MapObject::map_object_mouse_hovered->ShowActionToolTip(video);
	}
}
#ifndef MAPOBJECT_H
#define MAPOBJECT_H

#include "Timer.h"
#include "ToolTip.h"

namespace GPL
{
	class MapObject
	{
	private:
		using GetActionPositionMethod = float(MapObject::*)() const;

		using Event = Signal<void,MapObject&>;
		using InteractionEvent = Signal<void,MapObject&,MapObject&>;

		//Estrutura para armazenar dados do objeto do mapa e o próprio
		struct MapObjectState
		{
			//Objeto do mapa
			MapObject* map_object;

			//Objetos que entraram na área de interação
			std::vector<const MapObject*> entered_interaction_area_map_objects;

			//Construtor
			MapObjectState(MapObject& map_object) :
				map_object(&map_object) {}

			//Operador igual
			bool operator==(const MapObjectState& map_object_state) const
			{
				return (this->map_object == map_object_state.map_object);
			}

			//Verificar se o objeto do mapa já entrou na área de interação
			bool MapObjectEnteredInteractionArea(const MapObject& map_object)
			{
				return std::find(this->entered_interaction_area_map_objects.begin(),this->entered_interaction_area_map_objects.end(),&map_object) != this->entered_interaction_area_map_objects.end();
			}

			//Adicionar objeto do mapa que porque entrou na área de interação
			void AddEnteredMapObjectInteractionArea(const MapObject& map_object)
			{
				this->entered_interaction_area_map_objects.push_back(&map_object);
			}

			//Remover objeto do mapa que porque deixou a área de interação
			void RemoveEnteredMapObjectInteractionArea(const MapObject& map_object)
			{
				this->entered_interaction_area_map_objects.erase(std::remove(this->entered_interaction_area_map_objects.begin(),this->entered_interaction_area_map_objects.end(),&map_object),this->entered_interaction_area_map_objects.end());
			}
		};

		//Mostrar o texto ação da interação por cima do objeto do mapa
		const bool enable_action_tooltip;

		//Ignorar qualquer tipo de interação com o Mouse no objeto do mapa
		const bool ignore_any_mouse_interaction;

		//Mostrar o objeto do mapa
		bool show;

		//Objeto do mapa que pode interagir com este objeto do mapa
		MapObject* interaction;

		//Referência da câmera que será aplicada sobre o objeto do mapa
		const Point2D<float>* camera;

		//Último valor do text de ação em cima do objeto
		std::string old_action_text;

		//Dimensão do objeto
		Rect<float> object_rect;

		//Área de interação para que outros objetos quando entrar nela possam interagir
		Rect<float> interaction_area;

		//Texto da ação de interação com o objeto do mapa
		ToolTip action_tooltip;

		//Evento do Mouse passando sobre o objeto do mapa
		Event on_mouse_hover;

		//Evento do Mouse quando clicar sobre o objeto do mapa
		Event on_mouse_left_click;

		//Evento ao mostrar o objeto do mapa
		Event on_show;

		//Evento quando um objeto do mapa interage com este objeto do mapa
		InteractionEvent on_interaction_event;

		//Evento quando um objeto do mapa entra na área de interação deste objeto do mapa
		InteractionEvent on_enter_interaction_area_event;

		//Evento quando um objeto do mapa deixa a área de interação deste objeto do mapa
		InteractionEvent on_leave_interaction_area_event;

		//Objeto do mapa que recebeu o foco do Mouse com um clique
		static MapObject* map_object_focused;

		//Objeto do mapa que Mouse foi passado por cima
		static MapObject* map_object_mouse_hovered;

		//Objeto do mapa que interagiu
		static MapObject* map_object_interacted;

		//Objetos do mapa ordenados que serão processados e verificados por eventos
		static std::list<MapObjectState> sorted_map_objects;

		//Verificar se o outro objeto do mapa se moveu para a posição que ele deve ir para este objeto do mapa
		bool MovedToMoveToPositionOf(const MapObject& map_object) const;

		//Verificar por evento On Mouse Hover
		static void CheckOnMouseHover(MapObject& map_object);

		//Verificar por evento On Mouse Left Click
		static void CheckOnMouseLeftClick(MapObject& map_object);

		//Verificar por evento On Interaction
		static void CheckOnInteraction(MapObject& map_object,MapObject& sub_map_object);

		//Verificar por evento On Enter Interaction Area
		static void CheckOnEnterInteractionArea(MapObject& map_object,MapObjectState& map_object_state,MapObject& sub_map_object);

		//Verificar por evento On Leave Interaction Area
		static void CheckOnLeaveInteractionArea(MapObject& map_object,MapObjectState& map_object_state,MapObject& sub_map_object);
	protected:
		//Pegar Move To Position
		GPL_DLL float GetMoveToPositionBase(const GetActionPositionMethod& GetActionPosition,const MapObject& map_object,const float add_value) const;

		//Pegar Interaction
		GPL_DLL MapObject& GetInteraction();

		//Verificar por eventos específicos do objeto do mapa
		GPL_DLL virtual void CheckForSpecificEvents();
	public:
		//Construtor
		GPL_DLL MapObject(const float w = 0.0f,const float h = 0.0f,const float interaction_area_w = 0.0f,const float interaction_area_h = 0.0f,const bool enable_action_tooltip = true,const bool ignore_any_mouse_interaction = false);

		//Destrutor
		GPL_DLL virtual ~MapObject();

		//Alterar Show
		GPL_DLL void SetShow(const bool show);

		//Alterar Interaction
		GPL_DLL void SetInteraction(MapObject& interaction);

		//Alterar Camera
		GPL_DLL void SetCamera(const Point2D<float>& camera);

		//Pegar Camera X
		GPL_DLL float GetCameraX() const;

		//Pegar Camera Y
		GPL_DLL float GetCameraY() const;

		//Alterar X
		GPL_DLL void SetX(const float x);

		//Pegar X
		GPL_DLL float GetX() const;

		//Alterar Y
		GPL_DLL void SetY(const float y);

		//Pegar Y
		GPL_DLL float GetY() const;

		//Alterar W
		GPL_DLL void SetW(const float w);

		//Pegar W
		GPL_DLL float GetW() const;

		//Alterar H
		GPL_DLL void SetH(const float h);

		//Pegar H
		GPL_DLL float GetH() const;

		//Alterar Position
		GPL_DLL void SetPosition(const float x,const float y,const bool centralize = false);

		//Pegar Interaction Area
		GPL_DLL Rect<float>& GetInteractionArea();


		GPL_DLL const Rect<float>& GetInteractionArea() const;

		//Pegar Draw Point
		GPL_DLL float GetDrawPoint() const;

		//Alterar Action ToolTip Text
		GPL_DLL void SetActionToolTipText(const Font& font,const std::string& text,const Color& text_color,const float edge_distance,const std::string& additional_text = "",const Color& additional_text_color = Color::Null);

		//Mostrar o texto da ação da interação com o objeto do mapa
		GPL_DLL void ShowActionToolTip(Video& video);

		//Se o Mouse passa sobre o objeto
		GPL_DLL bool IsMouseHover(const Input& input) const;

		//Fazer um objeto do map virar para o outro
		GPL_DLL void TurnTo(MapObject& map_object);

		//Adicionar o objeto do mapa para seus eventos serem processados
		GPL_DLL bool AddMapObject();

		//Remover todos os eventos On Show
		GPL_DLL void RemoveAllEventsOnShow();

		template<class Event,class Object> void AddEventOnMouseHover(const Event& event,Object& object) { this->on_mouse_hover.Add(event,object,std::placeholders::_1); }
		template<class Event,class Object> void AddEventOnMouseLeftClick(const Event& event,Object& object) { this->on_mouse_left_click.Add(event,object,std::placeholders::_1); }
		template<class Event,class Object> void AddEventOnShow(const Event& event,Object& object) { this->on_show.Add(event,object,std::placeholders::_1); }
		template<class Event,class Object> void AddEventOnInteraction(const Event& event,Object& object) { this->on_interaction_event.Add(event,object,std::placeholders::_1,std::placeholders::_2); }
		template<class Event,class Object> void AddEventOnEnterInteractionArea(const Event& event,Object& object) { this->on_enter_interaction_area_event.Add(event,object,std::placeholders::_1,std::placeholders::_2); }
		template<class Event,class Object> void AddEventOnLeaveInteractionArea(const Event& event,Object& object) { this->on_leave_interaction_area_event.Add(event,object,std::placeholders::_1,std::placeholders::_2); }

		//Pegar Action Position X
		GPL_DLL virtual float GetActionPositionX() const;

		//Pegar Action Position Y
		GPL_DLL virtual float GetActionPositionY() const;

		//Pegar Move To Position X
		GPL_DLL virtual float GetMoveToPositionX(const MapObject& map_object) const;

		//Pegar Move To Position Y
		GPL_DLL virtual float GetMoveToPositionY(const MapObject& map_object) const;

		//Alterar Pause
		GPL_DLL virtual void SetPause(const bool pause);

		//Alterar Gray Scale
		GPL_DLL virtual void SetGrayScale(const bool gray_scale);

		//Virar para esquerda
		GPL_DLL virtual void TurnLeft();

		//Virar para direita
		GPL_DLL virtual void TurnRight();

		//Virar para cima
		GPL_DLL virtual void TurnUp();

		//Virar para baixo
		GPL_DLL virtual void TurnDown();

		//Verificar se está movendo
		GPL_DLL virtual bool IsMoving() const;

		//Bloquear movimentos
		GPL_DLL virtual void LockMovement();

		//Desbloquear movimentos
		GPL_DLL virtual void UnlockMovement();

		//Atualizar dados de relacionados aos movimentos
		GPL_DLL virtual void UpdateMovement(const Timer& timer);

		//Atualizar dados do objeto
		virtual void Update(const Timer& timer) = 0;

		//Mostrar o objeto
		virtual void Show(Video& video,const Timer& timer) = 0;

		//Pegar Map Object Focused
		GPL_DLL static const MapObject* GetMapObjectFocused();

		//Pegar Map Object Interacted
		GPL_DLL static MapObject* GetMapObjectInteracted();

		//Resetar Map Object Interacted
		GPL_DLL static void ResetMapObjectInteracted();

		//Verificar e processar vários eventos para os objetos do mapa adicionados
		GPL_DLL static void ProcessEvents(const Input& input,const Timer& timer,const bool skip_mouse_interaction);

		//Mostrar todos os objetos do mapa já ordenados
		GPL_DLL static void ShowMapObjectsSorted(Video& video,const Timer& timer);

		//Mostrar algum texto de ação de interação de por cima do objeto do mapa quando necessário
		GPL_DLL static void ShowMapObjectActionToolTip(Video& video);
	};
}

#endif
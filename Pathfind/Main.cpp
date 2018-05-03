#include "VideoDirect3D9.h"
#include "AudioXAudio.h"
#include "AudioOpenAL.h"
#include "GameState.h"
#include "Text.h"
#include "Pathfind.h"

using namespace std;
using namespace GPL;

const int node_distance = 50;
const float pixel_gap = 1.0f;
const string font_file_name("Consolas.ttf");

class GamePathfindBuilder : public Game
{
public:
	GamePathfindBuilder::GamePathfindBuilder() :
		Game(make_unique<ApplicationWin32>())
	{
		ResourceFile::SetResourceFileName("Data.pkg");

		
		remove("Data.pkg");
		ResourceFile::Write("../Game Programming Library/Shaders/Render.vsh");
		ResourceFile::Write("../Game Programming Library/Shaders/Render.psh");
		

		
	}

	void CreateGame() override
	{
		VideoMode video_mode(640,480,BitsPerPixel::ColorDepth32Bits,true,true);
		this->Initialize("Pathfind Builder v1.0",video_mode,AudioEngine::XAudio,0);
		this->GetVideo().SetBackBufferClearColor(Color::White);
		this->GetApplication().SetShowCursor(true);
	}
};

class MainState : public GameState
{
private:
	int node_total_x;
	int node_total_y;
	float character_x;
	float character_y;
	Pathfind pathfind;
	Model character;
	Model node_initial;
	vector<unique_ptr<Model>> path;
	vector<vector<unique_ptr<Model>>> grid;
	vector<vector<unique_ptr<Text>>> information;
public:
	//Construtor
	MainState() :
		node_total_x(0),
		node_total_y(0),
		character_x(0.0f),
		character_y(0.0f)
	{
		GamePathfindBuilder& game = GameState::GetGame<GamePathfindBuilder>();

		game.GetVideo().LoadVertexShader(0);
		game.GetVideo().LoadPixelShader(1);
		game.GetVideo().LoadFont(font_file_name,8);

		this->node_total_x = (game.GetVideo().GetVirtualWidth() / node_distance);
		this->node_total_y = (game.GetVideo().GetVirtualHeight() / node_distance);

		this->grid.resize(node_total_x);
		for (auto& iterator : this->grid)
		{
			iterator = vector<unique_ptr<Model>>(node_total_y);
			for (auto& i : iterator)
				i = make_unique<Model>();
		}

		this->information.resize(node_total_x);
		for (auto& iterator : this->information)
		{
			iterator = vector<unique_ptr<Text>>(node_total_y);
			for (auto& i : iterator)
				i = make_unique<Text>();
		}

		this->pathfind.CreateGridNodeMap(node_total_x,node_total_y,node_distance);
		//pathfind.SetCameraIndex(0,0,node_total_x - 5,node_total_y - 5);

		character.ResizeVertices(4);
		character.SetPrimitiveCount(character.GetVertexTotal() - 2);
		character.SetPrimitiveType(PrimitiveType::TriangleStrip);
		this->character_x = static_cast<float>(pathfind.GetNodeInitial().GetX());
		this->character_y = static_cast<float>(pathfind.GetNodeInitial().GetY());

		for (size_t i = 0; i < character.GetVertexTotal(); i++)
			character.SetVertexColor(i,Color::Cyan);

		for (int y = 0; y < node_total_y; y++)
		{
			for (int x = 0; x < node_total_x; x++)
			{
				Model& iterator = *grid[x][y];

				iterator.ResizeVertices(4);
				iterator.SetPrimitiveCount(iterator.GetVertexTotal() - 2);
				iterator.SetPrimitiveType(PrimitiveType::TriangleStrip);

				const float x_1 = (x * node_distance) + pixel_gap;
				const float y_1 = (y * node_distance) + pixel_gap;

				const float x_2 = x_1 + node_distance - pixel_gap;
				const float y_2 = y_1 + node_distance - pixel_gap;

				iterator.SetVertexPosition(0,x_1,y_1);
				iterator.SetVertexPosition(1,x_2,y_1);
				iterator.SetVertexPosition(2,x_1,y_2);
				iterator.SetVertexPosition(3,x_2,y_2);

				for (size_t i = 0; i < iterator.GetVertexTotal(); i++)
				{
					if (pathfind.GetNode(x,y).GetWalkable())
						iterator.SetVertexColor(i,Color(0.0f,0.0f,0.0f,0.5f));
					else
						iterator.SetVertexColor(i,Color(0.0f,0.0f,1.0f,0.5f));
				}
			}
		}

		node_initial.ResizeVertices(4);
		node_initial.SetPrimitiveCount(node_initial.GetVertexTotal() - 2);
		node_initial.SetPrimitiveType(PrimitiveType::TriangleStrip);
		for (size_t i = 0; i < node_initial.GetVertexTotal(); i++)
			node_initial.SetVertexColor(i,Color(0.0f,1.0f,0.0f,0.5f));
	}

	//Atualizar dados e a lógica de todo o conteúdo
	virtual void Update()
	{
	}

	//Mostrar todo o conteúdo
	virtual void Show()
	{
		GamePathfindBuilder& game = GameState::GetGame<GamePathfindBuilder>();

		if (game.GetInput().IsKeyboardKeyPressedOnce(KeyboardKey::Esc))
			game.GetApplication().Quit();

		const float mx = static_cast<float>(game.GetInput().GetMouseX());
		const float my = static_cast<float>(game.GetInput().GetMouseY());

		const int mouse_index_x = static_cast<int>(mx / node_distance);
		const int mouse_index_y = static_cast<int>(my / node_distance);

		const bool mouse_button_left = game.GetInput().IsMouseButtonPressedOnce(MouseButton::Left);
		const bool mouse_button_right = game.GetInput().IsMouseButtonPressedOnce(MouseButton::Right);

		bool path_update = false;
		if (mouse_button_left || mouse_button_right)
		{
			if ((mx < this->node_total_x * node_distance) && (my < this->node_total_y * node_distance))
			{
				const Node& current_node = this->pathfind.GetNode(mouse_index_x,mouse_index_y);

				if (mouse_button_left)
				{
					if (&this->pathfind.GetNodeInitial() != &current_node)
						path_update = this->pathfind.SetNodeWalkable(mouse_index_x,mouse_index_y,(!current_node.GetWalkable()));
				}
				else if (mouse_button_right)
				{
					if (&current_node != &this->pathfind.GetNodeInitial())
					{
						this->pathfind.SetNodeFinal(mouse_index_x,mouse_index_y);
						path_update = this->pathfind.FindPath();
					}
				}
			}
		}

		if (path_update)
		{
			path.clear();

			for (size_t i = 0; i < this->pathfind.GetPath().size(); i++)
			{
				const Node* node_path = this->pathfind.GetPath()[i];

				const float x = static_cast<float>(node_path->GetX() - (node_distance / 2));
				const float y = static_cast<float>(node_path->GetY() - (node_distance / 2));

				path.push_back(make_unique<Model>(PrimitiveType::TriangleStrip,2,4));

				Model& iterator = *path.back();

				const float x_1 = x + pixel_gap;
				const float y_1 = y + pixel_gap;

				const float x_2 = x_1 + node_distance - pixel_gap;
				const float y_2 = y_1 + node_distance - pixel_gap;

				iterator.SetVertexPosition(0,x_1,y_1);
				iterator.SetVertexPosition(1,x_2,y_1);
				iterator.SetVertexPosition(2,x_1,y_2);
				iterator.SetVertexPosition(3,x_2,y_2);

				for (size_t i = 0; i < iterator.GetVertexTotal(); i++)
				{
					Color color(Color::Gold);
					color.SetAlpha(0.5f);
					iterator.SetVertexColor(i,color);
				}
			}
		}

		static Interval movement_timer(0.015f);

		const float movement_speed = 3.0f;
		if (movement_timer.Action(game.GetTimer()))
		{
			this->pathfind.MovementNodeByNode(static_cast<int>(character_x),static_cast<int>(character_y),static_cast<int>(movement_speed));

			const Movement movement_horizontal = pathfind.GetHorizontalMovement();

			if (movement_horizontal == Movement::Right)
				character_x += movement_speed;
			else if (movement_horizontal == Movement::Left)
				character_x -= movement_speed;
			else if (movement_horizontal == Movement::Done)
				character_x = static_cast<float>(pathfind.GetCurrentNodeMovement().GetX());

			const Movement movement_vertical = pathfind.GetVerticalMovement();
			if (movement_vertical == Movement::Down)
				character_y += movement_speed;
			else if (movement_vertical == Movement::Up)
				character_y -= movement_speed;
			else if (movement_vertical == Movement::Done)
				character_y = static_cast<float>(pathfind.GetCurrentNodeMovement().GetY());
		}

		const float size = node_distance * 0.7f;

		const float x_1 = character_x - (size / 2.0f)/*- (node_distance / 2.0f)*//* + (pixel_gap * 2.0f)*/;
		const float y_1 = character_y - (size / 2.0f) /*- (node_distance / 2.0f)*//* + (pixel_gap * 2.0f)*/;

		const float x_2 = x_1 + size/*(node_distance / 1.0f)*//* - (pixel_gap * 3.0f)*/;
		const float y_2 = y_1 + size/*(node_distance / 1.0f)*//* - (pixel_gap * 3.0f)*/;

		character.SetVertexPosition(0,x_1,y_1);
		character.SetVertexPosition(1,x_2,y_1);
		character.SetVertexPosition(2,x_1,y_2);
		character.SetVertexPosition(3,x_2,y_2);

		for (int y = 0; y < node_total_y; y++)
		{
			for (int x = 0; x < node_total_x; x++)
			{
				game.GetVideo().Draw(*grid[x][y]);

				Text& text = *information[x][y];

				const Node& current_node = pathfind.GetNode(x,y);

				text.SetText(game.GetVideo().GetFont(font_file_name),Convert::NumberToString(pathfind.GetNode(x,y).GetG() / 50) + " " + Convert::NumberToString(pathfind.GetNode(x,y).GetH() / 50),Color::Gold);
				text.SetPosition(static_cast<float>(current_node.GetX()),static_cast<float>(current_node.GetY()),true);
				text.Show(game.GetVideo());

				Model& model = *grid[x][y];

				for (size_t i = 0; i < model.GetVertexTotal(); i++)
				{
					if (current_node.GetWalkable())
						model.SetVertexColor(i,Color(0.0f,0.0f,0.0f,0.5f));
					else
						model.SetVertexColor(i,Color(0.0f,0.0f,1.0f,0.5f));
				}

				if (&pathfind.GetNodeInitial())
					ShowNode(game.GetVideo(),pathfind.GetNodeInitial(),node_initial,static_cast<float>(x),static_cast<float>(y));
			}
		}

		for (size_t i = 0; i < path.size(); i++)
			game.GetVideo().Draw(*path[i]);

		game.GetVideo().Draw(character);
	}

	static void ShowNode(Video& video,const Node& node,Model& model,const float x,const float y)
	{
		if (((node.GetX() / node_distance) == x) && ((node.GetY() / node_distance) == y))
		{
			const float x_1 = (x * node_distance) + pixel_gap;
			const float y_1 = (y * node_distance) + pixel_gap;

			const float x_2 = x_1 + node_distance - pixel_gap;
			const float y_2 = y_1 + node_distance - pixel_gap;

			model.SetVertexPosition(0,x_1,y_1);
			model.SetVertexPosition(1,x_2,y_1);
			model.SetVertexPosition(2,x_1,y_2);
			model.SetVertexPosition(3,x_2,y_2);

			video.Draw(model);
		}
	}
};

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	GamePathfindBuilder game;
	game.RegisterVideoEngine<VideoDirect3D9>(VideoEngine::Direct3D9);
	game.RegisterAudioEngine<AudioXAudio>(AudioEngine::XAudio);
	game.RegisterAudioEngine<AudioOpenAL>(AudioEngine::OpenAL);
	game.CreateGame();
	GameState::SetGame(game);
	GameState::AddGameState(make_unique<MainState>(),GameStateAction::None);
	return GameState::Main();
}
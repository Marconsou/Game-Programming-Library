#include "VideoDirect3D9.h"
#include "AudioXAudio.h"
#include "AudioOpenAL.h"
#include "Sprite.h"
#include "MessageLog.h"
#include "GameState.h"
#include "TextDynamicWave.h"

using namespace std;
using namespace GPL;

class GameApplicationTest : public Game
{
public:
	GameApplicationTest::GameApplicationTest() :
		Game(make_unique<ApplicationWin32>(true))
	{
		ResourceFile::SetResourceFileName("Data.pkg");

		remove("Data.pkg");
		ResourceFile::Write("../Game Programming Library/Shaders/Render.vsh");
		ResourceFile::Write("../Game Programming Library/Shaders/Render.psh");
		ResourceFile::Write("Qlassik Bold.otf");
		ResourceFile::Write("Alucard.png");
	}

	void CreateGame() override
	{
		VideoMode video_mode(800,600,BitsPerPixel::ColorDepth32Bits,true,true);
		this->Initialize("Application",video_mode,AudioEngine::XAudio);
		this->GetVideo().SetAspectRatio(AspectRatio::Normal4x3);
		this->GetVideo().SetBackBufferClearColor(Color::White);
		this->GetApplication().SetShowCursor(true);
	}
};

class MainState : public GameState
{
public:
	MainState() :
		object_3d(PrimitiveType::TriangleStrip,2,4,4),
		object_3d_2(PrimitiveType::TriangleStrip,2,4,4)
	{
		GameApplicationTest& game = GameState::GetGame<GameApplicationTest>();

		game.GetVideo().LoadVertexShader(0);
		game.GetVideo().LoadPixelShader(1);
		game.GetVideo().LoadFont(2,32,32UL,126UL);
		game.GetVideo().LoadTexture(3,Color::Green);

		this->message_log.SetMessageLog(game.GetVideo().GetFont(2),"",Color::Gold);

		this->view_2d.GetViewport().SetPosition(0.25f,0.25f);
		this->view_2d.GetViewport().SetSize(0.75f - 0.25f,0.75f - 0.25);

		this->view_3d.GetViewport().SetPosition(0.10f,0.10f);
		this->view_3d.GetViewport().SetSize(0.90f - 0.10f,0.90f - 0.10f);
		this->object_3d.SetView(this->view_3d);
		this->object_3d_2.SetView(this->view_3d);

		this->alucard.SetTexture(game.GetVideo().GetTexture(3));
		this->alucard.SetSize(64.0f,96.0f);
		this->alucard.SetView(this->view_2d);
		//this->alucard.SetColor(Color::Red,Color::Green,Color::Blue,Color::Yellow);

		this->font_sprite.SetTexture(game.GetVideo().GetFont(2).GetTexture());
		this->font_sprite.SetSize(static_cast<float>(this->font_sprite.GetTexture().GetWidth()),static_cast<float>(this->font_sprite.GetTexture().GetHeight()));
		//this->font_sprite.SetColor(Color::Green);
		this->font_sprite.SetPosition(0,100);

		
		
		this->text.SetText(game.GetVideo().GetFont(2),"a b g W[f]ypgabcd efgW [x]",Color::Green);
		
		

		this->text.SetColorTop(Color::Red);
		this->text.SetColorRight(Color::Green);
		this->text.SetColorBottom(Color::Blue);

		this->text.AddText(" A",Color(Color::Red,0.5f));

		this->text.SetAlpha(0.25f);

		this->text.SetAlpha(3,1.0f);

		this->text.AddText(" A",Color(Color::Red,0.5f));

		
		




		this->text_dynamic.SetTextDynamic(game.GetVideo().GetFont(2),"TextDynamicWave!",Color::Blue);


		this->font_rect.SetColor(Color(Color::Red,0.5f));
		this->font_rect.SetPosition(this->text.GetX(),this->text.GetY());
		this->font_rect.SetSize(this->text.GetW(),this->text.GetH());

		const bool is_3d = true;

		if (is_3d)
		{
			float z = 3.0f;
			float size = 1.0f;
			this->object_3d.SetProjection(Projection::Perspective);
			this->object_3d.SetVertexPosition(0,-size,size,z + 2.0f);
			this->object_3d.SetVertexPosition(1,size,size,z);
			this->object_3d.SetVertexPosition(2,-size,-size,z);
			this->object_3d.SetVertexPosition(3,size,-size,z);

			//this->object_3d.GetTranslate().SetZ(0.0f);
			//this->object_3d.GetRotate().SetX(5.0f);

			/*this->object_3d.SetTexture(game.GetVideo().GetTexture(3));
			this->object_3d.SetVertexTextureCoordinate(0,0.0f,0.0f);
			this->object_3d.SetVertexTextureCoordinate(1,1.0f,0.0f);
			this->object_3d.SetVertexTextureCoordinate(2,0.0f,1.0f);
			this->object_3d.SetVertexTextureCoordinate(3,1.0f,1.0f);*/


			z = 5.0f;
			size = 5.0f;
			this->object_3d_2.SetProjection(Projection::Perspective);
			this->object_3d_2.SetVertexPosition(0,-size,size,z);
			this->object_3d_2.SetVertexPosition(1,size,size,z);
			this->object_3d_2.SetVertexPosition(2,-size,-size,z);
			this->object_3d_2.SetVertexPosition(3,size,-size,z);
		}
		else
		{
			const float z = FLT_MAX;
			const float size = 100.0f;
			this->object_3d.SetProjection(Projection::Orthographic);
			this->object_3d.SetVertexPosition(0,0.0f,0.0f,z);
			this->object_3d.SetVertexPosition(1,size,0.0f,z);
			this->object_3d.SetVertexPosition(2,0.0f,size,z);
			this->object_3d.SetVertexPosition(3,size,size,z);
		}

		this->object_3d.SetVertexColor(0,Color::Red);
		this->object_3d.SetVertexColor(1,Color::Green);
		this->object_3d.SetVertexColor(2,Color::Black);
		this->object_3d.SetVertexColor(3,Color::White);
		this->object_3d.SetIndex(0,0);
		this->object_3d.SetIndex(1,1);
		this->object_3d.SetIndex(2,2);
		this->object_3d.SetIndex(3,3);

		this->object_3d_2.SetVertexColor(0,Color(Color::Gold,0.5f));
		this->object_3d_2.SetVertexColor(1,Color(Color::Magenta,0.5f));
		this->object_3d_2.SetVertexColor(2,Color(Color::Yellow,0.5f));
		this->object_3d_2.SetVertexColor(3,Color(Color::Silver,0.5f));
		this->object_3d_2.SetIndex(0,0);
		this->object_3d_2.SetIndex(1,1);
		this->object_3d_2.SetIndex(2,2);
		this->object_3d_2.SetIndex(3,3);
	}

	void Update() override
	{
		GameApplicationTest& game = GameState::GetGame<GameApplicationTest>();

		const float speed = 0.2f;
		const float speed_fast = 1.5f;
		static float translate_x = 0.0f;
		static float translate_z = 0.0f;
		static float rotate_x = 0.0f;
		static float rotate_y = 0.0f;

		const float mx = static_cast<float>(game.GetInput().GetMouseX());
		const float my = static_cast<float>(game.GetInput().GetMouseY());

		const string fps = "FPS: " + Convert::NumberToString(game.GetTimer().FPS()) + " ";
		const string timer = "Timer: " + Convert::NumberToString(+game.GetTimer().CurrentTimeAsMilliseconds()) + " ";

		game.GetApplication().SetTitle(fps + timer);

		if (game.GetInput().IsKeyboardKeyPressedOnce(KeyboardKey::Esc))
			game.GetApplication().Quit();

		else if (game.GetInput().IsKeyboardKeyPressedOnce(KeyboardKey::Enter))
		{
			static bool windowed = false;
			VideoMode video_mode(1280,720,BitsPerPixel::ColorDepth32Bits,true/*windowed*/,true);
			game.GetVideo().ChangeSettings(game.GetApplication(),video_mode);
			windowed = !windowed;
		}

		else if (game.GetInput().IsKeyboardKeyPressedOnce(KeyboardKey::T))
		{
			static bool pause = !game.GetTimer().GetPause();
			game.GetTimer().Pause(pause);
			pause = !pause;
		}
		else if (game.GetInput().IsKeyboardKeyPressedOnce(KeyboardKey::P))
		{
			static AspectRatio ar = game.GetVideo().GetAspectRatio();

			if (ar == AspectRatio::None)
				ar = AspectRatio::Normal4x3;

			else if (ar == AspectRatio::Normal4x3)
				ar = AspectRatio::Widescreen16x9;

			else if (ar == AspectRatio::Widescreen16x9)
				ar = AspectRatio::Widescreen16x10;

			else if (ar == AspectRatio::Widescreen16x10)
				ar = AspectRatio::None;

			game.GetVideo().SetAspectRatio(ar);
		}
		else if (game.GetInput().IsJoystickButtonPressedOnce(JoystickButton::Button03))
		{
			/*this->message_log.NewMessage(game.GetTimer(),"New Message!",Color::Yellow);
			this->message_log.AddMessage("Add Message!",Color::Green);*/
			this->message_log.NewMessage(game.GetTimer(),"!",Color::White);

		}
		else if (game.GetInput().IsKeyboardKeyPressedOnce(KeyboardKey::Space))
		{
			static TextureFilter texture_filter = game.GetVideo().GetTextureFilter();

			if (texture_filter == TextureFilter::Point)
				texture_filter = TextureFilter::Linear;

			else if (texture_filter == TextureFilter::Linear)
				texture_filter = TextureFilter::Point;

			game.GetVideo().SetTextureFilter(texture_filter);
		}
		else if (game.GetInput().IsMouseButtonPressedOnce(MouseButton::Left))
			this->text_dynamic.Play(true);

		if ((game.GetInput().IsJoystickPOVLeft()) || (game.GetInput().IsJoystickXAxisDown()))
			translate_x += speed;

		else if ((game.GetInput().IsJoystickPOVRight()) || (game.GetInput().IsJoystickXAxisUp()))
			translate_x -= speed;

		if ((game.GetInput().IsJoystickPOVUp()) || (game.GetInput().IsJoystickYAxisDown()))
			translate_z -= speed;

		else if ((game.GetInput().IsJoystickPOVDown()) || (game.GetInput().IsJoystickYAxisUp()))
			translate_z += speed;

		if (game.GetInput().IsJoystickZAxisUp())
			rotate_x -= speed_fast;

		else if (game.GetInput().IsJoystickZAxisDown())
			rotate_x += speed_fast;

		if ((game.GetInput().IsJoystickZAxisRotationUp()))
			rotate_y -= speed_fast;

		else if ((game.GetInput().IsJoystickZAxisRotationDown()))
			rotate_y += speed_fast;

		this->view_3d.GetRotate().SetX(rotate_x);
		this->view_3d.GetRotate().SetY(rotate_y);

		this->view_3d.GetTranslate().SetX(translate_x);
		this->view_3d.GetTranslate().SetZ(translate_z);

		//this->view_3d.GetTransform().SetX(translate_x);
		this->view_3d.GetTransform().SetZ(-translate_z -20.0f);

		//this->object_3d_2.GetTranslate().SetZ(translate);
		this->alucard.SetPosition(mx,my,true);
		this->view_2d.GetTransform().SetX(mx);
		this->view_2d.GetTransform().SetY(my);

		/*this->alucard.SetLeftTopVertexPosition(-25.0f,-25.0f);
		this->alucard.SetRightTopVertexPosition(+25.0f,-25.0f);
		this->alucard.SetLeftBottomVertexPosition(-25.0f,+25.0f);
		this->alucard.SetRightBottomVertexPosition(+25.0f,+25.0f);*/

		//this->view_2d.GetRotate().SetZ(static_cast<float>(game.GetTimer().CurrentTimeAsMilliseconds() % 360));

		this->text_dynamic.SetPosition(mx,my,true);
	}

	void Show() override
	{
		GameApplicationTest& game = GameState::GetGame<GameApplicationTest>();

		this->message_log.ShowMessageLog(game.GetVideo(),game.GetTimer());
		game.GetVideo().Draw(this->object_3d_2);
		this->alucard.Show(game.GetVideo());
		game.GetVideo().Draw(this->object_3d);
		//this->font_sprite.Show(game.GetVideo());
		this->text.Show(game.GetVideo());
		this->text_dynamic.Show(game.GetVideo(),game.GetTimer());
		//this->font_rect.Show(game.GetVideo());
		
	}
private:
	MessageLog message_log;
	Sprite alucard;
	Sprite font_sprite;
	Model object_3d;
	Model object_3d_2;
	View view_2d;
	View view_3d;
	Text text;
	TextDynamicWave text_dynamic;
	Sprite font_rect;
};

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	GameApplicationTest game;
	game.RegisterVideoEngine<VideoDirect3D9>(VideoEngine::Direct3D9);
	game.RegisterAudioEngine<AudioXAudio>(AudioEngine::XAudio);
	game.RegisterAudioEngine<AudioOpenAL>(AudioEngine::OpenAL);
	game.CreateGame();
	GameState::SetGame(game);
	GameState::AddGameState(make_unique<MainState>(),GameStateAction::None);
	return GameState::Main();
}
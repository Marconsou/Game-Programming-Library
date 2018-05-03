#include "ColorChanger.h"
#include "Random.h"
#include "AnimationFrame.h"
#include "TextDynamicZoom.h"
#include "TextDynamicWave.h"
#include "MessageLog.h"
#include "Window.h"
#include "TextBox.h"
#include "Button.h"
#include "TrackBar.h"
#include "CheckBox.h"
#include "RadioButton.h"
#include "DialogueBox.h"
#include "ComboBox.h"
#include "Label.h"
#include "GameState.h"
#include "ApplicationWin32.h"
#include "VideoDirect3D.h"
#include "AudioXAudio.h"
#include "AudioOpenAL.h"

using namespace std;
using namespace GPL;

class MyClass
{
public:
	Window* window;
	Video* video;
	Application* application;

	int mouse_up_count;
	int mouse_down_count;
	int mouse_click_count;
	int mouse_enter;
	int mouse_leave;
	int click;

	int leave;
	int enter;

	int key_down;
	int key_up;

	MyClass()
	{
		this->mouse_up_count = 0;
		this->mouse_down_count = 0;
		this->mouse_click_count = 0;

		this->mouse_enter = 0;
		this->mouse_leave = 0;

		this->click = 0;

		this->leave = 0;
		this->enter = 0;

		this->key_down = 0;
		this->key_up = 0;
	}

	void VALUECHANGED(const Control& control)
	{
		application->SetTitle("VALUECHANGED VALUECHANGED VALUECHANGED VALUECHANGED VALUECHANGED VALUECHANGED VALUECHANGED VALUECHANGED");
	}

	void LEAVE(const Control& control)
	{
		this->leave++;
	}

	void ENTER(const Control& control)
	{
		this->enter++;
	}

	void Inside(const Control& control)
	{
		this->mouse_enter++;
		this->window->SetCurrentBackground(2);
	}

	void Outside(const Control& control)
	{
		this->mouse_leave++;
		this->window->SetCurrentBackground(3);
	}

	void Hover(const Control& control)
	{
		this->window->SetCurrentBackground(0);
	}

	void HoverTeste(const Control& control)
	{
		application->SetTitle("HOVERHOVERHOVERHOVERHOVERHOVERHOVERHOVERHOVERHOVERHOVER");
	}

	void OutsideTeste(const Control& control)
	{
		application->SetTitle("OUTSIDEOUTSIDEOUTSIDEOUTSIDEOUTSIDEOUTSIDEOUTSIDEOUTSIDEOUTSIDE");
	}

	void Down(const Control& control,const MouseButton mouse_button,const float mouse_x,const float mouse_y)
	{
		this->mouse_down_count++;
		application->SetTitle("DOWNDOWNDOWNDOWNDOWNDOWNDOWNDOWNDOWNDOWNDOWNDOWN");
	}

	void Up(const Control& control,const MouseButton mouse_button,const float mouse_x,const float mouse_y)
	{
		this->mouse_up_count++;
		application->SetTitle("UPUPUPUPUPUPUPUPUPUPUPUPUPUPUPUPUPUPUPUPUPUPUPUUPPUUPPUUP");
	}

	void Click(const Control& control)
	{
		this->click++;
		application->SetTitle("CLICK CLICK CLICK CLICK CLICK CLICK CLICK CLICK CLICK CLICK");
	}

	void KEYDOWN(const Control& control,const KeyboardKey keyboard_key)
	{
		this->key_down++;
		application->SetTitle("Key Down Key Down Key Down Key Down Key Down Key Down Key Down");
	}

	void KEYUP(const Control& control,const KeyboardKey keyboard_key)
	{
		this->key_up++;
		application->SetTitle("Key Up Key Up Key Up Key Up Key Up Key Up Key Up Key Up Key Up Key Up ");
	}

	void MouseClick(const Control& control,const MouseButton mouse_button,const float mouse_x,const float mouse_y)
	{
		this->mouse_click_count++;

		if (mouse_button == MouseButton::Left)
			application->SetTitle("Left Left Left Left Left Left Left Left Left Left Left Left Left Left Left ");
		else if (mouse_button == MouseButton::Right)
			application->SetTitle("Right Right Right Right Right Right Right Right Right Right Right Right Right ");
		else if (mouse_button == MouseButton::Middle)
			application->SetTitle("Middle Middle Middle Middle Middle Middle Middle Middle Middle Middle Middle ");
		else
			application->SetTitle("ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ");
	}

	void Sair(const Control& control)
	{
		application->Quit();
	}
};

class GameApplicationTest : public Game
{
public:
	GameApplicationTest::GameApplicationTest() :
		Game(make_unique<ApplicationWin32>())
	{
		ResourceFile::SetResourceFileName("Data.pkg");

		
		remove("Data.pkg");
		ResourceFile::Write("Alucard.png");
		ResourceFile::Write("Warrior 00.png");
		ResourceFile::Write("Verdana.ttf");
		ResourceFile::Write("Qlassik Bold.otf");
		ResourceFile::Write("Using Item.ogg");
		ResourceFile::Write("Save.ogg");
		ResourceFile::Write("Main Music 02.ogg");
		ResourceFile::Write("Main Music 03.ogg");
		ResourceFile::Write("1.png");
		ResourceFile::Write("../Game Programming Library/Shaders/Render.vsh");
		ResourceFile::Write("../Game Programming Library/Shaders/Render.psh");
		ResourceFile::Write("Window1.png");
		ResourceFile::Write("Arial.ttf");
		ResourceFile::Write("Window.png");
		ResourceFile::Write("Close Button.png");
		ResourceFile::Write("Button.png");
		ResourceFile::Write("Radio Button.png");
		ResourceFile::Write("Check Box.png");
	}

	void CreateGame() override
	{
		this->Initialize(AudioEngine::XAudio,"Application Test",640,480,32,true,true,true,9);
		this->GetVideo().SetBackBufferClearColor(Color::White);
	}
};

class MainState : public GameState
{
private:
	AnimationFrame animation_frame;
	Window window;
	MyClass my_class;
	TextBox tbx;
	TextBox tbx2;
	ComboBox cbx;
	Button button;
	Button button2;
	TrackBar track_bar;
	TrackBar track_bar2;
	CheckBox cb;
	RadioButton rb;
	RadioButton rb2;
	RadioButton rb3;
	RadioButton rb4;
	DialogueBox dbx;
	Label label;
	Text text;
	Text text_top;
	Text upper;
	Text lower;
	Text event_counter;
	MessageLog ml;
	Sprite alucard;
	Sprite font_sprite;
	Model quadrado;
	Model quadrado2;
	Model opaque;
	Model opaque2;
	TextDynamicWave td;
	float z_change;
public:
	//Construtor
	MainState() :
		quadrado(TriangleStrip,2,4,4),
		quadrado2(TriangleStrip,2,4,4),
		opaque(TriangleList,0,6,12),
		opaque2(TriangleStrip,2,4,4),
		z_change(3.0f)
	{
		GameApplicationTest& game = GameState::GetGame<GameApplicationTest>();

		game.GetAudio().AddToMusicPlaylist(6);
		game.GetAudio().AddToMusicPlaylist(7,0.5f,71.5f);
		//game.GetAudio().PlayMusicFromPlaylist(7);

		game.GetAudio().LoadSound("Using Item.ogg");
		//game.GetAudio().LoadSound("Save.ogg");

		//game.GetAudio().LoadSound(5);
		game.GetAudio().LoadSound(5);

		const int font_index = 3;
		const FT_ULong first_character = ' ';
		const FT_ULong last_character = '~';
		game.GetVideo().LoadFont("Verdana.ttf",12,first_character,last_character);
		game.GetVideo().LoadFont(font_index,16);
		game.GetVideo().LoadFont("Arial.ttf",19,0,255);

		game.GetVideo().LoadTexture(0,Color::Magenta);
		game.GetVideo().LoadTexture(1);
		game.GetVideo().LoadTexture("1.png");
		game.GetVideo().LoadTexture("Window1.png",Color::Magenta);
		game.GetVideo().LoadTexture("Close Button.png");
		game.GetVideo().LoadTexture("Button.png");
		game.GetVideo().LoadTexture("Radio Button.png");
		game.GetVideo().LoadTexture("Check Box.png");

		animation_frame.SetAnimationFrame(game.GetTimer(),game.GetVideo().GetTexture("1.png"),192,192,3,0.33f);
		animation_frame.PlayAnimationFrame(game.GetTimer());
		//animation_frame.SetColor(Color::Green);

		Window::WindowsProperties(game.GetVideo().GetTexture("Window1.png"),4,63,1);

		my_class.window = &window;
		my_class.video = &game.GetVideo();
		my_class.application = &game.GetApplication();
		window.SetWindow(4,8,5.0f);
		//window.SetWindow(2,2,Color::Red,Color::Green,Color::Blue,Color::Yellow,5.0f);

		//window.SetPosition(300,300,false);
		window.SetPosition(101,121);

		window.AddEventOnMouseEnter(&MyClass::Inside,my_class);
		window.AddEventOnMouseHover(&MyClass::Hover,my_class);
		window.AddEventOnMouseLeave(&MyClass::Outside,my_class);

		window.AddEventOnEnter(&MyClass::ENTER,my_class);
		window.AddEventOnLeave(&MyClass::LEAVE,my_class);

		window.AddControl();

		tbx.SetTextBox(game.GetVideo().GetFont("Arial.ttf"),NameInput,15,1.0f,Color::Red,Color::Black,Color::Yellow,Color::Red);
		tbx.SetPosition(113,131);

		tbx.AddEventOnMouseEnter(&MyClass::Inside,my_class);
		tbx.AddEventOnMouseHover(&MyClass::Hover,my_class);
		tbx.AddEventOnMouseHover(&MyClass::HoverTeste,my_class);
		tbx.AddEventOnMouseLeave(&MyClass::Outside,my_class);
		tbx.AddEventOnMouseLeave(&MyClass::OutsideTeste,my_class);

		tbx.AddEventOnEnter(&MyClass::ENTER,my_class);
		tbx.AddEventOnLeave(&MyClass::LEAVE,my_class);

		tbx.SetBackgroundText("Type a text",Color::Gray);

		tbx.AddControl();

		tbx2.SetTextBox(game.GetVideo().GetFont("Verdana.ttf"),NameInput,15,3.0f,Color::Gold,Color::Yellow,Color(0.5f,0.5f,0.0f,0.5f),Color::Platinum);
		tbx2.SetPosition(101 + 25,tbx.GetY() + 70);

		tbx2.AddEventOnMouseEnter(&MyClass::Inside,my_class);
		tbx2.AddEventOnMouseHover(&MyClass::Hover,my_class);
		tbx2.AddEventOnMouseLeave(&MyClass::Outside,my_class);
		tbx2.AddControl();

		tbx2.AddEventOnEnter(&MyClass::ENTER,my_class);
		tbx2.AddEventOnLeave(&MyClass::LEAVE,my_class);

		tbx2.AddEventOnTextChanged(&MyClass::VALUECHANGED,my_class);

		tbx2.GainFocus(true);

		cbx.SetComboBox(game.GetVideo().GetFont("Verdana.ttf"),250,3.0f,Color(0.5f,0.0f,0.0f,1.0f));
		cbx.SetPosition(20,20);
		/*cbx.AddTextItem("MyItem_0",Color::Red);
		cbx.AddTextItem("MyItem_1",Color::Green);
		cbx.AddTextItem("MyItem_2",Color::Blue);
		cbx.AddTextItem("MyItem_3",Color::Yellow);
		cbx.AddTextItem("MyItem_4",Color::Magenta);
		cbx.AddTextItem("MyItem_5",Color::Cyan);*/

		vector<string> sr(game.GetVideo().GetSupportedResolutions(false,16));

		for (size_t i = 0; i < sr.size(); i++)
			cbx.AddTextItem(sr[i],Color::Yellow);

		cbx.SetSelectedIndex(1);
		cbx.AddControl();

		cbx.AddEventOnSelectedItemChanged(&MyClass::VALUECHANGED,my_class);
		//cbx.Clear();

		button.SetButton(game.GetVideo().GetFont(font_index),"My ",Color::White,Color::Platinum,true);
		button.AddButtonText("G",Color::Yellow);
		button.AddButtonText("ame Button",Color::White);
		button.SetButton(game.GetVideo().GetTexture("Button.png"),162,38);
		//button.SetButton(150,250,50,50);

		button.SetToolTip(game.GetVideo().GetFont(font_index),2);

		button.NewToolTipTextLine("My ToolTip Gold ",Color::Gold);
		button.AddToolTipTextLine("My ToolTip White ",Color::Platinum);
		button.NewToolTipTextLine("Red ",Color::Red);
		button.AddToolTipTextLine("Y ",Color::Yellow);
		button.NewToolTipTextLine("RedasdsadssssssssssssssssssssWg",Color::Blue);

		button.SetKeyboardKeyShortcut(KeyboardKey::F5);
		button.SetPosition(150,239);

		button.AddEventOnMouseEnter(&MyClass::Inside,my_class);
		button.AddEventOnMouseLeave(&MyClass::Outside,my_class);

		button.AddEventOnEnter(&MyClass::ENTER,my_class);
		button.AddEventOnLeave(&MyClass::LEAVE,my_class);

		button.AddEventOnClick(&MyClass::Click,my_class);
		button.AddEventOnMouseClick(&MyClass::MouseClick,my_class);
		button.AddEventOnMouseDown(&MyClass::Down,my_class);
		button.AddEventOnMouseUp(&MyClass::Up,my_class);
		button.AddEventOnKeyDown(&MyClass::KEYDOWN,my_class);
		button.AddEventOnKeyUp(&MyClass::KEYUP,my_class);
		button.AddControl();

		button2.SetButton(game.GetVideo().GetFont(font_index),"Another ",Color::Yellow);
		button2.AddButtonText("B",Color::Red);
		button2.AddButtonText("utton!",Color::Yellow);
		button2.SetKeyboardKeyShortcut(KeyboardKey::F6);
		button2.SetPosition(120,310);

		Color ccc(Color::Black.GetRed(),Color::Black.GetGreen(),Color::Black.GetBlue());
		ccc.SetAlpha(0.5f);
		button2.SetToolTip(game.GetVideo().GetFont("Verdana.ttf"),20.0f,ccc);
		button2.NewToolTipTextLine("My ToolTip Gold ",Color::Gold);
		button2.AddToolTipTextLine("My ToolTip White ",Color::Platinum);
		button2.NewToolTipTextLine("Red",Color::Red,TextAlignRight);
		button2.AddToolTipTextLine("Y",Color::Yellow);
		button2.NewToolTipTextLine("Redasdsadsssssssssssssssssssssssssssssssssssssssssss",Color::Blue,TextAlignLeft);

		button2.AddEventOnMouseEnter(&MyClass::Inside,my_class);
		button2.AddEventOnMouseLeave(&MyClass::Outside,my_class);

		button2.AddEventOnEnter(&MyClass::ENTER,my_class);
		button2.AddEventOnLeave(&MyClass::LEAVE,my_class);

		button2.AddEventOnClick(&MyClass::Click,my_class);
		button2.AddEventOnMouseClick(&MyClass::MouseClick,my_class);
		button2.AddEventOnMouseDown(&MyClass::Down,my_class);
		button2.AddEventOnMouseUp(&MyClass::Up,my_class);
		button2.AddEventOnKeyDown(&MyClass::KEYDOWN,my_class);
		button2.AddEventOnKeyUp(&MyClass::KEYUP,my_class);
		button2.AddControl();

		track_bar.SetTrackBar(37,100,15,20,50,Color::Black,Color::Red,OrientationHorizontal);
		track_bar.SetPosition(300,300);
		track_bar.AddEventOnValueChanged(&MyClass::VALUECHANGED,my_class);
		track_bar.AddControl();

		track_bar2.SetTrackBar(37,100,15,20,50,Color::Black,Color::Red,OrientationVertical);
		track_bar2.SetPosition(420,310);
		track_bar2.AddControl();

		cb.SetCheckBox(game.GetVideo().GetFont("Verdana.ttf"),"MyCheckBoxWgyvW",Color::Green,true,game.GetVideo().GetTexture("Check Box.png"),16.0f,16.0f,0.0f,0.0f,32.0f,32.0f,16.0f,0.0f);
		cb.SetPosition(1,340);
		cb.AddEventOnCheckedChanged(&MyClass::VALUECHANGED,my_class);
		cb.AddControl();

		rb.SetRadioButton(game.GetVideo().GetFont("Verdana.ttf"),"RB1",Color::Gold,true,game.GetVideo().GetTexture("Radio Button.png"),16.0f,16.0f,0.0f,0.0f);
		rb.SetPosition(1,420);
		rb.AddControl();

		rb2.SetRadioButton(game.GetVideo().GetFont("Verdana.ttf"),"RB2",Color::Gold,true,game.GetVideo().GetTexture("Radio Button.png"),16.0f,16.0f,0.0f,0.0f);
		rb2.SetPosition(1,450);
		rb2.AddEventOnCheckedChanged(&MyClass::VALUECHANGED,my_class);

		rb2.AddControl();

		rb3.SetRadioButton(game.GetVideo().GetFont("Verdana.ttf"),"RB3",Color::Gold,true,game.GetVideo().GetTexture("Radio Button.png"),16.0f,16.0f,0.0f,0.0f,"a");
		rb3.SetPosition(100,420);
		rb3.AddControl();

		rb4.SetRadioButton(game.GetVideo().GetFont("Verdana.ttf"),"RB4",Color::Gold,true,game.GetVideo().GetTexture("Radio Button.png"),16.0f,16.0f,0.0f,0.0f,"a");
		rb4.SetPosition(100,450);
		rb4.AddControl();

		dbx.SetDialogueBox(game.GetVideo().GetFont("Arial.ttf"),3,Window::GetBlockSize() * 12,10,10,0.030f,"My Title Default",Color::Green,true);
		dbx.SetWindow(Color(0,0,0,1),Color(0,0,1,1),Color(0,0,1,1),Color(0,0,0,1),5.0f);
		//dbx.SetWindow(5);
		dbx.SetWindowCurrentBackground(2);
		//dbx.SetPosition(10,10);
		dbx.AddText(" C++ is one of the",Color::Gold);
		dbx.AddText(" most popular programming languages and is implemented on a wide variety of hardware and operating system platforms. As an efficient compiler to native code, its application domains include systems software",Color::Gold);
		dbx.AddText("MyText @    Space     ",Color::White);
		dbx.AddText("Bre",Color::Red);
		dbx.AddText("Yellow",Color::Yellow);
		dbx.AddText("novo texto ",Color::White);
		dbx.AddText("parag nov ",Color::White);
		dbx.AddText("pteste2",Color::White);
		dbx.AddText("ptestedd3",Color::White);
		dbx.AddText("func3parg",Color::White);
		dbx.AddText("ending now >",Color::Red);
		//dbx.AddText("ending now         ",Color::Red);

		dbx.AddOption("Buy",Color::Yellow,5);
		dbx.AddOptionText("/",Color::Green);
		dbx.AddOptionText("Trade",Color::Blue);
		dbx.AddOption("Sell [CLICK HERE]",Color::Gold,10);
		dbx.AddOption("Exit [CLICK HERE]",Color::White,15);
		dbx.AddOption("Silver",Color::Silver,25);
		dbx.AddOption("Buy",Color::Yellow,5);
		dbx.AddOptionText("/",Color::Green);
		dbx.AddOptionText("Trade",Color::Blue);
		dbx.AddOption("Sell",Color::Gold,10);
		dbx.AddOption("Exit",Color::White,15);
		dbx.AddOption("ULTIMATE",Color::Cyan,25);
		dbx.AddOptionEventOnClick(6,&MyClass::Sair,my_class);
		dbx.SetPosition(50,50);

		label.SetText(game.GetVideo().GetFont("Arial.ttf"),"LABEL",Color::Yellow,true);
		label.SetToolTip(game.GetVideo().GetFont("Verdana.ttf"),3.0f,ccc);
		label.NewToolTipTextLine("My tooltip hover label",Color::Green);
		label.SetPosition(540,380);
		label.AddControl();

		text.SetText(game.GetVideo().GetFont(font_index),"",Color::Gold,true);

		string buf;	for (char i = ' '; i < '~'; i++) buf.push_back(i);
		text_top.SetText(game.GetVideo().GetFont(font_index),"Wgy pW" + buf,Color::Red,true);

		text_top.SetColor(1,Color::Gold);

		upper.SetText(game.GetVideo().GetFont("Arial.ttf"),text_top.GetString(),Color::Green,true);
		upper.SetPosition(0,text_top.GetH());

		lower.SetText(game.GetVideo().GetFont("Verdana.ttf"),text_top.GetString(),Color::Blue,true);
		lower.SetPosition(0,upper.GetY() + upper.GetH());

		event_counter.SetText(game.GetVideo().GetFont("Verdana.ttf"),"",Color::Green,true);
		event_counter.SetPosition(0,400);

		ml.SetMessageLog(game.GetVideo().GetFont(font_index),"Log: ",Color::Yellow,3);
		ml.SetPosition(0,450);

		alucard.SetTexture(game.GetVideo().GetTexture(0));
		alucard.SetColor(Color(1,1,1,0.5f));
		alucard.SetSize(64.0f,96.0f);
		//alucard.SetTexturePosition(32,48);

		font_sprite.SetColor(Color::Green);
		font_sprite.SetTexture(game.GetVideo().GetTexture("Arial.ttf"));
		font_sprite.SetSize(static_cast<float>(font_sprite.GetTexture().GetWidth()),static_cast<float>(font_sprite.GetTexture().GetHeight()));
		font_sprite.SetPosition(0,lower.GetY() + lower.GetH());

		//3D
		const float alpha_b1 = 0.3f;
		const float z1 = 3;

		quadrado.SetVertexPosition(0,-1,1,z1);
		quadrado.SetVertexColor(0,Color(1,0,0,alpha_b1));
		quadrado.SetVertexPosition(1,3,1,z1);
		quadrado.SetVertexColor(1,Color(1,0,0,alpha_b1));
		quadrado.SetVertexPosition(2,-1,-1,z1);
		quadrado.SetVertexColor(2,Color(1,0,0,alpha_b1));
		quadrado.SetVertexPosition(3,1,-1,z1);
		quadrado.SetVertexColor(3,Color(1,0,0,alpha_b1));
		quadrado.SetIndex(0,0);quadrado.SetIndex(1,1);quadrado.SetIndex(2,2);quadrado.SetIndex(3,3);

		const float alpha_b = 0.9f;
		const float z2 = -1;

		quadrado2.SetVertexPosition(0,-1,1,z2);
		quadrado2.SetVertexColor(0,Color(1,0,0,alpha_b));
		quadrado2.SetVertexTextureCoordinate(0,0,0);
		quadrado2.SetVertexPosition(1,1,1,z2);
		quadrado2.SetVertexColor(1,Color(0,1,0,alpha_b));
		quadrado2.SetVertexTextureCoordinate(1,0.5f,0);
		quadrado2.SetVertexPosition(2,-1,-1,z2);
		quadrado2.SetVertexColor(2,Color(0,0,1,alpha_b));
		quadrado2.SetVertexTextureCoordinate(2,0,0.75f);
		quadrado2.SetVertexPosition(3,1,-1,z2);
		quadrado2.SetVertexColor(3,Color(0,0,0,alpha_b));
		quadrado2.SetVertexTextureCoordinate(3,0.5f,0.75f);
		quadrado2.SetIndex(0,0);quadrado2.SetIndex(1,1);quadrado2.SetIndex(2,2);quadrado2.SetIndex(3,3);
		quadrado2.SetTexture(game.GetVideo().GetTexture(0));

		const float z3 = 6;

		opaque.SetVertexPosition(0,-1,1,z3);
		opaque.SetVertexColor(0,Color(0,0,1,0.5f));
		opaque.SetVertexPosition(1,1,1,z3);
		opaque.SetVertexColor(1,Color(0,0,1,0.5f));
		opaque.SetVertexPosition(2,-1,-1,z3);
		opaque.SetVertexColor(2,Color(0,0,1,0.5f));
		opaque.SetVertexPosition(3,1,-1,z3);
		opaque.SetVertexColor(3,Color(0,0,1,0.5f));
		opaque.SetVertexPosition(4,1,1,z3 + 1);
		opaque.SetVertexColor(4,Color::Cyan);
		opaque.SetVertexPosition(5,1,-1,z3 + 1);
		opaque.SetVertexColor(5,Color::Magenta);
		opaque.SetIndex(0,0);opaque.SetIndex(1,1);opaque.SetIndex(2,2);
		opaque.SetIndex(3,3);opaque.SetIndex(4,2);opaque.SetIndex(5,1);
		opaque.SetIndex(6,1);opaque.SetIndex(7,4);opaque.SetIndex(8,3);
		opaque.SetIndex(9,5);opaque.SetIndex(10,3);opaque.SetIndex(11,4);
		opaque.SetPrimitiveCount(opaque.GetVertexTotal() - 2);

		opaque2.SetVertexPosition(0,-1,1,2);
		opaque2.SetVertexColor(0,Color::Yellow);
		opaque2.SetVertexPosition(1,1,1,2);
		opaque2.SetVertexColor(1,Color::Yellow);
		opaque2.SetVertexPosition(2,-1,-1,2);
		opaque2.SetVertexColor(2,Color::Yellow);
		opaque2.SetVertexPosition(3,1,-1,2);
		opaque2.SetVertexColor(3,Color::Yellow);
		opaque2.SetIndex(0,0);opaque2.SetIndex(1,1);opaque2.SetIndex(2,2);opaque2.SetIndex(3,3);

		game.GetScreenEffect().StartFadeInScreen(FadeNormal);
	}

	//Atualizar dados e a lógica de todo o conteúdo
	virtual void Update()
	{
	}

	//Mostrar todo o conteúdo
	virtual void Show()
	{
		GameApplicationTest& game = GameState::GetGame<GameApplicationTest>();

		if (game.GetInput().IsKeyboardKeyPressedOnce(KeyboardKey::Esc))
			game.GetApplication().Quit();

		else if (game.GetInput().IsKeyboardKeyPressedOnce(KeyboardKey::I))
			game.GetVideo().ChangeSettings(game.GetApplication(),800,600,32,false,true);

		else if (game.GetInput().IsKeyboardKeyPressedOnce(KeyboardKey::P))
			game.GetVideo().ChangeSettings(game.GetApplication(),640,480,32,true,true);

		else if (game.GetInput().IsKeyboardKeyPressedOnce(KeyboardKey::O))
			game.GetVideo().ChangeSettings(game.GetApplication(),1280,800,16,true,true);

		else if (game.GetInput().IsKeyboardKeyPressedOnce(KeyboardKey::F))
			game.GetVideo().ChangeSettings(game.GetApplication(),1920,1080,32,false,true);

		else if (game.GetInput().IsKeyboardKeyPressedOnce(KeyboardKey::U))
			game.GetVideo().ChangeSettings(game.GetApplication(),1920,1080,32,true,true);

		else if (game.GetInput().IsKeyboardKeyPressedOnce(KeyboardKey::Enter))
			game.GetVideo().ChangeSettings(game.GetApplication(),640,480,32,false,true);

		else if (game.GetInput().IsKeyboardKeyPressedOnce(KeyboardKey::Key1))
			game.GetAudio().PlayMusicFromPlaylist(7);

		else if (game.GetInput().IsKeyboardKeyPressedOnce(KeyboardKey::Key2))
			game.GetAudio().PlayMusicFromPlaylist(6);

		else if (game.GetInput().IsKeyboardKeyPressedOnce(KeyboardKey::Key3))
			game.GetAudio().EnableSound();

		else if (game.GetInput().IsKeyboardKeyPressedOnce(KeyboardKey::Key4))
			game.GetAudio().DisableSound();

		else if (game.GetInput().IsKeyboardKeyPressedOnce(KeyboardKey::Key5))
			game.GetAudio().EnableMusic();

		else if (game.GetInput().IsKeyboardKeyPressedOnce(KeyboardKey::Key6))
			game.GetAudio().DisableMusic();

		else if (game.GetInput().IsKeyboardKeyPressedOnce(KeyboardKey::Key7))
		{
			game.GetAudio().StartFadeOutMusic();
			game.GetScreenEffect().StartFadeOutScreen(FadeNormal);
		}
		else if (game.GetInput().IsKeyboardKeyPressedOnce(KeyboardKey::Key8))
		{
			game.GetAudio().StartFadeInMusic();
			game.GetScreenEffect().StartFadeInScreen(FadeNormal);
		}
		else if (game.GetInput().IsKeyboardKeyPressedOnce(KeyboardKey::Key9))
			game.GetAudio().PlaySound(5);

		else if (game.GetInput().IsKeyboardKeyPressedOnce(KeyboardKey::Key0))
			game.GetAudio().PlaySound("Using Item.ogg");

		game.GetTimer().Pause(game.GetInput().IsKeyboardKeyPressed(KeyboardKey::M));

		const float mx = static_cast<float>(game.GetInput().GetMouseX());
		const float my = static_cast<float>(game.GetInput().GetMouseY());

		const float speed = 0.2f;
		if (game.GetInput().IsKeyboardKeyPressed(KeyboardKey::Insert))
			z_change += speed;
		if (game.GetInput().IsKeyboardKeyPressed(KeyboardKey::Delete))
			z_change -= speed;

		for (size_t i = 0; i < quadrado2.GetVertexTotal(); i++)
			quadrado2.SetVertexPosition(i,quadrado2.GetVertexPosition(i).GetX(),quadrado2.GetVertexPosition(i).GetY(),z_change);

		const float spd = 0.1f;
		if (game.GetInput().IsKeyboardKeyPressed(KeyboardKey::Left))
			game.GetVideo().GetCamera().GetPerspectiveCameraPosition().SetX(game.GetVideo().GetCamera().GetPerspectiveCameraPosition().GetX() + spd);
		else if (game.GetInput().IsKeyboardKeyPressed(KeyboardKey::Right))
			game.GetVideo().GetCamera().GetPerspectiveCameraPosition().SetX(game.GetVideo().GetCamera().GetPerspectiveCameraPosition().GetX() - spd);

		if (game.GetInput().IsKeyboardKeyPressed(KeyboardKey::Down))
			game.GetVideo().GetCamera().GetPerspectiveCameraPosition().SetZ(game.GetVideo().GetCamera().GetPerspectiveCameraPosition().GetZ() + spd);
		else if (game.GetInput().IsKeyboardKeyPressed(KeyboardKey::Up))
			game.GetVideo().GetCamera().GetPerspectiveCameraPosition().SetZ(game.GetVideo().GetCamera().GetPerspectiveCameraPosition().GetZ() - spd);

		if (game.GetInput().IsKeyboardKeyPressed(KeyboardKey::PageUp))
			game.GetVideo().GetCamera().GetPerspectiveCameraPosition().SetY(game.GetVideo().GetCamera().GetPerspectiveCameraPosition().GetY() + spd);
		else if (game.GetInput().IsKeyboardKeyPressed(KeyboardKey::PageDown))
			game.GetVideo().GetCamera().GetPerspectiveCameraPosition().SetY(game.GetVideo().GetCamera().GetPerspectiveCameraPosition().GetY() - spd);

		game.GetVideo().GetCamera().GetPerspectiveCameraRotation().SetX(my - 240);
		game.GetVideo().GetCamera().GetPerspectiveCameraRotation().SetY(-mx - 320);

		game.GetVideo().Draw(opaque2);
		game.GetVideo().Draw(quadrado);

		game.GetVideo().Draw(quadrado2);

		game.GetVideo().Draw(opaque);

		quadrado.GetRotate().SetZ(game.GetTimer().CurrentTime() / 0.01f);

		static float rot = 0.0f;

		if (game.GetInput().IsKeyboardKeyPressed(KeyboardKey::T))
		{
			alucard.SetRotate(game.GetTimer().CurrentTime() / 0.01f);
			alucard.SetTransformX(alucard.GetW() / 2);
			alucard.SetTransformY(alucard.GetH() / 2);
		}
		
		text.SetRotate(game.GetTimer().CurrentTime() / 0.01f);

		const string buffer("MV: " + Convert::NumberToString(game.GetAudio().GetMusicVolume()) + " " + Convert::NumberToString(Timer::FPS()) + " " + Convert::NumberToString(game.GetTimer().CurrentTime()) + " " + Convert::NumberToString(game.GetInput().GetMouseX()) + "x" + Convert::NumberToString(game.GetInput().GetMouseY()));
		if (game.GetInput().IsKeyboardKeyPressed(KeyboardKey::LeftControl) || game.GetInput().IsKeyboardKeyPressed(KeyboardKey::RightControl))
			game.GetAudio().SetMusicVolume(mx / (static_cast<float>(game.GetVideo().GetWidth())));

		game.GetApplication().SetTitle(buffer);
		//game.GetVideo().SetTitle(Convert::NumberToString(track_bar.GetValue()) + " " +Convert::NumberToString(track_bar2.GetValue()));

		if (game.GetInput().IsKeyboardKeyPressed(KeyboardKey::Space))
			game.GetAudio().SetMusicFrequencyRatio(mx / (static_cast<float>(game.GetVideo().GetWidth()) / 2.0f));
		else
			game.GetAudio().SetMusicFrequencyRatio(1.0f);

		text.SetPosition(game.GetVideo().GetWidth() / 2.0f ,game.GetVideo().GetHeight() / 2.0f,true);
		text.SetTransformX(text.GetW() / 2);
		text.SetTransformY(text.GetH() / 2);

		static int ci = 0;
		static Interval cii(0.1f,game.GetTimer());
		if (cii.Action(game.GetTimer()))
		{
			ci++;
			ci %= text_top.GetValidCharacterTotal();
		}

		if (ci > 0)
			text_top.SetColor(ci - 1,Color::Red);

		{
			const float r = Random::GenerateNumber(0,255) / 255.0f;
			const float g = Random::GenerateNumber(0,255) / 255.0f;
			const float b = Random::GenerateNumber(0,255) / 255.0f;
			text_top.SetColor(ci,Color(r,g,b));
		}

		if (game.GetInput().IsKeyboardKeyPressed(KeyboardKey::R))
			alucard.SetColor(Color::Red,Color::Green,Color::Blue,Color::Gold);
		else
			alucard.SetColor(Color::White);


		if (game.GetInput().IsMouseWheelUp())
		{
			alucard.SetColor(Color::Gold);
			game.GetInput().SetMousePosition(400,300);
		}
		else if (game.GetInput().IsMouseWheelDown())
		{
			game.GetInput().SetMousePosition(0,0);
			alucard.SetColor(Color::Silver);
		}
		else
			alucard.SetColor(Color::White);

		game.GetVideo().SetTextureFilter(static_cast<VideoTextureFilter>(game.GetInput().IsKeyboardKeyPressed(KeyboardKey::Space)));

		const bool w_pressed = game.GetInput().IsKeyboardKeyPressed(KeyboardKey::W);
		alucard.SetTurnHorizontal(w_pressed);
		alucard.SetTurnVertical(w_pressed);

		if (w_pressed)
			quadrado2.GetTextureCoordinateInverted().SetX((64.0f + ((quadrado.GetVertexPosition(0).GetX()+1) * 2.0f)) / 128.0f);
		else
			quadrado2.GetTextureCoordinateInverted().SetX(0.0f);

		if (w_pressed)
			quadrado2.GetTextureCoordinateInverted().SetY((96.0f + ((quadrado.GetVertexPosition(0).GetY()-1) * 2.0f)) / 128.0f);
		else
			quadrado2.GetTextureCoordinateInverted().SetY(0.0f);

		static string audio_library;

		if (game.GetInput().IsKeyboardKeyPressedOnce(KeyboardKey::F1))
		{
			audio_library = "XAudio";
			game.GetApplication().SetTitle("LOADING:" + audio_library + buffer);
			game.ChangeAudioEngine(AudioEngine::XAudio);
		}

		if (game.GetInput().IsKeyboardKeyPressedOnce(KeyboardKey::F2))
		{
			audio_library = "OpenAL";
			game.GetApplication().SetTitle("LOADING:" + audio_library + buffer);
			game.ChangeAudioEngine(AudioEngine::OpenAL);
		}

		alucard.SetPosition(mx,my);

		if (!game.GetInput().IsMouseButtonPressed(MouseButton::Right))
		{
			//text.SetColor(Color::Gold);
			text.SetString(game.GetVideo().GetDeviceDisplayName());
			text.SetColor(3,Color::Red);
		}
		else
		{
			//text.SetColor(Color::Blue);
			text.SetString(game.GetAudio().GetDeviceDisplayName() + " " + audio_library);
		}

		float mod_y = 50;
		if (game.GetInput().IsKeyboardKeyPressedOnce(KeyboardKey::N))
		{
			animation_frame.PlayAnimationFrame(game.GetTimer());

			static bool c = false;
			c = !c;
			//c = true;
			//c = false;

			/*if (1)
			{
			const float r = Random::GenerateNumber(0,255) / 255.0f;
			const float g = Random::GenerateNumber(0,255) / 255.0f;
			const float b = Random::GenerateNumber(0,255) / 255.0f;

			td.push_back(TextDynamic());
			TextDynamic& t = td.back();
			t.SetTextDynamic(game.GetVideo().GetFont("Arial.ttf"),"+"+ Convert::NumberToString(Random::GenerateNumber(1000,9999)),Color(r,g,b,1.0f),(c) ? StyleWave : StyleZoom);
			t.SetPosition(mx,my - mod_y,true);
			t.PlayTextDynamic(game.GetVideo());
			}
			else
			{
			td1.SetTextDynamic(game.GetVideo().GetFont(3),"+" + Convert::NumberToString(Random::GenerateNumber(1000,9999)),Color::Green,(c) ? StyleWave : StyleZoom);
			td1.SetPosition(mx,my,true);
			td1.PlayTextDynamic(game.GetVideo());
			}*/

			const float r = Random::GenerateNumber(0,255) / 255.0f;
			const float g = Random::GenerateNumber(0,255) / 255.0f;
			const float b = Random::GenerateNumber(0,255) / 255.0f;

			td.SetTextDynamic(game.GetVideo().GetFont("Arial.ttf"),"+"+ Convert::NumberToString(Random::GenerateNumber(1000,9999)),Color(r,g,b,1.0f));
			td.SetPosition(mx,my - mod_y,true);
			td.PlayTextDynamic(game.GetVideo());

			ml.NewMessage(game.GetTimer(),"Gold ",Color::Gold);
			ml.AddMessage("Red ",Color::Red);
			ml.AddMessage("Green ",Color::Green);
		}

		event_counter.SetString("MU:" + Convert::NumberToString(my_class.mouse_up_count) +
			"   MD:" + Convert::NumberToString(my_class.mouse_down_count) +
			"   MC:" + Convert::NumberToString(my_class.mouse_click_count) +
			"   ME:" + Convert::NumberToString(my_class.mouse_enter) +
			"   ML:" + Convert::NumberToString(my_class.mouse_leave) +
			"   C:" + Convert::NumberToString(my_class.click) +
			"   E:" + Convert::NumberToString(my_class.enter) +
			"   L:" + Convert::NumberToString(my_class.leave) +
			"   KD:" + Convert::NumberToString(my_class.key_down) +
			"   KU:" + Convert::NumberToString(my_class.key_up));

		font_sprite.ShowSprite(game.GetVideo());
		alucard.ShowSprite(game.GetVideo());

		text_top.ShowText(game.GetVideo());
		upper.ShowText(game.GetVideo());
		lower.ShowText(game.GetVideo());
		text.ShowText(game.GetVideo());

		event_counter.ShowText(game.GetVideo());

		animation_frame.SetPosition(game.GetVideo().GetWidth() / 2.0f,game.GetVideo().GetHeight() / 2.0f,true);
		animation_frame.ShowAnimationFrame(game.GetVideo(),game.GetTimer(),true);

		td.SetPosition(mx,my,true);
		td.ShowTextDynamic(game.GetVideo(),game.GetTimer());

		/*if (!td.empty())
		td.back().SetPosition(mx,my - mod_y,true);

		static vector<int> del;
		for (size_t i = 0; i < del.size(); i++)
		{
		td.erase(td.begin() + del[i]);
		del.erase(del.begin() + i);
		}

		for (size_t i = 0; i < td.size(); i++)
		{
		if (!td[i].ShowTextDynamic(game.GetVideo(),game.GetTimer()))
		del.push_back(i);
		}*/

		if (game.GetInput().IsKeyboardKeyPressedOnce(KeyboardKey::SingleQuote))
		{
			tbx.SetEnabled(!tbx.GetEnabled());
			button.SetEnabled(!button.GetEnabled());
			track_bar.SetEnabled(!track_bar.GetEnabled());
			cb.SetEnabled(!cb.GetEnabled());
			rb.SetEnabled(!rb.GetEnabled());
			button2.RemoveControl();
			dbx.SetEnabled(!dbx.GetEnabled());
			cbx.SetEnabled(!cbx.GetEnabled());
			label.SetEnabled(!label.GetEnabled());
		}
		if (game.GetInput().IsKeyboardKeyPressedOnce(KeyboardKey::Q))
		{
			dbx.AddControl();
		}

		if (game.GetInput().IsKeyboardKeyPressed(KeyboardKey::F3))
			window.SetInnerBlockQuantity(game.GetInput().GetMouseX() / static_cast<int>(Window::GetBlockSize()),game.GetInput().GetMouseY() / static_cast<int>(Window::GetBlockSize()));

		ml.ShowMessageLog(game.GetVideo(),game.GetTimer());

		if (!game.GetInput().IsKeyboardKeyPressed(KeyboardKey::A))
			dbx.SetPosition(mx,my,true);
		else
			dbx.SetPosition(50,50);

		Control::ShowControls(game.GetInput(),game.GetVideo(),game.GetTimer());
		game.GetScreenEffect().ShowScreenEffect(game.GetVideo(),game.GetTimer());
	}
};

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	GameApplicationTest game;
	game.RegisterVideoEngine<VideoDirect3D>(VideoEngine::Direct3D);
	game.RegisterAudioEngine<AudioXAudio>(AudioEngine::XAudio);
	game.RegisterAudioEngine<AudioOpenAL>(AudioEngine::OpenAL);
	game.CreateGame();
	GameState::SetGame(game);
	GameState::AddGameState(make_shared<MainState>(),NoGameStateAction);
	return GameState::Main();
}
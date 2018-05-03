#include "OptionsMenuGameplay.h"

using namespace std;
using namespace GPL;
using namespace RPG;

OptionsMenuGameplay::OptionsMenuGameplay(const float start_x,const float start_y) :
	Menu(OptionsMenuGameplayControlMax)
{
	//Language Label
	this->CreateControl<Label>();

	//Language Combo Box
	this->CreateControl<ComboBox>();

	//Text Speed Label
	this->CreateControl<Label>();

	//Text Speed Combo Box
	this->CreateControl<ComboBox>();

	//Default Window Radio Button
	this->CreateControl<RadioButton>();

	//Default Window Combo Box
	this->CreateControl<ComboBox>();

	//Custom Window Radio Button
	this->CreateControl<RadioButton>();

	//Custom Window Combo Box
	this->CreateControl<ComboBox>();

	//Red Component Track Bar
	this->CreateControl<TrackBar>();

	//Green Component Track Bar
	this->CreateControl<TrackBar>();

	//Blue Component Track Bar
	this->CreateControl<TrackBar>();

	//Alpha Component Track Bar
	this->CreateControl<TrackBar>();

	//Sample Window
	this->CreateControl<Window>();

	this->LoadContents(true,start_x,start_y);
}

void OptionsMenuGameplay::Hiding()
{
	GameState::Hiding();
	this->ControlsUpdate(false);
}

void OptionsMenuGameplay::Showing()
{
	GameState::Showing();
	this->ControlsUpdate(true);
}

void OptionsMenuGameplay::LoadContents(const bool load_once,const float start_x,const float start_y)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	game.GetConfiguration().LoadFromFile();

	this->color_left_top.SetRed(game.GetConfiguration().GetColorLeftTop().GetRed());
	this->color_left_top.SetGreen(game.GetConfiguration().GetColorLeftTop().GetGreen());
	this->color_left_top.SetBlue(game.GetConfiguration().GetColorLeftTop().GetBlue());
	this->color_left_top.SetAlpha(game.GetConfiguration().GetColorLeftTop().GetAlpha());

	this->color_right_top.SetRed(game.GetConfiguration().GetColorRightTop().GetRed());
	this->color_right_top.SetGreen(game.GetConfiguration().GetColorRightTop().GetGreen());
	this->color_right_top.SetBlue(game.GetConfiguration().GetColorRightTop().GetBlue());
	this->color_right_top.SetAlpha(game.GetConfiguration().GetColorRightTop().GetAlpha());

	this->color_left_bottom.SetRed(game.GetConfiguration().GetColorLeftBottom().GetRed());
	this->color_left_bottom.SetGreen(game.GetConfiguration().GetColorLeftBottom().GetGreen());
	this->color_left_bottom.SetBlue(game.GetConfiguration().GetColorLeftBottom().GetBlue());
	this->color_left_bottom.SetAlpha(game.GetConfiguration().GetColorLeftBottom().GetAlpha());

	this->color_right_bottom.SetRed(game.GetConfiguration().GetColorRightBottom().GetRed());
	this->color_right_bottom.SetGreen(game.GetConfiguration().GetColorRightBottom().GetGreen());
	this->color_right_bottom.SetBlue(game.GetConfiguration().GetColorRightBottom().GetBlue());
	this->color_right_bottom.SetAlpha(game.GetConfiguration().GetColorRightBottom().GetAlpha());

	//Language Label
	Label& language_label = this->GetControl<Label>(LanguageLabel);
	language_label.SetText(this->GetDefaultFontMedium(),game.GetDatabase().GetLanguageText(OptionsMenuLanguageTextID),Color::White);
	if (load_once)
		language_label.SetPosition(start_x + 10.0f,start_y + 10.0f);

	const Color combo_box_background_color(0.0f,0.0f,0.0f,0.75f);
	const Color combo_box_border_color(Color::Gold);
	const Color combo_box_selection_color(1.0f,1.0f,1.0f,0.5f);

	//Language Combo Box
	ComboBox& language_combo_box = this->GetControl<ComboBox>(LanguageComboBox);
	language_combo_box.Clear();
	language_combo_box.SetComboBox(this->GetDefaultFontMedium(),165.0f,2.0f,combo_box_background_color,combo_box_border_color,combo_box_selection_color);
	language_combo_box.AddTextItem(game.GetDatabase().GetLanguageText(OptionsMenuEnglishTextID),Color::White);
	language_combo_box.AddTextItem(game.GetDatabase().GetLanguageText(OptionsMenuPortugueseTextID),Color::White);
	language_combo_box.SetSelectedIndex(game.GetConfiguration().GetLanguage().GetCurrent());
	if (load_once)
	{
		language_combo_box.SetPosition(language_label.GetX() + 210.0f,language_label.GetY() - 1.0f);
		language_combo_box.AddEventOnClick(&Menu::GeneralOnClick,static_cast<Menu&>(*this));
	}

	//Text Speed Label
	Label& text_speed_label = this->GetControl<Label>(TextSpeedLabel);
	text_speed_label.SetText(this->GetDefaultFontMedium(),game.GetDatabase().GetLanguageText(OptionsMenuTextSpeedTextID),Color::White);
	if (load_once)
		text_speed_label.SetPosition(language_label.GetX(),language_label.GetY() + language_label.GetH() + 10.0f);

	//Text Speed Combo Box
	ComboBox& text_speed_combo_box = this->GetControl<ComboBox>(TextSpeedComboBox);
	text_speed_combo_box.Clear();
	text_speed_combo_box.SetComboBox(this->GetDefaultFontMedium(),165.0f,2.0f,combo_box_background_color,combo_box_border_color,combo_box_selection_color);
	text_speed_combo_box.AddTextItem(game.GetDatabase().GetLanguageText(OptionsMenuNormalTextID),Color::White);
	text_speed_combo_box.AddTextItem(game.GetDatabase().GetLanguageText(OptionsMenuFastTextID),Color::White);
	text_speed_combo_box.AddTextItem(game.GetDatabase().GetLanguageText(OptionsMenuInstantlyTextID),Color::White);
	text_speed_combo_box.SetSelectedIndex(game.GetConfiguration().GetTextSpeed().GetCurrent());
	if (load_once)
	{
		text_speed_combo_box.SetPosition(text_speed_label.GetX() + 210.0f,text_speed_label.GetY() - 1.0f);
		text_speed_combo_box.AddEventOnClick(&Menu::GeneralOnClick,static_cast<Menu&>(*this));
	}

	//Default Window Radio Button
	RadioButton& default_window_radio_button = this->GetControl<RadioButton>(DefaultWindowRadioButton);
	default_window_radio_button.SetRadioButton(this->GetDefaultFontMedium(),game.GetDatabase().GetLanguageText(OptionsMenuDefaultWindowTextID),Color::White,game.GetVideo().GetTexture(TextureCommonFileID),16.0f,16.0f,65.0f,17.0f);
	default_window_radio_button.SetChecked(game.GetConfiguration().GetDefaultWindowSelected());
	if (load_once)
	{
		default_window_radio_button.SetPosition(text_speed_label.GetX(),text_speed_label.GetY() + text_speed_label.GetH() + 10.0f);
		default_window_radio_button.AddEventOnMouseDown(&OptionsMenuGameplay::GeneralOnMouseDown,*this);
		default_window_radio_button.AddEventOnCheckedChanged(&OptionsMenuGameplay::DefaultWindowOnCheckedChanged,*this);
	}

	//Default Window Combo Box
	ComboBox& default_window_combo_box = this->GetControl<ComboBox>(DefaultWindowComboBox);
	default_window_combo_box.Clear();
	default_window_combo_box.SetComboBox(this->GetDefaultFontMedium(),165.0f,2.0f,combo_box_background_color,combo_box_border_color,combo_box_selection_color);
	default_window_combo_box.AddTextItem(game.GetDatabase().GetLanguageText(DefaultTextID),Color::White);
	default_window_combo_box.AddTextItem(game.GetDatabase().GetLanguageText(OptionsMenuRedBlackTextID),Color::White);
	default_window_combo_box.SetSelectedIndex(game.GetConfiguration().GetDefaultWindow().GetCurrent());
	if (load_once)
	{
		default_window_combo_box.SetPosition(default_window_radio_button.GetX() + 210.0f,default_window_radio_button.GetY() - 1.0f);
		default_window_combo_box.AddEventOnClick(&Menu::GeneralOnClick,static_cast<Menu&>(*this));
		default_window_combo_box.AddEventOnSelectedItemChanged(&OptionsMenuGameplay::DefaultWindowOnSelectedItemChanged,*this);
	}

	//Custom Window Radio Button
	RadioButton& custom_window_radio_button = this->GetControl<RadioButton>(CustomWindowRadioButton);
	custom_window_radio_button.SetRadioButton(this->GetDefaultFontMedium(),game.GetDatabase().GetLanguageText(OptionsMenuCustomWindowTextID),Color::White,game.GetVideo().GetTexture(TextureCommonFileID),16.0f,16.0f,65.0f,17.0f);
	custom_window_radio_button.SetChecked(!game.GetConfiguration().GetDefaultWindowSelected());
	if (load_once)
	{
		custom_window_radio_button.SetPosition(default_window_radio_button.GetX(),default_window_radio_button.GetY() + default_window_radio_button.GetH() + 10.0f);
		custom_window_radio_button.AddEventOnMouseDown(&OptionsMenuGameplay::GeneralOnMouseDown,*this);
	}

	ComboBox& custom_window_combo_box = this->GetControl<ComboBox>(CustomWindowComboBox);
	const int selected_item_index = custom_window_combo_box.GetSelectedIndex();

	//Custom Window Combo Box
	custom_window_combo_box.Clear();
	custom_window_combo_box.SetComboBox(this->GetDefaultFontMedium(),165.0f,2.0f,combo_box_background_color,combo_box_border_color,combo_box_selection_color);
	custom_window_combo_box.AddTextItem(game.GetDatabase().GetLanguageText(OptionsMenuLeftTopTextID),Color::White);
	custom_window_combo_box.AddTextItem(game.GetDatabase().GetLanguageText(OptionsMenuRightTopTextID),Color::White);
	custom_window_combo_box.AddTextItem(game.GetDatabase().GetLanguageText(OptionsMenuLeftBottomTextID),Color::White);
	custom_window_combo_box.AddTextItem(game.GetDatabase().GetLanguageText(OptionsMenuRightBottomTextID),Color::White);
	custom_window_combo_box.SetSelectedIndex(max(selected_item_index,0));
	if (load_once)
	{
		custom_window_combo_box.SetPosition(custom_window_radio_button.GetX() + 210.0f,custom_window_radio_button.GetY() - 1.0f);
		custom_window_combo_box.AddEventOnClick(&Menu::GeneralOnClick,static_cast<Menu&>(*this));
		custom_window_combo_box.AddEventOnSelectedItemChanged(&OptionsMenuGameplay::CustomWindowOnSelectedItemChanged,*this);
	}

	//Colors Track Bar
	if (load_once)
	{
		TrackBar& red_component_track_bar = this->GetControl<TrackBar>(RedComponentTrackBar);
		red_component_track_bar.SetTrackBar(255,100.0f,10.0f,10.0f,30.0f,Color::Gold,Color::Red);
		red_component_track_bar.SetPosition(custom_window_radio_button.GetX(),custom_window_radio_button.GetY() + custom_window_radio_button.GetH() + 20.0f);
		red_component_track_bar.AddEventOnValueChanged(&OptionsMenuGameplay::RedComponentOnValueChanged,*this);

		TrackBar& green_component_track_bar = this->GetControl<TrackBar>(GreenComponentTrackBar);
		green_component_track_bar.SetTrackBar(255,100.0f,10.0f,10.0f,30.0f,Color::Gold,Color::Green);
		green_component_track_bar.SetPosition(red_component_track_bar.GetX(),red_component_track_bar.GetY() + red_component_track_bar.GetH() + 10.0f);
		green_component_track_bar.AddEventOnValueChanged(&OptionsMenuGameplay::GreenComponentOnValueChanged,*this);

		TrackBar& blue_component_track_bar = this->GetControl<TrackBar>(BlueComponentTrackBar);
		blue_component_track_bar.SetTrackBar(255,100.0f,10.0f,10.0f,30.0f,Color::Gold,Color::Blue);
		blue_component_track_bar.SetPosition(red_component_track_bar.GetX() + red_component_track_bar.GetW() + 10.0f,red_component_track_bar.GetY());
		blue_component_track_bar.AddEventOnValueChanged(&OptionsMenuGameplay::BlueComponentOnValueChanged,*this);

		TrackBar& alpha_component_track_bar = this->GetControl<TrackBar>(AlphaComponentTrackBar);
		alpha_component_track_bar.SetTrackBar(255,100.0f,10.0f,10.0f,30.0f,Color::Gold,Color(0.5f,0.5f,0.5f,0.5f));
		alpha_component_track_bar.SetPosition(blue_component_track_bar.GetX(),blue_component_track_bar.GetY() + blue_component_track_bar.GetH() + 10.0f);
		alpha_component_track_bar.AddEventOnValueChanged(&OptionsMenuGameplay::AlphaComponentOnValueChanged,*this);
	}

	this->CustomWindowControlsUpdate();
	this->TrackBarColorUpdate();
}

void OptionsMenuGameplay::CustomWindowControlsUpdate()
{
	const bool enabled = this->GetControl<RadioButton>(CustomWindowRadioButton).GetChecked();

	this->GetControl<ComboBox>(CustomWindowComboBox).SetEnabled(enabled);
	this->GetControl<TrackBar>(RedComponentTrackBar).SetEnabled(enabled);
	this->GetControl<TrackBar>(GreenComponentTrackBar).SetEnabled(enabled);
	this->GetControl<TrackBar>(BlueComponentTrackBar).SetEnabled(enabled);
	this->GetControl<TrackBar>(AlphaComponentTrackBar).SetEnabled(enabled);

	this->SampleWindowUpdate();
}

void OptionsMenuGameplay::SampleWindowUpdate()
{
	Window& sample_window = this->GetControl<Window>(SampleWindow);

	sample_window.SetCurrentBackground(this->GetControl<ComboBox>(DefaultWindowComboBox).GetSelectedIndex());

	if (this->GetControl<RadioButton>(CustomWindowRadioButton).GetChecked())
		sample_window.SetWindow(2,2,this->color_left_top,this->color_right_top,this->color_left_bottom,this->color_right_bottom,5.0f);
	else
		sample_window.SetWindow(2,2,5.0f);

	TrackBar& blue_component_track_bar = this->GetControl<TrackBar>(BlueComponentTrackBar);
	TrackBar& alpha_component_track_bar = this->GetControl<TrackBar>(AlphaComponentTrackBar);

	sample_window.SetPosition(blue_component_track_bar.GetX() + blue_component_track_bar.GetW() + (sample_window.GetW() / 2.0f) + 50.0f,(((alpha_component_track_bar.GetY() + alpha_component_track_bar.GetH()) - blue_component_track_bar.GetY()) / 2.0f) + blue_component_track_bar.GetY(),true);
}

Color& OptionsMenuGameplay::CornerSelectedColor()
{
	const int selected_index = this->GetControl<ComboBox>(CustomWindowComboBox).GetSelectedIndex();

	//Left Top
	if (selected_index == 0)
		return this->color_left_top;

	//Right Top
	else if (selected_index == 1)
		return this->color_right_top;

	//Left Bottom
	else if (selected_index == 2)
		return this->color_left_bottom;

	//Right Bottom
	else
		return this->color_right_bottom;
}

void OptionsMenuGameplay::CornerColorUpdate()
{
	Color& color = this->CornerSelectedColor();

	color.SetRed(this->GetControl<TrackBar>(RedComponentTrackBar).GetValue() / 255.0f);
	color.SetGreen(this->GetControl<TrackBar>(GreenComponentTrackBar).GetValue() / 255.0f);
	color.SetBlue(this->GetControl<TrackBar>(BlueComponentTrackBar).GetValue() / 255.0f);
	color.SetAlpha(this->GetControl<TrackBar>(AlphaComponentTrackBar).GetValue() / 255.0f);

	this->SampleWindowUpdate();
}

void OptionsMenuGameplay::TrackBarColorUpdate()
{
	const Color& color = this->CornerSelectedColor();

	this->GetControl<TrackBar>(RedComponentTrackBar).SetValue(static_cast<int>(color.GetRed() * 255));
	this->GetControl<TrackBar>(GreenComponentTrackBar).SetValue(static_cast<int>(color.GetGreen() * 255));
	this->GetControl<TrackBar>(BlueComponentTrackBar).SetValue(static_cast<int>(color.GetBlue() * 255));
	this->GetControl<TrackBar>(AlphaComponentTrackBar).SetValue(static_cast<int>(color.GetAlpha() * 255));
}

void OptionsMenuGameplay::DefaultConfiguration()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	this->GetControl<ComboBox>(TextSpeedComboBox).SetSelectedIndex(0);
	this->GetControl<RadioButton>(DefaultWindowRadioButton).SetChecked(true);
	this->GetControl<ComboBox>(DefaultWindowComboBox).SetSelectedIndex(0);
	this->GetControl<Window>(SampleWindow).SetCurrentBackground(this->GetControl<ComboBox>(DefaultWindowComboBox).GetSelectedIndex());
	this->color_left_top = game.GetConfiguration().GetDefaultColorLeftTop();
	this->color_right_top = game.GetConfiguration().GetDefaultColorRightTop();
	this->color_left_bottom = game.GetConfiguration().GetDefaultColorLeftBottom();
	this->color_right_bottom = game.GetConfiguration().GetDefaultColorRightBottom();
}

void OptionsMenuGameplay::SaveConfiguration()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	game.GetConfiguration().GetLanguage().SetCurrent(this->GetControl<ComboBox>(LanguageComboBox).GetSelectedIndex());
	game.GetConfiguration().GetTextSpeed().SetCurrent(this->GetControl<ComboBox>(TextSpeedComboBox).GetSelectedIndex());
	game.GetConfiguration().SetDefaultWindowSelected(this->GetControl<RadioButton>(DefaultWindowRadioButton).GetChecked());
	game.GetConfiguration().GetDefaultWindow().SetCurrent(this->GetControl<ComboBox>(DefaultWindowComboBox).GetSelectedIndex());
	game.GetConfiguration().GetColorLeftTop().SetRed(this->color_left_top.GetRed());
	game.GetConfiguration().GetColorLeftTop().SetGreen(this->color_left_top.GetGreen());
	game.GetConfiguration().GetColorLeftTop().SetBlue(this->color_left_top.GetBlue());
	game.GetConfiguration().GetColorLeftTop().SetAlpha(this->color_left_top.GetAlpha());
	game.GetConfiguration().GetColorRightTop().SetRed(this->color_right_top.GetRed());
	game.GetConfiguration().GetColorRightTop().SetGreen(this->color_right_top.GetGreen());
	game.GetConfiguration().GetColorRightTop().SetBlue(this->color_right_top.GetBlue());
	game.GetConfiguration().GetColorRightTop().SetAlpha(this->color_right_top.GetAlpha());
	game.GetConfiguration().GetColorLeftBottom().SetRed(this->color_left_bottom.GetRed());
	game.GetConfiguration().GetColorLeftBottom().SetGreen(this->color_left_bottom.GetGreen());
	game.GetConfiguration().GetColorLeftBottom().SetBlue(this->color_left_bottom.GetBlue());
	game.GetConfiguration().GetColorLeftBottom().SetAlpha(this->color_left_bottom.GetAlpha());
	game.GetConfiguration().GetColorRightBottom().SetRed(this->color_right_bottom.GetRed());
	game.GetConfiguration().GetColorRightBottom().SetGreen(this->color_right_bottom.GetGreen());
	game.GetConfiguration().GetColorRightBottom().SetBlue(this->color_right_bottom.GetBlue());
	game.GetConfiguration().GetColorRightBottom().SetAlpha(this->color_right_bottom.GetAlpha());
	game.GetConfiguration().SaveToFile();

	game.LoadDatabase();
}

void OptionsMenuGameplay::GeneralOnMouseDown(const Control& control,const MouseButton mouse_button,const float mouse_x,const float mouse_y)
{
	this->GeneralOnClick(control);
}

void OptionsMenuGameplay::DefaultWindowOnCheckedChanged(const Control& control)
{
	this->CustomWindowControlsUpdate();
}

void OptionsMenuGameplay::DefaultWindowOnSelectedItemChanged(const Control& control)
{
	this->GetControl<Window>(SampleWindow).SetCurrentBackground(this->GetControl<ComboBox>(DefaultWindowComboBox).GetSelectedIndex());
}

void OptionsMenuGameplay::CustomWindowOnSelectedItemChanged(const Control& control)
{
	this->TrackBarColorUpdate();
}

void OptionsMenuGameplay::RedComponentOnValueChanged(const Control& control)
{
	this->CornerColorUpdate();
}

void OptionsMenuGameplay::GreenComponentOnValueChanged(const Control& control)
{
	this->CornerColorUpdate();
}

void OptionsMenuGameplay::BlueComponentOnValueChanged(const Control& control)
{
	this->CornerColorUpdate();
}

void OptionsMenuGameplay::AlphaComponentOnValueChanged(const Control& control)
{
	this->CornerColorUpdate();
}
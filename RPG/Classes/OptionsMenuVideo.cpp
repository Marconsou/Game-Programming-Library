#include "OptionsMenuVideo.h"

using namespace std;
using namespace GPL;
using namespace RPG;

OptionsMenuVideo::OptionsMenuVideo(const float start_x,const float start_y) :
	Menu(OptionsMenuVideoControlMax)
{
	//Video Information Label
	this->CreateControl<Label>();

	//Resolution Label
	this->CreateControl<Label>();

	//Resolution Combo Box
	this->CreateControl<ComboBox>();

	//Color Depth Label
	this->CreateControl<Label>();

	//Color Depth Combo Box
	this->CreateControl<ComboBox>();

	//Texture Filter Label
	this->CreateControl<Label>();

	//Texture Filter Combo Box
	this->CreateControl<ComboBox>();

	//Fullscreen Check Box
	this->CreateControl<CheckBox>();

	//VSync Check Box
	this->CreateControl<CheckBox>();

	this->LoadContents(true,start_x,start_y);
}

void OptionsMenuVideo::Hiding()
{
	GameState::Hiding();
	this->ControlsUpdate(false);
}

void OptionsMenuVideo::Showing()
{
	GameState::Showing();
	this->ControlsUpdate(true);
}

void OptionsMenuVideo::LoadContents(const bool load_once,const float start_x,const float start_y)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	game.GetConfiguration().LoadFromFile();

	//Video Information Label
	Label& video_information_label = this->GetControl<Label>(VideoInformationLabel);
	video_information_label.SetText(this->GetDefaultFontMedium(),game.GetVideo().GetDeviceDisplayName(),Color::Yellow);
	if (load_once)
		video_information_label.SetPosition(start_x + 10.0f,start_y + 10.0f);

	//Resolution Label
	Label& resolution_label = this->GetControl<Label>(ResolutionLabel);
	resolution_label.SetText(this->GetDefaultFontMedium(),game.GetDatabase().GetLanguageText(OptionsMenuResolutionTextID),Color::White);
	if (load_once)
		resolution_label.SetPosition(video_information_label.GetX(),video_information_label.GetY() + video_information_label.GetH() + 10.0f);

	//Color Depth Label
	Label& color_depth_label = this->GetControl<Label>(ColorDepthLabel);
	color_depth_label.SetText(this->GetDefaultFontMedium(),game.GetDatabase().GetLanguageText(OptionsMenuColorDepthTextID),Color::White);
	if (load_once)
		color_depth_label.SetPosition(resolution_label.GetX(),resolution_label.GetY() + resolution_label.GetH() + 10.0f);

	const Color combo_box_background_color(0.0f,0.0f,0.0f,0.75f);
	const Color combo_box_border_color = Color::Gold;
	const Color combo_box_selection_color(1.0f,1.0f,1.0f,0.5f);

	//Color Depth Combo Box
	ComboBox& color_depth_combo_box = this->GetControl<ComboBox>(ColorDepthComboBox);
	color_depth_combo_box.Clear();
	color_depth_combo_box.SetComboBox(this->GetDefaultFontMedium(),215.0f,2.0f,combo_box_background_color,combo_box_border_color,combo_box_selection_color);
	color_depth_combo_box.AddTextItem("32 bit",Color::White);
	color_depth_combo_box.AddTextItem("16 bit",Color::White);

	//Atualizar valor antes do Resolution Combo Box
	color_depth_combo_box.SetSelectedIndex(game.GetConfiguration().GetColorDepth().GetCurrent());

	CheckBox& fullscreen_check_box = this->GetControl<CheckBox>(FullscreenCheckBox);
	fullscreen_check_box.SetChecked(game.GetConfiguration().GetFullscreen());

	if (load_once)
	{
		color_depth_combo_box.SetPosition(color_depth_label.GetX() + 160.0f,color_depth_label.GetY() - 1.0f);
		color_depth_combo_box.AddEventOnClick(&Menu::GeneralOnClick,static_cast<Menu&>(*this));
		color_depth_combo_box.AddEventOnSelectedItemChanged(&OptionsMenuVideo::ColorDepthOnSelectedItemChanged,*this);
	}

	//Resolution Combo Box
	this->ResolutionComboBoxUpdate(load_once);

	//Texture Filter Label
	Label& texture_filter_label = this->GetControl<Label>(TextureFilterLabel);
	texture_filter_label.SetText(this->GetDefaultFontMedium(),game.GetDatabase().GetLanguageText(OptionsMenuTextureFilterTextID),Color::White);
	if (load_once)
		texture_filter_label.SetPosition(color_depth_label.GetX(),color_depth_label.GetY() + color_depth_label.GetH() + 10.0f);

	//Texture Filter Combo Box
	ComboBox& texture_filter_combo_box = this->GetControl<ComboBox>(TextureFilterComboBox);
	texture_filter_combo_box.Clear();
	texture_filter_combo_box.SetComboBox(this->GetDefaultFontMedium(),215.0f,2.0f,combo_box_background_color,combo_box_border_color,combo_box_selection_color);
	texture_filter_combo_box.AddTextItem(game.GetDatabase().GetLanguageText(OptionsMenuNoneTextID),Color::White);
	texture_filter_combo_box.AddTextItem(game.GetDatabase().GetLanguageText(OptionsMenuLinearTextID),Color::White);
	texture_filter_combo_box.SetSelectedIndex(game.GetConfiguration().GetTextureFilter().GetCurrent());
	if (load_once)
	{
		texture_filter_combo_box.SetPosition(texture_filter_label.GetX() + 160.0f,texture_filter_label.GetY() - 1.0f);
		texture_filter_combo_box.AddEventOnClick(&Menu::GeneralOnClick,static_cast<Menu&>(*this));
	}

	//Fullscreen Check Box
	fullscreen_check_box.SetCheckBox(this->GetDefaultFontMedium(),game.GetDatabase().GetLanguageText(OptionsMenuFullscreenTextID),Color::White,game.GetVideo().GetTexture(TextureCommonFileID),16.0f,16.0f,65.0f,34.0f,16.0f,16.0f,81.0f,34.0f);
	if (load_once)
	{
		fullscreen_check_box.SetPosition(texture_filter_label.GetX(),texture_filter_label.GetY() + texture_filter_label.GetH() + 10.0f);
		fullscreen_check_box.AddEventOnMouseDown(&OptionsMenuVideo::GeneralOnMouseDown,*this);
		fullscreen_check_box.AddEventOnCheckedChanged(&OptionsMenuVideo::FullscreenOnCheckedChanged,*this);
	}

	//VSync Check Box
	CheckBox& vsync_check_box = this->GetControl<CheckBox>(VSyncCheckBox);
	vsync_check_box.SetCheckBox(this->GetDefaultFontMedium(),game.GetDatabase().GetLanguageText(OptionsMenuVSyncTextID),Color::White,game.GetVideo().GetTexture(TextureCommonFileID),16.0f,16.0f,65.0f,34.0f,16.0f,16.0f,81.0f,34.0f);
	vsync_check_box.SetChecked(game.GetConfiguration().GetVSync());
	if (load_once)
	{
		vsync_check_box.SetPosition(fullscreen_check_box.GetX(),fullscreen_check_box.GetY() + fullscreen_check_box.GetH() + 10.0f);
		vsync_check_box.AddEventOnMouseDown(&OptionsMenuVideo::GeneralOnMouseDown,*this);
	}

	if (!load_once)
		game.LoadVideoSettingsFromConfiguration();
}

void OptionsMenuVideo::LoadSupportedResolutions(vector<string>& supported_resolutions) const
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	VideoMode video_mode(0,0,(this->GetControl<ComboBox>(ColorDepthComboBox).GetSelectedIndex() == 0) ? BitsPerPixel::ColorDepth32Bits : BitsPerPixel::ColorDepth16Bits,!this->GetControl<CheckBox>(FullscreenCheckBox).GetChecked(),this->GetControl<CheckBox>(VSyncCheckBox).GetChecked());
	supported_resolutions = game.GetVideo().GetSupportedResolutions(video_mode);

	//Removendo resoluções dentro de uma variação
	for (size_t i = 0; i < supported_resolutions.size(); i++)
	{
		const string& iterator = supported_resolutions[i];

		const int width = Convert::StringToNumber(iterator.substr(0,4));
		const int height = Convert::StringToNumber(iterator.substr(5,4));

		if ((width < 800) || (height < 600))
		{
			supported_resolutions.erase(supported_resolutions.begin() + i);
			i = -1;
		}
	}

	//Removendo resoluções específicas
	vector<string> remove_resolutions;
	remove_resolutions.push_back("1366x768");
	remove_resolutions.push_back("1600x900");
	remove_resolutions.push_back("1600x1024");
	remove_resolutions.push_back("1680x1050");
	for (size_t i = 0; i < remove_resolutions.size(); i++)
	{
		for (size_t j = 0; j < supported_resolutions.size(); j++)
		{
			if (supported_resolutions[j].find(remove_resolutions[i]) != string::npos)
			{
				supported_resolutions.erase(supported_resolutions.begin() + j);
				break;
			}
		}
	}
}

void OptionsMenuVideo::ResolutionComboBoxUpdate(const bool load_once)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	ComboBox& resolution_combo_box = this->GetControl<ComboBox>(ResolutionComboBox);
	resolution_combo_box.SetComboBox(this->GetDefaultFontMedium(),215.0f,2.0f,Color(0.0f,0.0f,0.0f,0.75f),Color::Gold,Color(1.0f,1.0f,1.0f,0.5f));

	vector<string> supported_resolutions;
	this->LoadSupportedResolutions(supported_resolutions);

	int width = game.GetConfiguration().GetWidth();
	int height = game.GetConfiguration().GetHeight();

	if (resolution_combo_box.GetSelectedIndex() != -1)
	{
		const string& resolution = resolution_combo_box.GetSelectedTextItem();

		width = Convert::StringToNumber(resolution.substr(0,4));
		height = Convert::StringToNumber(resolution.substr(5,4));
	}

	int resolution_selected_index = -1;
	const string resolution(((width > 1000) ? "" : " ") + Convert::NumberToString(width) + "x" + Convert::NumberToString(height));

	if (!load_once)
		resolution_selected_index = resolution_combo_box.FindTextItem(resolution);

	resolution_combo_box.Clear();
	for (size_t i = 0; i < supported_resolutions.size(); i++)
		resolution_combo_box.AddTextItem(supported_resolutions[i],Color::White);

	if (load_once)
	{
		Label& resolution_label = this->GetControl<Label>(ResolutionLabel);

		resolution_selected_index = resolution_combo_box.FindTextItem(resolution);
		resolution_combo_box.SetPosition(resolution_label.GetX() + 160.0f,resolution_label.GetY() - 1.0f);
		resolution_combo_box.AddEventOnClick(&Menu::GeneralOnClick,static_cast<Menu&>(*this));
	}
	if (resolution_selected_index != -1)
		resolution_combo_box.SetSelectedIndex(resolution_selected_index);
}

void OptionsMenuVideo::DefaultConfiguration()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	this->GetControl<ComboBox>(ResolutionComboBox).SetSelectedIndex(0);
	this->GetControl<ComboBox>(ColorDepthComboBox).SetSelectedIndex(0);
	this->GetControl<ComboBox>(TextureFilterComboBox).SetSelectedIndex(0);
	this->GetControl<CheckBox>(FullscreenCheckBox).SetChecked(false);
	this->GetControl<CheckBox>(VSyncCheckBox).SetChecked(true);
}

void OptionsMenuVideo::SaveConfiguration()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	ComboBox& resolution_combo_box = this->GetControl<ComboBox>(ResolutionComboBox);
	if (resolution_combo_box.GetSelectedIndex() != -1)
	{
		const string resolution_string(resolution_combo_box.GetSelectedTextItem());
		game.GetConfiguration().SetWidth(Convert::StringToNumber(resolution_string.substr(0,4)));
		game.GetConfiguration().SetHeight(Convert::StringToNumber(resolution_string.substr(5,4)));
	}
	game.GetConfiguration().GetColorDepth().SetCurrent(this->GetControl<ComboBox>(ColorDepthComboBox).GetSelectedIndex());
	game.GetConfiguration().GetTextureFilter().SetCurrent(this->GetControl<ComboBox>(TextureFilterComboBox).GetSelectedIndex());
	game.GetConfiguration().SetFullscreen(this->GetControl<CheckBox>(FullscreenCheckBox).GetChecked());
	game.GetConfiguration().SetVSync(this->GetControl<CheckBox>(VSyncCheckBox).GetChecked());
	game.GetConfiguration().SaveToFile();
}

void OptionsMenuVideo::GeneralOnMouseDown(const Control& control,const MouseButton mouse_button,const float mouse_x,const float mouse_y)
{
	this->GeneralOnClick(control);
}

void OptionsMenuVideo::ColorDepthOnSelectedItemChanged(const Control& control)
{
	this->ResolutionComboBoxUpdate(false);
}

void OptionsMenuVideo::FullscreenOnCheckedChanged(const Control& control)
{
	this->ResolutionComboBoxUpdate(false);
}
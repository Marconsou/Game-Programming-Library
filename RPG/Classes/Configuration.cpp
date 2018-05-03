#include "Configuration.h"

using namespace std;
using namespace GPL;
using namespace RPG;

Configuration::Configuration() :
	save_path("Saves/"),
	game_config_file_name("GameConfig.ini"),
	default_color_left_top(Color::Black),
	default_color_right_top(Color(0.0f,0.0f,0.75f,1.0f)),
	default_color_left_bottom(Color(0.0f,0.0f,0.75f,1.0f)),
	default_color_right_bottom(Color::Black),
	color_left_top(default_color_left_top),
	color_right_top(default_color_right_top),
	color_left_bottom(default_color_left_bottom),
	color_right_bottom(default_color_right_bottom),
	language(0,2),
	text_speed(0,3),
	default_window(0,2),
	color_depth(0,2),
	texture_filter(0,2),
	audio_engine(0,2),
	default_window_selected(true),
	fullscreen(false),
	vsync(true),
	music_enabled(true),
	sound_enabled(true),
	width(800),
	height(600),
	music_volume(1.0f),
	sound_volume(1.0f)
{
	this->LoadFromFile();
}

const Color& Configuration::GetDefaultColorLeftTop() const
{
	return this->default_color_left_top;
}

const Color& Configuration::GetDefaultColorRightTop() const
{
	return this->default_color_right_top;
}

const Color& Configuration::GetDefaultColorLeftBottom() const
{
	return this->default_color_left_bottom;
}

const Color& Configuration::GetDefaultColorRightBottom() const
{
	return this->default_color_right_bottom;
}

Color& Configuration::GetColorLeftTop()
{
	return this->color_left_top;
}

Color& Configuration::GetColorRightTop()
{
	return this->color_right_top;
}

Color& Configuration::GetColorLeftBottom()
{
	return this->color_left_bottom;
}

Color& Configuration::GetColorRightBottom()
{
	return this->color_right_bottom;
}

Quantity& Configuration::GetLanguage()
{
	return this->language;
}

Quantity& Configuration::GetTextSpeed()
{
	return this->text_speed;
}

Quantity& Configuration::GetDefaultWindow()
{
	return this->default_window;
}

Quantity& Configuration::GetColorDepth()
{
	return this->color_depth;
}

Quantity& Configuration::GetTextureFilter()
{
	return this->texture_filter;
}

Quantity& Configuration::GetAudioEngine()
{
	return this->audio_engine;
}

void Configuration::SetDefaultWindowSelected(const bool default_window_selected)
{
	this->default_window_selected = default_window_selected;
}

bool Configuration::GetDefaultWindowSelected() const
{
	return this->default_window_selected;
}

void Configuration::SetFullscreen(const bool fullscreen)
{
	this->fullscreen = fullscreen;
}

bool Configuration::GetFullscreen() const
{
	return this->fullscreen;
}

void Configuration::SetVSync(const bool vsync)
{
	this->vsync = vsync;
}

bool Configuration::GetVSync() const
{
	return this->vsync;
}

void Configuration::SetMusicEnabled(const bool music_enabled)
{
	this->music_enabled = music_enabled;
}

bool Configuration::GetMusicEnabled() const
{
	return this->music_enabled;
}

void Configuration::SetSoundEnabled(const bool sound_enabled)
{
	this->sound_enabled = sound_enabled;
}

bool Configuration::GetSoundEnabled() const
{
	return this->sound_enabled;
}

void Configuration::SetWidth(const int width)
{
	this->width = width;
}

int Configuration::GetWidth() const
{
	return this->width;
}

void Configuration::SetHeight(const int height)
{
	this->height = height;
}

int Configuration::GetHeight() const
{
	return this->height;
}

void Configuration::SetMusicVolume(const float music_volume)
{
	this->music_volume = music_volume;
}

float Configuration::GetMusicVolume() const
{
	return this->music_volume;
}

void Configuration::SetSoundVolume(const float sound_volume)
{
	this->sound_volume = sound_volume;
}

float Configuration::GetSoundVolume() const
{
	return this->sound_volume;
}

void Configuration::SaveToFile() const
{
	//Criando diretório
	Directory::NewDirectory(this->save_path);

	//Criando arquivo
	ofstream save(string(this->save_path + this->game_config_file_name).c_str());

	//Configuração
	this->SaveSingleData(save,"Language",this->language.GetCurrent());
	this->SaveSingleData(save,"TextSpeed",this->text_speed.GetCurrent());
	this->SaveSingleData(save,"DefaultWindow",this->default_window.GetCurrent());
	this->SaveSingleData(save,"DefaultWindowSelected",this->default_window_selected);
	this->SaveSingleData(save,"ColorLeftTopR",this->color_left_top.GetRed());
	this->SaveSingleData(save,"ColorLeftTopG",this->color_left_top.GetGreen());
	this->SaveSingleData(save,"ColorLeftTopB",this->color_left_top.GetBlue());
	this->SaveSingleData(save,"ColorLeftTopA",this->color_left_top.GetAlpha());
	this->SaveSingleData(save,"ColorRightTopR",this->color_right_top.GetRed());
	this->SaveSingleData(save,"ColorRightTopG",this->color_right_top.GetGreen());
	this->SaveSingleData(save,"ColorRightTopB",this->color_right_top.GetBlue());
	this->SaveSingleData(save,"ColorRightTopA",this->color_right_top.GetAlpha());
	this->SaveSingleData(save,"ColorLeftBottomR",this->color_left_bottom.GetRed());
	this->SaveSingleData(save,"ColorLeftBottomG",this->color_left_bottom.GetGreen());
	this->SaveSingleData(save,"ColorLeftBottomB",this->color_left_bottom.GetBlue());
	this->SaveSingleData(save,"ColorLeftBottomA",this->color_left_bottom.GetAlpha());
	this->SaveSingleData(save,"ColorRightBottomR",this->color_right_bottom.GetRed());
	this->SaveSingleData(save,"ColorRightBottomG",this->color_right_bottom.GetGreen());
	this->SaveSingleData(save,"ColorRightBottomB",this->color_right_bottom.GetBlue());
	this->SaveSingleData(save,"ColorRightBottomA",this->color_right_bottom.GetAlpha());
	this->SaveSingleData(save,"Width",this->width);
	this->SaveSingleData(save,"Height",this->height);
	this->SaveSingleData(save,"ColorDepth",this->color_depth.GetCurrent());
	this->SaveSingleData(save,"TextureFilter",this->texture_filter.GetCurrent());
	this->SaveSingleData(save,"Fullscreen",this->fullscreen);
	this->SaveSingleData(save,"VSync",this->vsync);
	this->SaveSingleData(save,"AudioEngine",this->audio_engine.GetCurrent());
	this->SaveSingleData(save,"MusicEnabled",this->music_enabled);
	this->SaveSingleData(save,"SoundEnabled",this->sound_enabled);
	save.setf(ios::fixed,ios::floatfield);
	save.precision(2);
	this->SaveSingleData(save,"MusicVolume",this->music_volume);
	this->SaveSingleData(save,"SoundVolume",this->sound_volume);

	//Fechando arquivo
	save.close();
}

void Configuration::LoadFromFile()
{
	//Carregando arquivo
	ifstream load(string(this->save_path + this->game_config_file_name).c_str());

	//Verificando se o arquivo existe
	if (load.is_open())
	{
		//Configuração
		this->language.SetCurrent(this->LoadSingleData(load,0,this->language.GetTotal() - 1));
		this->text_speed.SetCurrent(this->LoadSingleData(load,0,this->text_speed.GetTotal() - 1));
		this->default_window.SetCurrent(this->LoadSingleData(load,0,this->default_window.GetTotal() - 1));
		this->default_window_selected = this->LoadSingleData<bool>(load);
		this->color_left_top.SetRed(this->LoadSingleData<float>(load));
		this->color_left_top.SetGreen(this->LoadSingleData<float>(load));
		this->color_left_top.SetBlue(this->LoadSingleData<float>(load));
		this->color_left_top.SetAlpha(this->LoadSingleData<float>(load));
		this->color_right_top.SetRed(this->LoadSingleData<float>(load));
		this->color_right_top.SetGreen(this->LoadSingleData<float>(load));
		this->color_right_top.SetBlue(this->LoadSingleData<float>(load));
		this->color_right_top.SetAlpha(this->LoadSingleData<float>(load));
		this->color_left_bottom.SetRed(this->LoadSingleData<float>(load));
		this->color_left_bottom.SetGreen(this->LoadSingleData<float>(load));
		this->color_left_bottom.SetBlue(this->LoadSingleData<float>(load));
		this->color_left_bottom.SetAlpha(this->LoadSingleData<float>(load));
		this->color_right_bottom.SetRed(this->LoadSingleData<float>(load));
		this->color_right_bottom.SetGreen(this->LoadSingleData<float>(load));
		this->color_right_bottom.SetBlue(this->LoadSingleData<float>(load));
		this->color_right_bottom.SetAlpha(this->LoadSingleData<float>(load));
		this->width = this->LoadSingleData<int>(load,800,1920);
		this->height = this->LoadSingleData<int>(load,600,1200);
		this->color_depth.SetCurrent(this->LoadSingleData(load,0,this->color_depth.GetTotal() - 1));
		this->texture_filter.SetCurrent(this->LoadSingleData(load,0,this->texture_filter.GetTotal() - 1));
		this->fullscreen = this->LoadSingleData<bool>(load);
		this->vsync = this->LoadSingleData<bool>(load);
		this->audio_engine.SetCurrent(this->LoadSingleData(load,0,this->audio_engine.GetTotal() - 1));
		this->music_enabled = this->LoadSingleData<bool>(load);
		this->sound_enabled = this->LoadSingleData<bool>(load);
		this->music_volume = this->LoadSingleData<float>(load);
		this->sound_volume = this->LoadSingleData<float>(load);

		//Fechando arquivo
		load.close();
	}
	else
		this->SaveToFile();
}
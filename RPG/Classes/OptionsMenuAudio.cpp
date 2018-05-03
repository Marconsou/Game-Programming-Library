#include "OptionsMenuAudio.h"

using namespace std;
using namespace GPL;
using namespace RPG;

OptionsMenuAudio::OptionsMenuAudio(const float start_x,const float start_y) :
	Menu(OptionsMenuAudioControlMax),
	last_audio_engine(static_cast<AudioEngine>(GameState::GetGame<GameRPG>().GetConfiguration().GetAudioEngine().GetCurrent()))
{
	//Audio Information Label
	this->CreateControl<Label>();

	//Audio Engine Label
	this->CreateControl<Label>();

	//Audio Engine Combo Box
	this->CreateControl<ComboBox>();

	//Music Volume Check Box
	this->CreateControl<CheckBox>();

	//Music Volume Value Track Bar
	this->CreateControl<TrackBar>();

	//Music Volume Value Label
	this->CreateControl<Label>();

	//Sound Volume Check Box
	this->CreateControl<CheckBox>();

	//Sound Volume Value Track Bar
	this->CreateControl<TrackBar>();

	//Sound Volume Value Label
	this->CreateControl<Label>();

	this->LoadContents(true,start_x,start_y);
}

void OptionsMenuAudio::Hiding()
{
	GameState::Hiding();
	this->ControlsUpdate(false);
}

void OptionsMenuAudio::Showing()
{
	GameState::Showing();
	this->ControlsUpdate(true);
}

void OptionsMenuAudio::LoadContents(const bool load_once,const float start_x,const float start_y)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	game.GetConfiguration().LoadFromFile();

	//Audio Information Label
	Label& audio_information_label = this->GetControl<Label>(AudioInformationLabel);
	audio_information_label.SetText(this->GetDefaultFontMedium(),game.GetAudio().GetDeviceDisplayName(),Color::Yellow);
	if (load_once)
		audio_information_label.SetPosition(start_x + 10.0f,start_y + 10.0f);

	//Audio Engine Label
	Label& audio_engine_label = this->GetControl<Label>(AudioEngineLabel);
	audio_engine_label.SetText(this->GetDefaultFontMedium(),game.GetDatabase().GetLanguageText(OptionsMenuAudioEngineTextID),Color::White);
	if (load_once)
		audio_engine_label.SetPosition(audio_information_label.GetX(),audio_information_label.GetY() + audio_information_label.GetH() + 10.0f);

	const Color combo_box_background_color(0.0f,0.0f,0.0f,0.75f);
	const Color combo_box_border_color = Color::Gold;
	const Color combo_box_selection_color(1.0f,1.0f,1.0f,0.5f);

	//Audio Engine Combo Box
	ComboBox& audio_engine_combo_box = this->GetControl<ComboBox>(AudioEngineComboBox);
	audio_engine_combo_box.Clear();
	audio_engine_combo_box.SetComboBox(this->GetDefaultFontMedium(),165.0f,2.0f,combo_box_background_color,combo_box_border_color,combo_box_selection_color);
	audio_engine_combo_box.AddTextItem("XAudio",Color::White);
	audio_engine_combo_box.AddTextItem("OpenAL",Color::White);
	audio_engine_combo_box.SetSelectedIndex(game.GetConfiguration().GetAudioEngine().GetCurrent());
	if (load_once)
	{
		audio_engine_combo_box.SetPosition(audio_engine_label.GetX() + 210.0f,audio_engine_label.GetY() - 1.0f);
		audio_engine_combo_box.AddEventOnClick(&Menu::GeneralOnClick,static_cast<Menu&>(*this));
	}

	//Music Volume Check Box
	CheckBox& music_volume_check_box = this->GetControl<CheckBox>(MusicVolumeCheckBox);
	music_volume_check_box.SetCheckBox(this->GetDefaultFontMedium(),game.GetDatabase().GetLanguageText(OptionsMenuMusicVolumeTextID),Color::White,game.GetVideo().GetTexture(TextureCommonFileID),16.0f,16.0f,65.0f,34.0f,16.0f,16.0f,81.0f,34.0f);
	music_volume_check_box.SetChecked(game.GetConfiguration().GetMusicEnabled());
	if (load_once)
	{
		music_volume_check_box.SetPosition(audio_engine_label.GetX(),audio_engine_label.GetY() + audio_engine_label.GetH() + 20.0f);
		music_volume_check_box.AddEventOnMouseDown(&OptionsMenuAudio::GeneralOnMouseDown,*this);
		music_volume_check_box.AddEventOnCheckedChanged(&OptionsMenuAudio::MusicVolumeOnCheckedChanged,*this);
	}

	//Music Volume Value Track Bar
	TrackBar& music_volume_value_track_bar = this->GetControl<TrackBar>(MusicVolumeValueTrackBar);
	music_volume_value_track_bar.SetEnabled(music_volume_check_box.GetChecked());
	if (load_once)
	{
		music_volume_value_track_bar.SetTrackBar(100,100.0f,10.0f,10.0f,30.0f,Color::Gold,Color::Gray);
		music_volume_value_track_bar.SetPosition(music_volume_check_box.GetX() + 210.0f,music_volume_check_box.GetY());
		music_volume_value_track_bar.SetValue(static_cast<int>(game.GetConfiguration().GetMusicVolume() * 100));
		music_volume_value_track_bar.AddEventOnValueChanged(&OptionsMenuAudio::MusicVolumeValueOnValueChanged,*this);
	}

	//Music Volume Value Label
	Label& music_volume_value_label = this->GetControl<Label>(MusicVolumeValueLabel);
	music_volume_value_label.SetEnabled(music_volume_check_box.GetChecked());
	music_volume_value_label.SetText(this->GetDefaultFontMedium(),Convert::NumberToString(music_volume_value_track_bar.GetValue()) + "%",Color::Green);
	if (load_once)
		music_volume_value_label.SetPosition(music_volume_value_track_bar.GetX() + music_volume_value_track_bar.GetW() + 10.0f,music_volume_value_track_bar.GetY());

	//Sound Volume Check Box
	CheckBox& sound_volume_check_box = this->GetControl<CheckBox>(SoundVolumeCheckBox);
	sound_volume_check_box.SetCheckBox(this->GetDefaultFontMedium(),game.GetDatabase().GetLanguageText(OptionsMenuSoundVolumeTextID),Color::White,game.GetVideo().GetTexture(TextureCommonFileID),16.0f,16.0f,65.0f,34.0f,16.0f,16.0f,81.0f,34.0f);
	sound_volume_check_box.SetChecked(game.GetConfiguration().GetSoundEnabled());
	if (load_once)
	{
		sound_volume_check_box.SetPosition(music_volume_check_box.GetX(),music_volume_check_box.GetY() + music_volume_check_box.GetH() + 20.0f);
		sound_volume_check_box.AddEventOnMouseDown(&OptionsMenuAudio::GeneralOnMouseDown,*this);
		sound_volume_check_box.AddEventOnCheckedChanged(&OptionsMenuAudio::SoundVolumeOnCheckedChanged,*this);
	}

	//Sound Volume Value Track Bar
	TrackBar& sound_volume_value_track_bar = this->GetControl<TrackBar>(SoundVolumeValueTrackBar);
	sound_volume_value_track_bar.SetEnabled(sound_volume_check_box.GetChecked());
	if (load_once)
	{
		sound_volume_value_track_bar.SetTrackBar(100,100.0f,10.0f,10.0f,30.0f,Color::Gold,Color::Gray);
		sound_volume_value_track_bar.SetPosition(sound_volume_check_box.GetX() + 210.f,sound_volume_check_box.GetY());
		sound_volume_value_track_bar.SetValue(static_cast<int>(game.GetConfiguration().GetSoundVolume() * 100));
		sound_volume_value_track_bar.AddEventOnValueChanged(&OptionsMenuAudio::SoundVolumeValueOnValueChanged,*this);
	}

	//Sound Volume Value Label
	Label& sound_volume_value_label = this->GetControl<Label>(SoundVolumeValueLabel);
	sound_volume_value_label.SetEnabled(sound_volume_check_box.GetChecked());
	sound_volume_value_label.SetText(this->GetDefaultFontMedium(),Convert::NumberToString(sound_volume_value_track_bar.GetValue()) + "%",Color::Green);
	if (load_once)
		sound_volume_value_label.SetPosition(sound_volume_value_track_bar.GetX() + sound_volume_value_track_bar.GetW() + 10.0f,sound_volume_value_track_bar.GetY());

	if (!load_once)
	{
		const bool load_audio_engine = (this->last_audio_engine != static_cast<AudioEngine>(game.GetConfiguration().GetAudioEngine().GetCurrent()));
		game.LoadAudioSettingsFromConfiguration(load_audio_engine);
		this->last_audio_engine = static_cast<AudioEngine>(game.GetConfiguration().GetAudioEngine().GetCurrent());
	}
}

void OptionsMenuAudio::DefaultConfiguration()
{
	GameRPG& game = GameState::GetGame<GameRPG>();
	
	this->GetControl<CheckBox>(MusicVolumeCheckBox).SetChecked(true);
	this->GetControl<CheckBox>(SoundVolumeCheckBox).SetChecked(true);
	this->GetControl<TrackBar>(MusicVolumeValueTrackBar).SetValue(100);
	this->GetControl<TrackBar>(SoundVolumeValueTrackBar).SetValue(100);
}

void OptionsMenuAudio::SaveConfiguration()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	game.GetConfiguration().GetAudioEngine().SetCurrent(this->GetControl<ComboBox>(AudioEngineComboBox).GetSelectedIndex());
	game.GetConfiguration().SetMusicEnabled(this->GetControl<CheckBox>(MusicVolumeCheckBox).GetChecked());
	game.GetConfiguration().SetSoundEnabled(this->GetControl<CheckBox>(SoundVolumeCheckBox).GetChecked());
	game.GetConfiguration().SetMusicVolume(this->GetControl<TrackBar>(MusicVolumeValueTrackBar).GetValue() / 100.0f);
	game.GetConfiguration().SetSoundVolume(this->GetControl<TrackBar>(SoundVolumeValueTrackBar).GetValue() / 100.0f);
	game.GetConfiguration().SaveToFile();
}

void OptionsMenuAudio::GeneralOnMouseDown(const Control& control,const MouseButton mouse_button,const float mouse_x,const float mouse_y)
{
	this->GeneralOnClick(control);
}

void OptionsMenuAudio::MusicVolumeOnCheckedChanged(const Control& control)
{
	const bool enabled = this->GetControl<CheckBox>(MusicVolumeCheckBox).GetChecked();

	this->GetControl<TrackBar>(MusicVolumeValueTrackBar).SetEnabled(enabled);
	this->GetControl<Label>(MusicVolumeValueLabel).SetEnabled(enabled);
}

void OptionsMenuAudio::SoundVolumeOnCheckedChanged(const Control& control)
{
	const bool enabled = this->GetControl<CheckBox>(SoundVolumeCheckBox).GetChecked();

	this->GetControl<TrackBar>(SoundVolumeValueTrackBar).SetEnabled(enabled);
	this->GetControl<Label>(SoundVolumeValueLabel).SetEnabled(enabled);
}

void OptionsMenuAudio::MusicVolumeValueOnValueChanged(const Control& control)
{
	this->GetControl<Label>(MusicVolumeValueLabel).SetTextString(Convert::NumberToString(this->GetControl<TrackBar>(MusicVolumeValueTrackBar).GetValue()) + "%");
}

void OptionsMenuAudio::SoundVolumeValueOnValueChanged(const Control& control)
{
	this->GetControl<Label>(SoundVolumeValueLabel).SetTextString(Convert::NumberToString(this->GetControl<TrackBar>(SoundVolumeValueTrackBar).GetValue()) + "%");
}
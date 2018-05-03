#include "Audio.h"

using namespace std;
using namespace GPL;

Audio::Audio(const bool enable_music,const bool enable_sound) :
enable_music(enable_music),
enable_sound(enable_sound)
{

}

float Audio::GetAudioFadeVolume() const
{
	return this->music_volume_max * 0.01f;
}

void Audio::SetMusicVolume(const float music_volume)
{
	this->music_volume = music_volume;
	this->music_volume_max = music_volume;
}

float Audio::GetMusicVolume() const
{
	return this->music_volume;
}

void Audio::SetSoundVolume(const float sound_volume)
{
	this->sound_volume = sound_volume;
}

float Audio::GetSoundVolume() const
{
	return this->sound_volume;
}

void Audio::SetMusicFrequencyRatio(const float music_frequency_ratio)
{
	if (this->current_music)
		this->current_music->SetFrequencyRatio(music_frequency_ratio);
}

double Audio::GetMusicRestartPosition(const string& music_id) const
{
	return this->music_playlist.GetResource(music_id)->restart_position;
}

double Audio::GetMusicFinishPosition(const string& music_id) const
{
	return this->music_playlist.GetResource(music_id)->finish_position;
}

void Audio::SetMusicCurrentPosition(const string& music_id,const double current_position)
{
	this->music_playlist.GetResource(music_id)->current_position = current_position;
}

double Audio::GetMusicCurrentPosition(const string& music_id) const
{
	return this->music_playlist.GetResource(music_id)->current_position;
}

unique_ptr<Music>& Audio::GetCurrentMusic()
{
	return this->current_music;
}

ResourceManager<unique_ptr<Sound>>& Audio::GetSounds()
{
	return this->sounds;
}

vector<unique_ptr<Source>>& Audio::GetSoundSources()
{
	return this->sound_sources;
}

void Audio::EnableMusic()
{
	this->enable_music = true;
}

void Audio::DisableMusic()
{
	this->enable_music = false;
}

bool Audio::MusicIsEnabled() const
{
	return this->enable_music;
}

void Audio::EnableSound()
{
	this->enable_sound = true;
}

void Audio::DisableSound()
{
	this->enable_sound = false;
}

bool Audio::SoundIsEnabled() const
{
	return this->enable_sound;
}

void Audio::StartFadeInMusic()
{
	this->fading_in_music = true;
	this->fading_out_music = false;
}

void Audio::StartFadeOutMusic()
{
	this->fading_out_music = true;
	this->fading_in_music = false;
}

void Audio::ChangeAudioEngine(unique_ptr<Audio>& new_audio)
{
	static bool copy_from_current_engine = false;
	if (copy_from_current_engine)
	{
		//Music Volume
		const float music_volume = this->GetMusicVolume();
		const float music_volume_max = this->music_volume_max;

		//Sound Volume
		const float sound_volume = this->GetSoundVolume();

		//Music Enabled
		if (this->MusicIsEnabled())
			new_audio->EnableMusic();
		else
			new_audio->DisableMusic();

		//Sound Enabled
		if (this->SoundIsEnabled())
			new_audio->EnableSound();
		else
			new_audio->DisableSound();

		//Music Playlist
		new_audio->music_playlist = move(this->music_playlist);

		//Music Save
		const bool using_music = (this->current_music.get() != nullptr);
		const double music_current_position = (using_music) ? this->current_music->GetCurrentPosition() : 0;

		//Sounds Save
		vector<string> sound_ids;
		vector<bool> sound_resource_from_file;
		for (auto& iterator = this->sounds.GetResources().begin(); iterator != this->sounds.GetResources().end(); iterator++)
		{
			const bool resource_from_file = get<1>(iterator->second);

			sound_ids.push_back((*iterator).first);
			sound_resource_from_file.push_back(resource_from_file);
		}

		//Fade
		new_audio->fading_in_music = this->fading_in_music;
		new_audio->fading_out_music = this->fading_out_music;

		//Destruir a Audio Engine atual
		this->DestroyAudioEngine();

		//Criar uma Audio Engine Nova
		new_audio->CreateAudioEngine();

		//Music Load
		if (using_music)
		{
			//Carregando
			if (this->last_music_is_from_file)
				new_audio->PlayMusicFromPlaylist(this->last_music_id_played,this->last_music_restore_previous_position);
			else
				new_audio->PlayMusicFromPlaylist(Convert::StringToNumber(this->last_music_id_played),this->last_music_restore_previous_position);

			//Atualizando posição
			new_audio->SetMusicVolume(music_volume);
			new_audio->music_volume_max = music_volume_max;
			new_audio->current_music->SetCurrentPosition(music_current_position);
		}

		//Sounds Load
		new_audio->SetSoundVolume(sound_volume);
		for (size_t i = 0; i < sound_ids.size(); i++)
		{
			//Carregando
			if (sound_resource_from_file[i])
				new_audio->LoadSound(sound_ids[i]);
			else
				new_audio->LoadSound(Convert::StringToNumber(sound_ids[i]));
		}
	}
	else
	{
		//Primeira execução
		new_audio->CreateAudioEngine();
		copy_from_current_engine = true;
	}
}

void Audio::AddToMusicPlaylistBase(const bool resource_from_file,const string& file_name,const int music_id,const double restart_position,const double finish_position)
{
	const string correct_music_id(resource_from_file ? file_name : Convert::NumberToString(music_id));

	unique_ptr<MusicTrack>& music_track = this->music_playlist.AddResource(correct_music_id,resource_from_file);

	music_track = make_unique<MusicTrack>();

	music_track->id = correct_music_id;
	music_track->restart_position = restart_position;
	music_track->finish_position = finish_position;
}

void Audio::AddToMusicPlaylist(const string& file_name,const double restart_position,const double finish_position)
{
	this->AddToMusicPlaylistBase(true,file_name,-1,restart_position,finish_position);
}

void Audio::AddToMusicPlaylist(const int music_id,const double restart_position,const double finish_position)
{
	this->AddToMusicPlaylistBase(false,"",music_id,restart_position,finish_position);
}

void Audio::PlayMusicFromPlaylistBase(const string& file_name,const int music_id,const bool restore_previous_position)
{
	const bool resource_from_file = (!file_name.empty());
	const string final_music_id((resource_from_file) ? file_name : Convert::NumberToString(music_id));
	unique_ptr<char[]> memory_buffer;
	size_t size = 0;

	//Verificar se já está tocando alguma música para utilizar a temporária como auxílio
	this->SwapMusic(final_music_id);

	//Carregar de um arquivo de recursos
	if (!resource_from_file)
	{
		//Extraindo arquivo de música do arquivo de recursos
		size = ResourceFile::Read(music_id,memory_buffer);
		if (!size)
			Log::Error(__FUNCTION__,"Read",final_music_id);
	}

	//Formato do arquivo de audio
	AudioFormat audio_format;
	if (resource_from_file)
		audio_format = this->DetectFileType(file_name);
	else
		audio_format = this->DetectFileType(memory_buffer);

	//Salvar o volume atual
	const float music_volume = this->GetMusicVolume();

	//OGG
	if (audio_format == AudioFormat::OGG)
		this->LoadMusicOGG(final_music_id,memory_buffer,size);
	else
		Log::Error(__FUNCTION__,"AudioFormat::Unknown",final_music_id);

	//Restaurando a última posição da música registrada anteriormente se necessário
	if (restore_previous_position)
		this->RestoreMusicCurrentPosition(final_music_id);

	//Atualizando o volume atual
	this->SetMusicVolume(music_volume);

	//Atualizando dados desta música atual
	this->last_music_is_from_file = resource_from_file;
	this->last_music_restore_previous_position = restore_previous_position;
	this->last_music_id_played = final_music_id;
}

void Audio::PlayMusicFromPlaylist(const string& music_id,const bool restore_previous_position)
{
	this->PlayMusicFromPlaylistBase(music_id,-1,restore_previous_position);
}

void Audio::PlayMusicFromPlaylist(const int music_id,const bool restore_previous_position)
{
	this->PlayMusicFromPlaylistBase("",music_id,restore_previous_position);
}

void Audio::LoadSoundBase(const string& file_name,const int sound_id)
{
	const string final_sound_id((file_name.empty()) ? Convert::NumberToString(sound_id) : file_name);
	unique_ptr<char[]> memory_buffer;
	size_t size = 0;

	//Carregar de um arquivo de recursos
	if (file_name.empty())
	{
		//Extraindo arquivo de som do arquivo de recursos
		size = ResourceFile::Read(sound_id,memory_buffer);
		if (!size)
			Log::Error(__FUNCTION__,"Read",final_sound_id);
	}

	//Formato do arquivo de audio
	AudioFormat audio_format;
	if (file_name.empty())
		audio_format = this->DetectFileType(memory_buffer);
	else
		audio_format = this->DetectFileType(file_name);

	//OGG
	if (audio_format == AudioFormat::OGG)
		this->LoadSoundOGG(final_sound_id,memory_buffer,size);
	else
		Log::Error(__FUNCTION__,"AudioFormat::Unknown",final_sound_id);
}

void Audio::LoadSound(const string& file_name)
{
	this->LoadSoundBase(file_name,-1);
}

void Audio::LoadSound(const int sound_id)
{
	this->LoadSoundBase("",sound_id);
}

Audio::AudioFormat Audio::DetectFileType(const string& file_name) const
{
	//Abrindo o arquivo
	ifstream file(file_name.c_str(),ios::binary);

	//Verificar se o arquivo foi aberto
	if (file.is_open())
	{
		//Lendo do arquivo
		string buffer;
		file >> buffer;

		//Fechando o arquivo
		file.close();

		//OGG
		if (buffer.find_first_of("OggS") == 0)
			return AudioFormat::OGG;
	}

	//Formato desconhecido
	return AudioFormat::Unknown;
}

Audio::AudioFormat Audio::DetectFileType(const unique_ptr<char[]>& memory_buffer) const
{
	const string buffer(memory_buffer.get(),4);

	//OGG
	if (buffer.find_first_of("OggS") == 0)
		return AudioFormat::OGG;

	//Formato desconhecido
	return AudioFormat::Unknown;
}

void Audio::CheckMusicFadeEvent()
{
	if (this->current_music)
	{
		//Fade In
		if ((this->fading_in_music) && (!this->fading_out_music))
		{
			this->current_music->SetVolume(min(this->current_music->GetVolume() + this->GetAudioFadeVolume(),this->music_volume_max));
			if (this->current_music->GetVolume() == this->music_volume_max)
				this->fading_in_music = false;
		}

		//Fade Out
		if ((this->fading_out_music) && (!this->fading_in_music))
		{
			this->current_music->SetVolume(max(this->current_music->GetVolume() - this->GetAudioFadeVolume(),0.0f));
			if (this->current_music->GetVolume() == 0.0f)
				this->fading_out_music = false;
		}
	}
}

void Audio::SwapMusic(const string& music_id)
{
	static string last_music_id = music_id;

	//Verificar se já está tocando alguma música para utilizar a temporária como auxílio
	if (this->current_music)
	{
		//Salvando a posição da música atual
		this->SetMusicCurrentPosition(last_music_id,this->current_music->GetCurrentPosition());

		//Música temporária passará a ser a atual e será finalizada em seguida
		this->temporary_music = move(this->current_music);
		this->temporary_music->Stop();
		this->temporary_music->SetVolume(this->music_volume_max);

		//Iniciar a alteração de volume da música principal na troca das músicas
		this->music_volume_swap = true;
	}

	last_music_id = music_id;
}

void Audio::RestoreMusicCurrentPosition(const string& music_id)
{
	this->current_music->SetCurrentPosition(this->GetMusicCurrentPosition(music_id));
}

void Audio::PlayingMusic(unique_ptr<Music>& music,const bool using_current_music)
{
	static bool reset_volume = true;

	//Se for a música principal
	if (using_current_music)
	{
		//Se tiver trocando de música
		if (this->music_volume_swap)
		{
			//Resetar volume
			if (reset_volume)
			{
				music->SetVolume(0.0f);
				reset_volume = false;
			}
		}
	}

	if (music)
	{
		if (this->MusicIsEnabled())
			music->Playing();
		else
			music->Stop();

		//Caso for a música atual deve-ser considerar Music Volume Swap, caso for a temporária não precisa
		if (((using_current_music) && (this->music_volume_swap)) || (!using_current_music))
		{
			//Ajustando volume
			const float audio_fade_volume = this->GetAudioFadeVolume() / 1.5f;
			const float volume = music->GetVolume() + (using_current_music ? +audio_fade_volume : -audio_fade_volume);
			const float volume_to_compare = using_current_music ? this->music_volume_max : 0.0f;
			music->SetVolume(using_current_music ? min(volume,volume_to_compare) : max(volume,volume_to_compare));

			//Evento final da música
			if (music->GetVolume() == volume_to_compare)
			{
				//Caso for a música principal
				if (using_current_music)
				{
					this->music_volume_swap = false;
					reset_volume = true;
				}
				else
					music.reset();
			}
		}
	}
}

void Audio::ProcessAudio()
{
	//Música
	if (this->MusicIsEnabled())
	{
		//Atualizando o volume da música
		if (this->current_music)
			this->current_music->SetVolume(this->music_volume);

		//Atualizando o evento de Fade da música
		this->CheckMusicFadeEvent();

		//Música atual
		this->PlayingMusic(this->current_music,true);

		//Música temporária
		this->PlayingMusic(this->temporary_music,false);
	}

	//Sons
	for (size_t i = 0; i < this->sound_sources.size(); i++)
	{
		if (this->SoundIsEnabled())
			this->sound_sources[i]->SetVolume(this->sound_volume);
		else
			this->sound_sources[i]->Stop();
	}
}

void Audio::DestroyResources()
{
	this->current_music.reset();
	this->temporary_music.reset();
	this->sound_sources.clear();
	this->sounds.Clear();
}
#include "AudioXAudio.h"

using namespace std;
using namespace GPL;

AudioXAudio::AudioXAudio(const bool enable_music,const bool enable_sound) :
Audio(enable_music,enable_sound)
{
}

AudioXAudio::~AudioXAudio()
{
	this->DestroyAudioEngine();
}

const Sound& AudioXAudio::GetSound(const string& sound_id)
{
	return this->FindSound(sound_id);
}

const Sound& AudioXAudio::GetSound(const int sound_id)
{
	return this->FindSound(Convert::NumberToString(sound_id));
}

string AudioXAudio::GetDeviceDisplayName() const
{
	return this->xaudio.GetDeviceDisplayName();
}

void AudioXAudio::CreateAudioEngine()
{
	this->xaudio.CreateXAudio();
}

void AudioXAudio::DestroyAudioEngine()
{
	this->DestroyResources();
	this->xaudio.DestroyXAudio();
}

const SoundXAudio& AudioXAudio::FindSound(const string& sound_id)
{
	//OGG
	return static_cast<SoundXAudio&>(*this->GetSounds().GetResource(sound_id));
}

void AudioXAudio::PlaySourceVoice(const SoundXAudio& sound_xaudio,const float frequency_ratio)
{
	if (this->SoundIsEnabled())
	{
		const SourceVoiceXAudio* source_voice = nullptr;
		for (size_t i = 0; i < this->GetSoundSources().size(); i++)
		{
			const SourceVoiceXAudio& iterator = static_cast<SourceVoiceXAudio&>(*this->GetSoundSources()[i]);

			//Verificando o tipo de formato
			if (iterator.CheckSourceVoiceFormat(sound_xaudio.GetBufferXAudio().GetWaveFormat()))
			{
				//Obter o primeiro Source Voice disponível para este formato adequado
				if (!source_voice)
					source_voice = &iterator;

				//Se o Source Voice estiver livre para ser usado
				if (iterator.HasBuffersQueued() == 0)
				{
					source_voice = &iterator;
					break;
				}
			}
		}

		//Source Voice escolhido para começar a ser utilizado
		source_voice->Stop();
		source_voice->Start(sound_xaudio.GetBufferXAudio().GetXAudioBuffer(),frequency_ratio);
	}
}

void AudioXAudio::AddSourceVoices(const WAVEFORMATEX& wave_format)
{
	bool format_exists = false;
	for (size_t i = 0; i < this->GetSoundSources().size(); i++)
	{
		const SourceVoiceXAudio& iterator = static_cast<SourceVoiceXAudio&>(*this->GetSoundSources()[i]);

		//Verificar se já existe este formato de audio
		if (iterator.CheckSourceVoiceFormat(wave_format))
		{
			format_exists = true;
			break;
		}
	}

	//Se não existe, então criar novos Source Voices com base neste formato
	if (!format_exists)
	{
		//Criando vários Source Voices
		const size_t total = 8;
		for (size_t i = total; i > 0; i--)
		{
			//Alocando um novo Source Voice
			this->GetSoundSources().push_back(make_unique<SourceVoiceXAudio>());

			//Último Source Voice adicionado acima
			SourceVoiceXAudio& iterator = static_cast<SourceVoiceXAudio&>(*this->GetSoundSources().back());

			//Criar Source Voice
			iterator.CreateSourceVoice(this->xaudio.GetXAudio(),wave_format);
		}
	}
}

void AudioXAudio::LoadMusicOGG(const string& music_id,unique_ptr<char[]>& memory_buffer,const size_t size)
{
	//Realocar a nova música
	this->GetCurrentMusic() = make_unique<MusicXAudioOGG>(this->GetMusicRestartPosition(music_id),this->GetMusicFinishPosition(music_id));

	//Carregar música
	if (size == 0)
		this->GetCurrentMusic()->LoadMusic(music_id);
	else
		this->GetCurrentMusic()->LoadMusic(memory_buffer,size);

	//Criar Source Voice
	MusicXAudioOGG& music_xaudio_ogg = static_cast<MusicXAudioOGG&>(*this->GetCurrentMusic());
	music_xaudio_ogg.CreateSourceVoice(this->xaudio.GetXAudio(),music_xaudio_ogg.GetBufferXAudio().GetWaveFormat());
}

void AudioXAudio::LoadSoundOGG(const string& sound_id,unique_ptr<char[]>& memory_buffer,const size_t size)
{
	//Novo som
	unique_ptr<Sound>& sound = this->GetSounds().AddResource(sound_id,(size == 0));
	sound = make_unique<SoundXAudioOGG>();

	//Carregar som
	if (size == 0)
		sound->LoadSound(sound_id);
	else
		sound->LoadSound(memory_buffer,size);

	//Verificar se é necessário adicionar Source Voices para este formato de audio
	this->AddSourceVoices(static_cast<SoundXAudioOGG&>(*sound).GetBufferXAudio().GetWaveFormat());
}

void AudioXAudio::PlaySoundFromBuffer(const string& sound_id,const float frequency_ratio)
{
	this->PlaySourceVoice(this->FindSound(sound_id),frequency_ratio);
}

void AudioXAudio::PlaySoundFromBuffer(const int sound_id,const float frequency_ratio)
{
	this->PlaySourceVoice(this->FindSound(Convert::NumberToString(sound_id)),frequency_ratio);
}

void AudioXAudio::ResumeAudio()
{
	this->xaudio.ResumeAudio();
}

void AudioXAudio::PauseAudio()
{
	this->xaudio.PauseAudio();
}
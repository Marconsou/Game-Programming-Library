#include "AudioOpenAL.h"

using namespace std;
using namespace GPL;

AudioOpenAL::AudioOpenAL(const bool enable_music,const bool enable_sound) :
Audio(enable_music,enable_sound)
{
}

AudioOpenAL::~AudioOpenAL()
{
	this->DestroyAudioEngine();
}

string AudioOpenAL::GetDeviceDisplayName() const
{
	return this->openal.GetDeviceDisplayName();
}

void AudioOpenAL::CreateAudioEngine()
{
	this->openal.CreateOpenAL();

	//Gerando os Sound Sources
	for (size_t i = 0; i < 16; i++)
	{
		//Adicionando Source OpenAL
		this->GetSoundSources().push_back(make_unique<SourceOpenAL>());

		//�ltimo Source adicionado acima
		SourceOpenAL& iterator = static_cast<SourceOpenAL&>(*this->GetSoundSources().back());

		//Criar Source
		iterator.CreateSource();
	}
}

void AudioOpenAL::DestroyAudioEngine()
{
	this->DestroyResources();
	this->openal.DestroyOpenAL();
}

const SoundOpenAL& AudioOpenAL::FindSound(const string& sound_id)
{
	//OGG
	return static_cast<SoundOpenAL&>(*this->GetSounds().GetResource(sound_id));
}

void AudioOpenAL::PlaySource(const SoundOpenAL& sound_openal,const float frequency_ratio)
{
	if (this->SoundIsEnabled())
	{
		//Indice de menor prioridade e candidato a ser parado de tocar
		static int low_priority_index = 0;

		size_t i;
		SourceOpenAL* source_openal = nullptr;
		for (i = 0; i < this->GetSoundSources().size(); i++)
		{
			SourceOpenAL& iterator = static_cast<SourceOpenAL&>(*this->GetSoundSources()[i]);

			//Fonte de som parado por que chegou ao fim ou n�o foi utilizado ainda
			if ((iterator.IsInitial()) || (iterator.IsStopped()))
			{
				//Selecionando o Source
				source_openal = &iterator;

				//Resetar o �ndice de menor prioridade, pois a fonte j� est� sendo tocada e estava dispon�vel para uso
				low_priority_index = 0;
				break;
			}
		}

		//Todas as fontes est�o ocupadas
		if (i == this->GetSoundSources().size())
		{
			SourceOpenAL& iterator = static_cast<SourceOpenAL&>(*this->GetSoundSources()[low_priority_index]);

			//Parando o som com menor prioridade
			iterator.Stop();

			//Selecionando o Source
			source_openal = &iterator;

			//Passando para o pr�ximo e se necess�rio, voltar ao in�cio com o �ndice de menor prioridade
			low_priority_index++;
			if (low_priority_index == this->GetSoundSources().size())
				low_priority_index = 0;
		}

		//Tocar o Source obtido
		if (source_openal)
		{
			source_openal->SetFrequencyRatio(frequency_ratio);
			source_openal->Play(sound_openal.GetBuffer());
		}
	}
}

void AudioOpenAL::LoadMusicOGG(const string& music_id,unique_ptr<char[]>& memory_buffer,const size_t size)
{
	//Realocar a nova m�sica
	this->GetCurrentMusic() = make_unique<MusicOpenALOGG>(this->GetMusicRestartPosition(music_id),this->GetMusicFinishPosition(music_id));

	//Carregar m�sica
	if (size == 0)
		this->GetCurrentMusic()->LoadMusic(music_id);
	else
		this->GetCurrentMusic()->LoadMusic(memory_buffer,size);
}

void AudioOpenAL::LoadSoundOGG(const string& sound_id,unique_ptr<char[]>& memory_buffer,const size_t size)
{
	//Novo som
	unique_ptr<Sound>& sound = this->GetSounds().AddResource(sound_id,(size == 0));
	sound = make_unique<SoundOpenALOGG>();

	//Carregar som
	if (size == 0)
		sound->LoadSound(sound_id);
	else
		sound->LoadSound(memory_buffer,size);
}

void AudioOpenAL::PlaySoundFromBuffer(const string& sound_id,const float frequency_ratio)
{
	this->PlaySource(this->FindSound(sound_id),frequency_ratio);
}

void AudioOpenAL::PlaySoundFromBuffer(const int sound_id,const float frequency_ratio)
{
	this->PlaySource(this->FindSound(Convert::NumberToString(sound_id)),frequency_ratio);
}

void AudioOpenAL::ResumeAudio()
{
	for (size_t i = 0; i < this->GetSoundSources().size(); i++)
	{
		SourceOpenAL& iterator = static_cast<SourceOpenAL&>(*this->GetSoundSources()[i]);

		if (iterator.IsPaused())
			iterator.Play();
	}
}

void AudioOpenAL::PauseAudio()
{
	for (size_t i = 0; i < this->GetSoundSources().size(); i++)
	{
		SourceOpenAL& iterator = static_cast<SourceOpenAL&>(*this->GetSoundSources()[i]);

		if (iterator.IsPlaying())
			iterator.Pause();
	}
}
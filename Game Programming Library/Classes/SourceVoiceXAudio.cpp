#include "SourceVoiceXAudio.h"

using namespace GPL;

SourceVoiceXAudio::~SourceVoiceXAudio()
{
	this->DeleteSourceVoice();
}

void SourceVoiceXAudio::SetVolume(const float volume)
{
	if (FAILED(this->xaudio_source_voice->SetVolume(min(max(0.0f,volume),1.0f))))
		Log::Error(__FUNCTION__,"SetVolume");
}

float SourceVoiceXAudio::GetVolume() const
{
	float volume;
	this->xaudio_source_voice->GetVolume(&volume);
	return volume;
}

void SourceVoiceXAudio::CreateSourceVoice(IXAudio2* xaudio,const WAVEFORMATEX& wave_format)
{
	this->bits = wave_format.wBitsPerSample;
	this->channels = wave_format.nChannels;
	this->rate = wave_format.nSamplesPerSec;

	//Deletar Source Voice se necessário
	this->DeleteSourceVoice();

	//Criar Source Voice
	if (FAILED(xaudio->CreateSourceVoice(&this->xaudio_source_voice,&wave_format)))
		Log::Error(__FUNCTION__,"CreateSourceVoice");
}

void SourceVoiceXAudio::Start(const XAUDIO2_BUFFER& xaudio_buffer,const float frequency_ratio) const
{
	//Alterando a frequência
	if (FAILED(this->xaudio_source_voice->SetFrequencyRatio(frequency_ratio)))
		Log::Error(__FUNCTION__,"SetFrequencyRatio");

	//Iniciar
	if (FAILED(this->xaudio_source_voice->Start()))
		Log::Error(__FUNCTION__,"Start");

	//Utilizar um Buffer para tocar o audio
	if (FAILED(this->xaudio_source_voice->SubmitSourceBuffer(&xaudio_buffer,nullptr)))
		Log::Error(__FUNCTION__,"SubmitSourceBuffer");
}

void SourceVoiceXAudio::Stop() const
{
	//Parar
	if (FAILED(this->xaudio_source_voice->Stop()))
		Log::Error(__FUNCTION__,"Stop");

	//Remover todos os Buffers pendentes se houver
	if (FAILED(this->xaudio_source_voice->FlushSourceBuffers()))
		Log::Error(__FUNCTION__,"FlushSourceBuffers");
}

bool SourceVoiceXAudio::CheckSourceVoiceFormat(const WAVEFORMATEX& wave_format) const
{
	return ((this->bits == wave_format.wBitsPerSample) && (this->channels == wave_format.nChannels) && (this->rate == wave_format.nSamplesPerSec));
}

int SourceVoiceXAudio::HasBuffersQueued() const
{
	XAUDIO2_VOICE_STATE state;
	this->xaudio_source_voice->GetState(&state);
	return state.BuffersQueued;
}

void SourceVoiceXAudio::DeleteSourceVoice()
{
	if (this->xaudio_source_voice)
	{
		this->xaudio_source_voice->DestroyVoice();
		this->xaudio_source_voice = nullptr;
	}
}
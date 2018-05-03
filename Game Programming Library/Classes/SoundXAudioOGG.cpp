#include "SoundXAudioOGG.h"

using namespace std;
using namespace GPL;

void SoundXAudioOGG::LoadAudioData(OGGFile& ogg_file)
{
	//Lendo o arquivo OGG e atualizar o Audio Data
	const size_t size = ogg_file.ReadAllData(this->GetAudioData());

	//Wave Format
	this->GetBufferXAudio().GetWaveFormat().wFormatTag = WAVE_FORMAT_PCM;
	this->GetBufferXAudio().GetWaveFormat().wBitsPerSample = 16;
	this->GetBufferXAudio().GetWaveFormat().nChannels = ogg_file.GetChannels();
	this->GetBufferXAudio().GetWaveFormat().nSamplesPerSec = ogg_file.GetRate();
	this->GetBufferXAudio().GetWaveFormat().nBlockAlign = (this->GetBufferXAudio().GetWaveFormat().nChannels * this->GetBufferXAudio().GetWaveFormat().wBitsPerSample) / 8;
	this->GetBufferXAudio().GetWaveFormat().nAvgBytesPerSec = (this->GetBufferXAudio().GetWaveFormat().nSamplesPerSec * this->GetBufferXAudio().GetWaveFormat().nBlockAlign);
	this->GetBufferXAudio().GetWaveFormat().cbSize = sizeof(WAVEFORMATEX);

	//XAudio Buffer
	this->GetBufferXAudio().GetXAudioBuffer().pAudioData = reinterpret_cast<BYTE*>(&this->GetAudioData()[0]);
	this->GetBufferXAudio().GetXAudioBuffer().AudioBytes = size;
	this->GetBufferXAudio().GetXAudioBuffer().Flags = XAUDIO2_END_OF_STREAM;
}

void SoundXAudioOGG::LoadSound(const string& file_name)
{
	//Carregar dados de audio
	this->LoadAudioData(OGGFile(file_name));
}

void SoundXAudioOGG::LoadSound(unique_ptr<char[]>& memory_buffer,const size_t size)
{
	//Carregar dados de audio
	this->LoadAudioData(OGGFile(memory_buffer,size));
}
#include "MusicXAudioOGG.h"

using namespace std;
using namespace GPL;

MusicXAudioOGG::MusicXAudioOGG(const double restart_position,const double finish_position) :
Music(restart_position,finish_position)
{
}

BufferXAudio& MusicXAudioOGG::GetBufferXAudio()
{
	return this->buffer_xaudio;
}

void MusicXAudioOGG::SetVolume(const float volume)
{
	this->source_voice_xaudio.SetVolume(volume);
}

float MusicXAudioOGG::GetVolume() const
{
	return this->source_voice_xaudio.GetVolume();
}

void MusicXAudioOGG::SetCurrentPosition(const double current_position)
{
	this->ogg_file.SetCurrentPosition(current_position);
}

double MusicXAudioOGG::GetCurrentPosition()
{
	return this->ogg_file.GetCurrentPosition();
}

void MusicXAudioOGG::CreateSourceVoice(IXAudio2* xaudio,const WAVEFORMATEX& wave_format)
{
	this->source_voice_xaudio.CreateSourceVoice(xaudio,wave_format);
}

void MusicXAudioOGG::LoadAudioData(const OGGFile& ogg_file)
{
	//Wave Format
	this->buffer_xaudio.GetWaveFormat().wFormatTag = WAVE_FORMAT_PCM;
	this->buffer_xaudio.GetWaveFormat().wBitsPerSample = 16;
	this->buffer_xaudio.GetWaveFormat().nChannels = this->ogg_file.GetChannels();
	this->buffer_xaudio.GetWaveFormat().nSamplesPerSec = this->ogg_file.GetRate();
	this->buffer_xaudio.GetWaveFormat().nBlockAlign = (this->buffer_xaudio.GetWaveFormat().nChannels * this->buffer_xaudio.GetWaveFormat().wBitsPerSample) / 8;
	this->buffer_xaudio.GetWaveFormat().nAvgBytesPerSec = (this->buffer_xaudio.GetWaveFormat().nSamplesPerSec * this->buffer_xaudio.GetWaveFormat().nBlockAlign);
	this->buffer_xaudio.GetWaveFormat().cbSize = sizeof(WAVEFORMATEX);

	//XAudio Buffer
	this->buffer_xaudio.GetXAudioBuffer().Flags = XAUDIO2_END_OF_STREAM;
}

void MusicXAudioOGG::LoadMusic(const string& file_name)
{
	//Abrindo o arquivo OGG, será fechado quando este objeto for deletado
	this->ogg_file.Open(file_name);

	//Carregar dados de audio
	this->LoadAudioData(ogg_file);
}

void MusicXAudioOGG::LoadMusic(unique_ptr<char[]>& memory_buffer,const size_t size)
{
	//Abrindo o arquivo OGG, será fechado quando este objeto for deletado
	this->ogg_file.Open(memory_buffer,size);

	//Carregar dados de audio
	this->LoadAudioData(ogg_file);
}

void MusicXAudioOGG::Playing()
{
	if (this->source_voice_xaudio.HasBuffersQueued() < this->GetBufferTotal() - 1)
	{
		//Buffer atual
		char* current_buffer = this->GetCurrentBuffer();

		//Lendo do parte do arquivo e colocando no Buffer atual
		const size_t size = this->ogg_file.ReadChunkData(current_buffer,this->GetBufferSize(),true);

		//Retocando a música para um ponto específico quando necessário
		this->ogg_file.CheckForReplay(this->GetRestartPosition(),this->GetFinishPosition());

		//Se tiver algo para tocar
		if (size != 0)
		{
			//Atualizando o Buffer com os dados lidos
			this->buffer_xaudio.GetXAudioBuffer().pAudioData = reinterpret_cast<BYTE*>(current_buffer);
			this->buffer_xaudio.GetXAudioBuffer().AudioBytes = size;

			//Tocar
			this->source_voice_xaudio.Start(this->buffer_xaudio.GetXAudioBuffer(),this->GetFrequencyRatio());
		}

		//Incrementa o índice do Buffer atual
		this->NextBuffer();
	}
}

void MusicXAudioOGG::Stop() const
{
	this->source_voice_xaudio.Stop();
}
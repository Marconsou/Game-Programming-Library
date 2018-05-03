#include "MusicOpenALOGG.h"

using namespace std;
using namespace GPL;

MusicOpenALOGG::MusicOpenALOGG(const double restart_position,const double finish_position) :
Music(restart_position,finish_position)
{
}

void MusicOpenALOGG::SetVolume(const float volume)
{
	this->source_openal.SetVolume(volume);
}

float MusicOpenALOGG::GetVolume() const
{
	return this->source_openal.GetVolume();
}

void MusicOpenALOGG::SetCurrentPosition(const double current_position)
{
	this->ogg_file.SetCurrentPosition(current_position);
}

double MusicOpenALOGG::GetCurrentPosition()
{
	return this->ogg_file.GetCurrentPosition();
}

void MusicOpenALOGG::LoadAudioData(OGGFile& ogg_file)
{
	//Criar Buffer OpenAL
	this->buffer_openal.CreateBuffer(ogg_file.GetChannels(),this->GetBufferTotal());

	//Criar Source OpenAL
	this->source_openal.CreateSource();
}

void MusicOpenALOGG::LoadMusic(const string& file_name)
{
	//Abrindo o arquivo OGG, será fechado quando este objeto for deletado
	this->ogg_file.Open(file_name);

	//Carregar dados de audio
	this->LoadAudioData(ogg_file);
}

void MusicOpenALOGG::LoadMusic(unique_ptr<char[]>& memory_buffer,const size_t size)
{
	//Abrindo o arquivo OGG, será fechado quando este objeto for deletado
	this->ogg_file.Open(memory_buffer,size);

	//Carregar dados de audio
	this->LoadAudioData(ogg_file);
}

bool MusicOpenALOGG::Decode(const int buffer_index)
{
	if (this->source_openal.HasBuffersQueued() < this->GetBufferTotal())
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
			this->buffer_openal.BufferData(current_buffer,buffer_index,size,this->ogg_file.GetRate());

			//Incrementa o índice do Buffer atual
			this->NextBuffer();

			//Buffer será adicionado e tocado
			return true;
		}
	}
	return false;
}

void MusicOpenALOGG::Playing()
{
	//Buffers processados
	ALint processed = this->source_openal.HasBuffersProcessed();
	while (processed--)
	{
		//Remover Buffer da fila
		ALuint current_buffer;
		this->source_openal.UnqueueBuffers(1,&current_buffer);

		//Obter o índice do Buffer removido
		size_t index = -1;
		for (size_t i = 0; i < this->buffer_openal.GetBuffer().size(); i++)
		{
			if (this->buffer_openal.GetBuffer()[i] == current_buffer)
			{
				index = i;
				break;
			}
		}

		//Decodificar
		this->Decode(index);

		//Adicionar Buffer que for removido anteriormente e que recebeu novos dados de audio para a fila
		this->source_openal.QueueBuffers(1,&current_buffer);
	}

	//Se não tiver tocando
	if (!this->source_openal.IsPlaying())
	{
		ALsizei buffers_to_queue = 0;
		for (int i = 0; i < this->GetBufferTotal(); i++)
		{
			if (this->Decode(i))
				buffers_to_queue++;
		}

		//Adicionar e tocar todos os Buffers que foram decodificados e que receberam nosos dados de audio
		this->source_openal.QueueBuffers(buffers_to_queue,&this->buffer_openal.GetBuffer()[0]);
		this->source_openal.Play();
	}

	//Atualizando a frequência
	this->source_openal.SetFrequencyRatio(this->GetFrequencyRatio());
}

void MusicOpenALOGG::Stop() const
{
	this->source_openal.Stop();
}
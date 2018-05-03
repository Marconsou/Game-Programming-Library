#include "OGGFile.h"

using namespace std;
using namespace GPL;

OGGFile::OGGFile()
{
	memset(&this->ogg_vorbis_file,0,sizeof(OggVorbis_File));
}

OGGFile::OGGFile(const string& file_name) :
OGGFile()
{
	this->Open(file_name);
}

OGGFile::OGGFile(unique_ptr<char[]>& memory_buffer,const size_t size) :
OGGFile()
{
	this->Open(memory_buffer,size);
}

OGGFile::~OGGFile()
{
	this->Close();
}

size_t OGGFile::GetAudioBufferSize()
{
	return static_cast<size_t>(ov_pcm_total(&this->ogg_vorbis_file,-1) * this->GetChannels() * sizeof(short));
}

int OGGFile::GetChannels() const
{
	return this->ogg_vorbis_file.vi->channels;
}

long OGGFile::GetRate() const
{
	return this->ogg_vorbis_file.vi->rate;
}

void OGGFile::SetCurrentPosition(const double current_position)
{
	//Alterando posição atual
	if (ov_time_seek(&this->ogg_vorbis_file,current_position) != 0)
		Log::Error(__FUNCTION__,"ov_time_seek");
}

double OGGFile::GetCurrentPosition()
{
	//Buscando posição atual
	const double current_position = ov_time_tell(&this->ogg_vorbis_file);
	if (current_position == OV_EINVAL)
		Log::Error(__FUNCTION__,"ov_time_tell");
	return current_position;
}

void OGGFile::Open(const string& file_name)
{
	//Abrindo de um arquivo
	if (ov_fopen(file_name.c_str(),&this->ogg_vorbis_file) < 0)
		Log::Error(__FUNCTION__,"ov_fopen",file_name);
}

void OGGFile::Open(unique_ptr<char[]>& memory_buffer,const size_t size)
{
	//Atualizando a estrutura para as funções callbacks
	this->ogg_file_callback.file_pointer = move(memory_buffer);
	this->ogg_file_callback.current_pointer = this->ogg_file_callback.file_pointer.get();
	this->ogg_file_callback.file_size = size;

	//Funções callbacks
	const ov_callbacks callbacks = {OGGFile::ReadCallback,OGGFile::SeekCallback,OGGFile::CloseCallback,OGGFile::TellCallback};

	//Abrindo arquivo na memória
	if (ov_open_callbacks(static_cast<void*>(&this->ogg_file_callback),&this->ogg_vorbis_file,nullptr,0,callbacks) < 0)
		Log::Error(__FUNCTION__,"ov_open_callbacks");
}

size_t OGGFile::ReadAllData(unique_ptr<char[]>& audio_buffer)
{
	//Alocando espaço para Audio Buffer
	const size_t audio_buffer_size = this->GetAudioBufferSize();
	audio_buffer = make_unique<char[]>(audio_buffer_size);

	//Ler dados
	this->ReadChunkData(audio_buffer.get(),audio_buffer_size,false);

	//Retornando o tamanho do Audio Buffer
	return audio_buffer_size;
}

size_t OGGFile::ReadChunkData(char* audio_buffer,const size_t audio_buffer_size,const bool rewind)
{
	size_t position = 0;
	size_t result;
	int bitstream;

	do
	{
		//Lendo bytes de audio do arquivo
		result = ov_read(&this->ogg_vorbis_file,&audio_buffer[0] + position,audio_buffer_size - position,0,2,1,&bitstream);

		//Fim do aquivo (EOF)
		if (result == 0)
		{
			//Rebobinar o audio
			if (rewind)
				this->SetCurrentPosition(0);

			break;
		}

		//Erro fatal
		else if (result < 0)
			Log::Error(__FUNCTION__,"ov_read");

		//Atualizando a posição para ler os próximos bytes
		position += result;
	} while (position < audio_buffer_size);

	return position;
}

void OGGFile::CheckForReplay(const double restart_position,const double finish_position)
{
	if (restart_position != finish_position)
	{
		//Se passou do ponto final
		if (this->GetCurrentPosition() >= finish_position)
		{
			//Reinciar o audio para o ponto de replay
			this->SetCurrentPosition(restart_position);
		}
	}
}

void OGGFile::Close()
{
	//Verificar se o Datasource aponta para algum arquivo
	if (this->ogg_vorbis_file.datasource)
	{
		//Fechando arquivo
		if (ov_clear(&this->ogg_vorbis_file) != 0)
			Log::Error(__FUNCTION__,"ov_clear");
	}
}

size_t OGGFile::ReadCallback(void* ptr,size_t size,size_t nmemb,void* datasource)
{
	//Post com o source para implementação de leitura na memória
	//http://stackoverflow.com/questions/13437422/libvorbis-audio-decode-from-memory-in-c
	//https://github.com/TTimo/doom3.gpl/blob/master/neo/sound/snd_decoder.cpp

	OGGFileCallback* ogg_file_callback = static_cast<OGGFileCallback*>(datasource);

	size_t length = size * nmemb;
	if (ogg_file_callback->current_pointer + length > ogg_file_callback->file_pointer.get() + ogg_file_callback->file_size)
		length = ogg_file_callback->file_pointer.get() + ogg_file_callback->file_size - ogg_file_callback->current_pointer;

	memcpy(ptr,ogg_file_callback->current_pointer,length);
	ogg_file_callback->current_pointer += length;
	return length;
}

int OGGFile::SeekCallback(void* datasource,ogg_int64_t offset,int whence)
{
	OGGFileCallback* ogg_file_callback = static_cast<OGGFileCallback*>(datasource);

	switch (whence)
	{
	case SEEK_CUR:
		ogg_file_callback->current_pointer += offset;
		break;
	case SEEK_END:
		ogg_file_callback->current_pointer = ogg_file_callback->file_pointer.get() + ogg_file_callback->file_size - offset;
		break;
	case SEEK_SET:
		ogg_file_callback->current_pointer = ogg_file_callback->file_pointer.get() + offset;
		break;
	default:
		return -1;
	}

	if (ogg_file_callback->current_pointer < ogg_file_callback->file_pointer.get())
	{
		ogg_file_callback->current_pointer = ogg_file_callback->file_pointer.get();
		return -1;
	}

	if (ogg_file_callback->current_pointer > ogg_file_callback->file_pointer.get() + ogg_file_callback->file_size)
	{
		ogg_file_callback->current_pointer = ogg_file_callback->file_pointer.get() + ogg_file_callback->file_size;
		return -1;
	}
	return 0;
}

int OGGFile::CloseCallback(void* datasource)
{
	return 0;
}

long OGGFile::TellCallback(void* datasource)
{
	OGGFileCallback* ogg_file_callback = static_cast<OGGFileCallback*>(datasource);
	return (ogg_file_callback->current_pointer - ogg_file_callback->file_pointer.get());
}
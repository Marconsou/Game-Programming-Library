#include "BufferOpenAL.h"

using namespace std;
using namespace GPL;

BufferOpenAL::~BufferOpenAL()
{
	this->DeleteBuffer();
}

vector<ALuint>& BufferOpenAL::GetBuffer()
{
	return this->buffer;
}

const vector<ALuint>& BufferOpenAL::GetBuffer() const
{
	return this->buffer;
}

void BufferOpenAL::CreateBuffer(const int channels,const int buffer_total)
{
	//Deletar Buffer se precisar
	this->DeleteBuffer();

	//Gerando Buffer
	this->buffer.resize(buffer_total,0);
	alGenBuffers(this->buffer.size(),&this->buffer[0]);
	if (alGetError() != AL_NO_ERROR)
		Log::Error(__FUNCTION__,"alGenBuffers");

	//Format com base nos Channels
	if (channels == 1)
		this->format = AL_FORMAT_MONO16;
	else
		this->format = AL_FORMAT_STEREO16;
}

void BufferOpenAL::CreateBuffer(char* audio_data,const int channels,const ALsizei size,const ALsizei rate)
{
	//Criar Buffer
	this->CreateBuffer(channels,1);

	//Utilizando o Audio Data para o Buffer criado
	this->BufferData(audio_data,0,size,rate);
}

void BufferOpenAL::BufferData(char* audio_data,const int buffer_index,const ALsizei size,const ALsizei rate)
{
	//Alimentando o Buffer
	alBufferData(this->buffer[buffer_index],this->format,&audio_data[0],size,rate);
	if (alGetError() != AL_NO_ERROR)
		Log::Error(__FUNCTION__,"alBufferData");
}

void BufferOpenAL::DeleteBuffer()
{
	//Se o primeiro índice for diferente de 0, todos serão
	if ((!this->buffer.empty()) && (this->buffer[0] != 0))
	{
		const size_t size = this->buffer.size();

		//Deletando os Buffers
		alDeleteBuffers(size,&this->buffer[0]);
		if (alGetError() != AL_NO_ERROR)
			Log::Error(__FUNCTION__,"alDeleteBuffers");

		//Resetar os valores do Buffer
		this->buffer.clear();
		this->buffer.resize(size,0);
	}
}
#include "Music.h"

using namespace std;
using namespace GPL;

Music::Music(const double restart_position,const double finish_position,const int buffer_total,const int buffer_size) :
restart_position(restart_position),
finish_position(finish_position),
buffer_total(buffer_total),
buffer_size(buffer_size),
buffers(buffer_total * buffer_size)
{
}

void Music::SetFrequencyRatio(const float frequency_ratio)
{
	this->frequency_ratio = frequency_ratio;
}

float Music::GetFrequencyRatio() const
{
	return this->frequency_ratio;
}

double Music::GetRestartPosition() const
{
	return this->restart_position;
}

double Music::GetFinishPosition() const
{
	return this->finish_position;
}

int Music::GetBufferTotal() const
{
	return this->buffer_total;
}

int Music::GetBufferSize() const
{
	return this->buffer_size;
}

char* Music::GetCurrentBuffer()
{
	return &this->buffers[this->buffer_size * this->current_buffer_index];
}

void Music::NextBuffer()
{
	this->current_buffer_index++;
	this->current_buffer_index %= this->buffer_total;
}
#include "SoundOpenALOGG.h"

using namespace std;
using namespace GPL;

void SoundOpenALOGG::LoadAudioData(OGGFile& ogg_file)
{
	//Lendo o arquivo OGG e atualizar o Audio Data
	const size_t size = ogg_file.ReadAllData(this->GetAudioData());

	//Criando o buffer
	this->CreateBuffer(ogg_file.GetChannels(),size,ogg_file.GetRate());
}

void SoundOpenALOGG::LoadSound(const string& file_name)
{
	this->LoadAudioData(OGGFile(file_name));
}

void SoundOpenALOGG::LoadSound(unique_ptr<char[]>& memory_buffer,const size_t size)
{
	this->LoadAudioData(OGGFile(memory_buffer,size));
}
#include "OpenAL.h"

using namespace std;
using namespace GPL;

OpenAL::~OpenAL()
{
	this->DestroyOpenAL();
}

string OpenAL::GetDeviceDisplayName() const
{
	string all_device_specifier(alcGetString(this->openal_device,ALC_DEFAULT_ALL_DEVICES_SPECIFIER));
	all_device_specifier.erase(0,string(string(alcGetString(this->openal_device,ALC_DEFAULT_DEVICE_SPECIFIER)) + " on ").size());
	return all_device_specifier;
}

void OpenAL::CreateOpenAL()
{
	//Abrindo o dispositivo principal
	this->openal_device = alcOpenDevice(nullptr);
	if (alcGetError(this->openal_device) != ALC_NO_ERROR)
		Log::Error(__FUNCTION__,"alcOpenDevice");

	//Criando o contexto
	this->openal_context = alcCreateContext(this->openal_device,nullptr);
	if (alcGetError(this->openal_device) != ALC_NO_ERROR)
		Log::Error(__FUNCTION__,"alcCreateContext");

	//Atualizando o contexto atual com o recém criado
	if (!alcMakeContextCurrent(this->openal_context))
		Log::Error(__FUNCTION__,"alcMakeContextCurrent");

	if (alcGetError(this->openal_device) != ALC_NO_ERROR)
		Log::Error(__FUNCTION__,"alcMakeContextCurrent");
}

void OpenAL::DestroyOpenAL()
{
	//Obter o Context atual do OpenAL
	if (this->openal_context)
	{
		this->openal_context = alcGetCurrentContext();
		if (alcGetError(this->openal_device) != ALC_NO_ERROR)
			Log::Error(__FUNCTION__,"alcGetCurrentContext");
	}
	//Obter o dispositivo do Context atual
	if ((this->openal_device) && (this->openal_context))
	{
		this->openal_device = alcGetContextsDevice(this->openal_context);
		if (alcGetError(this->openal_device) != ALC_NO_ERROR)
			Log::Error(__FUNCTION__,"alcGetContextsDevice");
	}

	//Desfazendo do Context atual, para destruí-lo em seguida
	if (this->openal_context)
	{
		if (!alcMakeContextCurrent(nullptr))
			Log::Error(__FUNCTION__,"alcMakeContextCurrent");

		if (alcGetError(this->openal_device) != ALC_NO_ERROR)
			Log::Error(__FUNCTION__,"alcMakeContextCurrent");
	}

	//Destruir o OpenAL Context
	if (this->openal_context)
	{
		alcDestroyContext(this->openal_context);
		if (alcGetError(this->openal_device) != ALC_NO_ERROR)
			Log::Error(__FUNCTION__,"alcDestroyContext");

		this->openal_context = nullptr;
	}

	//Fechar o OpenAL Device
	if (this->openal_device)
	{
		if (!alcCloseDevice(this->openal_device))
			Log::Error(__FUNCTION__,"alcCloseDevice");

		this->openal_device = nullptr;
	}
}
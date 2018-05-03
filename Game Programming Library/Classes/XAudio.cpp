#include "XAudio.h"

using namespace std;
using namespace GPL;

XAudio::~XAudio()
{
	this->DestroyXAudio();
}

IXAudio2* XAudio::GetXAudio() const
{
	return this->xaudio;
}

string XAudio::GetDeviceDisplayName() const
{
	//Estrutura para os detalhes do hardware de audio
	XAUDIO2_DEVICE_DETAILS device_details;
	if (FAILED(this->xaudio->GetDeviceDetails(0,&device_details)))
		Log::Error(__FUNCTION__,"GetDeviceDetails");

	//Convertendo para string
	wstring buffer_w_char(device_details.DisplayName);
	return string(buffer_w_char.begin(),buffer_w_char.end());
}

void XAudio::CreateXAudio()
{
	//Iniciar Multithreading
	if (FAILED(CoInitializeEx(nullptr,COINIT_MULTITHREADED)))
		Log::Error(__FUNCTION__,"CoInitializeEx");

	//Criando XAudio
	DWORD flags;
#ifdef _DEBUG
	flags = XAUDIO2_DEBUG_ENGINE;
#else
	flags = 0;
#endif

	if (FAILED(XAudio2Create(&this->xaudio,flags)))
		Log::Error(__FUNCTION__,"XAudio2Create");

	//Criando Master Voice
	if (FAILED(this->xaudio->CreateMasteringVoice(&this->xaudio_master_voice)))
		Log::Error(__FUNCTION__,"CreateMasteringVoice");
}

void XAudio::DestroyXAudio()
{
	if (this->xaudio_master_voice)
	{
		this->xaudio_master_voice->DestroyVoice();
		this->xaudio_master_voice = nullptr;
	}

	const bool call_couninitialize = (this->xaudio != nullptr);
	if (this->xaudio)
		this->xaudio.Release();

	//Finalizar Multithreading
	if (call_couninitialize)
		CoUninitialize();
}

void XAudio::ResumeAudio() const
{
	if (FAILED(this->xaudio->StartEngine()))
		Log::Error(__FUNCTION__,"StartEngine");
}

void XAudio::PauseAudio() const
{
	this->xaudio->StopEngine();
}
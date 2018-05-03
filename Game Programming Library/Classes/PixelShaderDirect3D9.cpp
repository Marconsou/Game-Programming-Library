#include "PixelShaderDirect3D9.h"

using namespace std;
using namespace GPL;

const PixelShaderDirect3D9* PixelShaderDirect3D9::last_pixel_shader{};

void PixelShaderDirect3D9::SetPixelShaderConstantF(const CComPtr<IDirect3DDevice9>& direct3d_device,const PixelShaderConstantRegister start_register,const float value) const
{
	if (FAILED(direct3d_device->SetPixelShaderConstantF(static_cast<UINT>(start_register),&value,1)))
		Log::Error(__FUNCTION__,"SetPixelShaderConstantF");
}

void PixelShaderDirect3D9::CreatePixelShaderBase(const CComPtr<IDirect3DDevice9>& direct3d_device,const string& main_entry_point,const unique_ptr<char[]>& memory_buffer,const size_t size)
{
	//Deletar Pixel Shader se necessário
	this->direct3d_pixel_shader.Release();

	//Compilando o arquivo de Shader
	CComPtr<ID3D10Blob> compiled_buffer;
	CComPtr<ID3D10Blob> errors;
	UINT flags;

#ifdef _DEBUG
	flags = D3DCOMPILE_DEBUG;
#else
	flags = 0;
#endif

	if (FAILED(D3DCompile(memory_buffer.get(),size,nullptr,nullptr,nullptr,main_entry_point.c_str(),"ps_2_0",flags,0,&compiled_buffer,&errors)))
	{
		const string error_message(static_cast<char*>(errors->GetBufferPointer()));
		errors.Release();
		Log::Error(__FUNCTION__,"D3DCompile",error_message);
	}

	//Criando Pixel Shader
	if (FAILED(direct3d_device->CreatePixelShader(static_cast<DWORD*>(compiled_buffer->GetBufferPointer()),&this->direct3d_pixel_shader)))
		Log::Error(__FUNCTION__,"CreatePixelShader");
}

void PixelShaderDirect3D9::CreatePixelShader(const CComPtr<IDirect3DDevice9>& direct3d_device,const string& main_entry_point,const string file_name)
{
	ifstream file(file_name.c_str(),ifstream::binary);

	if (file.is_open())
	{
		file.seekg(0,ios::end);
		const size_t size = static_cast<size_t>(file.tellg());
		file.seekg(0,ios::beg);

		unique_ptr<char[]> memory_buffer = make_unique<char[]>(size);

		if (!file.read(memory_buffer.get(),size))
			Log::Error(__FUNCTION__,"read",file_name);

		file.close();

		this->CreatePixelShaderBase(direct3d_device,main_entry_point,memory_buffer,size);
	}
	else
		Log::Error(__FUNCTION__,"is_open",file_name);
}

void PixelShaderDirect3D9::CreatePixelShader(const CComPtr<IDirect3DDevice9>& direct3d_device,const string& main_entry_point,const int pixel_shader_id)
{
	unique_ptr<char[]> memory_buffer;
	const size_t size = ResourceFile::Read(pixel_shader_id,memory_buffer);
	if (!size)
		Log::Error(__FUNCTION__,"Read");

	this->CreatePixelShaderBase(direct3d_device,main_entry_point,memory_buffer,size);
}

void PixelShaderDirect3D9::ActivatePixelShader(const CComPtr<IDirect3DDevice9>& direct3d_device) const
{
	if (PixelShaderDirect3D9::last_pixel_shader != this)
	{
		PixelShaderDirect3D9::last_pixel_shader = this;
		if (FAILED(direct3d_device->SetPixelShader(this->direct3d_pixel_shader)))
			Log::Error(__FUNCTION__,"SetPixelShader");
	}
}

void PixelShaderDirect3D9::DeactivatePixelShader(const CComPtr<IDirect3DDevice9>& direct3d_device)
{
	PixelShaderDirect3D9::last_pixel_shader = nullptr;
	if (FAILED(direct3d_device->SetPixelShader(nullptr)))
		Log::Error(__FUNCTION__,"SetPixelShader");
}
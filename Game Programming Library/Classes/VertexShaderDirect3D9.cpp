#include "VertexShaderDirect3D9.h"

using namespace std;
using namespace GPL;

const VertexShaderDirect3D9* VertexShaderDirect3D9::last_vertex_shader{};

void VertexShaderDirect3D9::SetVertexShaderConstantF(const CComPtr<IDirect3DDevice9>& direct3d_device,const VertexShaderConstantRegister start_register,const float value) const
{
	if (FAILED(direct3d_device->SetVertexShaderConstantF(static_cast<UINT>(start_register),&value,1)))
		Log::Error(__FUNCTION__,"SetVertexShaderConstantF");
}

void VertexShaderDirect3D9::SetVertexShaderConstantF(const CComPtr<IDirect3DDevice9>& direct3d_device,const VertexShaderConstantRegister start_register,const XMMATRIX& value) const
{
	if (FAILED(direct3d_device->SetVertexShaderConstantF(static_cast<UINT>(start_register),reinterpret_cast<const float*>(&value),4)))
		Log::Error(__FUNCTION__,"SetVertexShaderConstantF");
}

void VertexShaderDirect3D9::CreateVertexShaderBase(const CComPtr<IDirect3DDevice9>& direct3d_device,const string& main_entry_point,const unique_ptr<char[]>& memory_buffer,const size_t size)
{
	//Deletar Vertex Shader se necessário
	this->direct3d_vertex_shader.Release();

	//Compilando o arquivo de Shader
	CComPtr<ID3D10Blob> compiled_buffer;
	CComPtr<ID3D10Blob> errors;
	UINT flags;

#ifdef _DEBUG
	flags = D3DCOMPILE_DEBUG;
#else
	flags = 0;
#endif

	if (FAILED(D3DCompile(memory_buffer.get(),size,nullptr,nullptr,nullptr,main_entry_point.c_str(),"vs_2_0",flags,0,&compiled_buffer,&errors)))
	{
		const string error_message(static_cast<char*>(errors->GetBufferPointer()));
		errors.Release();
		Log::Error(__FUNCTION__,"D3DCompile",error_message);
	}

	//Criando Vertex Shader
	if (FAILED(direct3d_device->CreateVertexShader(static_cast<DWORD*>(compiled_buffer->GetBufferPointer()),&this->direct3d_vertex_shader)))
		Log::Error(__FUNCTION__,"CreateVertexShader");
}

void VertexShaderDirect3D9::CreateVertexShader(const CComPtr<IDirect3DDevice9>& direct3d_device,const string& main_entry_point,const string file_name)
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

		this->CreateVertexShaderBase(direct3d_device,main_entry_point,memory_buffer,size);
	}
	else
		Log::Error(__FUNCTION__,"is_open",file_name);
}

void VertexShaderDirect3D9::CreateVertexShader(const CComPtr<IDirect3DDevice9>& direct3d_device,const string& main_entry_point,const int vertex_shader_id)
{
	unique_ptr<char[]> memory_buffer;
	const size_t size = ResourceFile::Read(vertex_shader_id,memory_buffer);
	if (!size)
		Log::Error(__FUNCTION__,"Read");

	this->CreateVertexShaderBase(direct3d_device,main_entry_point,memory_buffer,size);
}

void VertexShaderDirect3D9::ActivateVertexShader(const CComPtr<IDirect3DDevice9>& direct3d_device) const
{
	if (VertexShaderDirect3D9::last_vertex_shader != this)
	{
		VertexShaderDirect3D9::last_vertex_shader = this;
		if (FAILED(direct3d_device->SetVertexShader(this->direct3d_vertex_shader)))
			Log::Error(__FUNCTION__,"SetVertexShader");
	}
}

void VertexShaderDirect3D9::DeactivateVertexShader(const CComPtr<IDirect3DDevice9>& direct3d_device)
{
	VertexShaderDirect3D9::last_vertex_shader = nullptr;
	if (FAILED(direct3d_device->SetVertexShader(nullptr)))
		Log::Error(__FUNCTION__,"SetVertexShader");
}
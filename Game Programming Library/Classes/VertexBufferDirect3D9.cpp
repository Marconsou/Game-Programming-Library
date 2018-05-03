#include "VertexBufferDirect3D9.h"

using namespace GPL;

float* VertexBufferDirect3D9::vertex_data{};
int VertexBufferDirect3D9::vertex_data_index{};

UINT VertexBufferDirect3D9::GetOffsetInBytes() const
{
	return this->offset_in_bytes;
}

UINT VertexBufferDirect3D9::GetSize() const
{
	//Estrutura com descrição do Vertex Buffer
	static D3DVERTEXBUFFER_DESC vertex_buffer_desc;

	//Obter o tamanho atual
	if (this->direct3d_vertex_buffer)
	{
		if (FAILED(this->direct3d_vertex_buffer->GetDesc(&vertex_buffer_desc)))
			Log::Error(__FUNCTION__,"GetDesc");

		return vertex_buffer_desc.Size;
	}
	return 0;
}

void VertexBufferDirect3D9::ResetOffsetInBytes()
{
	this->offset_in_bytes = 0;
}

void VertexBufferDirect3D9::IncrementOffsetInBytes(const UINT increment)
{
	this->offset_in_bytes += increment;
}

void VertexBufferDirect3D9::CreateVertexBuffer(const CComPtr<IDirect3DDevice9>& direct3d_device,const UINT new_vertex_buffer_size,const bool dynamic_vertex_buffer)
{
	//Criar se precisar de um espaço maior e caso for estático, uma vez apenas
	if ((new_vertex_buffer_size > this->GetSize()) && (this->dynamic_vertex_buffer))
	{
		//Deletar Vertex Buffer caso necessário
		this->DeleteVertexBuffer();

		//Tipo do Vertex Buffer
		this->dynamic_vertex_buffer = dynamic_vertex_buffer;
		const DWORD usage = (this->dynamic_vertex_buffer) ? (D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY) : 0;
		const D3DPOOL pool = (this->dynamic_vertex_buffer) ? D3DPOOL_DEFAULT : D3DPOOL_MANAGED;

		//Criar Vertex Buffer
		if (FAILED(direct3d_device->CreateVertexBuffer(new_vertex_buffer_size,usage,0,pool,&this->direct3d_vertex_buffer,nullptr)))
			Log::Error(__FUNCTION__,"CreateVertexBuffer");
	}
}

void VertexBufferDirect3D9::ActivateVertexBuffer(const CComPtr<IDirect3DDevice9>& direct3d_device,const UINT stride) const
{
	if (FAILED(direct3d_device->SetStreamSource(0,this->direct3d_vertex_buffer,this->offset_in_bytes,stride)))
		Log::Error(__FUNCTION__,"SetStreamSource");
}

void VertexBufferDirect3D9::DeactivateVertexBuffer(const CComPtr<IDirect3DDevice9>& direct3d_device)
{
	if (FAILED(direct3d_device->SetStreamSource(0,nullptr,0,0)))
		Log::Error(__FUNCTION__,"SetStreamSource");
}

void VertexBufferDirect3D9::Lock() const
{
	//Resetando valores para escrita dos dados
	VertexBufferDirect3D9::vertex_data = nullptr;
	VertexBufferDirect3D9::vertex_data_index = 0;

	//Tipo do Vertex Buffer
	const DWORD flags = (this->dynamic_vertex_buffer) ? D3DLOCK_DISCARD : 0;

	if (FAILED(this->direct3d_vertex_buffer->Lock(0,0,reinterpret_cast<void**>(&VertexBufferDirect3D9::vertex_data),flags)))
		Log::Error(__FUNCTION__,"Lock");
}

void VertexBufferDirect3D9::Unlock() const
{
	if (FAILED(this->direct3d_vertex_buffer->Unlock()))
		Log::Error(__FUNCTION__,"Unlock");
}

void VertexBufferDirect3D9::DeleteVertexBuffer()
{
	this->direct3d_vertex_buffer.Release();
}

void VertexBufferDirect3D9::AddVertexData(const float vertex_data)
{
	VertexBufferDirect3D9::vertex_data[VertexBufferDirect3D9::vertex_data_index] = vertex_data;
	VertexBufferDirect3D9::vertex_data_index++;
}
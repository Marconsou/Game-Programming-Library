#include "IndexBufferDirect3D9.h"

using namespace GPL;

short* IndexBufferDirect3D9::index_data{};
int IndexBufferDirect3D9::index_data_index{};
const IndexBufferDirect3D9* IndexBufferDirect3D9::last_index_buffer{};

UINT IndexBufferDirect3D9::GetStartIndex() const
{
	return this->start_index;
}

UINT IndexBufferDirect3D9::GetSize() const
{
	//Estrutura com descrição do Index Buffer
	static D3DINDEXBUFFER_DESC index_buffer_desc;

	//Obter o tamanho atual
	if (this->direct3d_index_buffer)
	{
		if (FAILED(this->direct3d_index_buffer->GetDesc(&index_buffer_desc)))
			Log::Error(__FUNCTION__,"GetDesc");

		return index_buffer_desc.Size;
	}
	return 0;
}

void IndexBufferDirect3D9::ResetStartIndex()
{
	this->start_index = 0;
}

void IndexBufferDirect3D9::IncrementStartIndex(const UINT increment)
{
	this->start_index += increment;
}

void IndexBufferDirect3D9::CreateIndexBuffer(const CComPtr<IDirect3DDevice9>& direct3d_device,const UINT new_index_buffer_size,const bool dynamic_index_buffer)
{
	//Criar se precisar de um espaço maior e caso for estático, uma vez apenas
	if ((new_index_buffer_size > this->GetSize()) && (this->dynamic_index_buffer))
	{
		//Deletar Index Buffer caso necessário
		this->DeleteIndexBuffer();

		//Tipo do Index Buffer
		this->dynamic_index_buffer = dynamic_index_buffer;
		const DWORD usage = (this->dynamic_index_buffer) ? (D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY) : 0;
		const D3DPOOL pool = (this->dynamic_index_buffer) ? D3DPOOL_DEFAULT : D3DPOOL_MANAGED;

		//Criar Index Buffer
		if (FAILED(direct3d_device->CreateIndexBuffer(new_index_buffer_size,usage,D3DFMT_INDEX16,pool,&this->direct3d_index_buffer,nullptr)))
			Log::Error(__FUNCTION__,"CreateIndexBuffer");
	}
}

void IndexBufferDirect3D9::ActivateIndexBuffer(const CComPtr<IDirect3DDevice9>& direct3d_device) const
{
	if (IndexBufferDirect3D9::last_index_buffer != this)
	{
		IndexBufferDirect3D9::last_index_buffer = this;
		if (FAILED(direct3d_device->SetIndices(this->direct3d_index_buffer)))
			Log::Error(__FUNCTION__,"SetIndices");
	}
}

void IndexBufferDirect3D9::DeactivateIndexBuffer(const CComPtr<IDirect3DDevice9>& direct3d_device)
{
	IndexBufferDirect3D9::last_index_buffer = nullptr;
	if (FAILED(direct3d_device->SetIndices(nullptr)))
		Log::Error(__FUNCTION__,"SetIndices");
}

void IndexBufferDirect3D9::Lock() const
{
	//Resetando valores para escrita dos dados
	IndexBufferDirect3D9::index_data = nullptr;
	IndexBufferDirect3D9::index_data_index = 0;

	//Tipo do Index Buffer
	const DWORD flags = (this->dynamic_index_buffer) ? D3DLOCK_DISCARD : 0;

	if (FAILED(this->direct3d_index_buffer->Lock(0,0,reinterpret_cast<void**>(&IndexBufferDirect3D9::index_data),flags)))
		Log::Error(__FUNCTION__,"Lock");
}

void IndexBufferDirect3D9::Unlock() const
{
	if (FAILED(this->direct3d_index_buffer->Unlock()))
		Log::Error(__FUNCTION__,"Unlock");
}

void IndexBufferDirect3D9::DeleteIndexBuffer()
{
	this->direct3d_index_buffer.Release();
}

void IndexBufferDirect3D9::AddIndexData(const short index_data)
{
	IndexBufferDirect3D9::index_data[IndexBufferDirect3D9::index_data_index] = index_data;
	IndexBufferDirect3D9::index_data_index++;
}
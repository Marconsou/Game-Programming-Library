#ifndef INDEXBUFFERDIRECT3D9_H
#define INDEXBUFFERDIRECT3D9_H

#include <d3d9.h>
#include <atlbase.h>
#include "Log.h"

namespace GPL
{
	class IndexBufferDirect3D9
	{
	public:
		GPL_DLL IndexBufferDirect3D9() = default;
		GPL_DLL UINT GetStartIndex() const;
		GPL_DLL UINT GetSize() const;
		GPL_DLL void ResetStartIndex();
		GPL_DLL void IncrementStartIndex(const UINT increment);
		GPL_DLL void CreateIndexBuffer(const CComPtr<IDirect3DDevice9>& direct3d_device,const UINT new_index_buffer_size,const bool dynamic_index_buffer);
		GPL_DLL void ActivateIndexBuffer(const CComPtr<IDirect3DDevice9>& direct3d_device) const;
		GPL_DLL void Lock() const;
		GPL_DLL void Unlock() const;
		GPL_DLL void DeleteIndexBuffer();
		GPL_DLL static void AddIndexData(const short index_data);
		static void DeactivateIndexBuffer(const CComPtr<IDirect3DDevice9>& direct3d_device);
	private:
		CComPtr<IDirect3DIndexBuffer9> direct3d_index_buffer;
		UINT start_index{};
		bool dynamic_index_buffer{true};
		static short* index_data;
		static int index_data_index;
		static const IndexBufferDirect3D9* last_index_buffer;
		IndexBufferDirect3D9(const IndexBufferDirect3D9&) = delete;
		IndexBufferDirect3D9& operator=(const IndexBufferDirect3D9&) = delete;
	};
}

#endif
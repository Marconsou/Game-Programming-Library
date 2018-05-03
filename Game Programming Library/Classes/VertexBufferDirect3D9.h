#ifndef VERTEXBUFFERDIRECT3D9_H
#define VERTEXBUFFERDIRECT3D9_H

#include <d3d9.h>
#include <atlbase.h>
#include "Log.h"

namespace GPL
{
	class VertexBufferDirect3D9
	{
	public:
		GPL_DLL VertexBufferDirect3D9() = default;
		GPL_DLL UINT GetOffsetInBytes() const;
		GPL_DLL UINT GetSize() const;
		GPL_DLL void ResetOffsetInBytes();
		GPL_DLL void IncrementOffsetInBytes(const UINT increment);
		GPL_DLL void CreateVertexBuffer(const CComPtr<IDirect3DDevice9>& direct3d_device,const UINT new_vertex_buffer_size,const bool dynamic_vertex_buffer);
		GPL_DLL void ActivateVertexBuffer(const CComPtr<IDirect3DDevice9>& direct3d_device,const UINT stride) const;
		GPL_DLL void Lock() const;
		GPL_DLL void Unlock() const;
		GPL_DLL void DeleteVertexBuffer();
		GPL_DLL static void AddVertexData(const float vertex_data);
		static void DeactivateVertexBuffer(const CComPtr<IDirect3DDevice9>& direct3d_device);
	private:
		CComPtr<IDirect3DVertexBuffer9> direct3d_vertex_buffer;
		UINT offset_in_bytes{};
		bool dynamic_vertex_buffer{true};
		static float* vertex_data;
		static int vertex_data_index;
		VertexBufferDirect3D9(const VertexBufferDirect3D9&) = delete;
		VertexBufferDirect3D9& operator=(const VertexBufferDirect3D9&) = delete;
	};
}

#endif
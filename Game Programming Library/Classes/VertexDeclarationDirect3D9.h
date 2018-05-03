#ifndef VERTEXDECLARATIONDIRECT3D9_H
#define VERTEXDECLARATIONDIRECT3D9_H

#include <d3d9.h>
#include <atlbase.h>
#include "Log.h"

namespace GPL
{
	class VertexDeclarationDirect3D9
	{
	public:
		GPL_DLL VertexDeclarationDirect3D9() = default;
		GPL_DLL void CreateVertexDeclaration(const CComPtr<IDirect3DDevice9>& direct3d_device,const D3DVERTEXELEMENT9& direct3d_vertex_element);
		GPL_DLL void ActivateVertexDeclaration(const CComPtr<IDirect3DDevice9>& direct3d_device) const;
	private:
		CComPtr<IDirect3DVertexDeclaration9> direct3d_vertex_declaration;
		VertexDeclarationDirect3D9(const VertexDeclarationDirect3D9&) = delete;
		VertexDeclarationDirect3D9& operator=(const VertexDeclarationDirect3D9&) = delete;
	};
}

#endif
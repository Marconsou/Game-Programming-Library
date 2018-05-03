#include "VertexDeclarationDirect3D9.h"

using namespace GPL;

void VertexDeclarationDirect3D9::CreateVertexDeclaration(const CComPtr<IDirect3DDevice9>& direct3d_device,const D3DVERTEXELEMENT9& direct3d_vertex_element)
{
	if (FAILED(direct3d_device->CreateVertexDeclaration(&direct3d_vertex_element,&this->direct3d_vertex_declaration)))
		Log::Error(__FUNCTION__,"CreateVertexDeclaration");
}

void VertexDeclarationDirect3D9::ActivateVertexDeclaration(const CComPtr<IDirect3DDevice9>& direct3d_device) const
{
	if (FAILED(direct3d_device->SetVertexDeclaration(this->direct3d_vertex_declaration)))
		Log::Error(__FUNCTION__,"SetVertexDeclaration");
}
#ifndef VERTEXSHADERDIRECT3D9_H
#define VERTEXSHADERDIRECT3D9_H

#include <D3Dcompiler.h>
#include <d3d9.h>
#include <xnamath.h>
#include <atlbase.h>
#include "Log.h"
#include "ResourceFile.h"

namespace GPL
{
	enum class VertexShaderConstantRegister
	{
		WorldViewProjection,
	};

	class VertexShaderDirect3D9
	{
	public:
		GPL_DLL VertexShaderDirect3D9() = default;
		GPL_DLL void SetVertexShaderConstantF(const CComPtr<IDirect3DDevice9>& direct3d_device,const VertexShaderConstantRegister start_register,const float value) const;
		GPL_DLL void SetVertexShaderConstantF(const CComPtr<IDirect3DDevice9>& direct3d_device,const VertexShaderConstantRegister start_register,const XMMATRIX& value) const;
		GPL_DLL void CreateVertexShader(const CComPtr<IDirect3DDevice9>& direct3d_device,const std::string& main_entry_point,const std::string file_name);
		GPL_DLL void CreateVertexShader(const CComPtr<IDirect3DDevice9>& direct3d_device,const std::string& main_entry_point,const int vertex_shader_id);
		GPL_DLL void ActivateVertexShader(const CComPtr<IDirect3DDevice9>& direct3d_device) const;
		static void DeactivateVertexShader(const CComPtr<IDirect3DDevice9>& direct3d_device);
	private:
		CComPtr<IDirect3DVertexShader9> direct3d_vertex_shader;
		static const VertexShaderDirect3D9* last_vertex_shader;
		VertexShaderDirect3D9(const VertexShaderDirect3D9&) = delete;
		VertexShaderDirect3D9& operator=(const VertexShaderDirect3D9&) = delete;
		void CreateVertexShaderBase(const CComPtr<IDirect3DDevice9>& direct3d_device,const std::string& main_entry_point,const std::unique_ptr<char[]>& memory_buffer,const size_t size);
	};
}

#endif
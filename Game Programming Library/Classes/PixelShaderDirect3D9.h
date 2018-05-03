#ifndef PIXELSHADERDIRECT3D9_H
#define PIXELSHADERDIRECT3D9_H

#include <D3Dcompiler.h>
#include <d3d9.h>
#include <atlbase.h>
#include "Log.h"
#include "ResourceFile.h"

namespace GPL
{
	enum class PixelShaderConstantRegister
	{
		InvertColor,
		GrayScale,
		TurnHorizontal,
		TurnVertical,
		PixelateGridSize,
	};

	class PixelShaderDirect3D9
	{
	public:
		GPL_DLL PixelShaderDirect3D9() = default;
		GPL_DLL void SetPixelShaderConstantF(const CComPtr<IDirect3DDevice9>& direct3d_device,const PixelShaderConstantRegister start_register,const float value) const;
		GPL_DLL void CreatePixelShader(const CComPtr<IDirect3DDevice9>& direct3d_device,const std::string& main_entry_point,const std::string file_name);
		GPL_DLL void CreatePixelShader(const CComPtr<IDirect3DDevice9>& direct3d_device,const std::string& main_entry_point,const int pixel_shader_id);
		GPL_DLL void ActivatePixelShader(const CComPtr<IDirect3DDevice9>& direct3d_device) const;
		static void DeactivatePixelShader(const CComPtr<IDirect3DDevice9>& direct3d_device);
	private:
		CComPtr<IDirect3DPixelShader9> direct3d_pixel_shader;
		static const PixelShaderDirect3D9* last_pixel_shader;
		PixelShaderDirect3D9(const PixelShaderDirect3D9&) = delete;
		PixelShaderDirect3D9& operator=(const PixelShaderDirect3D9&) = delete;
		void CreatePixelShaderBase(const CComPtr<IDirect3DDevice9>& direct3d_device,const std::string& main_entry_point,const std::unique_ptr<char[]>& memory_buffer,const size_t size);
	};
}

#endif
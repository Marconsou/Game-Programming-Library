#ifndef DIRECT3D9_H
#define DIRECT3D9_H

#include <d3d9.h>
#include <xnamath.h>
#include <atlbase.h>
#include "VideoMode.h"
#include "Convert.h"
#include "Log.h"
#include "View.h"
#include "Model.h"

namespace GPL
{
	class Direct3D9
	{
	public:
		GPL_DLL Direct3D9() = default;
		GPL_DLL const CComPtr<IDirect3DDevice9>& GetDevice() const;
		GPL_DLL HRESULT GetDeviceState() const;
		GPL_DLL std::string GetDeviceDisplayName() const;
		GPL_DLL std::vector<std::string> GetSupportedResolutions(const VideoMode& video_mode) const;
		GPL_DLL void SetPresentParameters(const VideoMode& video_mode);
		GPL_DLL void SetRenderState(const D3DRENDERSTATETYPE render_state_type,const DWORD new_value) const;
		GPL_DLL void SetSamplerState(const D3DSAMPLERSTATETYPE sampler_state_type,const DWORD new_value) const;
		GPL_DLL void SetViewport(const int x,const int y,const int width,const int height) const;
		GPL_DLL void CreateDirect3D(const HWND& handle_window,const VideoMode& video_mode);
		GPL_DLL bool CheckDisplayMode(const VideoMode& video_mode) const;
		GPL_DLL void OrthographicProjection(const float width,const float height,const float near_z,const float far_z) const;
		GPL_DLL void PerspectiveProjection(const float width,const float height,const float fov) const;
		GPL_DLL const XMMATRIX& ProcessMatrix(const Model& model) const;
		GPL_DLL void ResetDevice();
		GPL_DLL void ClearBeginScene(const Color& clear_color) const;
		GPL_DLL void DrawIndexedPrimitive(const D3DPRIMITIVETYPE mode,const UINT vertex_total,const UINT start_index,const UINT primitive_count) const;
		GPL_DLL void EndRender() const;
		GPL_DLL void Present() const;
	private:
		CComPtr<IDirect3D9> direct3d;
		CComPtr<IDirect3DDevice9> direct3d_device;
		D3DPRESENT_PARAMETERS present_parameters;
		static XMMATRIX projection;
		Direct3D9(const Direct3D9&) = delete;
		Direct3D9& operator=(const Direct3D9&) = delete;
		bool MatrixOperations(XMMATRIX& matrix,const Point3D<float>& translate,const Point3D<float>& transform,const Point3D<float>& scale,const Point3D<float>& rotate) const;
		static D3DFORMAT BackBufferFormat(const VideoMode& video_mode);
		static int ColorDepth(const D3DFORMAT format);
		static UINT VSync(const VideoMode& video_mode);
	};
}

#endif
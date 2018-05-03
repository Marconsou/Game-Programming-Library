#include "Direct3D9.h"

using namespace std;
using namespace GPL;

XMMATRIX Direct3D9::projection;

const CComPtr<IDirect3DDevice9>& Direct3D9::GetDevice() const
{
	return this->direct3d_device;
}

HRESULT Direct3D9::GetDeviceState() const
{
	return this->direct3d_device->TestCooperativeLevel();
}

string Direct3D9::GetDeviceDisplayName() const
{
	//Estrutura para os detalhes do hardware de video
	D3DADAPTER_IDENTIFIER9 adapter_identifier;
	if (FAILED(this->direct3d->GetAdapterIdentifier(D3DADAPTER_DEFAULT,0,&adapter_identifier)))
		Log::Error(__FUNCTION__,"GetAdapterIdentifier");

	return string(adapter_identifier.Description);
}

vector<string> Direct3D9::GetSupportedResolutions(const VideoMode& video_mode) const
{
	vector<string> supported_resolutions;

	const D3DFORMAT back_buffer_format = Direct3D9::BackBufferFormat(video_mode);

	//Configurações que estão armazenadas no registro
	DEVMODE dev_mode;
	if (!EnumDisplaySettings(nullptr,ENUM_REGISTRY_SETTINGS,&dev_mode))
		Log::Error(__FUNCTION__,"EnumDisplaySettings");

	D3DDISPLAYMODE display_mode;
	for (UINT i = 0; i < this->direct3d->GetAdapterModeCount(D3DADAPTER_DEFAULT,back_buffer_format); i++)
	{
		//Obter o Display Mode da lista suportada
		if (FAILED(this->direct3d->EnumAdapterModes(D3DADAPTER_DEFAULT,back_buffer_format,i,&display_mode)))
			Log::Error(__FUNCTION__,"EnumAdapterModes");

		const int refresh_rate = (video_mode.GetWindowed()) ? (dev_mode.dmDisplayFrequency) : (video_mode.GetFullScreenRefreshRate());
		if (display_mode.RefreshRate == refresh_rate)
		{
			const int width = static_cast<int>(display_mode.Width);
			const int height = static_cast<int>(display_mode.Height);

			if (width > height)
			{
				//Adicionando configuração
				supported_resolutions.push_back(((width > 1000) ? "" : " ") +
												Convert::NumberToString(width) + "x" +
												Convert::NumberToString(height) + " " +
												Convert::NumberToString(Direct3D9::ColorDepth(back_buffer_format)) + "bits " +
												Convert::NumberToString(refresh_rate) + "Hz");
			}
		}
	}
	sort(supported_resolutions.begin(),supported_resolutions.end());
	supported_resolutions.erase(unique(supported_resolutions.begin(),supported_resolutions.end()),supported_resolutions.end());
	return supported_resolutions;
}

void Direct3D9::SetPresentParameters(const VideoMode& video_mode)
{
	this->present_parameters.BackBufferWidth = video_mode.GetWidth();
	this->present_parameters.BackBufferHeight = video_mode.GetHeight();
	this->present_parameters.BackBufferFormat = Direct3D9::BackBufferFormat(video_mode);
	this->present_parameters.Windowed = video_mode.GetWindowed();
	this->present_parameters.PresentationInterval = Direct3D9::VSync(video_mode);
	this->present_parameters.FullScreen_RefreshRateInHz = (video_mode.GetWindowed()) ? D3DPRESENT_RATE_DEFAULT : video_mode.GetFullScreenRefreshRate();
	this->present_parameters.BackBufferCount = 1;
	this->present_parameters.MultiSampleType = D3DMULTISAMPLE_NONE;
	this->present_parameters.MultiSampleQuality = 0;
	this->present_parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	this->present_parameters.EnableAutoDepthStencil = true;
	this->present_parameters.AutoDepthStencilFormat = D3DFMT_D24X8;
	this->present_parameters.Flags = 0;
}

void Direct3D9::SetRenderState(const D3DRENDERSTATETYPE render_state_type,const DWORD new_value) const
{
	//Obter o valor atual
	DWORD current_value;
	if (FAILED(this->direct3d_device->GetRenderState(render_state_type,&current_value)))
		Log::Error(__FUNCTION__,"GetRenderState");

	//Verificar a necessidade de trocar para o novo valor
	if (current_value != new_value)
	{
		if (FAILED(this->direct3d_device->SetRenderState(render_state_type,new_value)))
			Log::Error(__FUNCTION__,"SetRenderState");
	}
}

void Direct3D9::SetSamplerState(const D3DSAMPLERSTATETYPE sampler_state_type,const DWORD new_value) const
{
	//Obter o valor atual
	DWORD current_value;
	if (FAILED(this->direct3d_device->GetSamplerState(0,sampler_state_type,&current_value)))
		Log::Error(__FUNCTION__,"GetSamplerState");

	//Verificar a necessidade de trocar para o novo valor
	if (current_value != new_value)
	{
		if (FAILED(this->direct3d_device->SetSamplerState(0,sampler_state_type,new_value)))
			Log::Error(__FUNCTION__,"SetSamplerState");
	}
}

void Direct3D9::SetViewport(const int x,const int y,const int width,const int height) const
{
	const D3DVIEWPORT9 viewport{x,y,width,height,0.0f,1.0f};
	if (FAILED(this->direct3d_device->SetViewport(&viewport)))
		Log::Error(__FUNCTION__,"SetViewport");
}

void Direct3D9::CreateDirect3D(const HWND& handle_window,const VideoMode& video_mode)
{
	this->direct3d.Attach(Direct3DCreate9(D3D_SDK_VERSION));
	if (!this->direct3d)
		Log::Error(__FUNCTION__,"Direct3DCreate9");

	//Verificando se as configurações serão aceitas pelo dispositivo
	const D3DFORMAT back_buffer_format = Direct3D9::BackBufferFormat(video_mode);
	if (FAILED(this->direct3d->CheckDeviceType(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,back_buffer_format,back_buffer_format,video_mode.GetWindowed())))
		Log::Error(__FUNCTION__,"CheckDeviceType");

	//Obtendo informações do dispositivo
	D3DCAPS9 caps;
	if (FAILED(this->direct3d->GetDeviceCaps(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,&caps)))
		Log::Error(__FUNCTION__,"GetDeviceCaps");

	this->SetPresentParameters(video_mode);
	this->present_parameters.hDeviceWindow = handle_window;

	//Verificando se suporta Transformation and Lighting via Hardware então utilizar Vertex Processing via Hardware
	const DWORD flags = (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) ? D3DCREATE_HARDWARE_VERTEXPROCESSING : D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	if (FAILED(this->direct3d->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,this->present_parameters.hDeviceWindow,flags,&this->present_parameters,&this->direct3d_device)))
		Log::Error(__FUNCTION__,"CreateDevice");
}

bool Direct3D9::CheckDisplayMode(const VideoMode& video_mode) const
{
	D3DDISPLAYMODE display_mode;
	const D3DFORMAT back_buffer_format = Direct3D9::BackBufferFormat(video_mode);
	const int width = video_mode.GetWidth();
	const int height = video_mode.GetHeight();
	for (UINT i = 0; i < this->direct3d->GetAdapterModeCount(D3DADAPTER_DEFAULT,back_buffer_format); i++)
	{
		//Obter o Display Mode da lista suportada
		if (FAILED(this->direct3d->EnumAdapterModes(D3DADAPTER_DEFAULT,back_buffer_format,i,&display_mode)))
			Log::Error(__FUNCTION__,"EnumAdapterModes");

		//Verificar se o Display Mode exigido é suportado
		//OBS: Refresh Rate não está sendo levado em consideração aqui
		if ((display_mode.Width == width) && (display_mode.Height == height) && (display_mode.Format == back_buffer_format))
			return true;
	}
	return false;
}

void Direct3D9::OrthographicProjection(const float width,const float height,const float near_z,const float far_z) const
{
	Direct3D9::projection = XMMatrixOrthographicOffCenterLH(0.0f,width,height,0.0f,near_z,far_z);
}

void Direct3D9::PerspectiveProjection(const float width,const float height,const float fov) const
{
	Direct3D9::projection = XMMatrixPerspectiveFovLH(fov,width / height,0.1f,1000.0f);
}

bool Direct3D9::MatrixOperations(XMMATRIX& matrix,const Point3D<float>& translate,const Point3D<float>& transform,const Point3D<float>& scale,const Point3D<float>& rotate) const
{
	matrix = XMMatrixIdentity();

	const bool scaling = ((scale.GetX() != 1.0f) || (scale.GetY() != 1.0f) || ((scale.GetZ() != 1.0f)));
	const bool rotating = ((rotate.GetX() != 0.0f) || (rotate.GetY() != 0.0f) || (rotate.GetZ() != 0.0f));
	const bool translating = ((translate.GetX() != 0.0f) || (translate.GetY() != 0.0f) || (translate.GetZ() != 0.0f));

	if ((scaling) || (rotating) || (translating))
	{
		const float transformed_x = transform.GetX();
		const float transformed_y = transform.GetY();
		const float transformed_z = transform.GetZ();

		static XMMATRIX buffer;

		//Translate antes para selecionar o ponto de transformação
		buffer = XMMatrixTranslation(-transformed_x,-transformed_y,-transformed_z);
		matrix = XMMatrixMultiply(matrix,buffer);

		//Scale
		if (scaling)
		{
			buffer = XMMatrixScaling(scale.GetX(),scale.GetY(),scale.GetZ());
			matrix = XMMatrixMultiply(matrix,buffer);
		}

		//Rotate
		if (rotating)
		{
			buffer = XMMatrixRotationRollPitchYaw(XMConvertToRadians(rotate.GetX()),XMConvertToRadians(rotate.GetY()),XMConvertToRadians(rotate.GetZ()));
			matrix = XMMatrixMultiply(matrix,buffer);
		}

		//Translate
		if (translating)
		{
			buffer = XMMatrixTranslation(translate.GetX(),translate.GetY(),translate.GetZ());
			matrix = XMMatrixMultiply(matrix,buffer);
		}

		//Translate depois para voltar ao ponto original já com o ponto transformado
		buffer = XMMatrixTranslation(transformed_x,transformed_y,transformed_z);
		matrix = XMMatrixMultiply(matrix,buffer);

		return true;
	}
	return false;
}

const XMMATRIX& Direct3D9::ProcessMatrix(const Model& model) const
{
	static XMMATRIX world;
	static XMMATRIX view;
	static XMMATRIX world_view_projection;

	this->MatrixOperations(world,model.GetTranslate(),model.GetTransform(),model.GetScale(),model.GetRotate());

	//Se houve alguma operação, então considerar o View na hora de multiplicar
	if (this->MatrixOperations(view,model.GetView().GetTranslate(),model.GetView().GetTransform(),model.GetView().GetScale(),model.GetView().GetRotate()))
		world_view_projection = (XMMatrixMultiply(world,view) * Direct3D9::projection);
	else
		world_view_projection = XMMatrixMultiply(world,Direct3D9::projection);

	//Matrix Transposta para o Vertex Shader
	world_view_projection = XMMatrixTranspose(world_view_projection);

	return world_view_projection;
}

void Direct3D9::ResetDevice()
{
	if (FAILED(this->direct3d_device->Reset(&this->present_parameters)))
		Log::Error(__FUNCTION__,"Reset");
}

void Direct3D9::ClearBeginScene(const Color& clear_color) const
{
	const int r = static_cast<int>(clear_color.GetRed() * 255);
	const int g = static_cast<int>(clear_color.GetGreen() * 255);
	const int b = static_cast<int>(clear_color.GetBlue() * 255);
	const int a = static_cast<int>(clear_color.GetAlpha() * 255);

	if (FAILED(this->direct3d_device->Clear(0,nullptr,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,D3DCOLOR_RGBA(r,g,b,a),1.0f,0)))
		Log::Error(__FUNCTION__,"Clear");

	if (FAILED(this->direct3d_device->BeginScene()))
		Log::Error(__FUNCTION__,"BeginScene");
}

void Direct3D9::DrawIndexedPrimitive(const D3DPRIMITIVETYPE mode,const UINT vertex_total,const UINT start_index,const UINT primitive_count) const
{
	if (FAILED(this->direct3d_device->DrawIndexedPrimitive(mode,0,0,vertex_total,start_index,primitive_count)))
		Log::Error(__FUNCTION__,"DrawIndexedPrimitive");
}

void Direct3D9::EndRender() const
{
	if (FAILED(this->direct3d_device->EndScene()))
		Log::Error(__FUNCTION__,"EndScene");
}

void Direct3D9::Present() const
{
	if (FAILED(this->direct3d_device->Present(nullptr,nullptr,nullptr,nullptr)))
		Log::Error(__FUNCTION__,"Present");
}

D3DFORMAT Direct3D9::BackBufferFormat(const VideoMode& video_mode)
{
	return (video_mode.GetBPP() == BitsPerPixel::ColorDepth32Bits) ? D3DFMT_X8R8G8B8 : (video_mode.GetBPP() == BitsPerPixel::ColorDepth16Bits) ? D3DFMT_R5G6B5 : D3DFMT_UNKNOWN;
}

int Direct3D9::ColorDepth(const D3DFORMAT format)
{
	return (format == D3DFMT_X8R8G8B8) ? 32 : (format == D3DFMT_R5G6B5) ? 16 : D3DFMT_UNKNOWN;
}

UINT Direct3D9::VSync(const VideoMode& video_mode)
{
	return (video_mode.GetVSync()) ? D3DPRESENT_INTERVAL_ONE : D3DPRESENT_INTERVAL_IMMEDIATE;
}
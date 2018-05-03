#include "VideoDirect3D9.h"

using namespace std;
using namespace GPL;

VideoDirect3D9::~VideoDirect3D9()
{
	this->DeactivateProperties();
}

void VideoDirect3D9::DesktopResolutionUpdate()
{
	this->SetDesktopResolution(GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN));
}

void VideoDirect3D9::CreateVideo(Application& application,const VideoMode& video_mode)
{
	this->SetVirtualResolution(video_mode.GetWidth(),video_mode.GetHeight());
	this->DesktopResolutionUpdate();

	this->direct3d.CreateDirect3D(static_cast<ApplicationWin32&>(application).GetHandleWindow(),video_mode);

	this->ChangeSettings(application,video_mode);

	const D3DVERTEXELEMENT9 declaration_pos2d_col[] =
	{
		{0,0,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0},
		{0,8,D3DDECLTYPE_FLOAT4,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_COLOR,0},
		D3DDECL_END()
	};

	const D3DVERTEXELEMENT9 declaration_pos2d_col_tex[] =
	{
		{0,0,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0},
		{0,8,D3DDECLTYPE_FLOAT4,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_COLOR,0},
		{0,24,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,0},
		D3DDECL_END()
	};

	const D3DVERTEXELEMENT9 declaration_pos3d_col[] =
	{
		{0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0},
		{0,12,D3DDECLTYPE_FLOAT4,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_COLOR,0},
		D3DDECL_END()
	};

	const D3DVERTEXELEMENT9 declaration_pos3d_col_tex[] =
	{
		{0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0},
		{0,12,D3DDECLTYPE_FLOAT4,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_COLOR,0},
		{0,28,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,0},
		D3DDECL_END()
	};

	this->vertex_declaration_pos2d_col.CreateVertexDeclaration(this->direct3d.GetDevice(),*declaration_pos2d_col);
	this->vertex_declaration_pos2d_col_tex.CreateVertexDeclaration(this->direct3d.GetDevice(),*declaration_pos2d_col_tex);
	this->vertex_declaration_pos3d_col.CreateVertexDeclaration(this->direct3d.GetDevice(),*declaration_pos3d_col);
	this->vertex_declaration_pos3d_col_tex.CreateVertexDeclaration(this->direct3d.GetDevice(),*declaration_pos3d_col_tex);

	this->index_buffer_static.CreateIndexBuffer(this->direct3d.GetDevice(),this->index_buffer_static_size * sizeof(short),false);

	this->index_buffer_static.Lock();

	//Gravar dados em sequência
	for (UINT i = 0; i < this->index_buffer_static_size; i++)
		IndexBufferDirect3D9::AddIndexData(i);

	this->index_buffer_static.Unlock();
}

const Texture& VideoDirect3D9::GetTexture(const string& texture_id) const
{
	return *this->textures.GetResource(texture_id);
}

const Texture& VideoDirect3D9::GetTexture(const int texture_id) const
{
	return *this->textures.GetResource(Convert::NumberToString(texture_id));
}

const Font& VideoDirect3D9::GetFont(const string& font_id) const
{
	return *this->fonts.GetResource(font_id);
}

const Font& VideoDirect3D9::GetFont(const int font_id) const
{
	return *this->fonts.GetResource(Convert::NumberToString(font_id));
}

string VideoDirect3D9::GetDeviceDisplayName() const
{
	return this->direct3d.GetDeviceDisplayName();
}

vector<string> VideoDirect3D9::GetSupportedResolutions(const VideoMode& video_mode) const
{
	return this->direct3d.GetSupportedResolutions(video_mode);
}

void VideoDirect3D9::LoadTextureBase(const bool resource_from_file,const string& file_name,const int texture_id,const Color& color_key)
{
	const string correct_texture_id(resource_from_file ? file_name : Convert::NumberToString(texture_id));

	unique_ptr<TextureDirect3D9>& texture = this->textures.AddResource(correct_texture_id,resource_from_file);

	texture = make_unique<TextureDirect3D9>();

	if (resource_from_file)
		texture->LoadTexture(this->direct3d.GetDevice(),file_name,color_key);
	else
		texture->LoadTexture(this->direct3d.GetDevice(),texture_id,color_key);
}

void VideoDirect3D9::LoadTexture(const string& file_name,const Color& color_key)
{
	this->LoadTextureBase(true,file_name,-1,color_key);
}

void VideoDirect3D9::LoadTexture(const int texture_id,const Color& color_key)
{
	this->LoadTextureBase(false,"",texture_id,color_key);
}

void VideoDirect3D9::UnloadTexture(const string& file_name)
{
	this->textures.RemoveResource(file_name);
}

void VideoDirect3D9::UnloadTexture(const int texture_id)
{
	this->textures.RemoveResource(Convert::NumberToString(texture_id));
}

void VideoDirect3D9::LoadFontBase(const bool resource_from_file,const string& file_name,const int font_id,const int size,const FT_ULong first_character,const FT_ULong last_character,const float outline)
{
	const string correct_font_id(resource_from_file ? file_name : Convert::NumberToString(font_id));

	unique_ptr<FontDirect3D9>& font = this->fonts.AddResource(correct_font_id,resource_from_file);

	font = make_unique<FontDirect3D9>();

	unique_ptr<TextureDirect3D9>& texture = this->textures.AddResource(correct_font_id,resource_from_file);

	texture = make_unique<TextureDirect3D9>();

	font->SetTexture(*texture);

	if (resource_from_file)
		font->LoadFont(this->direct3d.GetDevice(),file_name,size,first_character,last_character,outline);
	else
		font->LoadFont(this->direct3d.GetDevice(),font_id,size,first_character,last_character,outline);
}

void VideoDirect3D9::LoadFont(const string& file_name,const int size,const FT_ULong first_character,const FT_ULong last_character,const float outline)
{
	this->LoadFontBase(true,file_name,-1,size,first_character,last_character,outline);
}

void VideoDirect3D9::LoadFont(const int font_id,const int size,const FT_ULong first_character,const FT_ULong last_character,const float outline)
{
	this->LoadFontBase(false,"",font_id,size,first_character,last_character,outline);
}

void VideoDirect3D9::LoadVertexShader(const string& file_name)
{
	this->vertex_shader_basic.CreateVertexShader(this->direct3d.GetDevice(),this->GetShaderMainBasic(),file_name);
	this->vertex_shader_texture.CreateVertexShader(this->direct3d.GetDevice(),this->GetShaderMainTexture(),file_name);
}

void VideoDirect3D9::LoadVertexShader(const int vertex_shader_id)
{
	this->vertex_shader_basic.CreateVertexShader(this->direct3d.GetDevice(),this->GetShaderMainBasic(),vertex_shader_id);
	this->vertex_shader_texture.CreateVertexShader(this->direct3d.GetDevice(),this->GetShaderMainTexture(),vertex_shader_id);
}

void VideoDirect3D9::LoadPixelShader(const string& file_name)
{
	this->pixel_shader_basic.CreatePixelShader(this->direct3d.GetDevice(),this->GetShaderMainBasic(),file_name);
	this->pixel_shader_texture.CreatePixelShader(this->direct3d.GetDevice(),this->GetShaderMainTexture(),file_name);
}

void VideoDirect3D9::LoadPixelShader(const int pixel_shader_id)
{
	this->pixel_shader_basic.CreatePixelShader(this->direct3d.GetDevice(),this->GetShaderMainBasic(),pixel_shader_id);
	this->pixel_shader_texture.CreatePixelShader(this->direct3d.GetDevice(),this->GetShaderMainTexture(),pixel_shader_id);
}

void VideoDirect3D9::CreateRenderTarget(const int width,const int height,const Color& clear_color)
{
	this->GetRenderTargets().push_back(make_unique<RenderTargetDirect3D9>());
	static_cast<RenderTargetDirect3D9&>(*this->GetRenderTargets().back()).CreateTextureRenderTarget(this->direct3d.GetDevice(),width,height,clear_color);
}

bool VideoDirect3D9::ChangeSettings(Application& application,const VideoMode& video_mode)
{
	//Verificando se não é a mesma configuração antes de alterar
	static bool first_time_change = true;
	if ((this->GetVideoMode() != video_mode) || (first_time_change))
	{
		//Passando de Windowed para Fullscreen
		if ((!first_time_change) && (this->GetVideoMode().GetWindowed()) && (!video_mode.GetWindowed()))
			this->DesktopResolutionUpdate();

		//Verificando se a resolução é suportada
		if (this->direct3d.CheckDisplayMode(video_mode))
		{
			//Atualizando o Video Mode
			this->SetVideoMode(video_mode);

			//Alterando o estilo e tamanho da janela da aplicação
			application.ChangeApplicationSettings(video_mode.GetWidth(),video_mode.GetHeight(),video_mode.GetWindowed(),this->GetVirtualWidth(),this->GetVirtualHeight());

			//Liberando e recriando todos os recursos para aplicar as alterações de video
			if (!first_time_change)
			{
				//Alterar apenas o que for necessário
				this->direct3d.SetPresentParameters(video_mode);

				//Liberando os recursos
				this->OnLostDevice();

				//Resetando as configurações
				this->direct3d.ResetDevice();
			}

			//Recriando os recursos
			this->OnResetDevice();
			first_time_change = false;
			return true;
		}
		else
		{
			const string message(Convert::NumberToString(video_mode.GetWidth()) + "x" +
								 Convert::NumberToString(video_mode.GetHeight()) + "x" +
								 Convert::NumberToString(static_cast<int>(video_mode.GetBPP())) +
								 " is not supported!");

			if (first_time_change)
				Log::Error(message);
			else
				Log::Warning("Resolution not supported! " + message);
		}
	}
	return false;
}

void VideoDirect3D9::DeactivateProperties() const
{
	TextureDirect3D9::DeactivateTexture(this->direct3d.GetDevice());
	VertexShaderDirect3D9::DeactivateVertexShader(this->direct3d.GetDevice());
	PixelShaderDirect3D9::DeactivatePixelShader(this->direct3d.GetDevice());
	IndexBufferDirect3D9::DeactivateIndexBuffer(this->direct3d.GetDevice());
	VertexBufferDirect3D9::DeactivateVertexBuffer(this->direct3d.GetDevice());
}

void VideoDirect3D9::OnLostDevice()
{
	this->DeactivateProperties();

	this->vertex_buffer_dynamic.DeleteVertexBuffer();
	this->index_buffer_dynamic.DeleteIndexBuffer();

	if (this->GetPointerRenderTargetBackBuffer().get())
		this->GetPointerRenderTargetBackBuffer()->Clear();

	for (const auto& iterator : this->GetRenderTargets())
		iterator->Clear();
}

void VideoDirect3D9::OnResetDevice()
{
	this->direct3d.SetRenderState(D3DRS_LIGHTING,false);
	this->direct3d.SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	this->direct3d.SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	this->direct3d.SetSamplerState(D3DSAMP_ADDRESSU,D3DTADDRESS_CLAMP);
	this->direct3d.SetSamplerState(D3DSAMP_ADDRESSV,D3DTADDRESS_CLAMP);

	const int back_buffer_width = this->GetVideoMode().GetWidth();
	const int back_buffer_height = this->GetVideoMode().GetHeight();

	if (!this->GetPointerRenderTargetBackBuffer().get())
		this->GetPointerRenderTargetBackBuffer() = make_unique<RenderTargetDirect3D9>();

	static_cast<RenderTargetDirect3D9&>(*this->GetPointerRenderTargetBackBuffer().get()).RenderTargetFromBackBuffer(this->direct3d.GetDevice(),back_buffer_width,back_buffer_height,this->GetBackBufferClearColor());

	for (const auto& iterator : this->GetRenderTargets())
	{
		RenderTargetDirect3D9& converted_iterator = static_cast<RenderTargetDirect3D9&>(*iterator);

		converted_iterator.CreateTextureRenderTarget(this->direct3d.GetDevice(),converted_iterator.GetWidth(),converted_iterator.GetHeight(),converted_iterator.GetClearColor());
	}
}

void VideoDirect3D9::TextureFilterUpdate() const
{
	const D3DTEXTUREFILTERTYPE texture_filter_type = (this->GetTextureFilter() == TextureFilter::Linear) ? D3DTEXF_LINEAR : D3DTEXF_POINT;

	this->direct3d.SetSamplerState(D3DSAMP_MINFILTER,texture_filter_type);
	this->direct3d.SetSamplerState(D3DSAMP_MAGFILTER,texture_filter_type);
}

void VideoDirect3D9::BufferDynamicUpdate()
{
	UINT new_index_buffer_dynamic_size = 0;
	UINT new_vertex_buffer_dynamic_size = 0;

	for (const auto& iterator : this->GetModelsOrthographicProjection())
		this->CalculateBufferDynamicSize(*iterator,new_index_buffer_dynamic_size,new_vertex_buffer_dynamic_size);

	for (const auto& iterator : this->GetModelsPerspectiveProjection())
		this->CalculateBufferDynamicSize(*iterator,new_index_buffer_dynamic_size,new_vertex_buffer_dynamic_size);

	//Valor final precisa de 2 bytes ou 16 bits para cada índice
	new_index_buffer_dynamic_size *= sizeof(short);

	this->index_buffer_dynamic.CreateIndexBuffer(this->direct3d.GetDevice(),new_index_buffer_dynamic_size,true);
	this->vertex_buffer_dynamic.CreateVertexBuffer(this->direct3d.GetDevice(),new_vertex_buffer_dynamic_size,true);

	const bool use_index_buffer_dynamic = (this->index_buffer_dynamic.GetSize() > 0);
	const bool use_vertex_buffer_dynamic = (this->vertex_buffer_dynamic.GetSize() > 0);

	if (use_index_buffer_dynamic)
		this->index_buffer_dynamic.Lock();

	if (use_vertex_buffer_dynamic)
		this->vertex_buffer_dynamic.Lock();

	for (const auto& iterator : this->GetRenderTargets())
		this->AddBufferDynamicDataByRenderTarget(*iterator);

	this->AddBufferDynamicDataByRenderTarget(this->GetRenderTargetBackBuffer());

	if (use_vertex_buffer_dynamic)
		this->vertex_buffer_dynamic.Unlock();

	if (use_index_buffer_dynamic)
		this->index_buffer_dynamic.Unlock();

	this->index_buffer_dynamic.ResetStartIndex();
	this->vertex_buffer_dynamic.ResetOffsetInBytes();
}

void VideoDirect3D9::CalculateBufferDynamicSize(const Model& model,UINT& new_index_buffer_dynamic_size,UINT& new_vertex_buffer_dynamic_size) const
{
	//Index
	if (!model.IsIndicesSequenced(this->index_buffer_static_size))
		new_index_buffer_dynamic_size += model.GetIndices().size();

	//Vertex
	UINT size = model.GetVertexTotal();
	if (!model.Is3D())
	{
		if (model.IsTextured())
			size *= sizeof(VertexPos2DColTex);
		else
			size *= sizeof(VertexPos2DCol);
	}
	else
	{
		if (model.IsTextured())
			size *= sizeof(VertexPos3DColTex);
		else
			size *= sizeof(VertexPos3DCol);
	}
	new_vertex_buffer_dynamic_size += size;
}

void VideoDirect3D9::AddBufferDynamicDataByRenderTarget(const RenderTarget& render_target) const
{
	for (const auto& iterator : this->GetModelsPerspectiveProjection())
		this->AddBufferDynamicData(render_target,*iterator);

	for (const auto& iterator : this->GetModelsOrthographicProjection())
		this->AddBufferDynamicData(render_target,*iterator);
}

void VideoDirect3D9::AddBufferDynamicData(const RenderTarget& render_target,const Model& model) const
{
	if (&model.GetRenderTarget() == &render_target)
	{
		const bool use_index_buffer_dynamic = (this->index_buffer_dynamic.GetSize() > 0);
		const bool use_vertex_buffer_dynamic = (this->vertex_buffer_dynamic.GetSize() > 0);

		//Index
		if (use_index_buffer_dynamic)
		{
			if (!model.IsIndicesSequenced(this->index_buffer_static_size))
			{
				for (const auto& iterator : model.GetIndices())
					IndexBufferDirect3D9::AddIndexData(iterator);
			}
		}

		//Vertex
		if (use_vertex_buffer_dynamic)
		{
			const bool is_3d = model.Is3D();

			for (size_t i = 0; i < model.GetVertexTotal(); i++)
			{
				//Position
				const Point3D<float>& position = model.GetVertexPosition(i);

				//X
				VertexBufferDirect3D9::AddVertexData((!is_3d) ? VideoDirect3D9::AlignPixel(position.GetX()) : position.GetX());

				//Y
				VertexBufferDirect3D9::AddVertexData((!is_3d) ? VideoDirect3D9::AlignPixel(position.GetY()) : position.GetY());

				//Z
				if (is_3d)
					VertexBufferDirect3D9::AddVertexData(position.GetZ());

				//Color
				const Color& color = model.GetVertexColor(i);

				//Red
				VertexBufferDirect3D9::AddVertexData(color.GetRed());

				//Green
				VertexBufferDirect3D9::AddVertexData(color.GetGreen());

				//Blue
				VertexBufferDirect3D9::AddVertexData(color.GetBlue());

				//Alpha
				VertexBufferDirect3D9::AddVertexData(color.GetAlpha());

				//Texture Coordinate
				if (model.IsTextured())
				{
					const Point2D<float>& texture_coordinate = model.GetVertexTextureCoordinate(i);

					//U
					VertexBufferDirect3D9::AddVertexData(texture_coordinate.GetX());

					//V
					VertexBufferDirect3D9::AddVertexData(texture_coordinate.GetY());
				}
			}
		}
	}
}

void VideoDirect3D9::RenderModelsOrthographicProjection(const RenderTarget& render_target)
{
	if (!this->GetModelsOrthographicProjection().empty())
	{
		this->direct3d.OrthographicProjection(static_cast<float>(this->GetVirtualWidth()),static_cast<float>(this->GetVirtualHeight()),this->GetOrthographicNearZ(),this->GetOrthographicFarZ());

		//Com Alpha Blend e sem operações com Z
		this->direct3d.SetRenderState(D3DRS_ALPHABLENDENABLE,true);
		this->direct3d.SetRenderState(D3DRS_ZENABLE,false);
		this->direct3d.SetRenderState(D3DRS_ZWRITEENABLE,false);

		for (const auto& iterator : this->GetModelsOrthographicProjection())
			this->RenderModel(render_target,*iterator);
	}
}

void VideoDirect3D9::RenderModelsPerspectiveProjection(const RenderTarget& render_target)
{
	if (!this->GetModelsPerspectiveProjection().empty())
	{
		this->direct3d.PerspectiveProjection(static_cast<float>(this->GetVirtualWidth()),static_cast<float>(this->GetVirtualHeight()),this->GetPerspectiveFoV());

		//Renderização baseada no Painter’s Algorithm
		//http://blogs.msdn.com/b/shawnhar/archive/2009/02/18/depth-sorting-alpha-blended-objects.aspx

		//Rendererizar todos os objetos opacos, sem transparência e com uso do Z Buffer
		this->direct3d.SetRenderState(D3DRS_ZENABLE,true);
		this->direct3d.SetRenderState(D3DRS_ALPHABLENDENABLE,false);
		this->direct3d.SetRenderState(D3DRS_ZWRITEENABLE,true);
		for (const auto& iterator : this->GetModelsPerspectiveProjection())
		{
			if (iterator->IsOpaque())
				this->RenderModel(render_target,*iterator);
		}

		//Renderizar todos os objetos transparente, com transparência habilitada mas sem escrever no Z Buffer
		this->direct3d.SetRenderState(D3DRS_ALPHABLENDENABLE,true);
		this->direct3d.SetRenderState(D3DRS_ZWRITEENABLE,false);
		for (const auto& iterator : this->GetModelsPerspectiveProjection())
		{
			if (!iterator->IsOpaque())
				this->RenderModel(render_target,*iterator);
		}
	}
}

void VideoDirect3D9::SetViewport(const RenderTarget& render_target,const Model& model) const
{
	const Rect<int> viewport_aspect_ratio = this->AspectRatioUpdate(render_target,model);

	const Point2D<int>& position = viewport_aspect_ratio.GetPosition();
	const Point2D<int>& size = viewport_aspect_ratio.GetSize();

	this->direct3d.SetViewport(position.GetX(),position.GetY(),size.GetX(),size.GetY());
}

void VideoDirect3D9::SetTexture(const Model& model) const
{
	if (model.IsTextured())
	{
		const TextureDirect3D9& texture = static_cast<const TextureDirect3D9&>(model.GetTexture());

		texture.ActivateTexture(this->direct3d.GetDevice());
	}
}

void VideoDirect3D9::SetVertexShader(const Model& model) const
{
	const VertexShaderDirect3D9& vertex_shader = (model.IsTextured()) ? this->vertex_shader_texture : this->vertex_shader_basic;

	vertex_shader.ActivateVertexShader(this->direct3d.GetDevice());

	vertex_shader.SetVertexShaderConstantF(this->direct3d.GetDevice(),VertexShaderConstantRegister::WorldViewProjection,this->direct3d.ProcessMatrix(model));
}

void VideoDirect3D9::SetPixelShader(const Model& model) const
{
	const PixelShaderDirect3D9& pixel_shader = (model.IsTextured()) ? this->pixel_shader_texture : this->pixel_shader_basic;

	pixel_shader.ActivatePixelShader(this->direct3d.GetDevice());

	pixel_shader.SetPixelShaderConstantF(this->direct3d.GetDevice(),PixelShaderConstantRegister::InvertColor,model.GetInvertColor() ? 1.0f : 0.0f);
	pixel_shader.SetPixelShaderConstantF(this->direct3d.GetDevice(),PixelShaderConstantRegister::GrayScale,model.GetGrayScale() ? 1.0f : 0.0f);

	if (model.IsTextured())
	{
		pixel_shader.SetPixelShaderConstantF(this->direct3d.GetDevice(),PixelShaderConstantRegister::TurnHorizontal,model.GetTextureCoordinateInverted().GetX());
		pixel_shader.SetPixelShaderConstantF(this->direct3d.GetDevice(),PixelShaderConstantRegister::TurnVertical,model.GetTextureCoordinateInverted().GetY());
		pixel_shader.SetPixelShaderConstantF(this->direct3d.GetDevice(),PixelShaderConstantRegister::PixelateGridSize,model.GetPixelateGridSize());
	}
}

IndexBufferDirect3D9& VideoDirect3D9::SetIndexBuffer(const Model& model)
{
	this->index_buffer_static.ResetStartIndex();

	IndexBufferDirect3D9& index_buffer = (model.IsIndicesSequenced(this->index_buffer_static_size)) ? this->index_buffer_static : this->index_buffer_dynamic;

	index_buffer.ActivateIndexBuffer(this->direct3d.GetDevice());

	return index_buffer;
}

UINT VideoDirect3D9::SetVertexDeclaration(const Model& model) const
{
	UINT stride;
	const VertexDeclarationDirect3D9* vertex_declaration{};
	if (!model.Is3D())
	{
		if (model.IsTextured())
		{
			stride = sizeof(VideoDirect3D9::VertexPos2DColTex);
			vertex_declaration = &this->vertex_declaration_pos2d_col_tex;
		}
		else
		{
			stride = sizeof(VideoDirect3D9::VertexPos2DCol);
			vertex_declaration = &this->vertex_declaration_pos2d_col;
		}
	}
	else
	{
		if (model.IsTextured())
		{
			stride = sizeof(VideoDirect3D9::VertexPos3DColTex);
			vertex_declaration = &this->vertex_declaration_pos3d_col_tex;
		}
		else
		{
			stride = sizeof(VideoDirect3D9::VertexPos3DCol);
			vertex_declaration = &this->vertex_declaration_pos3d_col;
		}
	}
	vertex_declaration->ActivateVertexDeclaration(this->direct3d.GetDevice());
	return stride;
}

void VideoDirect3D9::SetVertexBuffer(const Model& model,const UINT stride)
{
	VertexBufferDirect3D9& vertex_buffer = this->vertex_buffer_dynamic;

	vertex_buffer.ActivateVertexBuffer(this->direct3d.GetDevice(),stride);
	vertex_buffer.IncrementOffsetInBytes(stride * model.GetVertexTotal());
}

D3DPRIMITIVETYPE VideoDirect3D9::GetPrimitiveType(const Model& model) const
{
	if (model.GetPrimitiveType() == PrimitiveType::TriangleStrip)
		return D3DPT_TRIANGLESTRIP;

	else if (model.GetPrimitiveType() == PrimitiveType::TriangleList)
		return D3DPT_TRIANGLELIST;

	else if (model.GetPrimitiveType() == PrimitiveType::LineStrip)
		return D3DPT_LINESTRIP;

	return D3DPT_POINTLIST;
}

void VideoDirect3D9::RenderModel(const RenderTarget& render_target,const Model& model)
{
	if (&model.GetRenderTarget() == &render_target)
	{
		this->SetViewport(render_target,model);

		this->SetTexture(model);

		this->SetVertexShader(model);

		this->SetPixelShader(model);

		IndexBufferDirect3D9& index_buffer = this->SetIndexBuffer(model);

		const UINT stride = this->SetVertexDeclaration(model);

		this->SetVertexBuffer(model,stride);

		const D3DPRIMITIVETYPE mode = this->GetPrimitiveType(model);

		this->direct3d.DrawIndexedPrimitive(mode,model.GetVertexTotal(),index_buffer.GetStartIndex(),model.GetPrimitiveCount());

		index_buffer.IncrementStartIndex(model.GetIndices().size());
	}
}

void VideoDirect3D9::RenderToRenderTarget(const RenderTarget& render_target)
{
	static_cast<const RenderTargetDirect3D9&>(render_target).ActivateRenderTarget(this->direct3d.GetDevice());

	this->direct3d.ClearBeginScene(render_target.GetClearColor());

	this->RenderModelsPerspectiveProjection(render_target);

	this->RenderModelsOrthographicProjection(render_target);

	this->direct3d.EndRender();
}

void VideoDirect3D9::ProcessRender()
{
	this->SortModelsPerspectiveProjection();

	this->TextureFilterUpdate();

	this->BufferDynamicUpdate();

	for (const auto& iterator : this->GetRenderTargets())
		this->RenderToRenderTarget(*iterator);

	this->RenderToRenderTarget(this->GetRenderTargetBackBuffer());

	this->direct3d.Present();

	this->ClearModels();
}

HRESULT VideoDirect3D9::HandleDeviceState()
{
	const HRESULT state = this->direct3d.GetDeviceState();

	if (FAILED(state))
	{
		if (state == D3DERR_DEVICENOTRESET)
		{
			this->OnLostDevice();
			this->direct3d.ResetDevice();
			this->OnResetDevice();
		}

		else if (state == D3DERR_DRIVERINTERNALERROR)
			Log::Error(__FUNCTION__,"GetDeviceState","D3DERR_DRIVERINTERNALERROR");
	}

	return state;
}

void VideoDirect3D9::Render()
{
	if (SUCCEEDED(this->HandleDeviceState()))
		this->ProcessRender();
}

float VideoDirect3D9::AlignPixel(const float unaligned_pixel)
{
	//http://msdn.microsoft.com/en-us/library/windows/desktop/bb219690%28v=vs.85%29.aspx
	return ((unaligned_pixel - static_cast<int>(unaligned_pixel) == 0.0f) ? (unaligned_pixel - 0.5f) : unaligned_pixel);
}
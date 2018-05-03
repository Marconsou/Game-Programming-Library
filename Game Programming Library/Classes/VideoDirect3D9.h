#ifndef VIDEODIRECT3D9_H
#define VIDEODIRECT3D9_H

#include "ResourceManager.h"
#include "FontDirect3D9.h"
#include "Video.h"
#include "ApplicationWin32.h"
#include "Direct3D9.h"
#include "IndexBufferDirect3D9.h"
#include "VertexBufferDirect3D9.h"
#include "VertexDeclarationDirect3D9.h"
#include "VertexShaderDirect3D9.h"
#include "PixelShaderDirect3D9.h"
#include "RenderTargetDirect3D9.h"

namespace GPL
{
	class VideoDirect3D9 : public Video
	{
	public:
		GPL_DLL ~VideoDirect3D9();
		GPL_DLL void CreateVideo(Application& application,const VideoMode& video_mode) override;
		GPL_DLL const Texture& GetTexture(const std::string& texture_id) const override;
		GPL_DLL const Texture& GetTexture(const int texture_id) const override;
		GPL_DLL const Font& GetFont(const std::string& font_id) const override;
		GPL_DLL const Font& GetFont(const int font_id) const override;
		GPL_DLL std::string GetDeviceDisplayName() const override;
		GPL_DLL std::vector<std::string> GetSupportedResolutions(const VideoMode& video_mode) const override;
		GPL_DLL void LoadTexture(const std::string& file_name,const Color& color_key) override;
		GPL_DLL void LoadTexture(const int texture_id,const Color& color_key) override;
		GPL_DLL void UnloadTexture(const std::string& file_name) override;
		GPL_DLL void UnloadTexture(const int texture_id) override;
		GPL_DLL void LoadFont(const std::string& file_name,const int size,const FT_ULong first_character,const FT_ULong last_character,const float outline) override;
		GPL_DLL void LoadFont(const int font_id,const int size,const FT_ULong first_character,const FT_ULong last_character,const float outline) override;
		GPL_DLL void LoadVertexShader(const std::string& file_name) override;
		GPL_DLL void LoadVertexShader(const int vertex_shader_id) override;
		GPL_DLL void LoadPixelShader(const std::string& file_name) override;
		GPL_DLL void LoadPixelShader(const int pixel_shader_id) override;
		GPL_DLL void CreateRenderTarget(const int width,const int height,const Color& clear_color) override;
		GPL_DLL bool ChangeSettings(Application& application,const VideoMode& video_mode) override;
		GPL_DLL void Render() override;
	private:
		struct VertexPos2DCol
		{
			XMFLOAT2 position;
			XMFLOAT4 color;
		};

		struct VertexPos2DColTex : public VertexPos2DCol
		{
			XMFLOAT2 textcoord;
		};

		struct VertexPos3DCol
		{
			XMFLOAT3 position;
			XMFLOAT4 color;
		};

		struct VertexPos3DColTex : public VertexPos3DCol
		{
			XMFLOAT2 textcoord;
		};

		const UINT index_buffer_static_size{1000};
		Direct3D9 direct3d;
		IndexBufferDirect3D9 index_buffer_static;
		IndexBufferDirect3D9 index_buffer_dynamic;
		VertexBufferDirect3D9 vertex_buffer_dynamic;
		VertexDeclarationDirect3D9 vertex_declaration_pos2d_col;
		VertexDeclarationDirect3D9 vertex_declaration_pos2d_col_tex;
		VertexDeclarationDirect3D9 vertex_declaration_pos3d_col;
		VertexDeclarationDirect3D9 vertex_declaration_pos3d_col_tex;
		VertexShaderDirect3D9 vertex_shader_basic;
		VertexShaderDirect3D9 vertex_shader_texture;
		PixelShaderDirect3D9 pixel_shader_basic;
		PixelShaderDirect3D9 pixel_shader_texture;
		ResourceManager<std::unique_ptr<TextureDirect3D9>> textures;
		ResourceManager<std::unique_ptr<FontDirect3D9>> fonts;
		void DesktopResolutionUpdate();
		void LoadTextureBase(const bool resource_from_file,const std::string& file_name,const int texture_id,const Color& color_key);
		void LoadFontBase(const bool resource_from_file,const std::string& file_name,const int font_id,const int size,const FT_ULong first_character,const FT_ULong last_character,const float outline);
		void DeactivateProperties() const;
		void OnLostDevice();
		void OnResetDevice();
		void TextureFilterUpdate() const;
		void BufferDynamicUpdate();
		void CalculateBufferDynamicSize(const Model& model,UINT& new_index_buffer_dynamic_size,UINT& new_vertex_buffer_dynamic_size) const;
		void AddBufferDynamicDataByRenderTarget(const RenderTarget& render_target) const;
		void AddBufferDynamicData(const RenderTarget& render_target,const Model& model) const;
		void RenderModelsOrthographicProjection(const RenderTarget& render_target);
		void RenderModelsPerspectiveProjection(const RenderTarget& render_target);
		void SetViewport(const RenderTarget& render_target,const Model& model) const;
		void SetTexture(const Model& model) const;
		void SetVertexShader(const Model& model) const;
		void SetPixelShader(const Model& model) const;
		IndexBufferDirect3D9& SetIndexBuffer(const Model& model);
		UINT SetVertexDeclaration(const Model& model) const;
		void SetVertexBuffer(const Model& model,const UINT stride);
		D3DPRIMITIVETYPE GetPrimitiveType(const Model& model) const;
		void RenderModel(const RenderTarget& render_target,const Model& model);
		void RenderToRenderTarget(const RenderTarget& render_target);
		void ProcessRender();
		HRESULT HandleDeviceState();
		static float AlignPixel(const float unaligned_pixel);
	};
}

#endif
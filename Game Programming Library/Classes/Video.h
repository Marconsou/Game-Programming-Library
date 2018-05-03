#ifndef VIDEO_H
#define VIDEO_H

#include "VideoMode.h"
#include "View.h"
#include "Application.h"
#include "RenderTarget.h"
#include "Model.h"
#include "Font.h"

namespace GPL
{
	enum class TextureFilter
	{
		Point,
		Linear,
	};

	enum class AspectRatio
	{
		None,
		Normal4x3,
		Widescreen16x9,
		Widescreen16x10,
	};

	class Video
	{
	public:
		GPL_DLL Video();
		GPL_DLL virtual ~Video() = 0 {};
		GPL_DLL void SetOrthographicZ(const float orthographic_near_z,const float orthographic_far_z);
		GPL_DLL int GetVirtualWidth() const;
		GPL_DLL int GetVirtualHeight() const;
		GPL_DLL const VideoMode& GetVideoMode() const;
		GPL_DLL void SetTextureFilter(const TextureFilter texture_filter);
		GPL_DLL TextureFilter GetTextureFilter() const;
		GPL_DLL void SetAspectRatio(const AspectRatio aspect_ratio);
		GPL_DLL AspectRatio GetAspectRatio() const;
		GPL_DLL void SetBackBufferClearColor(const Color& back_buffer_clear_color);
		GPL_DLL const Color& GetBackBufferClearColor() const;
		GPL_DLL const RenderTarget& GetRenderTargetBackBuffer() const;
		GPL_DLL const RenderTarget& GetRenderTarget(const size_t index) const;
		GPL_DLL const RenderTarget& GetLastRenderTarget() const;
		GPL_DLL void RemoveRenderTarget(const size_t index);
		GPL_DLL void RemoveLastRenderTarget();
		GPL_DLL float LimitX(const float x,const float w,const float change_x = 0.0f) const;
		GPL_DLL float LimitY(const float y,const float h,const float change_y = 0.0f) const;
		GPL_DLL void Draw(Model& model);
		GPL_DLL virtual void CreateVideo(Application& application,const VideoMode& video_mode) = 0;
		GPL_DLL virtual const Texture& GetTexture(const std::string& texture_id) const = 0;
		GPL_DLL virtual const Texture& GetTexture(const int texture_id) const = 0;
		GPL_DLL virtual const Font& GetFont(const std::string& font_id) const = 0;
		GPL_DLL virtual const Font& GetFont(const int font_id) const = 0;
		GPL_DLL virtual std::string GetDeviceDisplayName() const = 0;
		GPL_DLL virtual std::vector<std::string> GetSupportedResolutions(const VideoMode& video_mode) const = 0;
		GPL_DLL virtual void LoadTexture(const std::string& file_name,const Color& color_key = Color::Null) = 0;
		GPL_DLL virtual void LoadTexture(const int texture_id,const Color& color_key = Color::Null) = 0;
		GPL_DLL virtual void UnloadTexture(const std::string& file_name) = 0;
		GPL_DLL virtual void UnloadTexture(const int texture_id) = 0;
		GPL_DLL virtual void LoadFont(const std::string& file_name,const int size,const FT_ULong first_character = ' ',const FT_ULong last_character = '~',const float outline = 1.0f) = 0;
		GPL_DLL virtual void LoadFont(const int font_id,const int size,const FT_ULong first_character = ' ',const FT_ULong last_character = '~',const float outline = 1.0f) = 0;
		GPL_DLL virtual void LoadVertexShader(const std::string& file_name) = 0;
		GPL_DLL virtual void LoadVertexShader(const int vertex_shader_id) = 0;
		GPL_DLL virtual void LoadPixelShader(const std::string& file_name) = 0;
		GPL_DLL virtual void LoadPixelShader(const int pixel_shader_id) = 0;
		GPL_DLL virtual void CreateRenderTarget(const int width,const int height,const Color& clear_color = Color::Transparent) = 0;
		GPL_DLL virtual bool ChangeSettings(Application& application,const VideoMode& video_mode) = 0;
		GPL_DLL virtual void Render() = 0;
	protected:
		float GetOrthographicNearZ() const;
		float GetOrthographicFarZ() const;
		float GetPerspectiveFoV() const;
		const std::string& GetShaderMainBasic() const;
		const std::string& GetShaderMainTexture() const;
		void SetVirtualResolution(const int virtual_width,const int virtual_height);
		void SetDesktopResolution(const int desktop_width,const int desktop_height);
		void SetVideoMode(const VideoMode& video_mode);
		std::unique_ptr<RenderTarget>& GetPointerRenderTargetBackBuffer();
		std::vector<std::unique_ptr<RenderTarget>>& GetRenderTargets();
		const std::vector<const Model*>& GetModelsOrthographicProjection() const;
		const std::vector<const Model*>& GetModelsPerspectiveProjection() const;
		Rect<int> AspectRatioUpdate(const RenderTarget& render_target,const Model& model) const;
		void SortModelsPerspectiveProjection();
		void ClearModels();
	private:
		float orthographic_near_z{0.0f};
		float orthographic_far_z{1.0f};
		float perspective_fov{45.0f};
		const std::string shader_main_basic;
		const std::string shader_main_texture;
		Point2D<int> virtual_resolution;
		Point2D<int> desktop_resolution;
		VideoMode video_mode;
		TextureFilter texture_filter;
		AspectRatio aspect_ratio;
		View view;
		std::unique_ptr<RenderTarget> render_target_back_buffer;
		std::vector<std::unique_ptr<RenderTarget>> render_targets;
		std::vector<const Model*> models_orthographic_projection;
		std::vector<const Model*> models_perspective_projection;
		Video(const Video&) = delete;
		Video& operator=(const Video&) = delete;
		float LimitBase(const float initial,const float final,const float change,const float max) const;
	};
}

#endif
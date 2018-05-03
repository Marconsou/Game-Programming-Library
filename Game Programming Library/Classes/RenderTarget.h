#ifndef RENDERTARGET_H
#define RENDERTARGET_H

#include "Texture.h"

namespace GPL
{
	class RenderTarget
	{
	public:
		GPL_DLL RenderTarget() = default;
		GPL_DLL virtual ~RenderTarget() = 0 {};
		GPL_DLL int GetWidth() const;
		GPL_DLL int GetHeight() const;
		GPL_DLL void SetClearColor(const Color& clear_color);
		GPL_DLL const Color& GetClearColor() const;
		GPL_DLL const Texture& GetTexture() const;
		GPL_DLL virtual void Clear() = 0;
	protected:
		void SetRenderTarget(const int width,const int height,const Color& clear_color);
		std::unique_ptr<Texture>& GetPointerTexture();
	private:
		int width{};
		int height{};
		Color clear_color{Color::Transparent};
		std::unique_ptr<Texture> texture;
		RenderTarget(const RenderTarget&) = delete;
		RenderTarget& operator=(const RenderTarget&) = delete;
	};
}

#endif
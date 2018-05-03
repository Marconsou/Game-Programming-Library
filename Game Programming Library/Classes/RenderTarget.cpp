#include "RenderTarget.h"

using namespace std;
using namespace GPL;

void RenderTarget::SetRenderTarget(const int width,const int height,const Color& clear_color)
{
	this->width = width;
	this->height = height;
	this->clear_color = clear_color;
}

int RenderTarget::GetWidth() const
{
	return this->width;
}

int RenderTarget::GetHeight() const
{
	return this->height;
}

void RenderTarget::SetClearColor(const Color& clear_color)
{
	this->clear_color = clear_color;
}

const Color& RenderTarget::GetClearColor() const
{
	return this->clear_color;
}

const Texture& RenderTarget::GetTexture() const
{
	return *this->texture.get();
}

unique_ptr<Texture>& RenderTarget::GetPointerTexture()
{
	return this->texture;
}
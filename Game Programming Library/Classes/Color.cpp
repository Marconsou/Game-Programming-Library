#include "Color.h"

using namespace GPL;

const Color Color::Null(-1.0f,-1.0f,-1.0f,-1.0f);
const Color Color::Transparent(1.0f,1.0f,1.0f,0.0f);
const Color Color::Black(0.0f,0.0f,0.0f);
const Color Color::Gray(0.5f,0.5f,0.5f);
const Color Color::White(1.0f,1.0f,1.0f);
const Color Color::Red(1.0f,0.0f,0.0f);
const Color Color::Green(0.0f,1.0f,0.0f);
const Color Color::Blue(0.0f,0.0f,1.0f);
const Color Color::Yellow(1.0f,1.0f,0.0f);
const Color Color::Magenta(1.0f,0.0f,1.0f);
const Color Color::Cyan(0.0f,1.0f,1.0f);
const Color Color::Orange(1.0f,0.5f,0.0f);
const Color Color::Platinum(0.9f,0.89f,0.89f);
const Color Color::Gold(1.0f,0.84f,0.0f);
const Color Color::Silver(0.75f,0.75f,0.75f);
const Color Color::Bronze(0.8f,0.5f,0.2f);
const Color Color::Tan(0.82f,0.71f,0.55f);
const Color Color::Turquoise(0.19f,0.84f,0.78f);

Color::Color(const float red,const float green,const float blue,const float alpha) :
red(red),
green(green),
blue(blue),
alpha(alpha)
{

}

Color::Color(const Color& color,const float alpha) :
Color(color.GetRed(),color.GetGreen(),color.GetBlue(),alpha)
{

}

bool Color::operator==(const Color& color) const
{
	return ((this->red == color.red) && (this->green == color.green) && (this->blue == color.blue) && (this->alpha == color.alpha));
}

bool Color::operator!=(const Color& color) const
{
	return !this->operator==(color);
}

void Color::SetRed(const float red)
{
	this->red = red;
}

float Color::GetRed() const
{
	return this->red;
}

void Color::SetGreen(const float green)
{
	this->green = green;
}

float Color::GetGreen() const
{
	return this->green;
}

void Color::SetBlue(const float blue)
{
	this->blue = blue;
}

float Color::GetBlue() const
{
	return this->blue;
}

void Color::SetAlpha(const float alpha)
{
	this->alpha = alpha;
}

float Color::GetAlpha() const
{
	return this->alpha;
}

Color Color::GetInvertedColor() const
{
	return Color(1.0f - this->red,1.0f - this->green,1.0f - this->blue,this->alpha);
}

bool Color::IsOpaque() const
{
	return (this->alpha >= 1.0f);
}

bool Color::IsTransparent() const
{
	return (this->alpha <= 0.0f);
}
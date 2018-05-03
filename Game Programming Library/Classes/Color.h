#ifndef COLOR_H
#define COLOR_H

#include "BuildDLL.h"

namespace GPL
{
	class Color
	{
	public:
		GPL_DLL static const Color Null;
		GPL_DLL static const Color Transparent;
		GPL_DLL static const Color Black;
		GPL_DLL static const Color Gray;
		GPL_DLL static const Color White;
		GPL_DLL static const Color Red;
		GPL_DLL static const Color Green;
		GPL_DLL static const Color Blue;
		GPL_DLL static const Color Yellow;
		GPL_DLL static const Color Magenta;
		GPL_DLL static const Color Cyan;
		GPL_DLL static const Color Orange;
		GPL_DLL static const Color Platinum;
		GPL_DLL static const Color Gold;
		GPL_DLL static const Color Silver;
		GPL_DLL static const Color Bronze;
		GPL_DLL static const Color Tan;
		GPL_DLL static const Color Turquoise;
		GPL_DLL Color(const float red = 1.0f,const float green = 1.0f,const float blue = 1.0f,const float alpha = 1.0f);
		GPL_DLL Color(const Color& color,const float alpha);
		GPL_DLL bool operator==(const Color& color) const;
		GPL_DLL bool operator!=(const Color& color) const;
		GPL_DLL void SetRed(const float red);
		GPL_DLL float GetRed() const;
		GPL_DLL void SetGreen(const float green);
		GPL_DLL float GetGreen() const;
		GPL_DLL void SetBlue(const float blue);
		GPL_DLL float GetBlue() const;
		GPL_DLL void SetAlpha(const float alpha);
		GPL_DLL float GetAlpha() const;
		GPL_DLL Color GetInvertedColor() const;
		GPL_DLL bool IsOpaque() const;
		GPL_DLL bool IsTransparent() const;
	private:
		float red{};
		float green{};
		float blue{};
		float alpha{};
	};
}

#endif
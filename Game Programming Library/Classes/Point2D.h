#ifndef POINT2D_H
#define POINT2D_H

namespace GPL
{
	template<typename Type>
	class Point2D
	{
	public:
		Point2D(const Type x = {},const Type y = {}) :
			x(x),
			y(y) {}

		void SetX(const Type x)
		{
			this->x = x;
		}

		Type GetX() const
		{
			return this->x;
		}

		void SetY(const Type y)
		{
			this->y = y;
		}

		Type GetY() const
		{
			return this->y;
		}
	private:
		Type x{};
		Type y{};
	};
}

#endif
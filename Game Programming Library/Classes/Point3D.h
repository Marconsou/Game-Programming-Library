#ifndef POINT3D_H
#define POINT3D_H

namespace GPL
{
	template<typename Type>
	class Point3D
	{
	public:
		Point3D(const Type x = {},const Type y = {},const Type z = {}) :
			x(x),
			y(y),
			z(z) {}

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

		void SetZ(const Type z)
		{
			this->z = z;
		}

		Type GetZ() const
		{
			return this->z;
		}
	private:
		Type x{};
		Type y{};
		Type z{};
	};
}

#endif
#ifndef RECT_H
#define RECT_H

#include "Point2D.h"

namespace GPL
{
	template<typename Type>
	class Rect
	{
	public:
		Rect(const Type x = {},const Type y = {},const Type w = {},const Type h = {}) :
			position(x,y),
			size(w,h)	{}

		Point2D<Type>& GetPosition()
		{
			return this->position;
		}

		const Point2D<Type>& GetPosition() const
		{
			return this->position;
		}

		Point2D<Type>& GetSize()
		{
			return this->size;
		}

		const Point2D<Type>& GetSize() const
		{
			return this->size;
		}

		void SetPosition(const Type x,const Type y,const bool centralize = false)
		{
			if (!centralize)
			{
				this->position.SetX(x);
				this->position.SetY(y);
			}
			else
			{
				this->position.SetX(x - (this->size.GetX() / 2));
				this->position.SetY(y - (this->size.GetY() / 2));
			}
		}

		void SetSize(const Type w,const Type h)
		{
			this->size.SetX(w);
			this->size.SetY(h);
		}

		bool PointInRect(const Type point_x,const Type point_y) const
		{
			return ((point_x >= this->position.GetX()) && (point_x <= (this->position.GetX() + this->size.GetX())) &&
					(point_y >= this->position.GetY()) && (point_y <= (this->position.GetY() + this->size.GetY())));
		}
	private:
		Point2D<Type> position;
		Point2D<Type> size;
	};
}

#endif
#include "View.h"

using namespace GPL;

Point3D<float>& View::GetTransform()
{
	return this->transform;
}

const Point3D<float>& View::GetTransform() const
{
	return this->transform;
}

Point3D<float>& View::GetTranslate()
{
	return this->translate;
}

const Point3D<float>& View::GetTranslate() const
{
	return this->translate;
}

Point3D<float>& View::GetScale()
{
	return this->scale;
}

const Point3D<float>& View::GetScale() const
{
	return this->scale;
}

Point3D<float>& View::GetRotate()
{
	return this->rotate;
}

const Point3D<float>& View::GetRotate() const
{
	return this->rotate;
}

Rect<float>& View::GetViewport()
{
	return this->viewport;
}

const Rect<float>& View::GetViewport() const
{
	return this->viewport;
}
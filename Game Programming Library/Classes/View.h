#ifndef VIEW_H
#define VIEW_H

#include "Point3D.h"
#include "Rect.h"
#include "BuildDLL.h"

namespace GPL
{
	class View
	{
	public:
		View() = default;
		GPL_DLL Point3D<float>& GetTransform();
		GPL_DLL const Point3D<float>& GetTransform() const;
		GPL_DLL Point3D<float>& GetTranslate();
		GPL_DLL const Point3D<float>& GetTranslate() const;
		GPL_DLL Point3D<float>& GetScale();
		GPL_DLL const Point3D<float>& GetScale() const;
		GPL_DLL Point3D<float>& GetRotate();
		GPL_DLL const Point3D<float>& GetRotate() const;
		GPL_DLL Rect<float>& GetViewport();
		GPL_DLL const Rect<float>& GetViewport() const;
	private:
		Point3D<float> transform;
		Point3D<float> translate;
		Point3D<float> scale{1.0f,1.0f,1.0f};
		Point3D<float> rotate;
		Rect<float> viewport{0.0f,0.0f,1.0f,1.0f};
		View(const View&) = delete;
		View& operator=(const View&) = delete;
	};
}

#endif
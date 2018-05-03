#ifndef MODEL_H
#define MODEL_H

#include <algorithm>
#include <vector>
#include "Point2D.h"
#include "Point3D.h"
#include "Color.h"

namespace GPL
{
	enum class PrimitiveType
	{
		TriangleStrip,
		TriangleList,
		LineStrip,
	};

	enum class Projection
	{
		Orthographic,
		Perspective,
	};

	class Texture;
	class RenderTarget;
	class View;

	class Model final
	{
	public:
		GPL_DLL Model(const PrimitiveType primitive_type = PrimitiveType::TriangleStrip,const size_t primitive_count = 2,const size_t vertex_total = 0,const size_t index_total = 0);
		GPL_DLL ~Model();
		GPL_DLL void SetSourceModelAdded(std::vector<const Model*>& source_model_added);
		GPL_DLL void SetTexture(const Texture& texture);
		GPL_DLL const Texture& GetTexture() const;
		GPL_DLL void SetRenderTarget(const RenderTarget& render_target);
		GPL_DLL const RenderTarget& GetRenderTarget() const;
		GPL_DLL void SetView(const View& view);
		GPL_DLL const View& GetView() const;
		GPL_DLL void SetProjection(const Projection projection);
		GPL_DLL const Projection GetProjection() const;
		GPL_DLL void SetPrimitiveType(const PrimitiveType primitive_type);
		GPL_DLL PrimitiveType GetPrimitiveType() const;
		GPL_DLL void SetPrimitiveCount(const size_t primitive_count);
		GPL_DLL size_t GetPrimitiveCount() const;
		GPL_DLL void SetUseLimitedVertexTotal(const size_t use_limited_vertex_total);
		GPL_DLL float GetZPriority() const;
		GPL_DLL void SetPixelateGridSize(const float pixelate_grid_size);
		GPL_DLL float GetPixelateGridSize() const;
		GPL_DLL void SetInvertColor(const bool invert_color);
		GPL_DLL bool GetInvertColor() const;
		GPL_DLL void SetGrayScale(const bool gray_scale);
		GPL_DLL bool GetGrayScale() const;
		GPL_DLL Point3D<float>& GetTransform();
		GPL_DLL const Point3D<float>& GetTransform() const;
		GPL_DLL Point3D<float>& GetTranslate();
		GPL_DLL const Point3D<float>& GetTranslate() const;
		GPL_DLL Point3D<float>& GetScale();
		GPL_DLL const Point3D<float>& GetScale() const;
		GPL_DLL Point3D<float>& GetRotate();
		GPL_DLL const Point3D<float>& GetRotate() const;
		GPL_DLL Point2D<float>& GetTextureCoordinateInverted();
		GPL_DLL const Point2D<float>& GetTextureCoordinateInverted() const;
		GPL_DLL size_t GetVertexTotal() const;
		GPL_DLL void SetVertexPositionX(const int index,const float x);
		GPL_DLL void SetVertexPositionY(const int index,const float y);
		GPL_DLL void SetVertexPositionZ(const int index,const float z);
		GPL_DLL void SetVertexPosition(const int index,const float x,const float y,const float z = FLT_MAX);
		GPL_DLL const Point3D<float>& GetVertexPosition(const int index) const;
		GPL_DLL void SetVertexColor(const int index,const Color& color);
		GPL_DLL const Color& GetVertexColor(const int index) const;
		GPL_DLL void SetVertexTextureCoordinateU(const int index,float u);
		GPL_DLL void SetVertexTextureCoordinateV(const int index,float v);
		GPL_DLL void SetVertexTextureCoordinate(const int index,const float u,const float v);
		GPL_DLL const Point2D<float>& GetVertexTextureCoordinate(const int index) const;
		GPL_DLL void SetIndex(const int index,const short value);
		GPL_DLL const std::vector<short>& GetIndices() const;
		GPL_DLL void ResizeVertices(const size_t size);
		GPL_DLL void ResizeIndices(const size_t size);
		GPL_DLL bool IsOpaque() const;
		GPL_DLL bool Is3D() const;
		GPL_DLL bool IsTextured() const;
		GPL_DLL bool IsIndicesSequenced(const size_t max) const;
	private:
		struct Vertex
		{
			Point3D<float> position;
			Color color;
			Point2D<float> texture_coordinate;
		};
		std::vector<const Model*>* source_model_added{};
		const Texture* texture{};
		const RenderTarget* render_target{};
		const View* view{};
		Projection projection;
		PrimitiveType primitive_type;
		size_t primitive_count{};
		size_t use_limited_vertex_total{};
		float z_priority{FLT_MAX};
		float pixelate_grid_size{};
		bool invert_color{};
		bool gray_scale{};
		Point3D<float> transform;
		Point3D<float> translate;
		Point3D<float> scale{1.0f,1.0f,1.0f};
		Point3D<float> rotate;
		Point2D<float> texture_coordinate_inverted;
		std::vector<Vertex> vertices;
		std::vector<short> indices;
		Model(const Model&) = delete;
		Model& operator=(const Model&) = delete;
	};
}

#endif
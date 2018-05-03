#include "Model.h"

using namespace std;
using namespace GPL;

Model::Model(const PrimitiveType primitive_type,const size_t primitive_count,const size_t vertex_total,const size_t index_total) :
projection{},
primitive_type(primitive_type),
primitive_count(primitive_count),
use_limited_vertex_total(vertex_total),
vertices(vertex_total),
indices(index_total)
{

}

Model::~Model()
{
	if ((this->source_model_added) && (!this->source_model_added->empty()))
	{
		//Referência de onde foi adicionado este Model para removê-lo corretamente quando necessário (raramente), para evitar erros de iterator inválido no vector de Models da classe Video
		this->source_model_added->erase(remove(this->source_model_added->begin(),this->source_model_added->end(),this),this->source_model_added->end());
	}
}

void Model::SetSourceModelAdded(vector<const Model*>& source_model_added)
{
	this->source_model_added = &source_model_added;
}

void Model::SetTexture(const Texture& texture)
{
	this->texture = &texture;
}

const Texture& Model::GetTexture() const
{
	return *this->texture;
}

void Model::SetRenderTarget(const RenderTarget& render_target)
{
	this->render_target = &render_target;
}

const RenderTarget& Model::GetRenderTarget() const
{
	return *this->render_target;
}

void Model::SetView(const View& view)
{
	this->view = &view;
}

const View& Model::GetView() const
{
	return *this->view;
}

void Model::SetProjection(const Projection projection)
{
	this->projection = projection;
}

const Projection Model::GetProjection() const
{
	return this->projection;
}

void Model::SetPrimitiveType(const PrimitiveType primitive_type)
{
	this->primitive_type = primitive_type;
}

PrimitiveType Model::GetPrimitiveType() const
{
	return this->primitive_type;
}

void Model::SetPrimitiveCount(const size_t primitive_count)
{
	this->primitive_count = primitive_count;
}

size_t Model::GetPrimitiveCount() const
{
	return this->primitive_count;
}

void Model::SetUseLimitedVertexTotal(const size_t use_limited_vertex_total)
{
	this->use_limited_vertex_total = min(this->vertices.size(),use_limited_vertex_total);
}

float Model::GetZPriority() const
{
	return this->z_priority;
}

void Model::SetPixelateGridSize(const float pixelate_grid_size)
{
	this->pixelate_grid_size = pixelate_grid_size;
}

float Model::GetPixelateGridSize() const
{
	return this->pixelate_grid_size;
}

void Model::SetInvertColor(const bool invert_color)
{
	this->invert_color = invert_color;
}

bool Model::GetInvertColor() const
{
	return this->invert_color;
}

void Model::SetGrayScale(const bool gray_scale)
{
	this->gray_scale = gray_scale;
}

bool Model::GetGrayScale() const
{
	return this->gray_scale;
}

Point3D<float>& Model::GetTransform()
{
	return this->transform;
}

const Point3D<float>& Model::GetTransform() const
{
	return this->transform;
}

Point3D<float>& Model::GetTranslate()
{
	return this->translate;
}

const Point3D<float>& Model::GetTranslate() const
{
	return this->translate;
}

Point3D<float>& Model::GetScale()
{
	return this->scale;
}

const Point3D<float>& Model::GetScale() const
{
	return this->scale;
}

Point3D<float>& Model::GetRotate()
{
	return this->rotate;
}

const Point3D<float>& Model::GetRotate() const
{
	return this->rotate;
}

Point2D<float>& Model::GetTextureCoordinateInverted()
{
	return this->texture_coordinate_inverted;
}

const Point2D<float>& Model::GetTextureCoordinateInverted() const
{
	return this->texture_coordinate_inverted;
}

size_t Model::GetVertexTotal() const
{
	return min(this->vertices.size(),this->use_limited_vertex_total);
}

void Model::SetVertexPositionX(const int index,const float x)
{
	this->vertices[index].position.SetX(x);
}

void Model::SetVertexPositionY(const int index,const float y)
{
	this->vertices[index].position.SetY(y);
}

void Model::SetVertexPositionZ(const int index,const float z)
{
	//Utilizando o Z
	if (z != FLT_MAX)
	{
		this->vertices[index].position.SetZ(z);

		//Atualizando o Z priority
		this->z_priority = FLT_MAX;
		for (const auto& iterator : this->vertices)
			this->z_priority = min(this->z_priority,iterator.position.GetZ());
	}
}

void Model::SetVertexPosition(const int index,const float x,const float y,const float z)
{
	this->SetVertexPositionX(index,x);
	this->SetVertexPositionY(index,y);
	this->SetVertexPositionZ(index,z);
}

const Point3D<float>& Model::GetVertexPosition(const int index) const
{
	return this->vertices[index].position;
}

void Model::SetVertexColor(const int index,const Color& color)
{
	this->vertices[index].color = color;
}

const Color& Model::GetVertexColor(const int index) const
{
	return this->vertices[index].color;
}

void Model::SetVertexTextureCoordinateU(const int index,float u)
{
	this->vertices[index].texture_coordinate.SetX(u);
}

void Model::SetVertexTextureCoordinateV(const int index,float v)
{
	this->vertices[index].texture_coordinate.SetY(v);
}

void Model::SetVertexTextureCoordinate(const int index,const float u,const float v)
{
	this->SetVertexTextureCoordinateU(index,u);
	this->SetVertexTextureCoordinateV(index,v);
}

const Point2D<float>& Model::GetVertexTextureCoordinate(const int index) const
{
	return this->vertices[index].texture_coordinate;
}

void Model::SetIndex(const int index,const short value)
{
	this->indices[index] = value;
}

const vector<short>& Model::GetIndices() const
{
	return this->indices;
}

void Model::ResizeVertices(const size_t size)
{
	this->vertices.resize(size);
	this->use_limited_vertex_total = size;
}

void Model::ResizeIndices(const size_t size)
{
	this->indices.resize(size);
}

bool Model::IsOpaque() const
{
	for (size_t i = 0; i < this->GetVertexTotal(); i++)
	{
		if (!this->vertices[i].color.IsOpaque())
			return false;
	}
	return true;
}

bool Model::Is3D() const
{
	return (this->z_priority != FLT_MAX);
}

bool Model::IsTextured() const
{
	return (this->texture != nullptr);
}

bool Model::IsIndicesSequenced(const size_t max) const
{
	//Quantidade de índices é maior que o suportado
	if (this->indices.size() > max)
		return false;

	size_t size = min(this->indices.size(),max);
	for (size_t i = 0; i < size; i++)
	{
		//Qualquer índice fora de sequência
		if (this->indices[i] != i)
			return false;
	}

	//Índices estão em sequência
	return true;
}
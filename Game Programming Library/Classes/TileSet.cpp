#include "TileSet.h"

using namespace std;
using namespace GPL;

int TileSet::invalid_tile_id{-1};
float TileSet::Tile::tile_size{};

TileSet::TileSet(const Video& video,const Point2D<int>& tile_total,const int base_texture_id,const int dynamic_tile_set_quantity,const float dynamic_tile_set_timer) :
base_texture_id(base_texture_id),
tile_total(tile_total),
tiles(tile_total.GetX(),vector<Tile>(tile_total.GetY())),
change_texture_timer(dynamic_tile_set_timer),
texture_quantity(0,dynamic_tile_set_quantity)
{
	//Textura utilizada pelo Tile Set
	this->model.SetTexture(video.GetTexture(this->base_texture_id));
}

void TileSet::SetTileID(const int x,const int y,const int tile_id)
{
	this->tiles[x][y].tile_id = tile_id;
}

void TileSet::SetGrayScale(const bool gray_scale)
{
	this->model.SetGrayScale(gray_scale);
}

void TileSet::SetTileSize(const float tile_size)
{
	Tile::tile_size = tile_size;
}

float TileSet::GetTileSize()
{
	return Tile::tile_size;
}

size_t TileSet::CalculateValidTiles() const
{
	//Quantidade total
	size_t valid_tile_total = this->tile_total.GetX() * this->tile_total.GetY();

	for (int y = 0; y < this->tile_total.GetY(); y++)
	{
		for (int x = 0; x < this->tile_total.GetX(); x++)
		{
			//Identificou um ID inválido então descontar
			if (this->tiles[x][y].tile_id == TileSet::invalid_tile_id)
				valid_tile_total--;
		}
	}
	return valid_tile_total;
}

void TileSet::Build()
{
	//Quantidade de Tiles válidos para evitar de renderizar os inválidos
	const size_t valid_tile_total = this->CalculateValidTiles();

	//Redimensionando a quantidade necessária
	this->model.ResizeIndices(valid_tile_total * 6);
	this->model.ResizeVertices(valid_tile_total * 4);
	this->model.SetPrimitiveCount(valid_tile_total * 2);

	size_t index_value = 0;
	size_t indices_index = 0;
	size_t vertex_index = 0;

	float position_x = 0.0f;
	float position_y = 0.0f;

	//Dimensões da textura do Tile Set
	const float texture_w = static_cast<float>(this->model.GetTexture().GetWidth());
	const float texture_h = static_cast<float>(this->model.GetTexture().GetHeight());

	const int quantity_w_total = static_cast<int>(texture_w / Tile::tile_size);

	for (int y = 0; y < this->tile_total.GetY(); y++)
	{
		for (int x = 0; x < this->tile_total.GetX(); x++)
		{
			const int tile_id = this->tiles[x][y].tile_id;

			if (tile_id != TileSet::invalid_tile_id)
			{
				//Index Buffer
				this->model.SetIndex(indices_index,index_value);
				index_value++;
				indices_index++;

				this->model.SetIndex(indices_index,index_value);
				index_value++;
				indices_index++;

				this->model.SetIndex(indices_index,index_value);
				indices_index++;

				this->model.SetIndex(indices_index,index_value);
				index_value--;
				indices_index++;

				this->model.SetIndex(indices_index,index_value);
				index_value += 2;
				indices_index++;

				this->model.SetIndex(indices_index,index_value);
				index_value++;
				indices_index++;

				//Vertex Buffer
				float x_1 = position_x;
				float y_1 = position_y;

				float x_2 = x_1 + Tile::tile_size;
				float y_2 = y_1 + Tile::tile_size;

				const float u = ((tile_id % quantity_w_total) * Tile::tile_size) / texture_w;
				const float v = ((tile_id / quantity_w_total) * Tile::tile_size) / texture_h;

				const float uw = u + (Tile::tile_size / texture_w);
				const float vh = v + (Tile::tile_size / texture_h);

				this->model.SetVertexPosition(vertex_index,x_1,y_1);
				this->model.SetVertexTextureCoordinate(vertex_index,u,v);
				vertex_index++;

				this->model.SetVertexPosition(vertex_index,x_2,y_1);
				this->model.SetVertexTextureCoordinate(vertex_index,uw,v);
				vertex_index++;

				this->model.SetVertexPosition(vertex_index,x_1,y_2);
				this->model.SetVertexTextureCoordinate(vertex_index,u,vh);
				vertex_index++;

				this->model.SetVertexPosition(vertex_index,x_2,y_2);
				this->model.SetVertexTextureCoordinate(vertex_index,uw,vh);
				vertex_index++;
			}
			position_x += Tile::tile_size;
		}
		position_x = 0.0f;
		position_y += Tile::tile_size;
	}
}

void TileSet::Update(const Timer& timer,const Point2D<float>& camera)
{
	//Variando a textura do Tile Set dinamicamente
	if (this->texture_quantity.GetTotal() > 1)
	{
		//Passar para a próxima textura
		if (this->change_texture_timer.Action(timer))
			this->texture_quantity.Next();
	}

	//Atualizar o Tile Set com base na câmera para deslocá-lo juntamente
	this->model.GetTranslate().SetX(-camera.GetX());
	this->model.GetTranslate().SetY(-camera.GetY());
}

void TileSet::Show(Video& video)
{
	//Atualizando a textura
	this->model.SetTexture(video.GetTexture(this->base_texture_id + this->texture_quantity.GetCurrent()));

	//Mostrando todo o Tile Set
	video.Draw(this->model);
}
#ifndef TILESET_H
#define TILESET_H

#include "Quantity.h"
#include "Interval.h"
#include "Video.h"

namespace GPL
{
	class TileSet
	{
	public:
		GPL_DLL TileSet() = default;
		GPL_DLL TileSet(const Video& video,const Point2D<int>& tile_total,const int base_texture_id,const int dynamic_tile_set_quantity = 1,const float dynamic_tile_set_timer = 0.175f);
		GPL_DLL void SetTileID(const int x,const int y,const int tile_id);
		GPL_DLL void SetGrayScale(const bool gray_scale);
		GPL_DLL void Build();
		GPL_DLL void Update(const Timer& timer,const Point2D<float>& camera);
		GPL_DLL void Show(Video& video);
		GPL_DLL static void SetTileSize(const float tile_size);
		GPL_DLL static float GetTileSize();
	private:
		struct Tile
		{
			int tile_id{TileSet::invalid_tile_id};
			static float tile_size;
			GPL_DLL Tile() = default;
			Tile& operator=(const Tile&) = delete;
		};

		const int base_texture_id;
		const Point2D<int>& tile_total;
		std::vector<std::vector<Tile>> tiles;
		Interval change_texture_timer;
		Quantity texture_quantity;
		Model model{PrimitiveType::TriangleList};
		static int invalid_tile_id;
		TileSet(const TileSet&) = delete;
		TileSet& operator=(const TileSet&) = delete;
		size_t CalculateValidTiles() const;
	};
}

#endif
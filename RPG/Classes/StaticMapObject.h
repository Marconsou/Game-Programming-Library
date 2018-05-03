#ifndef STATICMAPOBJECT_H
#define STATICMAPOBJECT_H

#include "Sprite.h"
#include "MapObject.h"

namespace RPG
{
	class StaticMapObject : public GPL::MapObject
	{
	private:
		//Sprite do objeto
		GPL::Sprite sprite;

		//Alterar Gray Scale
		virtual void SetGrayScale(const bool gray_scale);

		//Atualizar dados de relacionados aos movimentos
		virtual void UpdateMovement(const GPL::Timer& timer);

		//Atualizar dados do objeto
		virtual void Update(const GPL::Timer& timer);

		//Mostrar o objeto
		virtual void Show(GPL::Video& video,const GPL::Timer& timer);
	public:
		//Construtor
		StaticMapObject();

		//Alterar Static Map Object
		void SetStaticMapObject(const GPL::Texture& texture,const float w,const float h,const float texture_position_x,const float texture_position_y);
	};
}

#endif
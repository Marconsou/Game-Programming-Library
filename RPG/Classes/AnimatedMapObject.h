#ifndef ANIMATEDMAPOBJECT_H
#define ANIMATEDMAPOBJECT_H

#include "AnimationFrame.h"
#include "MapObject.h"

namespace RPG
{
	class AnimatedMapObject : public GPL::MapObject
	{
	private:
		//Animação do objeto
		GPL::AnimationFrame animation_frame;

		//Alterar Pause
		virtual void SetPause(const bool pause);

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
		AnimatedMapObject();

		//Alterar Animated Map Object
		void SetAnimatedMapObject(const GPL::Timer& timer,const GPL::Texture& texture,const float frame_width,const float frame_height,const int frame_quantity,const float interval,const int pixel_gap = 0);
	};
}

#endif
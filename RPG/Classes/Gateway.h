#ifndef GATEWAY_H
#define GATEWAY_H

#include "MapObject.h"
#include "Database.h"

namespace RPG
{
	class Gateway : public GPL::MapObject
	{
	private:
		//ID do texto para onde vai após passar pelo Gateway
		const LanguageTextID new_map_text_id;

		//Referência do Database para o texto de ação em cima do Chest
		static const Database* database;
	protected:
		//Atualizar dados de relacionados aos movimentos
		virtual void UpdateMovement(const GPL::Timer& timer);

		//Atualizar dados do objeto
		virtual void Update(const GPL::Timer& timer);

		//Mostrar o objeto
		virtual void Show(GPL::Video& video,const GPL::Timer& timer);
	public:
		//Construtor
		Gateway(const LanguageTextID new_map_text_id);

		//Alterar Gateway
		void SetGateway(const float w,const float h);

		//Alterar Database
		static void SetDatabase(const Database& database);
	};
}

#endif
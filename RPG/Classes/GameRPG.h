#ifndef GAMERPG_H
#define GAMERPG_H

#include "AnimationFrame.h"
#include "TextDynamic.h"
#include "MessageLog.h"
#include "DialogueBox.h"
#include "Game.h"
#include "Configuration.h"
#include "Warrior.h"
#include "Mage.h"
#include "Database.h"

namespace RPG
{
	//Animações usadas durante o jogo
	enum Animations
	{
		HeroTeleporting = 0,
		AnimationsMax,
	};

	class GameRPG : public GPL::Game
	{
	private:
		//Mostrar mensagens no Log
		bool show_message_log;

		//Objeto principal para carregar as configurações do jogo
		Configuration configuration;

		//Banco de dados com as informações e conteúdos do jogo
		Database database;

		//Objeto principal do herói
		std::unique_ptr<Hero> hero;

		//Conquista desbloqueada recentemente
		std::string recent_achievement_unlocked;

		//Buffer para armazenar os textos dinâmicos
		std::vector<std::unique_ptr<GPL::TextDynamic>> text_dynamics;

		//Animações utilizadas durante o jogo que já podem ser carregadas no início
		std::vector<GPL::AnimationFrame> animations;

		//Mensagens para serem adicionadas e mostradas em forma de Log
		GPL::MessageLog message_log;
	public:
		//Construtor
		GameRPG(std::unique_ptr<GPL::Application>&& application);

		//Alterar Show Message Log
		void SetShowMessageLog(const bool show_message_log);

		//Pegar Configuration
		Configuration& GetConfiguration();

		//Pegar Database
		Database& GetDatabase();

		//Pegar Hero
		Hero& GetHero();

		//Alterar Recent Achievement Unlocked
		void SetRecentAchievementUnlocked(const std::string& recent_achievement_unlocked);

		//Pegar Recent Achievement Unlocked
		const std::string& GetRecentAchievementUnlocked() const;

		//Pegar Animations
		std::vector<GPL::AnimationFrame>& GetAnimations();

		//Alterar Window
		void SetWindow(GPL::Window& window,const int inner_block_quantity_w,const int inner_block_quantity_h);

		//Alterar Dialogue Box
		void SetDialogueBox(GPL::DialogueBox& dialogue_box);

		//Pegar Text Speed Interval
		float GetTextSpeedInterval();

		//Carregar o banco de dados
		void LoadDatabase();

		//Carregar principais arquivos
		void LoadResources();

		//Carregar configurações de Video
		void LoadVideoSettingsFromConfiguration();

		//Carregar configurações de Audio
		void LoadAudioSettingsFromConfiguration(const bool load_audio_engine);

		//Começar um novo jogo
		void StartNewGame(const FileID texture_id,const std::string& name);

		//Terminar o jogo atual
		void FinishCurrentGame();

		//Verificar se o herói foi criado
		bool HeroCreated() const;

		//Nova mensagem no Log
		void NewMessageLogText(const std::string& message,const GPL::Color& color = GPL::Color::White);

		//Adicionar mensagem no log na mesma linha
		void AddMessageLogText(const std::string& message,const GPL::Color& color = GPL::Color::White);

		//Mostrar os textos dinâmicos
		void ShowTextDynamic();

		//Mostrar as mensagens no Log
		void ShowMessageLog();

		//Adicionar texto dinâmico
		template<class Type>
		GPL::TextDynamic& AddTextDynamic(const std::string& text,const GPL::Color color,const float x,const float y,const bool centralize = true)
		{
			this->text_dynamics.push_back(std::make_unique<Type>());

			TextDynamic& text_dynamic = *this->text_dynamics.back();

			text_dynamic.SetTextDynamic(this->GetVideo().GetFont(FontQlassikBoldMediumFileID),text,color);
			text_dynamic.Play(false);
			text_dynamic.SetPosition(x,y,centralize);
			
			//Se precisar alterar outros dados dinâmicamente
			return text_dynamic;
		}

		virtual void CreateGame();
	};
}

#endif
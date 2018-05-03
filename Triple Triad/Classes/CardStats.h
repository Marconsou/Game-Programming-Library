#ifndef CARDSTATS_H
#define CARDSTATS_H

#include <string>

namespace TT
{
	enum class Elemental
	{
		None,
		Fire,
		Ice,
		Thunder,
		Poison,
		Earth,
		Wind,
		Water,
		Holy,
		Max,
	};

	enum class CardID
	{
		Geezard,Funguar,BiteBug,RedBat,Blobra,Gayla,Gesper,FastitocalonF,BloodSoul,Caterchipillar,Cockatrice,
		Grat,Buel,Mesmerize,GlacialEye,Belhelmel,Thrustaevis,Anacondaur,Creeps,Grendel,Jellyeye,GrandMantis,
		Forbidden,Armadodo,TriFace,Fastitocalon,SnowLion,Ochu,SAM08G,DeathClaw,Cactuar,Tonberry,AbyssWorm,
		Turtapod,Vysage,TRexaur,Bomb,Blitz,Wendigo,Torama,Imp,BlueDragon,Adamantoise,Hexadragon,
		IronGiant,Behemoth,Chimera,PuPu,Elastoid,GIM47N,Malboro,RubyDragon,Elnoyle,TonberryKing,BiggsWedge,
		FujinRaijin,Elvoret,XATM092,Granaldo,Gerogero,Iguion,Abadon,Trauma,Oilboyle,ShumiTribe,Krysta,
		Propagator,JumboCactuar,TriPoint,Gargantua,MobileType8,Sphinxara,Tiamat,BGH251F2,RedGiant,Catoblepas,UltimaWeapon,
		ChubbyChocobo,Angelo,Gilgamesh,MiniMog,Chocobo,Quezacotl,Shiva,Ifrit,Siren,Sacred,Minotaur,
		Carbuncle,Diablos,Leviathan,Odin,Pandemona,Cerberus,Alexander,Phoenix,Bahamut,Doomtrain,Eden,
		Ward,Kiros,Laguna,Selphie,Quistis,Irvine,Zell,Rinoa,Edea,Seifer,Squall,
		Max,
	};

	class CardStats
	{
	public:
		CardStats(const CardID id,const std::string& name,const int level,const int left,const int top,const int right,const int bottom,const Elemental elemental = Elemental::None);
		CardID GetID() const;
		const std::string& GetName() const;
		int GetLevel() const;
		int GetLeft() const;
		int GetTop() const;
		int GetRight() const;
		int GetBottom() const;
		Elemental GetElemental() const;
	private:
		const CardID id;
		const std::string name;
		const int level{};
		const int left{};
		const int top{};
		const int right{};
		const int bottom{};
		const Elemental elemental;
		CardStats(const CardStats&) = delete;
		CardStats& operator=(const CardStats&) = delete;
	};
}

#endif
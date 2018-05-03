#include "ItemButton.h"

using namespace std;
using namespace GPL;
using namespace RPG;

GameRPG* ItemButton::game(nullptr);
bool ItemButton::shopping(false);
vector<ItemButton::PointerGetBool> ItemButton::pointers_get_bool(15);
vector<ItemButton*> ItemButton::item_buttons_to_update;

ItemButton::ItemButton() :
	item(nullptr),
	default_empty_icon(ItemIconEmpty),
	item_id_changed(NullItemID),
	is_shop_item(false),
	mouse_entering(false),
	color_changing(false)
{
	this->SetButton(0.0f,0.0f,32.0f,32.0f);
	this->AddEventOnMouseEnter(&ItemButton::ItemOnMouseEnter,*this);
	this->AddEventOnMouseLeave(&ItemButton::ItemOnMouseLeave,*this);

	//Abilities
	if (!ItemButton::pointers_get_bool.front())
	{
		ItemButton::pointers_get_bool[0] = &Ability::GetAnalyzer;
		ItemButton::pointers_get_bool[1] = &Ability::GetTrainer;
		ItemButton::pointers_get_bool[2] = &Ability::GetBounty;
		ItemButton::pointers_get_bool[3] = &Ability::GetCustomer;
		ItemButton::pointers_get_bool[4] = &Ability::GetCoward;
		ItemButton::pointers_get_bool[5] = &Ability::GetBrave;
		ItemButton::pointers_get_bool[6] = &Ability::GetRunner;
		ItemButton::pointers_get_bool[7] = &Ability::GetSkinSlicer;
		ItemButton::pointers_get_bool[8] = &Ability::GetBoneCrusher;
		ItemButton::pointers_get_bool[9] = &Ability::GetShellDriller;
		ItemButton::pointers_get_bool[10] = &Ability::GetHumanEater;
		ItemButton::pointers_get_bool[11] = &Ability::GetBeastKiller;
		ItemButton::pointers_get_bool[12] = &Ability::GetUndeadPurifier;
		ItemButton::pointers_get_bool[13] = &Ability::GetDemonHunter;
		ItemButton::pointers_get_bool[14] = &Ability::GetDragonSlayer;
	}
}

void ItemButton::SetGame(GameRPG& game)
{
	ItemButton::game = &game;
}

void ItemButton::SetShopping(const bool shopping)
{
	ItemButton::shopping = shopping;
}

void ItemButton::SetItemButton(Item& item,const bool is_shop_item,const bool add_item_button_to_update)
{
	this->item = &item;
	this->is_shop_item = is_shop_item;

	//Este Item Button será atualizado junto com outros ao mesmo tempo em algumas situações, principalmente as de compra e venda de item em um shop
	if (add_item_button_to_update)
		ItemButton::item_buttons_to_update.push_back(this);

	this->SetDataUpdate(true);
}

Item& ItemButton::GetItem()
{
	return *this->item;
}

void ItemButton::SetDefaultEmptyIcon(const ItemIcon default_empty_icon)
{
	this->default_empty_icon = default_empty_icon;
}

void ItemButton::AddInformation(const string& label,const int value,const bool plus,const bool percentage,const Color& label_color,const Color& value_color)
{
	if (value)
	{
		this->NewToolTipTextLine(label + " ",label_color);
		this->AddToolTipTextLine((plus ? "+" : "") + Convert::NumberToString(value) + (percentage ? "%" : ""),value_color);
	}
}

void ItemButton::AddInformation(const string& label,const string& value,const Color& label_color,const Color& value_color)
{
	this->NewToolTipTextLine(label + " ",label_color);

	if (!value.empty())
		this->AddToolTipTextLine(value,value_color);
}

bool ItemButton::IsEquipmentButton() const
{
	return ((this->default_empty_icon >= ItemIconRightHand) && (this->default_empty_icon <= ItemIconLeftAccessory));
}

void ItemButton::UpdateIcon()
{
	const Video& video = ItemButton::game->GetVideo();

	float texture_position_x = 0.0f;
	float texture_position_y = this->GetW() + 1.0f;
	const Texture& texture = ((!this->item->IsEmpty()) ? (video.GetTexture(TextureUsableFileID + (this->item->GetClassType() - ItemClassUsable))) : (video.GetTexture(TextureCommonFileID)));

	//Restaurando o ícone padrão vazio
	if (this->item->IsEmpty())
		this->item->SetIcon(this->default_empty_icon);

	if (!this->item->IsEmpty())
	{
		const int quantity_w = static_cast<int>(texture.GetWidth() / this->GetW());

		texture_position_x = (this->item->GetIcon() % quantity_w) * this->GetW();
		texture_position_y = (this->item->GetIcon() / quantity_w) * this->GetH();
	}
	else if (this->item->GetIcon() == ItemIconRightHand)
	{
		texture_position_x = 99.0f;
		texture_position_y = 0.0f;
	}
	else if (this->item->GetIcon() == ItemIconLeftHand)
	{
		texture_position_x = 131.0f;
		texture_position_y = 0.0f;
	}
	else if (this->item->GetIcon() == ItemIconHelm)
	{
		texture_position_x = 99.0f;
		texture_position_y = 32.0f;
	}
	else if (this->item->GetIcon() == ItemIconArmor)
	{
		texture_position_x = 131.0f;
		texture_position_y = 32.0f;
	}
	else if (this->item->GetIcon() == ItemIconGloves)
	{
		texture_position_x = 163.0f;
		texture_position_y = 32.0f;
	}
	else if (this->item->GetIcon() == ItemIconBoots)
	{
		texture_position_x = 195.0f;
		texture_position_y = 32.0f;
	}
	else if (this->item->GetIcon() == ItemIconRightAccessory)
	{
		texture_position_x = 163.0f;
		texture_position_y = 0.0f;
	}
	else if (this->item->GetIcon() == ItemIconLeftAccessory)
	{
		texture_position_x = 195.0f;
		texture_position_y = 0.0f;
	}
	else if (this->item->GetIcon() == ItemIconDiscard)
	{
		texture_position_x = 195.0f;
		texture_position_y = 66.0f;
	}

	//Atualizar o botão
	this->SetButton(texture,this->GetW(),this->GetH(),texture_position_x,texture_position_y);
}

void ItemButton::DataUpdate()
{
	if (this->GetDataUpdate())
	{
		GameRPG& game = *ItemButton::game;

		Database& database = game.GetDatabase();

		//Atualizar dados do ToolTip
		this->ClearToolTip();
		this->SetToolTip(game.GetVideo().GetFont(FontQlassikBoldSmallFileID),3.0f);

		//Atualizar o ícone que será utilizado
		this->UpdateIcon();

		//Atualizar as informações do item
		if (!this->item->IsEmpty())
		{
			//Usable
			if (this->item->IsUsable())
			{
				this->NewToolTipTextLine(this->item->GetName(),Color::Green);
				this->NewToolTipTextLine(this->item->GetDescription(),Color::White);
			}

			//Quest Item
			else if (this->item->IsQuestItem())
			{
				this->NewToolTipTextLine(this->item->GetName(),Color::Orange);
				this->NewToolTipTextLine(this->item->GetDescription(),Color::White);
			}

			//Equipment
			else if (this->item->IsEquipment())
			{
				const Color label_color(Color::Yellow);
				const Color value_color(Color::White);

				this->NewToolTipTextLine(this->item->GetName(),Color::Gold);

				string weapon_damage_type;
				//Cut
				if ((this->item->IsDagger()) || (this->item->IsSword()) || (this->item->IsAxe()))
					weapon_damage_type = database.GetLanguageText(CutTextID);

				//Smash
				else if ((this->item->IsMace()) || (this->item->IsStaff()))
					weapon_damage_type = database.GetLanguageText(SmashTextID);

				//Pierce
				else if ((this->item->IsSpear()) || (this->item->IsBow()))
					weapon_damage_type = database.GetLanguageText(PierceTextID);

				this->AddInformation(database.GetLanguageText(ClassTextID),database.GetLanguageText(static_cast<LanguageTextID>(UsableTextID + this->item->GetClassType() - 1)) + (this->item->IsWeapon() ? " (" + weapon_damage_type + ")" : ""));

				const bool requirement_met = !game.GetHero().ItemRequirementNotMet(*this->item);
				this->AddInformation(database.GetLanguageText(RequiredLevelTextID),this->item->GetRequiredLevel(),false,false,requirement_met ? label_color : Color::Red,requirement_met ? value_color : Color::Red);

				this->AddInformation(database.GetLanguageText(WeightTextID),this->item->GetWeight());

				if (this->item->IsWeapon())
					this->AddInformation(this->item->IsOneHandedWeapon() ? database.GetLanguageText(OneHandTextID) : database.GetLanguageText(TwoHandsTextID));

				if (this->item->GetStats().GetElementalEffect())
					this->AddInformation(database.GetLanguageText(ElementalEffectTextID));

				if (this->item->GetStats().GetStatusEffect())
					this->AddInformation(database.GetLanguageText(StatusEffectTextID));

				if ((this->item->GetStats().GetPhysicalDamageMin()) && (this->item->GetStats().GetPhysicalDamageMax()))
					this->AddInformation(database.GetLanguageText(PhysicalDamageTextID),Convert::NumberToString(this->item->GetStats().GetPhysicalDamageMin()) + "-" + Convert::NumberToString(this->item->GetStats().GetPhysicalDamageMax()));

				if ((this->item->GetStats().GetMagicalDamageMin()) && (this->item->GetStats().GetMagicalDamageMax()))
					this->AddInformation(database.GetLanguageText(MagicalDamageTextID),Convert::NumberToString(this->item->GetStats().GetMagicalDamageMin()) + "-" + Convert::NumberToString(this->item->GetStats().GetMagicalDamageMax()));

				this->AddInformation(database.GetLanguageText(PhysicalResistTextID),this->item->GetStats().GetPhysicalResist(),true,true);
				this->AddInformation(database.GetLanguageText(MagicalResistTextID),this->item->GetStats().GetMagicalResist(),true,true);

				this->AddInformation(database.GetLanguageText(HPMaxTextID),this->item->GetStats().GetHPMax(),true);
				this->AddInformation(database.GetLanguageText(MPMaxTextID),this->item->GetStats().GetMPMax(),true);

				this->AddInformation(database.GetLanguageText(HitTextID),this->item->GetStats().GetHit(),true,true);
				this->AddInformation(database.GetLanguageText(EvadeTextID),this->item->GetStats().GetEvade(),true,true);
				this->AddInformation(database.GetLanguageText(SpeedTextID),this->item->GetStats().GetSpeed(),true);

				this->AddInformation(database.GetLanguageText(FireDamageTextID),this->item->GetElementalDamage().GetFire(),true);
				this->AddInformation(database.GetLanguageText(IceDamageTextID),this->item->GetElementalDamage().GetIce(),true);
				this->AddInformation(database.GetLanguageText(LightningDamageTextID),this->item->GetElementalDamage().GetLightning(),true);
				this->AddInformation(database.GetLanguageText(LightDamageTextID),this->item->GetElementalDamage().GetLight(),true);
				this->AddInformation(database.GetLanguageText(DarkDamageTextID),this->item->GetElementalDamage().GetDark(),true);

				this->AddInformation(database.GetLanguageText(FireResistTextID),this->item->GetElementalResist().GetFire(),true,true);
				this->AddInformation(database.GetLanguageText(IceResistTextID),this->item->GetElementalResist().GetIce(),true,true);
				this->AddInformation(database.GetLanguageText(LightningResistTextID),this->item->GetElementalResist().GetLightning(),true,true);
				this->AddInformation(database.GetLanguageText(LightResistTextID),this->item->GetElementalResist().GetLight(),true,true);
				this->AddInformation(database.GetLanguageText(DarkResistTextID),this->item->GetElementalResist().GetDark(),true,true);

				this->AddInformation(database.GetLanguageText(FireAbsorbTextID),this->item->GetElementalAbsorb().GetFire(),true,true);
				this->AddInformation(database.GetLanguageText(IceAbsorbTextID),this->item->GetElementalAbsorb().GetIce(),true,true);
				this->AddInformation(database.GetLanguageText(LightningAbsorbTextID),this->item->GetElementalAbsorb().GetLightning(),true,true);
				this->AddInformation(database.GetLanguageText(LightAbsorbTextID),this->item->GetElementalAbsorb().GetLight(),true,true);
				this->AddInformation(database.GetLanguageText(DarkAbsorbTextID),this->item->GetElementalAbsorb().GetDark(),true,true);

				this->AddInformation(database.GetLanguageText(WoundAttackTextID),this->item->GetStatusAttack().GetWound(),true,true);
				this->AddInformation(database.GetLanguageText(SlownessAttackTextID),this->item->GetStatusAttack().GetSlowness(),true,true);
				this->AddInformation(database.GetLanguageText(TirednessAttackTextID),this->item->GetStatusAttack().GetTiredness(),true,true);
				this->AddInformation(database.GetLanguageText(HeadacheAttackTextID),this->item->GetStatusAttack().GetHeadache(),true,true);
				this->AddInformation(database.GetLanguageText(BlindnessAttackTextID),this->item->GetStatusAttack().GetBlindness(),true,true);

				this->AddInformation(database.GetLanguageText(WoundDefenseTextID),this->item->GetStatusDefense().GetWound(),true,true);
				this->AddInformation(database.GetLanguageText(SlownessDefenseTextID),this->item->GetStatusDefense().GetSlowness(),true,true);
				this->AddInformation(database.GetLanguageText(TirednessDefenseTextID),this->item->GetStatusDefense().GetTiredness(),true,true);
				this->AddInformation(database.GetLanguageText(HeadacheDefenseTextID),this->item->GetStatusDefense().GetHeadache(),true,true);
				this->AddInformation(database.GetLanguageText(BlindnessDefenseTextID),this->item->GetStatusDefense().GetBlindness(),true,true);

				this->AddInformation(database.GetLanguageText(CriticalStrikeTextID),this->item->GetStats().GetCriticalStrike(),true,true);
				this->AddInformation(database.GetLanguageText(QuickStrikeTextID),this->item->GetStats().GetQuickStrike(),true,true);
				this->AddInformation(database.GetLanguageText(CounterStrikeTextID),this->item->GetStats().GetCounterStrike(),true,true);
				this->AddInformation(database.GetLanguageText(HPStealTextID),this->item->GetStats().GetHPSteal(),true,true);
				this->AddInformation(database.GetLanguageText(MPStealTextID),this->item->GetStats().GetMPSteal(),true,true);
				this->AddInformation(database.GetLanguageText(HPRegenTextID),this->item->GetStats().GetHPRegen(),true);
				this->AddInformation(database.GetLanguageText(MPRegenTextID),this->item->GetStats().GetMPRegen(),true);

				//Abilities
				for (size_t i = 0; i < this->pointers_get_bool.size(); i++)
				{
					if ((this->item->GetAbility().*this->pointers_get_bool[i])())
						this->AddInformation(database.GetLanguageText(static_cast<LanguageTextID>(AnalyzerTextID + i)));
				}
			}

			//Se não for um Quest Item
			if (!this->item->IsQuestItem())
			{
				//Valor de compra ou venda em Gold do item
				const int gold_value = (!this->is_shop_item) ? this->item->GetSellPrice() : this->item->GetBuyPrice();
				const bool not_enough_gold = (this->is_shop_item) && (!game.GetHero().GoldEnoughToBuy(*this->item));
				this->AddInformation(Convert::NumberToString(gold_value),database.GetLanguageText(GoldTextID),not_enough_gold ? Color::Red : Color::White,not_enough_gold ? Color::Red : Color::Gold);

				//Informações para os cliques
				const Color& color = Color::Cyan;
				if (!this->is_shop_item)
				{
					if (this->item->IsUsable())
						this->NewToolTipTextLine(database.GetLanguageText(RightClickToUseTextID),color);
				}

				//Informações para vender item
				if (ItemButton::shopping)
				{
					//Se não for um item de Shop
					if (!this->is_shop_item)
					{
						//Se não for um botão dos equipamentos (Ou seja só sobra o itens inventário e os itens de batalha, equipamentos não devem ser vendidos diretamente desta forma)
						if (!this->IsEquipmentButton())
							this->NewToolTipTextLine(database.GetLanguageText(ShiftClickToSellTextID),color);
					}
				}
			}

			//Informações de restrição do Quest Item
			else
				this->NewToolTipTextLine(database.GetLanguageText(QuestItemRestrictionTextID),Color::Red);
		}

		//Empty
		else 
		{
			//Se for algum botão de equipamento ou Discard Item para exibir sua descrição simples
			if ((this->IsEquipmentButton()) || (this->item == &game.GetHero().GetDiscardItem()))
				this->NewToolTipTextLine(this->item->GetDescription(),Color::White);
		}
		this->SetDataUpdate(false);
	}
}

void ItemButton::Update(const Input& input,const Timer& timer)
{
	GameRPG& game = *ItemButton::game;

	//Desabilitar qualquer item se for vazio ou se não tiver item pego pelo Mouse
	this->SetEnabled((!this->item->IsEmpty()) || (!game.GetHero().GetPickedItem().IsEmpty()));

	//Se tiver desabilitado, forçar o botão ter sua cor resetada (acontece quando vai vender um item)
	if (!this->GetEnabled())
		this->mouse_entering = false;

	//Perder o foco para fazer a escala do botão ser resetado
	if (!this->mouse_entering)
		this->GainFocus(false);

	//Tipos de item que tem função secundária com o botão direito do Mouse
	const bool secondary_function_item_type = ((this->item->IsUsable()) && (!this->item->IsQuestItem()) && (!this->item->IsEquipment()));

	//Tipos de item que podem ser vendidos
	const bool sellable_item_type = ((this->item->IsUsable()) || (this->item->IsEquipment()) && (!this->IsEquipmentButton()));

	//Tentando vender um item que pode ser vendido
	const bool attempting_to_sell_an_item = (ItemButton::shopping) && ((game.GetInput().IsKeyboardKeyPressed(KeyboardKey::LeftShift) || game.GetInput().IsKeyboardKeyPressed(KeyboardKey::RightShift)) && (sellable_item_type));

	//Habilitar botão direito do Mouse para este botão
	if ((this->is_shop_item) ||	(secondary_function_item_type) || (attempting_to_sell_an_item))
		this->EnableOnMouseClickRight();
	else
		this->DisableOnMouseClickRight();
	
	//Cor especial para a arma de duas mãos da esquerda que na verdade faz referência para a mão direita
	const bool two_handed_weapon_from_left_hand = (this->default_empty_icon == ItemIconLeftHand) && (this->item->IsTwoHandedWeapon());

	//Se os requerimentos não foram atigindos para usar o item ou se for um item de venda do shop e não tiver dinheiro suficiente para comprá-lo ou arma de duas mãos pela mão esquerda
	const Color& color = 
		(!this->item->CheckRequirement(game.GetHero().GetStats().GetLevel())) || 
		((this->is_shop_item) && (!game.GetHero().GoldEnoughToBuy(*this->item))) ? Color::Red : 
		(two_handed_weapon_from_left_hand) ? Color(Color::Red.GetRed(),Color::Red.GetGreen(),Color::Red.GetBlue(),0.5f) : Color::White;

	//Mouse entrou e está por cima do botão
	if (this->mouse_entering)
	{
		//Alterar a cor base de mudança somente no momento que Mouse entrar na região do botão ou o item mudar
		static ColorChanger color_changer;
		if ((!this->color_changing) || (this->item_id_changed != this->item->GetID()))
		{
			//Se for o item vazio colocar um destque de cor diferente aqui, que é somente se o Mouse estiver por cima do botão
			color_changer.SetColorChanger(game.GetTimer(),(!this->item->IsEmpty()) ? color : Color::Yellow,Color::Gray,0.015f,0.25f);
			this->color_changing = true;
		}

		//Mudando a cor gradualmente
		this->SetColor(color_changer.RunColorChanger(game.GetTimer()));
	}
	else
	{
		//Cor sendo resetada
		this->SetColor(color);
		this->color_changing = false;
	}

	//Atualizando para verificar se no próximo loop o item mudou
	this->item_id_changed = this->item->GetID();
}

bool ItemButton::Show(const Input& input,Video& video,const Timer& timer)
{
	//Atualizar dados
	this->DataUpdate();

	//Mostrar os objetos básicos do botão
	return Button::Show(input,video,timer);
}

bool ItemButton::BuyItem()
{
	GameRPG& game = *ItemButton::game;

	//Tem dinheiro suficiente para comprar
	const bool sucess = game.GetHero().BuyItemFromShop(*this->item);
	if (sucess)
	{
		game.GetAudio().PlaySoundFromBuffer(SoundBuySellFileID);
		ItemButton::UpdateAllItemButtons();

		//Houve alteração no Gold então resetar a atualização de cores do ícone do item
		this->color_changing = false;
	}
	else
		game.GetAudio().PlaySoundFromBuffer(SoundErrorFileID);

	return sucess;
}

bool ItemButton::SellItem(Item& item)
{
	GameRPG& game = *ItemButton::game;

	//Item vendido
	const int price = item.GetSellPrice();
	const bool sucess = game.GetHero().SellItemToShop(item);
	if (sucess)
	{
		game.AddTextDynamic<TextDynamicZoom>("+" + Convert::NumberToString(price),Color::Yellow,this->GetX() + (this->GetW() / 2.0f),this->GetY() + (this->GetH() / 2.0f));
		game.GetAudio().PlaySoundFromBuffer(SoundBuySellFileID);
		ItemButton::UpdateAllItemButtons();

		//Houve alteração no Gold então resetar a atualização de cores do ícone do item
		this->color_changing = false;
	}
	else
		game.GetAudio().PlaySoundFromBuffer(SoundErrorFileID);

	return sucess;
}

bool ItemButton::SwapPickedItem()
{
	GameRPG& game = *ItemButton::game;

	//Se tiver algum item associado ao botão ou item pego pelo Mouse
	if ((!this->item->IsEmpty()) || (!game.GetHero().GetPickedItem().IsEmpty()))
	{
		//Atualizando o ícone do item pego pelo Mouse
		game.GetHero().GetPickedItemIcon().SetTexturePosition(this->GetTexturePosition().GetX(),this->GetTexturePosition().GetY());
		game.GetHero().GetPickedItemIcon().SetTexture(this->GetTexture());

		//Trocando o item
		this->item->Swap(game.GetHero().GetPickedItem());
		this->SetDataUpdate(true);
		return true;
	}
	return false;
}

void ItemButton::ItemOnMouseEnter(const Control& control)
{
	this->mouse_entering = true;
}

void ItemButton::ItemOnMouseLeave(const Control& control)
{
	this->mouse_entering = false;
}

void ItemButton::ItemOnMouseClick(const MouseButton mouse_button,const float mouse_x,const float mouse_y,const bool can_put_quest_item,const bool usable_only)
{
	GameRPG& game = *ItemButton::game;

	const bool mouse_click_left_pressed = (mouse_button == MouseButton::Left);
	const bool mouse_click_right_pressed = (mouse_button == MouseButton::Right);
	Item& picked_item = game.GetHero().GetPickedItem();

	//Se não for um item de venda em um Shop
	if (!this->is_shop_item)
	{
		//Tentativa de vender algum item do inventário
		const bool selling_item_from_hero_to_shop = ((ItemButton::shopping) && ((game.GetInput().IsKeyboardKeyPressed(KeyboardKey::LeftShift) || game.GetInput().IsKeyboardKeyPressed(KeyboardKey::RightShift))));

		//Mouse Left Click
		if ((mouse_click_left_pressed) && (!selling_item_from_hero_to_shop))
		{
			//Verificar a condição sobre o item do tipo Quest Item (Ou é o Quest Item ou é outro tipo item)
			const bool quest_item_condition = ((can_put_quest_item) || ((!can_put_quest_item) && (!picked_item.IsQuestItem())));

			//Verificar a condição sobre item do tipo Usable
			const bool usable_condition = (usable_only) ? ((picked_item.IsUsable()) || (picked_item.IsEmpty())) : true;

			if ((quest_item_condition) && (usable_condition))
			{
				this->SwapPickedItem();
				game.GetAudio().PlaySoundFromBuffer(SoundPickItemFileID);
			}
			else
				game.GetAudio().PlaySoundFromBuffer(SoundErrorFileID);
		}

		//Mouse Right Click
		else if ((mouse_click_right_pressed) && (!selling_item_from_hero_to_shop))
		{
			//Se for um Usable
			if (this->item->IsUsable())
				this->ConsumeUsableItem(this->GetX() + (this->GetW() / 2.0f),this->GetY() + (this->GetH() / 2.0f));
		}

		//Vendendo o item com o clique do Mouse
		else if ((selling_item_from_hero_to_shop) && ((mouse_click_left_pressed) || (mouse_click_right_pressed)))
			this->SellItem(*this->item);
	}

	//Item do Shop
	else
	{
		//Clique do Mouse
		if ((mouse_click_left_pressed) || (mouse_click_right_pressed))
		{
			//Se não tiver item pego pelo Mouse
			if (picked_item.IsEmpty())
				this->BuyItem();
			else
			{
				if (mouse_click_left_pressed)
					this->SellItem(picked_item);

				else if (mouse_click_right_pressed)
					this->BuyItem();
			}
		}
	}
}

bool ItemButton::EquipItem(const string& empty_item_tooltip,const bool is_correct_slot)
{
	bool equipped = false;

	GameRPG& game = *ItemButton::game;

	const Item& picked_item = game.GetHero().GetPickedItem();

	FileID sound_file_id = static_cast<FileID>(0);

	//Se não tiver pego item pelo Mouse ou tiver mas deve ser o tipo de equipamento correto e com os requerimentos atendidos
	if (picked_item.IsEmpty() || ((!picked_item.IsEmpty()) && (!game.GetHero().PickedItemRequirementNotMet() && (is_correct_slot))))
	{
		this->SwapPickedItem();

		//Desequipar
		if (this->item->IsEmpty())
		{
			//Equipamento vazio restaurar a descrição simples
			this->item->SetDescription(empty_item_tooltip);
			sound_file_id = SoundPickItemFileID;
		}
		else
			sound_file_id = SoundEquipItemFileID;

		//Item equipado com sucesso
		equipped = true;
		this->SetDataUpdate(true);
	}
	else
		sound_file_id = SoundErrorFileID;

	//Se precisar de tocar algum som
	if (sound_file_id)
		game.GetAudio().PlaySoundFromBuffer(sound_file_id);

	return equipped;
}

bool ItemButton::EquipHand(ItemButton& right_hand,ItemButton& left_hand)
{
	GameRPG& game = *ItemButton::game;

	//Era uma arma de duas mãos equipada
	const bool right_hand_was_two_handed_weapon = right_hand.item->IsTwoHandedWeapon();

	//Se é a mão esquerda
	const bool is_left_hand = (this->item == game.GetHero().GetEquipments()[EquipmentSlotLeftHand].get());

	//Se pode equipar o item pego pelo Mouse considerando que seja a mão esquerda
	const bool can_equip = game.GetHero().CanEquipPickedItemOnHand(is_left_hand);

	//Equipar (ou tentar equipar) o item
	if (this->EquipItem(game.GetDatabase().GetLanguageText(EquipHandTextID),can_equip))
	{
		//Se antes estava equipado uma arma de duas mãos e está tentando equipar algo na mão esquerda
		if ((right_hand_was_two_handed_weapon) && (this == &left_hand))
		{
			//Restaurar mão esquerda (que antes está referenciando a mão direita), desta forma o item equipado na mão esquerda fica na esquerda e não vai para a direita
			left_hand.SetItemButton(*game.GetHero().GetEquipments()[EquipmentSlotLeftHand]);
			left_hand.item->Swap(*right_hand.item);
		}

		//Se a mão esquerda recebeu uma arma de duas mãos
		if (left_hand.item->IsTwoHandedWeapon())
		{
			//Se tiver algo na mão direita, então pegar com o Mouse automaticamente
			if (!right_hand.item->IsEmpty())
				right_hand.SwapPickedItem();

			//Colocar a arma de duas mãos na direita
			right_hand.item->Swap(*left_hand.item);
		}

		//Se a mão da direita for uma arma de duas mãos e a mão esquerda tiver algo
		if ((right_hand.item->IsTwoHandedWeapon()) && (!left_hand.item->IsEmpty()))
		{
			//A arma de duas mãos ocupará as duas mãos, então pegar o que está na mão esquerda e coloca no Mouse automaticamente
			left_hand.SwapPickedItem();
		}

		//Se equipou então atualizar os botões de ambas as mãos
		right_hand.SetDataUpdate(true);
		left_hand.SetDataUpdate(true);
	}
	return can_equip;
}

void ItemButton::ConsumeUsableItem(const float x,const float y)
{
	GameRPG& game = *ItemButton::game;

	StatsBasic& hero_stats = game.GetHero().GetStats().GetStatsBasic();
	StatusNegative& hero_status_negative_change = game.GetHero().GetStats().GetStatusNegativeChange();

	StatsBasic& item_stats = this->item->GetStats();
	StatusNegative& item_status_negative_recovery = this->item->GetStatusNegativeRecovery();

	string text(game.GetDatabase().GetLanguageText(RecoveredTextID));
	Color color(Color::Yellow);

	//HP
	if (item_stats.GetHP())
	{
		hero_stats.SetHP(hero_stats.GetHP() + item_stats.GetHP());
		text = "+" + Convert::NumberToString(item_stats.GetHP());
		color = Color::Green;
	}

	//MP
	if (item_stats.GetMP())
	{
		hero_stats.SetMP(hero_stats.GetMP() + item_stats.GetMP());
		text = "+" + Convert::NumberToString(item_stats.GetMP());
		color = Color::Blue;
	}

	//Wound
	if (item_status_negative_recovery.GetWound())
		hero_status_negative_change.SetWound(0);

	//Slowness
	if (item_status_negative_recovery.GetSlowness())
		hero_status_negative_change.SetSlowness(0);

	//Tiredness
	if (item_status_negative_recovery.GetTiredness())
		hero_status_negative_change.SetTiredness(0);

	//Headache
	if (item_status_negative_recovery.GetHeadache())
		hero_status_negative_change.SetHeadache(0);

	//Blindness
	if (item_status_negative_recovery.GetBlindness())
		hero_status_negative_change.SetBlindness(0);

	//Remover o item
	this->item->Remove();

	//Atualizar o botão do item
	this->SetDataUpdate(true);

	//Tocar o som de recuperação
	game.GetAudio().PlaySoundFromBuffer(SoundUsingRecoveryItemFileID);

	//Adicionar texto dinâmico do item usado
	game.AddTextDynamic<TextDynamicZoom>(text,color,x,y);
}

void ItemButton::UpdateAllItemButtons()
{
	for (size_t i = 0; i < ItemButton::item_buttons_to_update.size(); i++)
		ItemButton::item_buttons_to_update[i]->SetDataUpdate(true);
}

void ItemButton::ClearAllItemButtons()
{
	ItemButton::item_buttons_to_update.clear();
}
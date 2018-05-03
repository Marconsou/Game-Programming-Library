#include "Button.h"

using namespace std;
using namespace GPL;

Button::Button() :
scale(0.90f),
keyboard_key_shortcut(KeyboardKey::Unknown)
{
	this->AddEventOnLeave(&Button::OnLeave,*this);
	this->AddEventOnMouseDown(&Button::OnMouseDown,*this);
	this->AddEventOnMouseUp(&Button::OnMouseUp,*this);
}

void Button::SetKeyboardKeyShortcut(const KeyboardKey keyboard_key_shortcut)
{
	this->keyboard_key_shortcut = keyboard_key_shortcut;
}

KeyboardKey Button::GetKeyboardKeyShortcut() const
{
	return this->keyboard_key_shortcut;
}

const Texture& Button::GetTexture() const
{
	return this->sprite.GetTexture();
}

const Point2D<float>& Button::GetTexturePosition() const
{
	return this->sprite.GetTexturePosition();
}

void Button::SetColor(const Color& color)
{
	this->text.SetColor(color);
	this->sprite.SetColor(color);
}

void Button::SetButton(const float x,const float y,const float w,const float h,const bool centralize)
{
	//Não mostrar o texto
	this->text.Clear();

	//Não mostrar o Sprite
	this->sprite.SetTexture(*static_cast<Texture*>(nullptr));

	this->GetRect().SetPosition(x,y,centralize);
	this->GetRect().SetSize(w,h);
}

void Button::SetButton(const Font& font,const string& string_text,const Color& text_color,const Color& cursor_text_color)
{
	//Texto
	this->text.Clear();
	this->AddText(font,string_text,text_color);

	//Atualiza cursor do texto
	this->cursor_text.ResizeVertices(4);

	const Color color_1(cursor_text_color.GetRed(),cursor_text_color.GetGreen(),cursor_text_color.GetBlue(),0.125f);
	const Color color_2(cursor_text_color.GetRed(),cursor_text_color.GetGreen(),cursor_text_color.GetBlue(),0.439f);

	this->cursor_text.SetVertexColor(0,color_1);
	this->cursor_text.SetVertexColor(1,color_2);
	this->cursor_text.SetVertexColor(2,color_2);
	this->cursor_text.SetVertexColor(3,color_1);
}

void Button::SetButton(const Texture& texture,const float w,const float h,const float texture_position_x,const float texture_position_y)
{
	//Sprite
	this->sprite.SetTexture(texture);
	this->sprite.SetSize(w,h);
	this->sprite.SetTexturePosition(texture_position_x,texture_position_y);
	this->sprite.SetTransformX(this->sprite.GetW() / 2.0f);
	this->sprite.SetTransformY(this->sprite.GetH() / 2.0f);

	//Tamanho do botão
	this->GetRect().SetSize(this->sprite.GetW(),this->sprite.GetH());
}

void Button::SetToolTip(const Font& font,const float edge_distance,const Color& background_color)
{
	this->tooltip.SetToolTip(font,edge_distance,background_color);
}

void Button::AddText(const Font& font,const string& string_text,const Color& color)
{
	if (this->text.GetString().empty())
		this->text.SetText(font,string_text,color);
	else
		this->text.AddText(string_text,color);

	//Atualizar dados
	this->text.SetTransformX(this->text.GetW() / 2.0f);
	this->text.SetTransformY(this->text.GetH() / 2.0f);

	//Se não tiver usando sprite
	if ((&this->sprite.GetTexture() == nullptr))
		this->GetRect().SetSize(this->text.GetW(),this->text.GetH());
}

void Button::AddButtonText(const string& string_text,const Color& color,const bool clear_current_text)
{
	//Limpar o texto antes se necessário
	if (clear_current_text)
		this->text.Clear();

	this->AddText(this->text.GetFont(),string_text,color);
}

void Button::NewToolTipTextLine(const string& string_text,const Color& color,const ToolTipTextAlign text_align)
{
	this->tooltip.NewTextLine(string_text,color,text_align);
}

void Button::AddToolTipTextLine(const string& string_text,const Color& color)
{
	this->tooltip.AddTextLine(string_text,color);
}

void Button::ClearToolTip()
{
	this->tooltip.Clear();
}

void Button::ShowAdditionalContent(const Input& input,Video& video,const Timer& timer)
{
	//Mostrar no lado oposto do botão em relação a tela Y
	const float distance_y = 3.0f;
	const float tooltip_y = (this->GetY() > video.GetVirtualHeight() / 2.0f) ? (this->GetY() - (this->tooltip.GetH() / 2.0f) - distance_y) :
		(this->GetY() + this->GetH() + (this->tooltip.GetH() / 2.0f) + distance_y);

	this->tooltip.SetPosition(this->GetX() + (this->GetW() / 2.0f),tooltip_y,true);
	this->tooltip.ShowToolTip(video);
}

bool Button::Show(const Input& input,Video& video,const Timer& timer)
{
	//Se estiver usando Sprite
	const bool using_sprite = (&this->sprite.GetTexture() != nullptr);

	//Sprite
	if (using_sprite)
	{
		this->sprite.SetPosition(this->GetX(),this->GetY());
		this->sprite.Show(video);
	}

	//Texto
	if (!using_sprite)
		this->text.SetPosition(this->GetX(),this->GetY());
	else
		this->text.SetPosition(this->sprite.GetX() + (this->sprite.GetW() / 2.0f),this->sprite.GetY() + (this->sprite.GetH() / 2.0f),true);

	//Mostrar texto
	this->text.Show(video);

	//Mouse sobre o botão
	if (this->GetMouseHover())
	{
		//Cursor do texto
		if ((this->text.GetValidCharacterTotal() > 0) && (!using_sprite))
		{
			const float x_1 = this->GetX();
			const float y_1 = this->GetY();

			const float x_2 = x_1 + this->GetW();
			const float y_2 = y_1 + this->GetH();

			this->cursor_text.SetVertexPosition(0,x_1,y_1);
			this->cursor_text.SetVertexPosition(1,x_2,y_1);
			this->cursor_text.SetVertexPosition(2,x_1,y_2);
			this->cursor_text.SetVertexPosition(3,x_2,y_2);

			//Mostrar cursor do texto
			video.Draw(this->cursor_text);
		}
	}
	return this->GetMouseHover();
}

void Button::ScaleUpdate(const bool scaled)
{
	const float scale = (scaled) ? this->scale : 1.0f;

	//Texto
	this->text.SetScaleX(scale);
	this->text.SetScaleY(scale);

	//Sprite
	this->sprite.SetScaleX(scale);
	this->sprite.SetScaleY(scale);
}

void Button::OnEnabledChanged(const Control& control)
{
	const bool change = !this->GetEnabled();

	this->text.SetGrayScale(change);
	this->sprite.SetGrayScale(change);

	if (change)
		this->ScaleUpdate(false);
}

void Button::OnLeave(const Control& control)
{
	this->ScaleUpdate(false);
}

void Button::OnMouseDown(const Control& control,const MouseButton mouse_button,const float mouse_x,const float mouse_y)
{
	this->ScaleUpdate(true);
}

void Button::OnMouseUp(const Control& control,const MouseButton mouse_button,const float mouse_x,const float mouse_y)
{
	this->ScaleUpdate(false);
}
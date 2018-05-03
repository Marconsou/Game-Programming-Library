#include "Window.h"

using namespace std;
using namespace GPL;

const Texture* Window::texture(nullptr);
int Window::background_quantity(0);
int Window::pixel_gap(0);
float Window::background_size(0.0f);
float Window::block_size(0.0f);

Window::Window() :
	current_background(0),
	border_index(0),
	edge_distance(0.0f),
	show_border(true),
	background_texture(nullptr),
	background(PrimitiveType::TriangleList,6,8,18)
{
	this->background.SetIndex(0,0);
	this->background.SetIndex(1,1);
	this->background.SetIndex(2,2);

	this->background.SetIndex(3,2);
	this->background.SetIndex(4,3);
	this->background.SetIndex(5,0);

	this->background.SetIndex(6,0);
	this->background.SetIndex(7,3);
	this->background.SetIndex(8,7);

	this->background.SetIndex(9,7);
	this->background.SetIndex(10,3);
	this->background.SetIndex(11,4);

	this->background.SetIndex(12,4);
	this->background.SetIndex(13,5);
	this->background.SetIndex(14,6);

	this->background.SetIndex(15,6);
	this->background.SetIndex(16,7);
	this->background.SetIndex(17,4);
}

void Window::SetCurrentBackground(const int current_background)
{
	this->CheckForDataUpdate(this->current_background,current_background);
	this->current_background = current_background;
}

void Window::SetShowBorder(const bool show_border)
{
	this->CheckForDataUpdate(this->show_border,show_border);
	this->show_border = show_border;
}

const Color& Window::GetColorLeftTop() const
{
	return this->color_left_top;
}

const Color& Window::GetColorRightTop() const
{
	return this->color_right_top;
}

const Color& Window::GetColorLeftBottom() const
{
	return this->color_left_bottom;
}

const Color& Window::GetColorRightBottom() const
{
	return this->color_right_bottom;
}

void Window::SetInnerBlockQuantity(const int inner_block_quantity_w,const int inner_block_quantity_h)
{
	this->CheckForDataUpdate(this->GetInnerBlockQuantityW(),inner_block_quantity_w);
	this->CheckForDataUpdate(this->GetInnerBlockQuantityH(),inner_block_quantity_h);

	//Tamanho calculado da quina do início e fim
	const float total_edge_size = Window::block_size * 2;
	this->GetRect().GetSize().SetX((max(static_cast<float>(inner_block_quantity_w),0.0f) * Window::block_size) + total_edge_size);
	this->GetRect().GetSize().SetY((max(static_cast<float>(inner_block_quantity_h),0.0f) * Window::block_size) + total_edge_size);
}

int Window::GetInnerBlockQuantityW() const
{
	return static_cast<int>((this->GetW() / Window::block_size)) - 2;
}

int Window::GetInnerBlockQuantityH() const
{
	return static_cast<int>((this->GetH() / Window::block_size)) - 2;
}

int Window::GetBlockQuantityW() const
{
	return this->GetInnerBlockQuantityW() + 2;
}

int Window::GetBlockQuantityH() const
{
	return this->GetInnerBlockQuantityH() + 2;
}

void Window::SetWindow(const int inner_block_quantity_w,const int inner_block_quantity_h,const float edge_distance)
{
	this->CheckForDataUpdate(this->background_texture,Window::texture);

	this->SetWindow(inner_block_quantity_w,inner_block_quantity_h,Color::White,Color::White,Color::White,Color::White,edge_distance);
	this->background_texture = Window::texture;
}

void Window::SetWindow(const int inner_block_quantity_w,const int inner_block_quantity_h,const Color& color_left_top,const Color& color_right_top,const Color& color_left_bottom,const Color& color_right_bottom,const float edge_distance)
{
	this->CheckForDataUpdate(this->color_left_top,color_left_top);
	this->CheckForDataUpdate(this->color_right_top,color_right_top);
	this->CheckForDataUpdate(this->color_left_bottom,color_left_bottom);
	this->CheckForDataUpdate(this->color_right_bottom,color_right_bottom);
	this->CheckForDataUpdate<const Texture*>(this->background_texture,nullptr);

	this->SetInnerBlockQuantity(inner_block_quantity_w,inner_block_quantity_h);
	this->edge_distance = edge_distance;
	this->color_left_top = color_left_top;
	this->color_right_top = color_right_top;
	this->color_left_bottom = color_left_bottom;
	this->color_right_bottom = color_right_bottom;
	this->background_texture = nullptr;
}

void Window::SingleBorderUpdate(const float x,const float y,const float border_texture_position_x,const float border_texture_position_y)
{
	Sprite& border = *this->borders[this->border_index];
	this->border_index++;

	border.SetTexture(*Window::texture);
	border.SetSize(Window::block_size,Window::block_size);
	border.SetPosition(x,y);
	border.SetTexturePosition(border_texture_position_x,border_texture_position_y);
}

void Window::LineBorderUpdate(const float border_texture_position_x,const float border_texture_position_y,const bool last_line)
{
	const float x = this->GetX();
	float y = this->GetY();
	float added_y = 0.0f;

	//Última linha
	if (last_line)
	{
		y += this->GetH() - Window::block_size;
		added_y = (Window::block_size * 2);
	}

	//Início
	this->SingleBorderUpdate(x,y,border_texture_position_x,border_texture_position_y + added_y);

	//Meio
	int border;
	const int inner_block_quantity_w = this->GetInnerBlockQuantityW();
	for (border = 1; border <= inner_block_quantity_w; border++)
		this->SingleBorderUpdate(x + (Window::block_size * border),y,border_texture_position_x + Window::block_size,border_texture_position_y + added_y);

	//Fim
	this->SingleBorderUpdate(x + (Window::block_size * border),y,border_texture_position_x + (Window::block_size * 2),border_texture_position_y + added_y);
}

void Window::BackgroundDataUpdate(float& background_texture_position_x,float& background_texture_position_y)
{
	//Multiplica-se por 2 pois é a largura do fundo e a largura da borda
	const float total_width = (Window::background_size + Window::pixel_gap) * 2.0f;

	//Altura do fundo e borda são as mesmas
	const float total_height = Window::background_size + Window::pixel_gap;
	const int window_quantity_x = Window::texture->GetWidth() / static_cast<int>(total_width);
	background_texture_position_x = (total_width * (this->current_background % window_quantity_x));
	background_texture_position_y = total_height * (this->current_background / window_quantity_x);

	if (this->GetDataUpdate())
	{
		//	  (x12,y12)	1--------------2 (x21,y21)
		//             /                \
		//	(x11,y11) 0                  3 (x22,y22)
		//			  |    BACKGROUND	 |
		//	(x11,y42) 7					 4 (x22,y31)
		//             \				/
		//	  (x12,y41) 6--------------5 (xx21,y32)
		const float x = this->GetX();
		const float y = this->GetY();

		//Vertex Position
		float x_1_1 = x;
		float y_1_1 = y + this->edge_distance;

		float x_1_2 = x_1_1 + this->edge_distance;
		float y_1_2 = y;

		float x_2_1 = x_1_1 + this->GetW() - this->edge_distance;
		float y_2_1 = y_1_2;

		float x_2_2 = x_2_1 + this->edge_distance;
		float y_2_2 = y_1_1;

		float y_3_1 = y_2_1 + this->GetH() - this->edge_distance;
		float y_3_2 = y_3_1 + this->edge_distance;
		float y_4_1 = y_1_2 + this->GetH();
		float y_4_2 = y_4_1 - this->edge_distance;

		this->background.SetVertexPosition(0,x_1_1,y_1_1);
		this->background.SetVertexPosition(1,x_1_2,y_1_2);
		this->background.SetVertexPosition(2,x_2_1,y_2_1);
		this->background.SetVertexPosition(3,x_2_2,y_2_2);
		this->background.SetVertexPosition(4,x_2_2,y_3_1);
		this->background.SetVertexPosition(5,x_2_1,y_3_2);
		this->background.SetVertexPosition(6,x_1_2,y_4_1);
		this->background.SetVertexPosition(7,x_1_1,y_4_2);

		//Se estiver usando textura
		this->background.SetTexture(*this->background_texture);
		if (&this->background.GetTexture())
		{
			//Vertex Texture Coordinate
			const float u = background_texture_position_x / this->background.GetTexture().GetWidth();
			const float v = background_texture_position_y / this->background.GetTexture().GetHeight();

			const float uw = (Window::background_size - Window::pixel_gap) / this->background.GetTexture().GetWidth();
			const float vh = Window::background_size / this->background.GetTexture().GetHeight();

			const float edge_distance_u = this->edge_distance / this->background.GetTexture().GetWidth();
			const float edge_distance_v = this->edge_distance / this->background.GetTexture().GetHeight();

			x_1_1 = u;
			y_1_1 = v + edge_distance_v;

			x_1_2 = x_1_1 + edge_distance_u;
			y_1_2 = v;

			x_2_1 = x_1_1 + uw - edge_distance_u;
			y_2_1 = y_1_2;

			x_2_2 = x_2_1 + edge_distance_u;
			y_2_2 = y_1_1;

			y_3_1 = y_2_1 + vh - edge_distance_v;
			y_3_2 = y_3_1 + edge_distance_v;
			y_4_1 = y_1_2 + vh;
			y_4_2 = y_4_1 - edge_distance_v;

			this->background.SetVertexTextureCoordinate(0,x_1_1,y_1_1);
			this->background.SetVertexTextureCoordinate(1,x_1_2,y_1_2);
			this->background.SetVertexTextureCoordinate(2,x_2_1,y_2_1);
			this->background.SetVertexTextureCoordinate(3,x_2_2,y_2_2);
			this->background.SetVertexTextureCoordinate(4,x_2_2,y_3_1);
			this->background.SetVertexTextureCoordinate(5,x_2_1,y_3_2);
			this->background.SetVertexTextureCoordinate(6,x_1_2,y_4_1);
			this->background.SetVertexTextureCoordinate(7,x_1_1,y_4_2);
		}

		//Color
		this->background.SetVertexColor(0,this->color_left_top);
		this->background.SetVertexColor(1,this->color_left_top);
		this->background.SetVertexColor(2,this->color_right_top);
		this->background.SetVertexColor(3,this->color_right_top);
		this->background.SetVertexColor(4,this->color_right_bottom);
		this->background.SetVertexColor(5,this->color_right_bottom);
		this->background.SetVertexColor(6,this->color_left_bottom);
		this->background.SetVertexColor(7,this->color_left_bottom);

		//Se não for mostrar a borda, parar o processo de atualização de dados aqui
		if (!this->show_border)
			this->SetDataUpdate(false);
	}
}

void Window::BorderDataUpdate(const float background_texture_position_x,const float background_texture_position_y)
{
	if (this->GetDataUpdate())
	{
		//3 x 3
		//X >> Inner Blocks
		//WWWWW
		//HXXXH
		//HXXXH
		//HXXXH
		//WWWWW
		this->borders.resize(((this->GetInnerBlockQuantityW() + 2) * 2) + (this->GetInnerBlockQuantityH() * 2));
		this->border_index = 0;

		for (auto& iterator : this->borders)
			iterator = make_unique<Sprite>();

		const float border_texture_position_x = background_texture_position_x + Window::background_size + Window::pixel_gap;
		float border_texture_position_y = background_texture_position_y;

		//Primeira linha
		this->LineBorderUpdate(border_texture_position_x,border_texture_position_y,false);

		//Linhas do meio
		const float x = this->GetX();
		const float y = this->GetY();
		const float inner_block_quantity_h = (this->GetH() - (Window::block_size * 2)) / Window::block_size;
		border_texture_position_y += Window::block_size;

		int border_mid;
		for (border_mid = 1; border_mid <= inner_block_quantity_h; border_mid++)
		{
			//Primeira borda das linhas do meio
			this->SingleBorderUpdate(x,y + (Window::block_size * border_mid),border_texture_position_x,border_texture_position_y);

			//Última borda das linhas do meio
			this->SingleBorderUpdate(x + this->GetW() - Window::block_size,y + (Window::block_size * border_mid),border_texture_position_x + (Window::block_size * 2),border_texture_position_y);
		}

		//Última Linha
		border_texture_position_y -= Window::block_size;
		this->LineBorderUpdate(border_texture_position_x,border_texture_position_y,true);

		//Último processo
		this->SetDataUpdate(false);
	}
}

bool Window::Show(const Input& input,Video& video,const Timer& timer)
{
	//Atualizar dados do fundo
	float background_texture_position_x = 0.0f;
	float background_texture_position_y = 0.0f;
	this->BackgroundDataUpdate(background_texture_position_x,background_texture_position_y);

	//Mostrar o Background
	video.Draw(this->background);

	//Mostrando as bordas
	if (this->show_border)
	{
		//Atualizar dados das bordas
		this->BorderDataUpdate(background_texture_position_x,background_texture_position_y);

		//Mostrar as bordas
		for (size_t i = 0; i < this->borders.size(); i++)
			this->borders[i]->Show(video);
	}
	return false;
}

void Window::OnEnabledChanged(const Control& control)
{
	const bool change = !this->GetEnabled();

	//Background
	this->background.SetGrayScale(change);

	//Border
	for (size_t i = 0; i < this->borders.size(); i++)
		this->borders[i]->SetGrayScale(change);
}

int Window::GetBackgroundTotal()
{
	return Window::background_quantity;
}

float Window::GetBlockSize()
{
	return Window::block_size;
}

void Window::WindowsProperties(const Texture& texture,const int background_quantity,const float background_size,const int pixel_gap)
{
	Window::texture = &texture;
	Window::background_quantity = background_quantity;
	Window::background_size = background_size;
	Window::block_size = background_size / 3.0f;
	Window::pixel_gap = pixel_gap;
}
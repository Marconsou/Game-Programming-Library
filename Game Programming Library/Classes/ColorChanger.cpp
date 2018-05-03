#include "ColorChanger.h"

using namespace GPL;

ColorChanger::ColorChanger(const Color& begin_color,const Color& end_color,const float interval,const float total_time) :
change_color(begin_color),
begin_color(begin_color),
end_color(end_color),
interval(interval),
total_time(total_time)
{

}

void ColorChanger::SetColorChanger(const Timer& timer,const Color& begin_color,const Color& end_color,const float interval,const float total_time)
{
	this->change_color = begin_color;
	this->begin_color = begin_color;
	this->end_color = end_color;
	this->interval.SetInterval(interval);
	this->interval.Synchronize(timer);
	this->total_time = total_time;
	this->interval_elapsed = 0.0f;
	this->run_begin_to_end_color = true;
}

const Color& ColorChanger::RunColorChanger(const Timer& timer)
{
	if (this->interval.Action(timer))
	{
		//Tempo decorrido
		this->interval_elapsed += this->interval.GetInterval();

		//Relação entre o intervalo e o tempo total
		const float color_ratio = this->interval.GetInterval() / this->total_time;

		//Proporção das cores com base no tempo
		const float positive = (this->run_begin_to_end_color) ? 1.0f : -1.0f;
		const float r = (this->end_color.GetRed() - this->begin_color.GetRed()) * color_ratio * positive;
		const float g = (this->end_color.GetGreen() - this->begin_color.GetGreen()) * color_ratio * positive;
		const float b = (this->end_color.GetBlue() - this->begin_color.GetBlue()) * color_ratio * positive;
		const float a = (this->end_color.GetAlpha() - this->begin_color.GetAlpha()) * color_ratio * positive;

		//Atualizando cores
		this->change_color.SetRed(this->change_color.GetRed() + r);
		this->change_color.SetGreen(this->change_color.GetGreen() + g);
		this->change_color.SetBlue(this->change_color.GetBlue() + b);
		this->change_color.SetAlpha(this->change_color.GetAlpha() + a);
	}

	//Hora de trocar a direção de como as cores irão mudar
	if (this->interval_elapsed >= this->total_time)
	{
		//Resetar valor
		this->interval_elapsed = 0.0f;

		//Trocar
		this->run_begin_to_end_color = !this->run_begin_to_end_color;

		//Manter a última cor estável dentro do limite
		if (this->run_begin_to_end_color)
			this->change_color = this->begin_color;
		else
			this->change_color = this->end_color;
	}

	//Retornar a cor mudada
	return this->change_color;
}
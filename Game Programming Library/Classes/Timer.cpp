#include "Timer.h"

using namespace std;
using namespace std::chrono;
using namespace GPL;

const high_resolution_clock::time_point Timer::real_start(high_resolution_clock::now());
vector<Timer*> Timer::sub_timers;

Timer::Timer() :
start_time(Timer::RealTime())
{

}

void Timer::SetStartTime(const float start_time)
{
	this->start_time = Timer::RealTime() - start_time;
}

bool Timer::GetPause() const
{
	return this->pause;
}

float Timer::RealTime()
{
	return duration<float>(duration_cast<milliseconds>(high_resolution_clock::now() - Timer::real_start)).count();
}

float Timer::CurrentTime() const
{
	if (!this->pause)
		return (Timer::RealTime() - this->start_time);
	else
		return this->pause_time;
}

int Timer::CurrentTimeAsMilliseconds() const
{
	return static_cast<int>(this->CurrentTime() * 1000.0f);
}

void Timer::Pause(const bool pause)
{
	if (pause)
	{
		//Pause Time vai manter este valor até a próxima despausa
		if (!this->pause)
			this->pause_time = Timer::RealTime() - this->start_time;
	}
	else
	{
		//Start Time vai recuperar o valor desde a última pausa
		if (this->pause)
			this->start_time = Timer::RealTime() - this->pause_time;
	}

	//Chamado somente pelo Main Timer para (des)pausar todos os Sub Timers
	if (find(Timer::sub_timers.begin(),Timer::sub_timers.end(),this) == Timer::sub_timers.end())
	{
		for (auto iterator : Timer::sub_timers)
			iterator->Pause(pause);
	}

	this->pause = pause;
}

void Timer::AddSubTimer(Timer& sub_timer)
{
	if (find(Timer::sub_timers.begin(),Timer::sub_timers.end(),&sub_timer) == Timer::sub_timers.end())
		Timer::sub_timers.push_back(&sub_timer);
}

void Timer::RemoveSubTimer(Timer& sub_timer)
{
	Timer::sub_timers.erase(remove(Timer::sub_timers.begin(),Timer::sub_timers.end(),&sub_timer),Timer::sub_timers.end());
}

float Timer::FPS(const float update_time)
{
	static float fps{};
	static float frame_counter{};
	static float current_time{};
	static float last_time{};

	//Contador para os frames que serão executados
	frame_counter++;

	//Atualizar o tempo de frame para o tempo atual
	current_time = Timer::RealTime();

	//Intervalo do tempo atual com o tempo do último frame
	const float interval_time = current_time - last_time;

	//Se passou do tempo de atualização
	if (interval_time > update_time)
	{
		//Calculando o FPS com base no intervalo
		fps = frame_counter / interval_time;

		//Atualizar o tempo final deste frame
		last_time = current_time;

		//Resetar o contador de frames
		frame_counter = 0.0f;
	}
	return fps;
}
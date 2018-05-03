#include "Random.h"

using namespace std;
using namespace GPL;

int Random::GenerateNumber(const int min,const int max)
{
	random_device device;
	mt19937 random(device());
	uniform_int_distribution<> distribution(min,max);
	return distribution(random);
}
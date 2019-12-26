#pragma once

#include <random>

namespace random_tool
{
	// Функция, генерирующая псевдослучайное действительное число от min до max
	double random(double min, double max)
	{
		return (double)(rand()) / RAND_MAX*(max - min) + min;
	}
}
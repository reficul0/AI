#pragma once

#include <random>

namespace random_tool
{
	// �������, ������������ ��������������� �������������� ����� �� min �� max
	double random(double min, double max)
	{
		return (double)(rand()) / RAND_MAX*(max - min) + min;
	}
}
#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>

class Tparam
{
	std::vector<double> range;
	int id = 0;
	double val = 0;

	public:

		Tparam(double start, double end, double step);
		Tparam(double start, double end, double step, double value);
		void set_val(int val);
		void info();
		
};

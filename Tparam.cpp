#include "Tparam.hpp"
#include <cstdlib>

using namespace std;

Tparam::Tparam(double start, double end, double step)
{
	for (double i=start; i<end; i=i+step)
	{
		this->range.push_back(i);
	}
}

Tparam::Tparam(double start, double end, double step, double val)
{
	for (double i=start; i<end; i=i+step)
	{
		this->range.push_back(i);
	}
	this->set_val(val);
}

void Tparam::set_val(int val)
{
	double diff = 1e10;
	double temp_val = 0;

	for (int i=0; i<this->range.size();++i)	
	{
		double current_diff = abs(this->range[i] - val);	

		if (current_diff <= diff)
		{
			this->val = range[i];
			this->id = i;
			diff = current_diff;
		}
	}
}

void Tparam::info()
{
	cout << endl;
	cout << "set id: " << this->id << endl;
	cout << "set value: " << this->val << endl;
	cout << endl;
}

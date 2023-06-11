#include <iostream>
#include <math.h>
#include "Tparam.hpp"
#include <bitset>

using namespace std;

unsigned int Tparam::gens_count = 0;

Tparam::Tparam(double x_start, double x_end, double dx) : name {""}, description {""}, val_id {0}
{
	gens_count++;
	_id = gens_count;
	set_range(x_start, x_end, dx);
	set_rand_val();
}

Tparam::Tparam(double x_start, double x_end, double dx, double val) : Tparam::Tparam(x_start, x_end, dx)
{
	val_id = get_val_id(val);
}

Tparam::Tparam(std::string name, std::string description, double x_start, double x_end, double dx) : Tparam::Tparam(x_start, x_end, dx)
{
	this -> name = name;
	this -> description = description;
}

Tparam::Tparam(const Tparam &kopia)
{
	this -> name = kopia.name;
	this -> description = kopia.description;
	this -> x_start = kopia.x_start;
	this -> x_end = kopia.x_end;
	this -> dx = kopia.dx;
	
	set_rand_val();
	val_id += 1;
}

void Tparam::set_range(double x_start, double x_end, double dx)
{
	this -> x_start = x_start;
	this -> x_end = x_end;
	this -> dx = dx;
}

void Tparam::set_rand_val()
{
	int vals_count = fabs(x_end - x_start) / dx + 1;
	val_id = rand() % vals_count;
}

int Tparam::get_val_id(double val)
{
	if (val < x_start) return 0;
	else if (val > x_end) return (x_end - x_start) / dx;
	else 
	{
		double x = x_start;
		int _id = 0;
		while (fabs(x + _id * dx - val) > dx / 2) _id++;
		return _id;
	}
}

std::string Tparam::doubleToBinary(double value) {
    unsigned long long* ptr = reinterpret_cast<unsigned long long*>(&value);
    std::bitset<64> bits(*ptr);
    return bits.to_string();
}

double Tparam::binaryToDouble(const std::string& binary) {
    std::bitset<64> bits(binary);
    unsigned long long binaryValue = bits.to_ullong();

    double* valuePtr = reinterpret_cast<double*>(&binaryValue);
    return *valuePtr;
}

std::string Tparam::get_bval()
{
	double val = get_val();
	std::string bval = doubleToBinary(val);
	return bval;
}

void Tparam::info()
{
	cout << "++++++++++++++++++++++++\n";
	cout << "++ Parameter : " << name << ": " << description << "\n";
	cout << "++ \n";
	cout << "++ range: \n";
	cout << "++ - start value: " << x_start << "\n";
	cout << "++ - end value: " << x_end << "\n";
	cout << "++ - step: " << dx << "\n";
	cout << "++ \n";
	cout << "++ Present value: " << get_val() << "\n";
	cout << "++ Present val_id: " << val_id << "\n";
	cout << "++++++++++++++++++++++++\n\n";
}

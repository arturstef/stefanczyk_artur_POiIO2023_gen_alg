#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <string>

class Tparam
{
	private:
		static unsigned int gens_count;
		unsigned int _id;

		std::string name, description;
		double x_start, x_end, dx;
		int val_id;

	public:

		Tparam(double x_start, double x_end, double dx, double val);
		Tparam(double x_start, double x_end, double dx);

		Tparam(std::string name, std::string description, double x_start, double x_end, double dx);
		Tparam(const Tparam &kopia);

		~Tparam();

		std::string get_name() { return name; }
		std::string get_description() { return description; }

		double get_x_start() const { return x_start; }
		double get_x_end() const { return x_end; }
		double get_dx() const { return dx; }

		void set_range(double x_start, double x_end, double dx);

		void set_rand_val();

		void set_val(double val)
		{
			val_id = this->get_val_id(val);
		}
		double get_val() const { return x_start + val_id * dx; }
		void info();

	private:

		int get_val_id(double val);
};

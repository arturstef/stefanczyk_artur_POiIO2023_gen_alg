#include <iostream>
#include <math.h>
#include "Tcandidate.hpp"

using namespace std;

unsigned int Tcandidate::candidates_count = 0;

Tcandidate::Tcandidate(int num) : gens_count { num }
{
	_id = candidates_count;
	candidates_count++;
	init_vector();
	mark = 0;
	rand_gens_val();
	set_gens_names();
}

Tcandidate::Tcandidate(const Tcandidate &kopia) : gens_count { kopia.gens_count }
{
	_id = candidates_count;
	candidates_count++;
	init_vector();
	for (int i=0;i < kopia.gens_count; ++i)
	{
		double gen_val = kopia.genotype[i].get_val();
		
		double x_start = kopia.genotype[i].get_x_start();
		double x_end = kopia.genotype[i].get_x_end();
		double dx = kopia.genotype[i].get_dx();
		genotype[i].set_range(x_start,x_end,dx)	;

		genotype[i].set_val(gen_val);
	}
	set_gens_names();
	mark = kopia.mark;
}

void Tcandidate::rand_gens_val()
{
	for (int i = 0; i < gens_count; ++i)
	{
		genotype[i].set_rand_val();
	}
}

void Tcandidate::info()
{
	cout << "++++++++ CANDIDATE ++++++++\n";
	cout << "++ gens count: " << gens_count << "\n";

	for (int i = 0; i < gens_count; ++i)
	{
		cout << "++ " << genotype[i].get_name() << ": " << genotype[i].get_val() << "\n";
	} 
	cout << "++ \n";
	cout << "++ rate: " << mark << "\n";
	cout << "++++++++++++++++++++++++++\n";
}

void Tcandidate::init_vector()
{
	for (int i=0; i < gens_count; ++i)
	{
		genotype.push_back(Tparam {0,10,1});
	}
}

void Tcandidate::set_gens_names()
{
	for (int i=0;i<gens_count;++i)
	{
		string nazwa = "osobnik";
		nazwa += to_string(_id);
		nazwa += "_gen"	;
		nazwa += to_string(i);
	}
}

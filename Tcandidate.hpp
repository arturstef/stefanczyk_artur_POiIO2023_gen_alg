#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>

#include "Tparam.hpp"

class Tcandidate
{
	protected:
		static unsigned int candidates_count;
		unsigned int _id;
		const int gens_count = 2;
		std::vector<Tparam> genotype;
		double mark = 0;
	public:
	
		Tcandidate(int gens_count=0);
		Tcandidate(const Tcandidate &kopia);

//		virtual ~Tcandidate();
		virtual Tcandidate* create() { return new Tcandidate {}; } 
		virtual Tcandidate* create_copy() { return new Tcandidate {}; }

		double get_mark() { return mark; }
		virtual void rate() {}  
		void info();

		void replace_genotype(std::vector<Tparam> genotype)
 { this -> genotype.clear(); this -> genotype.swap(genotype); }				
		std::vector<Tparam> get_genotype() { return genotype; }
	protected:

		void rand_gens_val();
		void init_vector();
		void set_gens_names();
		virtual void set_range() {} 
};

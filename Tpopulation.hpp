#pragma once
#include <iostream>
#include <vector>

#include "Tcandidate.hpp"
#include "Tparam.hpp"

class Tpopulation 
{
	static unsigned int _id;
	unsigned int candidates_count;

	Tcandidate* candidate_pattern = nullptr;
	std::vector<Tcandidate*> candidates;
	double best_val = 0;

	public:
		
		Tpopulation();
		Tpopulation(const Tpopulation &pattern);
		void calculate();
		Tcandidate* get_best_candidate();

		Tpopulation* create_new() { return new Tpopulation(*this); }

		unsigned int get_id() { return _id; }
		unsigned int get_candidates_count() { return candidates_count; }
		double get_best_val() { return best_val; }

		void info();

	private:
		void init();
};

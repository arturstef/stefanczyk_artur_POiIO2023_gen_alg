#pragma once
#include <iostream>
#include <vector>

#include "Tcandidate.hpp"
#include "Tparam.hpp"
#include "Tpopulation.hpp"

class Talgorithm 
{

	unsigned int candidates_count;
	unsigned int max_population_count;
	unsigned int min_improvement_proc;
	unsigned int current_population;
	Tpopulation * wsk_population_pres = nullptr;
	Tpopulation * wsk_population_prev = nullptr;

	public:
		
		Talgorithm(unsigned int max_population_count = 20, unsigned int min_improvement_proc = 3);
		~Talgorithm();
		void run();
	private:
		bool is_stop();
};

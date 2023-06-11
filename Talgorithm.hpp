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
	const double cross_coef = 0.8;
	const double mutation_coef = 0.4;
	Tpopulation * wsk_population_pres = nullptr;
	Tpopulation * wsk_population_prev = nullptr;

	public:
		Talgorithm(unsigned int max_population_count = 20, unsigned int min_improvement_proc = 3);
		std::vector<Tcandidate*> sampleVector(const std::vector<Tcandidate*>& objects, std::vector<double>& probabilities);
		void pick_parents(const std::vector<Tcandidate*>& candidates, std::vector<Tcandidate*>& parents); 

		std::string combine_binary(const std::string& num1, const std::string& num2); 
		double binaryToDouble(const std::string& binary);
		int get_cut_index(int min, int max); 

		~Talgorithm();
		void run();
		void roullet();
		void cross();
		void mutate();
	private:
		bool is_stop();
};

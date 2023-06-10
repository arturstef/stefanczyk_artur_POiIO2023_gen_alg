#include <iostream>
#include <math.h>
#include <vector>
#include <random>
#include <numeric>
#include <algorithm>

#include "Talgorithm.hpp"

using namespace std;

Talgorithm::Talgorithm(unsigned int max_population_count, unsigned int min_improvement_proc)
{
	this->max_population_count = max_population_count;
	this->min_improvement_proc = min_improvement_proc;

	wsk_population_pres = new Tpopulation {};
}

Talgorithm::~Talgorithm()
{
	delete wsk_population_pres;
	delete wsk_population_prev;
	cout << "\nmemory cleared\n";
}

void Talgorithm::run()
{
	while (!wsk_population_prev || !is_stop())
	{
		wsk_population_pres -> calculate();
		cout << "++ Population #" << (*wsk_population_pres).get_id() << " best result: " << (*wsk_population_pres).get_best_val() << "\n";

		unsigned int candidates_count = (*wsk_population_pres).get_candidates_count();

		wsk_population_pres -> info();	

		delete wsk_population_prev;
		wsk_population_prev = wsk_population_pres;
		wsk_population_pres = new Tpopulation { *wsk_population_prev };
		roullet();
		cross();
	}
	cout << endl << "++++++ BEST CANDIDATE ++++++" << endl;
	wsk_population_prev->get_best_candidate()->info();
}

bool Talgorithm::is_stop()
{
	bool bool_stop_population_max = 0;
	bool bool_stop_improvement_min = 0;

	if (!wsk_population_prev)
	{
		bool_stop_population_max = ((*wsk_population_pres).get_id() >= max_population_count);
	} else {
		double population_val = (*wsk_population_pres).get_best_val();
		double population_prev_val = (*wsk_population_prev).get_best_val();
		unsigned int error = fabs(population_prev_val - population_val) / population_prev_val * 100;

		bool_stop_population_max = ( (*wsk_population_pres).get_id() >= max_population_count);
		bool_stop_improvement_min = (error < min_improvement_proc);
	}
	return bool_stop_population_max || bool_stop_improvement_min;
}
std::vector<Tcandidate*> Talgorithm::sampleVector(const std::vector<Tcandidate*>& objects, std::vector<double>& probabilities) {
    double sum = std::accumulate(probabilities.begin(), probabilities.end(), 0.0);
    
    for (auto& prob : probabilities) {
        prob /= sum;
    }
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> distribution(probabilities.begin(), probabilities.end());
    
    std::vector<Tcandidate*> result;
    result.reserve(objects.size());
    
    for (size_t i = 0; i < objects.size(); ++i) {
        int index = distribution(gen);
        result.push_back(objects[index]);
    }
    
    return result;
}
void Talgorithm::roullet()
{
	double cummulative_cost = 0;
	double mark = 0;
	vector<double> candidate_cost;
	candidate_cost.clear();
	vector<Tcandidate*> candidates = wsk_population_prev -> get_candidates();
	for (int i=0;i<wsk_population_prev -> get_candidates_count();++i)
	{
		mark = candidates[i] -> get_mark();
		cummulative_cost += mark;
		candidate_cost.push_back(mark);
	}
	for (int i=0;i<wsk_population_prev -> get_candidates_count();++i)
	{
		candidate_cost[i] = candidate_cost[i] / cummulative_cost;
	}
	vector<Tcandidate*> chosen_candidates = sampleVector(candidates, candidate_cost);	
	wsk_population_pres -> replace_candidates(chosen_candidates);
}

void Talgorithm::cross()
{
	vector<Tcandidate*> candidates = wsk_population_pres -> get_candidates();
	// cout << endl << candidates.size() << endl;	
	vector<Tcandidate*> mut_candidates(candidates.size());
	
	std::copy(candidates.begin(), candidates.end(), mut_candidates.begin());

	vector<Tcandidate*> parents;
	std::vector<Tparam> new_genotype;
		
	for (int i=0;i<candidates.size();++i)
	{
		// cout << endl << "i: " << i << endl;
		new_genotype.clear();
		parents.clear();
		pick_parents(candidates, parents);
		std::vector<Tparam> genotype1 = parents[0] -> get_genotype();
		std::vector<Tparam> genotype2 = parents[1] -> get_genotype();
		
		for (int ii=0;ii<parents[0]->get_genotype().size();++ii)
		{
			// cout << endl << "ii: " << ii << endl;
			std::string new_gen_value_binary = combine_binary(genotype1[ii].get_bval(), genotype2[ii].get_bval());
			double new_gen_value = binaryToDouble(new_gen_value_binary);
			// cout << endl << new_gen_value << endl;
			Tparam new_gen { genotype1[ii] };
			new_gen.set_val(new_gen_value);
			new_genotype.push_back(new_gen);	
		}	
		// TODO	
		mut_candidates[i] -> replace_genotype(new_genotype);
	}
	wsk_population_pres -> replace_candidates(mut_candidates);
}

void Talgorithm::pick_parents(const std::vector<Tcandidate*>& candidates, std::vector<Tcandidate*>& selectedElements) {
    
	std::vector<Tcandidate*> shuffledCandidates = candidates;

	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(shuffledCandidates.begin(), shuffledCandidates.end(), g);

	selectedElements.push_back(shuffledCandidates[0]);
	selectedElements.push_back(shuffledCandidates[1]);
}

std::string Talgorithm::combine_binary(const std::string& num1, const std::string& num2) {

    int cut_index = get_cut_index(1, num1.length() - 1); 

    std::string firstPart = num1.substr(0, cut_index);
    std::string secondPart = num2.substr(cut_index);

    return firstPart + secondPart;
}

int Talgorithm::get_cut_index(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(gen);
}

double Talgorithm::binaryToDouble(const std::string& binary) {
    std::bitset<64> bits(binary);
    unsigned long long binaryValue = bits.to_ullong();

    double* valuePtr = reinterpret_cast<double*>(&binaryValue);
    return *valuePtr;
}



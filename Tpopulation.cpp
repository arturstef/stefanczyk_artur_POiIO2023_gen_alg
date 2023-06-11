#include <iostream>
#include <algorithm>
#include "Tpopulation.hpp"

#include "TcandidateID0Gens2Zad1.hpp"
#include "TcandidateID0Gens2Zad2.hpp"
#include "TcandidateID0Gens2Zad3.hpp"
#include "TcandidateID0Gens2Zad4.hpp"

using namespace std;

unsigned int Tpopulation::_id = 0;

Tpopulation::Tpopulation()
{
	_id++;
	init();
	best_val = 0;
	for (unsigned int i=0;i<candidates_count;++i)
	{
		this->candidates.push_back(candidate_pattern -> create());
	}
}

Tpopulation::Tpopulation(const Tpopulation &pattern)
{
	_id++;
	candidates_count = pattern.candidates_count;
	candidate_pattern = pattern.candidate_pattern;
	best_val = 0;
	for (unsigned int i=0;i<candidates_count;++i)
	{
		this->candidates.push_back(candidate_pattern -> create());
	}
}


void Tpopulation::calculate()
{
	double best_val = 0;
	for (int i=0;i<candidates_count;++i)
	{
		candidates[i] -> rate();
		double val = candidates[i] -> get_mark();
		if (i) best_val = max(best_val, val);
		else best_val = val;
	}
	this -> best_val = best_val;
}

void Tpopulation::info()
{
	cout << "++++++ POPULATION ++++++\n";
	
	for (int i=0;i < candidates_count; ++i)
	{
		cout << "++ candidate#" << i << ": " << candidates[i] -> get_mark() << "\n";
	}
	cout << "++++++++++++++++++++++++\n";
}

Tcandidate* Tpopulation::get_best_candidate()
{
	int i = 0;
	while (candidates[i] -> get_mark() != best_val) i++;
	return candidates[i];
}

void Tpopulation::init()
{
	unsigned int candidate_id;
	cout << "Podaj id osobnika(0-3): ";
	cin >> candidate_id;
	
	if (candidate_id < 0 || candidate_id > 2)
		candidate_id = 0;
	
	switch (candidate_id)
	{
		case 0:
			candidate_pattern = new TcandidateID0Gens2Zad1 {};
			break;
		case 1:
			candidate_pattern = new TcandidateID0Gens2Zad2 {};
			break;
		case 2:
			candidate_pattern = new TcandidateID0Gens2Zad3 {};
			break;
		case 3:
			candidate_pattern = new TcandidateID0Gens2Zad4 {};
			break;
		default:
			candidate_pattern = new TcandidateID0Gens2Zad1 {};
			break;
	}

	unsigned int count;
	cout << "Podaj liczbę osobników w populacji: ";
	cin >> count;
	
	if (count % 2)
		count++;
	candidates_count = count;
}

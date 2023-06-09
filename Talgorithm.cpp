#include <iostream>
#include <math.h>

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

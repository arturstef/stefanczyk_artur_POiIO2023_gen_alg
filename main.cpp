#include <iostream>
#include <vector>
#include <stdlib.h>
#include <ctime>

#include "Tparam.hpp"
#include "Tcandidate.hpp"
#include "Tpopulation.hpp"
#include "Talgorithm.hpp"

using namespace std;

int main()
{
	srand(time(NULL));

	Talgorithm task {20,0};
	task.run();
}

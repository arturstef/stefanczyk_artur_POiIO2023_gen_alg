#include <iostream>
#include <vector>

#include "Tparam.hpp"

using namespace std;


int main()
{
	Tparam param1(1,4,1,2);
	param1.info();

	Tparam param2(0,10,0.5);
	param2.set_val(2);
	param2.info();

	param1.set_val(5);
	param1.info();

	param2.set_val(2.3);
	param2.info();

	return 0;
}



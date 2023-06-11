#ifndef TCANDIDATEID0GENS2ZAD4_H
#define TCANDIDATEID0GENS2ZAD4_H_

#include "Tcandidate.hpp"

class TcandidateID0Gens2Zad4 : public Tcandidate
{
    public:
        TcandidateID0Gens2Zad4() : Tcandidate(2)
	{
		set_range();
	}
	TcandidateID0Gens2Zad4(const TcandidateID0Gens2Zad4 &kopia) : Tcandidate(kopia) {}
	
	Tcandidate* create()
	{
		return new TcandidateID0Gens2Zad4();
	}

	Tcandidate* create_copy()
	{
		return new TcandidateID0Gens2Zad4(*this);
	}

        void rate()
        {
            double x1 = genotype[0].get_val();
            double x2 = genotype[1].get_val();

            mark = 2*(-x1*x1*x1 + x2*x1);
        }
	protected: 
		void set_range()
		{
			genotype[0].set_range(0,10,1);
			genotype[1].set_range(11,20,1);
		}
};
#endif

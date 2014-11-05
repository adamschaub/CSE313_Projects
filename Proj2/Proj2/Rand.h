// Rand.h: interface for the CRand class. 
//
//////////////////////////////////////////////////////////////////////

#pragma once

// the class for random number generator
class CRand  
{
public:
	CRand(){};
	virtual ~CRand(){};

	void setSeed(unsigned int s) {
		srand(s);
	}

	// uniform random number between [0, 1]
	double randu(){
		return (rand()/((double)RAND_MAX + 1));
	}

	// gaussian random number: between (-0.5, 0.5), near 0;
	double randg(){
		
		double x, y;
		double pi,r1,r2;
		double ranf();

		pi =  4*atan(1.0);
		r1 = -log(1-randu()); 
		r2 =  2*pi*randu();
		r1 =  sqrt(2*r1);
		x  = r1*cos(r2);
		y  = r1*sin(r2);
		return x/2;
	}

};



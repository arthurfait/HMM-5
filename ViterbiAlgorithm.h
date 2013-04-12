/*
 * ViterbiAlgorithm.h
 *
 *  Created on: Mar 14, 2013
 *      Author: ranjit
 */


#ifndef VITERBIALGORITHM_H_
#define VITERBIALGORITHM_H_

#include <vector>
#include <map>
using namespace std;

class ViterbiAlgorithm {
public:
	//variables
	struct Cell {
		double value;
		int maxCell;
	};
	int numStates;
	int numOutSymbols;
	vector<double> pi;
	vector<vector<double> > a;
	vector<char> outAlpha;
	vector<map<char, double> > b;
	vector<char> charSequence;
	vector<vector<Cell> > v;

	//methods
	ViterbiAlgorithm();
	void initialize();
	void induction();
	double termination();
	string backTracking();
	virtual ~ViterbiAlgorithm();
};

#endif /* VITERBIALGORITHM_H_ */

/*
 * ViterbiAlgorithm.cpp
 *
 *  Created on: Mar 14, 2013
 *      Author: ranjit
 */
#include <iostream>
#include <sstream>
#include "ViterbiAlgorithm.h"

using namespace std;

ViterbiAlgorithm::ViterbiAlgorithm() {
	numStates = 0;
	numOutSymbols = 0;
}

void ViterbiAlgorithm::initialize() {
	v.resize(charSequence.size());
	for(unsigned int t = 0; t < charSequence.size(); t++) {
		v[t].resize(numStates);
		for(int i = 0; i < numStates; i++) {
			Cell c = {-1, -1};
			v[t][i] = c;
		}
	}
	for(int j = 0; j < numStates; j++) {
		Cell c = {pi[j] * b[j].at(charSequence[0]), -1};
		v[0][j] = c;
	}
}

void ViterbiAlgorithm::induction() {
	for(unsigned int t = 1; t < charSequence.size(); t++) {
		for(int j = 0; j < numStates; j++) {
			double maxValue = 0;
			int maxValueState = 0;
			for(int i = 0; i < numStates; i++) {
				double cellValue = v[t-1][i].value * a[i][j];
				if(cellValue > maxValue) {
					maxValue = cellValue;
					maxValueState = i;
				}
			}
			v[t][j].value = maxValue * b[j].at(charSequence[t]);
			v[t][j].maxCell = maxValueState;
		}
	}
}

double ViterbiAlgorithm::termination() {
	double maxValue = 0;
	for(int i = 0; i < numStates; i++) {
		if(v[charSequence.size() - 1][i].value > maxValue)
			maxValue = v[charSequence.size() - 1][i].value;
	}
	return maxValue;
}

string ViterbiAlgorithm::backTracking() {
	double maxValue = 0;
	int maxState = 0;
	for(int i = 0; i < numStates; i++) {
		if(v[charSequence.size() - 1][i].value > maxValue) {
			maxValue = v[charSequence.size() - 1][i].value;
			maxState = i;
		}
	}

	ostringstream ss;
	ss << maxState;
	string mostLikelySeq = ss.str();
	for(unsigned int i = 0; i < charSequence.size() - 1; i++) {
		ostringstream ss;
		ss << v[charSequence.size() - i - 1][maxState].maxCell;
		mostLikelySeq = ss.str() + mostLikelySeq;
		maxState = v[charSequence.size() - i - 1][maxState].maxCell;
	}
	return mostLikelySeq;
}

ViterbiAlgorithm::~ViterbiAlgorithm() {
}

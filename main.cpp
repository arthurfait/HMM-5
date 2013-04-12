/*
 * main.cpp
 *
 *  Created on: Mar 14, 2013
 *      Author: ranjit
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "ViterbiAlgorithm.h"

using namespace std;

ViterbiAlgorithm V;
vector<vector<char> > charSequences;

//read input from the files and populate data
void readInput(char* inputfile) {
	ifstream infile(inputfile);

	//num states
	infile >> V.numStates;

	//initial state probabilities;
	V.pi.resize(V.numStates);
	for(int i = 0; i < V.numStates; i++) {
		infile >> V.pi[i];
	}

	//transition probabilities
	V.a.resize(V.numStates);
	for(int i = 0; i < V.numStates; i++) {
		V.a[i].resize(V.numStates);
		for(int j = 0; j < V.numStates; j++) {
			infile >> V.a[i][j];
		}
	}

	//outputDis
	infile >> V.numOutSymbols;
	V.outAlpha.resize(V.numOutSymbols);
	for(int i = 0; i < V.numOutSymbols; i++) {
		infile >> V.outAlpha[i];
	}

	double prob;
	V.b.resize(V.numStates);
	for(int i = 0; i < V.numStates; i++) {
		for(int j = 0; j < V.numOutSymbols; j++) {
			infile >> prob;
			V.b[i].insert(pair<char, double>(V.outAlpha[j], prob));
		}
	}
	infile.close();
}

void readTest(char* testfile) {
	ifstream tefile(testfile);
	//char sequence
	int count = 0;
	while(!tefile.eof()) {
		string line;
		getline(tefile, line);
		if(line != "") {
			charSequences.resize(count + 1);
			stringstream lineStream(line);
			char c;
			while(lineStream >> c)
				charSequences[count].push_back(c);
			count++;
		}
	}
	tefile.close();
}

int main(int argc, char* argv[]) {
	readInput(argv[1]);
	readTest(argv[2]);
	for(unsigned int i = 0; i < charSequences.size(); i++) {
		V.charSequence = charSequences[i];
		V.initialize();
		V.induction();
		double prob = V.termination();
		string seq = V.backTracking();
		cout << "MLS: " << seq << endl;
	}
	return 0;
}



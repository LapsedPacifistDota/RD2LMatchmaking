/*
 * interativeOptimalMatchmaker.h
 *
 *  Created on: Jun 4, 2015
 *      Author: user
 */

#ifndef INTERATIVEOPTIMALMATCHMAKER_H_
#define INTERATIVEOPTIMALMATCHMAKER_H_

#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <time.h>

using std::vector;
using namespace std;

class interativeOptimalMatchmaker
{
public:
	interativeOptimalMatchmaker(vector<vector<double>> MMS, const int &NumTeams);
	virtual ~interativeOptimalMatchmaker();
	void calculateOptimalMatchups();

	vector<vector<int>> m_matchupWithSideAssigned;
	vector<int> m_matchups;
	double m_bestScore;

private:

	void initializeMatchups();
	double calculateScore(const vector<vector<double>> &MMS,const vector<int> &matchup);
	void matchupPermuation(vector<int> &matchup);
	void assignSide();

	vector<vector<double>> m_MMS;
	unsigned int m_NumTeams;
	unsigned int m_NumTeamsHalved;
	unsigned long m_maxIters;

};

#endif /* INTERATIVEOPTIMALMATCHMAKER_H_ */

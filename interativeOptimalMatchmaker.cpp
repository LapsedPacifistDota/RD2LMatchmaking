/*
 * interativeOptimalMatchmaker.cpp
 *
 *  Created on: Jun 4, 2015
 *      Author: user
 */

#include "interativeOptimalMatchmaker.h"

interativeOptimalMatchmaker::interativeOptimalMatchmaker(vector<vector<double>> MMS, const int &NumTeams)
{
	/* initialize random seed: */
	srand (time(NULL));

	m_NumTeams = NumTeams;
	m_NumTeamsHalved = m_NumTeams/2;
	m_MMS = MMS;
	m_maxIters = m_NumTeams*(10e5);
	m_matchupWithSideAssigned.resize(m_NumTeamsHalved);
	for (int counter=0; counter < m_NumTeamsHalved; counter++)
	{
		m_matchupWithSideAssigned[counter].resize(2);
	}
	initializeMatchups();
	m_bestScore = calculateScore(m_MMS,m_matchups);
}

void interativeOptimalMatchmaker::calculateOptimalMatchups()
{
	vector<int> hypothesisMatchups;
	double hypothesisScore;
	unsigned int counter = 0;
	while((counter < m_maxIters)&&(m_bestScore > 0.1))
	{
		hypothesisMatchups = m_matchups;

		matchupPermuation(hypothesisMatchups);

		hypothesisScore = calculateScore(m_MMS,hypothesisMatchups);

		if (hypothesisScore < m_bestScore)
		{
			m_matchups = hypothesisMatchups;
			m_bestScore = hypothesisScore;
			cout<<"new Best Score: "<<m_bestScore<<" at "<<counter<<endl;
		}

		counter++;
	}
	assignSide();

}

void interativeOptimalMatchmaker::initializeMatchups()
{
	//size matchups
	m_matchups.resize(m_NumTeams); //NumTeams should be even

	//randomize starting matchups
	for (int counter=0; counter < m_NumTeamsHalved; counter++)
	{
		m_matchups[2*counter] = 2*counter+1;
		m_matchups[2*counter+1] = 2*counter;
	}
	//std::random_shuffle(m_matchups.begin(), m_matchups.end());
	for (int counter = 0; counter < 5; counter++)
	{
		matchupPermuation(m_matchups);
	}

}

void interativeOptimalMatchmaker::assignSide()
{

	vector<bool> usedMask;
	usedMask.resize(m_NumTeams);
	int teamMatchupsIndex = 0;

	for (int counter = 0; counter < m_NumTeams;counter++)
	{
		usedMask[counter]=false;
	}

	for(int counter = 0; counter< m_NumTeams;counter++)
	{

		if (usedMask[counter]==false)
		{
			int randInt = rand() % 10;
			if (randInt >= 5)
			{
				m_matchupWithSideAssigned[teamMatchupsIndex][0] = counter;
				m_matchupWithSideAssigned[teamMatchupsIndex][1] = m_matchups[counter];
			}
			else
			{
				m_matchupWithSideAssigned[teamMatchupsIndex][0] = m_matchups[counter];
				m_matchupWithSideAssigned[teamMatchupsIndex][1] = counter;
			}
			teamMatchupsIndex++;
			usedMask[counter] = true;
			usedMask[m_matchups[counter]] = true;
		}

	}
}

double interativeOptimalMatchmaker::calculateScore(const vector<vector<double>> &MMS,const vector<int> &matchup)
{
	double hypothesisScore = 0;
	for (int counter = 0; counter<m_NumTeams;counter++)
	{
		hypothesisScore += MMS[counter][matchup[counter]];
	}
	hypothesisScore = hypothesisScore/2; //Divide by 2 since we're double counting each matchup's score.
	//cout<<"hypothesisScore: "<<hypothesisScore<<endl;
	return hypothesisScore;
}

interativeOptimalMatchmaker::~interativeOptimalMatchmaker()
{
	// TODO Auto-generated destructor stub
}

void interativeOptimalMatchmaker::matchupPermuation(vector<int> &matchup)
{
	//Swap 4 teams matchups randomly
	int teamAIndex = rand() % m_NumTeams;
	int teamAMatchIndex,teamBMatchIndex;
	int teamBIndex = rand() % m_NumTeams;

	//If they're the same number no reason to waste an iteration, pick a new B.
	if (teamAIndex == teamBIndex)
	{
		teamBIndex = (teamBIndex+1) % m_NumTeams;
	}

	teamAMatchIndex = matchup[teamAIndex];

	//Are A and B matched with each other?  If so, pick a new B.
	if (teamAMatchIndex == teamBIndex)
	{
		teamBIndex = (teamBIndex+1) % m_NumTeams;
	}
	teamBMatchIndex = matchup[teamBIndex];

	//Assign the new matchups
	matchup[teamAIndex] = teamBMatchIndex;
	matchup[teamBIndex] = teamAMatchIndex;
	matchup[teamAMatchIndex] = teamBIndex;
	matchup[teamBMatchIndex] = teamAIndex;
}



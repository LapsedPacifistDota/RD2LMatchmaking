/*
 * RD2LMatchmakingSolver.cpp
 *
 *  Created on: Jun 4, 2015
 *      Author: user
 */

#include "RD2LMatchmakingSolver.h"

using namespace std;

vector<vector<double>> setupTestInputs(int &NumTeams);
vector<vector<double>> setupTestInputsDifficult(int &NumTeams);
int validateTestOutputs(vector<int> matchups,vector<vector<int>> matchupWithSideAssigned, double score, int NumTeams);
int validateTestOutputsDifficult(vector<int> matchups,vector<vector<int>> matchupWithSideAssigned, double score, int NumTeams);

int main ()
{
	int retval, NumTeams;

	//Test inputs
	vector<vector<double>> testMMS = setupTestInputs(NumTeams);


	//Run the solver
	interativeOptimalMatchmaker matchmakingSolver(testMMS, NumTeams);

	matchmakingSolver.calculateOptimalMatchups();


	//Check the output
	retval = validateTestOutputs(matchmakingSolver.m_matchups,matchmakingSolver.m_matchupWithSideAssigned, matchmakingSolver.m_bestScore,NumTeams);

	testMMS = setupTestInputsDifficult(NumTeams);

	interativeOptimalMatchmaker matchmakingSolver2(testMMS, NumTeams);

	matchmakingSolver2.calculateOptimalMatchups();

	retval = validateTestOutputsDifficult(matchmakingSolver2.m_matchups,matchmakingSolver2.m_matchupWithSideAssigned, matchmakingSolver2.m_bestScore,NumTeams);


	return retval;
}

vector<vector<double>> setupTestInputs(int &NumTeams)
{
	NumTeams=6;

	vector<vector<double>> testMMS {{100,2.760725774,2.1924500,2.28056585,3,2.35355339},
			{2.760725774,100,4.353553391,3.417554839,2.482345068,2.19245009},
			{2.19245009,4.353553391,100,0.6650449988,5.539600718,0.06804138174},
			{2.280565859,3.417554839,0.6650449988,100,2.431959398,2.894793818},
			{3,2.482345068,5.539600718,2.431959398,100,3.837117307},
			{2.353553391,2.19245009,0.06804138174,2.894793818,3.837117307,100}};

	return testMMS;
}

vector<vector<double>> setupTestInputsDifficult(int &NumTeams)
{
	NumTeams=14;

	vector<vector<double>> testMMS {{100,0.3535533906,0.2361111111,0.6495190528,1.020408163,0.0625,0.3935533906,1.027777778,0,0.6495190528,0.25,0,0.125,0.3535533906},
		{0.3535533906,100,0.1875,0.1454081633,1.837117307,0.3935533906,1.25,1.837117307,0.3535533906,0.1527777778,0.3535533906,0.3535533906,0.6495190528,0.1111111111},
		{0.2361111111,0.1875,100,0.6035533906,1.397542486,0.125,0.6495190528,1.437542486,0.125,0.3739615539,0.125,0.1527777778,0.3535533906,0.125},
		{0.6495190528,0.1454081633,0.6035533906,100,2.315032397,0.6495190528,1.397542486,2.565032397,0.6495190528,0.04,0.7120190528,0.6495190528,1.027777778,0.125},
		{1.020408163,1.837117307,1.397542486,2.315032397,100,1.25,0.4160533906,0.25,1.25,2.315032397,1.111111111,1,0.6495190528,1.837117307},
		{0.0625,0.3935533906,0.125,0.6495190528,1.25,100,0.3535533906,1,0,0.7606301639,0,0.25,0.125,0.3739615539},
		{0.3935533906,1.25,0.6495190528,1.397542486,0.4160533906,0.3535533906,100,0.3535533906,0.3535533906,1.397542486,0.3739615539,0.4646645017,0.125,1.027777778},
		{1.027777778,1.837117307,1.437542486,2.565032397,0.25,1,0.3535533906,100,1.020408163,2.315032397,1,1,0.7120190528,1.837117307},
		{0,0.3535533906,0.125,0.6495190528,1.04,0,0.3535533906,1.020408163,100,0.6495190528,0.02777777778,0.0625,0.2361111111,0.6035533906},
		{0.6495190528,0.1527777778,0.3739615539,0.04,2.315032397,0.7606301639,1.397542486,2.315032397,0.6495190528,100,0.6495190528,0.6495190528,1.25,0.1875},
		{0.25,0.3535533906,0.125,0.7120190528,1.111111111,0,0.3739615539,1,0.02777777778,0.6495190528,100,0.25,0.125,0.3535533906},
		{0,0.3535533906,0.1527777778,0.6495190528,1,0.25,0.4646645017,1,0.0625,0.6495190528,0.04,100,0.1454081633,0.3535533906},
		{0.125,0.6495190528,0.3535533906,1.027777778,0.6495190528,0.125,0.125,0.7120190528,0.2361111111,1.25,0.125,0.1454081633,100,0.6895190528},
		{0.3535533906,0.1111111111,0.125,0.125,1.837117307,0.3739615539,1.027777778,1.837117307,0.6035533906,0.1875,0.3535533906,0.3535533906,0.6895190528,100}};

	return testMMS;
}




int validateTestOutputs(vector<int> matchups,vector<vector<int>> matchupWithSideAssigned, double score, int NumTeams)
{
	int retval = 0;
	cout<<"Total MMS of Matchups: "<<score<<endl;

	cout<<"Matchups made: "<<endl;
	for (int counter = 0; counter < NumTeams; counter++)
	{
		cout<<counter<<" vs. "<<matchups[counter]<<endl;
	}

	cout<<"Matchups with side assigned: "<<endl;
	for (int counter = 0; counter < NumTeams/2; counter++)
	{
		cout<<matchupWithSideAssigned[counter][0]<<" at. "<<matchupWithSideAssigned[counter][1]<<endl;
	}

	vector<int> expectedMatchups = {3,4,5,0,1,2};

	if (matchups == expectedMatchups)
	{
		cout<<"Matchups matched expected optimal matchups for test case."<<endl;
		retval = 1;
	}
	return retval;
}

int validateTestOutputsDifficult(vector<int> matchups,vector<vector<int>> matchupWithSideAssigned, double score, int NumTeams)
{
	int retval = 0;
	cout<<"Total MMS of Matchups: "<<score<<endl;

	cout<<"Matchups made: "<<endl;
	for (int counter = 0; counter < NumTeams; counter++)
	{
		cout<<counter<<" vs. "<<matchups[counter]<<endl;
	}

	cout<<"Matchups with side assigned: "<<endl;
	for (int counter = 0; counter < NumTeams/2; counter++)
	{
		cout<<matchupWithSideAssigned[counter][0]<<" at. "<<matchupWithSideAssigned[counter][1]<<endl;
	}

	vector<int> expectedMatchups = {11,13,8,9,7,10,12,4,2,3,5,0,6,1};

	if (matchups == expectedMatchups)
	{
		cout<<"Matchups matched expected optimal matchups for test case."<<endl;
		retval = 1;
	}
	return retval;
}


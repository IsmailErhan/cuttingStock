#ifndef SHIFTSPACE
#define SHIFTSPACE

#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
#include <limits>
#include <math.h>

#include "utilities.h"
#include "FFD.h"
#include "tunning.h"

using namespace std;

bool compareScores(double*,double*);

bool checkMove(int,int,int,vector<vector<int>*>*,
	       vector<int>*,vector<int>*);

int initScoreArrays(vector<vector<int>*>*,vector<int>*,
		    vector<int>*,vector<int>*,int,
		    vector<double*>*,vector<double*>*);

int* next_move(vector<int>*, int,vector<vector<int>*>*,
	       vector<int>*,vector<int>*,vector<int>*,
	       vector<int>*,vector<double*>*,vector<double*>*);
#endif

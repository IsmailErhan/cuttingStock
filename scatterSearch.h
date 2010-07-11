#ifndef scatterSearch
#define SCATTERSEARCH_H
#include "utilities.h"
#include "Solution.h"
#include "genetic.h"
#include "tunning.h"
#include <utility>
#include <math.h>
#include <algorithm>
#include "localSearchBB.h"
using namespace std;

Solution scatterSearch(int P_size, int b, 
                       vector<int> &rlength,
                       vector<int> &lpiece, 
                       vector<int> &dpiece,
                       vector<int> &lot_s);

vector<Solution> genPset(vector<int> &rlength,
                         vector<int> &lpiece,
                         vector<int> &dpiece,
                         int P_size, 
                         vector<int> &lot_s);

double diff(Solution&,Solution&);

void diversity(vector<Solution>&,vector<Solution>&,
	      vector< pair<int,int> >&);

bool compareDivs(pair<int,int>,pair<int,int>);

bool compareFitness(Solution,Solution);

bool compareFitnessReverse(Solution,Solution);

bool find(Solution t, vector<Solution> set);
#endif

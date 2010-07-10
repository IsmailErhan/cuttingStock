#include "scatterSearch.h"
using namespace std;

Solution scatterSearch(int P_size, int b, 
                       vector<int> &rlength,
                       vector<int> &lpiece, 
                       vector<int> &dpiece) {
  vector<Solution> P = genPset(rlength,lpiece,dpiece,P_size);
}

int diff(Solution& sol1, Solution& sol2){
  int ngroups = sol1.diversity.size();
  int diff = 0;
  int ngroups = min(sol1.cgs.size(),sol2.cgs.size());
  int npieces = sol1.cgs[0].size();

  for (int i = 0; i<ngroups; ++i){
    for (int j = 0; j<npieces; ++j){
      diff += abs(sol1.diversity[i][j]-sol2.diversity[i][j]);
    }
  }

  return diff;
}

vector<int> diversity(vector< Solution >& refSet,
		      vector< Solution >& sols){
  int nsols = sols.size();
  int refSet = refSet.size();
  int div = 0;
  vector<int> divs = vector(nsols);

  for (int i = 0; i<nsols; ++i){
    for (int j = 0; j<nrefSet; ++j){
      div += diff(sols[i],sols[j]);
    }
    divs[i] = div;
    div = 0;
  }

  return divs;
}

vector<Solution> genPset(vector<int> &rlength,
                         vector<int> &lpiece,
                         vector<int> &dpiece,
                         int P_size) {
  vector<Solution> Pset;
  Solution initial = Solution(rlength, lpiece, dpiece);
  Solution ramdSol;
  Pset.reserve((size_t) P_size);
  for(int i = 0; i < P_size; i++) {
    ramdSol = randomSol(initial, lpiece, rlength);
    
  }
}



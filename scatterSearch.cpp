#include "scatterSearch.h"
using namespace std;

int diff(Solution& sol1, Solution& sol2){
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

bool compareDivs(pair<int,int> a, pair<int,int> b){
  return (a.second > b.second);
}

vector< pair<int,int> > diversity(vector< Solution >& refSet,
				  vector< Solution >& sols){
  int nsols = sols.size();
  int nRefSet = refSet.size();
  int div = 0;
  vector< pair<int,int> > divs(nRefSet,pair<int,int>());

  for (int i = 0; i<nRefSet; ++i){
    for (int j = 0; j<nsols; ++j){
      div += diff(sols[j],refSet[i]);
    }
    divs[i].first = i;
    divs[i].second = div;
    div = 0;
  }

  sort(divs.begin(),divs.end(),compareDivs);

  return divs;
}

Solution scatterSearch(int P_size, int b, 
                       vector<int> &rlength,
                       vector<int> &lpiece, 
                       vector<int> &dpiece,
                       vector<int> &lot_s) {
  vector<Solution> P = genPset(rlength,lpiece,dpiece,
                               P_size,lot_s);

  int M = lpiece.size();
  vector<Solution> refSet(M,Solution());
  int* pair;
  int candidates[M];
  for(int i = 0; i < M; i++) candidates[i] = i;
  int next_swap[2] = {0,2};
  pair = twoOnN(candidates,next_swap,M);
  std::pair<Solution,Solution> children;
  int index0 = pair[0];
  int index1 = pair[1];
  Solution theOne;
  bool newSolution = false;
  while (pair != NULL) {
    if (!refSet[index0].label || !refSet[index1].label) {
      // Conjuntos sin examinar
      refSet[index0].label = true;
      refSet[index1].label = true;
      children = Cross(&refSet[index0],&refSet[index1]);
      fixSolution(children.first, dpiece, rlength,lpiece);
      fixSolution(children.second, dpiece, rlength,lpiece);
      // Se toma la mejor solución resultante del cruce
      if (children.first.fitness < children.second.fitness) 
        theOne = children.first;
      else 
        theOne = children.second;
      
      localSearchBB(theOne,rlength, lot_s, lpiece, dpiece);
      if (theOne.fitness < refSet.back().fitness &&
          !find(theOne,refSet)) {
        refSet.pop_back();
        refSet.push_back(theOne);
        sort(refSet.begin(), refSet.end(), solComp);
        newSolution = true;
      }
    }
    free(pair);
    pair = twoOnN(candidates,next_swap,M);
  }
}

vector<Solution> genPset(vector<int> &rlength,
                         vector<int> &lpiece,
                         vector<int> &dpiece,
                         int P_size,
                         vector<int> &lot_s) {
  vector<Solution> Pset;
  Solution initial = Solution(rlength, lpiece, dpiece);
  Solution ramdSol;
  vector<pair<int,double> > control;
  Pset.reserve((size_t) P_size);
  int index;
  int cycle = 1000;
  for(int i = 0; i < P_size; i++) {
    ramdSol = randomSol(initial, lpiece, rlength);
    ramdSol.fitnessEval();
    localSearchBB(ramdSol, rlength, lot_s, lpiece, dpiece);
    ramdSol.fitnessEval();
    index = linSearch(control, ramdSol.fitness);
    if (index == -1) {
      // Se agrega solución ya que no está en conjunto P
      Pset.push_back(ramdSol);
      ramdSol.printSolution();
      control.push_back(make_pair(i,ramdSol.fitness));
      sort(control.begin(), control.end(), comparePairDouble);
      cycle--;
    }
    else { // Hay un elemento que tiene el mismo fitness 
           // que la solución generada aleatoriamente. 
           // Por lo que verificamos si son verdaderamente
           // iguales.
      int u = diff(ramdSol, Pset[index]);
      //      cout << "diff" << endl;
      // if (diff(ramdSol, Pset[index]) < 0) {
      //   // Si true entonces se descarta la solución 
      //   i--;
      //   cout << "diff" << endl;
      // }
      // else {  // No son iguales => se agrega ramdSol a Pset
      //   //        ramdSol.fitnessEval();
      //   Pset.push_back(ramdSol);
      //   ramdSol.printSolution();
      //   control.push_back(make_pair(i,ramdSol.fitness));
      //   sort(control.begin(), control.end(), comparePairDouble);
      // }

      if (cycle < 0) {cycle = MAX_CYCLE; i++;}
      else i--;
    }
  }
  return Pset;
}

#include "utilities.h"
#include "localSearchBB.h"
#include "shiftSpace.cpp"
#include "Solution.h"
using namespace std;

// Algoritmo de búsqueda local mejor mejor.
void localSearchBB(Solution &sol, 
                   vector<int> &rlenght, vector<int> &lot_s,
                   vector<int> &lpiece, vector<int> &dpiece)
{

  vector< vector<int> >* cgroups = &(sol.cgs);
  vector<int>* leftover   = &(sol.leftover);
  vector<int>* used_rolls = &(sol.used_rolls);
  vector<int>* rollType   = &(sol.rollType);
  vector<int>* variety    = &(sol.variety);

  vector<double*> origScores(lpiece.size());
  vector<double*> dstScores(lpiece.size());
  vector<int> status(2,0);

  for(int i=0; i<lpiece.size(); ++i){
    origScores[i] = new double[2];
    dstScores[i] = new double[2];
  }

  int maxIt = LSBB_MAXIT;
  int *info; // arreglo con información sobre el
               // el cambio de vecindad.
  initScoreArrays(cgroups, used_rolls, &lpiece, leftover, rollType, lpiece.size(),
		  &origScores, &dstScores);
  while (maxIt > 0 && status[0] < lpiece.size()) {
    info = next_move(&status, lpiece.size(), cgroups, variety, rollType,
     		     &lpiece, &rlenght, &lot_s ,&dstScores, &origScores);
    if (group_quality(info, *leftover, *used_rolls)) {
      // Se ejecuta el movimiento
      // Se actualiza leftover origen
      (*leftover)[info[0]] = info[3]; 
      // Se actualiza leftover destino
      (*leftover)[info[1]] = info[4]; 

      // Se actualiza used_rolls origen
      (*used_rolls)[info[0]] = info[5];
      // Se actualiza used_rolls destino
      (*used_rolls)[info[1]] = info[6];

      int nitems_orig = (*cgroups)[info[0]][info[2]];
      // Se actualiza estructura variety para destino
      if (((*cgroups)[info[1]])[info[2]] == 0)
	(*variety)[info[1]]++;

      // Se actualiza cgroups destino
      ((*cgroups)[info[1]])[info[2]] += min(nitems_orig,lot_s[info[2]]);
      // Se actualiza cgroups origen
      ((*cgroups)[info[0]])[info[2]] -= min(nitems_orig,lot_s[info[2]]);

      // Se actualiza estructura variety para origen
      if (((*cgroups)[info[0]])[info[2]] == 0) 
	(*variety)[info[0]]--; 

      // origScores.clear();
      // origScores.resize(lpiece.size());
      // dstScores.clear();
      // dstScores.resize(lpiece.size());
      status[0]=0;
      status[1]=0;
      initScoreArrays(cgroups, used_rolls, &lpiece, leftover, 
		      rollType, lpiece.size(),&origScores, &dstScores);
    }
    maxIt--;
    delete [] info;
    sol.fitnessEval();
  }
  // int i;
  // int j;
  // int sum;
  // for(i = 0; i < lpiece.size(); i++) {
  //   sum = 0;
  //   if (used_rolls[i]) {
  //     cout << "Tipo " << i << endl;
  //     cout << "rolls " << used_rolls[i] << endl;
  //     cout << "leftover " << leftover[i] << endl;
  //     for(j=0;j<lpiece.size();++j)
  //     	sum += cgroups[i]->at(j);
  //     cout << "n_used_pieces " << sum << endl; 
  //     cout << "------------" << endl;
  //     }
  // }
}
              

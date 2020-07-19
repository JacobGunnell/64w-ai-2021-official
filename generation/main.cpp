#include <iostream>
#include <list>
#include <random>
#include <ctime>
using namespace std;

#include "AI.h"

#include <chrono>
using namespace std::chrono;

int main()
{
  // Seed random number generators
  srand(time(0));
  arma_rng::set_seed_random();

  // Initialize Generation 0
  const int N_INPUTS = 3;
  const int N_HIDDEN = 1;
  const int POPULATION = 32; // must be a power of 2
  const int ELITE = 4; // must also be a power of 2
  const int MUTATION_CHANCE = 20; // percentage out of 100
  const int GEN_MAX = 5; // increase this
  list<Brain> cGen; // current generation
  Match m;
  int roundSize;
  int midx, fidx;
  list<Brain>::iterator mother, father;

  const int PREDESIGNED = 1;
  colvec predesigned[PREDESIGNED] = { {1.0,.7,.2} };
  for(int i = 0; i < PREDESIGNED; i++)
    cGen.push_front(Brain(mat(predesigned[i]), mat{1}, mat{0})); // seed current generation with predesigned brains
  for(int i = PREDESIGNED; i < POPULATION; i++)
    cGen.push_front(Brain(N_INPUTS, N_HIDDEN));

  for(int gen = 0; gen <= GEN_MAX; gen++)
  {
    cout << "Gen " << gen << " in progress...";
    high_resolution_clock::time_point start = high_resolution_clock::now();
    int totalPoints = 0, numPlays = 0;

    // Run elimination brackets (single elimination)
    while(cGen.size() > ELITE)
    {
      roundSize = cGen.size();
      cout << " r" << roundSize << "...";
      for(int i = 0; i < roundSize/2; i++) // run half as many matches as there are competitors
      {
        m.setContestants(&cGen.front(), &cGen.back()); // set red and blue teams
        if(m.run() == 0) // run it and kill the loser
          cGen.pop_back();
        else
          cGen.pop_front();
        totalPoints += m.wp + m.lp;
        numPlays += 2;
        m.wp = 0;
        m.lp = 0;
      }
    }

    // Save this generation's elite to file
    int n = 0;
    string fpath = "elite/";
    for(list<Brain>::iterator i = cGen.begin(); i != cGen.end(); ++i)
      i->save(fpath + to_string(gen) + "gen" + to_string(n++));


    // Elite get to breed the next generation
    cout << " breeding...";
    while(cGen.size() < POPULATION)
    {
      mother = cGen.begin();
      father = cGen.begin();
      midx = rand()%ELITE; // pick a mother and a father that are not the same
      do
      {
        fidx = rand()%ELITE;
      }
      while(midx == fidx);
      advance(mother, midx);
      advance(father, fidx);
      cGen.emplace_back(Brain(&*mother, &*father)); // make a child
      if(rand()%100 < MUTATION_CHANCE) // decide whether the child should be mutant
        (--cGen.end())->mutate();
    }

    high_resolution_clock::time_point stop = high_resolution_clock::now();
    milliseconds duration = duration_cast<milliseconds>(stop - start);
    cout << " complete in " << duration.count() / 1000.0 << " seconds. Avg points scored in a match: " << (double)totalPoints/numPlays << endl;
  }

  return 0;
}

// tell the linker to link the implementation files without creating a library; probably will create one in the future and make it a PROS library template
#include "../src/SensorWrapper.cpp"
#include "../src/Move.cpp"
#include "../src/Brain.cpp"
#include "../src/Match.cpp"

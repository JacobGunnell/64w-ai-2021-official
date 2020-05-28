#include <iostream>
#include <list>
#include <random>
#include <ctime>
using namespace std;

#include "AI.h"


//#define GENERATION_BENCHMARK 10000000

#include <chrono>
using namespace std::chrono;

int main()
{
  srand(time(0));
  arma_rng::set_seed_random();

#ifdef GENERATION_BENCHMARK
  mat WL1 = { {5, 2, 4},
              {2, 1, 3},
              {1, 8, 4},
              {0, 2, 7},
              {0, 1, 3},
              {0, 5, 7},
              {0, 0, 3},
              {0, 0, 2},
              {0, 0, 1} };

  colvec WL2 = {8, 5, 4};

  rowvec B = {1, 2, 0};

  Brain brain(WL1, WL2, B);

  mat X(GENERATION_BENCHMARK, 9, fill::randu);
  cout << "Integration start" << endl;
  auto start = high_resolution_clock::now();
  mat U = brain.integrate(X);
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(stop - start);
  cout << "Integration complete in " << duration.count() / 1000.0 << " seconds." << endl;
#endif // GENERATION_BENCHMARK

  // Initialize Generation 0
  const int N_INPUTS = 3;
  const int N_HIDDEN = 1;
  const int POPULATION = 32; // must be a power of 2
  const int ELITE = 4; // must also be a power of 2
  const int MUTATION_CHANCE = 20; // percentage out of 100
  const int GEN_MAX = 5; // increase this
  list<Brain> cGen; // current generation
  list<Brain>::iterator red;
  list<Brain>::reverse_iterator blue;
  Match *m;
  int roundSize;
  int midx, fidx;
  list<Brain>::iterator mother, father;

  const int PREDESIGNED = 1;
  colvec predesigned[PREDESIGNED] = { {1.0,.7,.2} };
  for(int i = 0; i < PREDESIGNED; i++)
    cGen.emplace_front(Brain(mat(predesigned[i]), mat{1}, mat{0})); // seed current generation with predesigned brains
  for(int i = PREDESIGNED; i < POPULATION; i++)
    cGen.emplace_front(Brain(N_INPUTS, N_HIDDEN));

  for(int gen = 0; gen <= GEN_MAX; gen++)
  {
    cout << "Generation " << gen << " in progress...";
    high_resolution_clock::time_point start = high_resolution_clock::now();
    int totalPoints = 0, numPlays = 0;

    // Run elimination brackets (single elimination)
    while(cGen.size() > ELITE)
    {
      red = cGen.begin();
      blue = cGen.rbegin();
      roundSize = cGen.size();
      for(int i = 0; i < roundSize/2; i++) // run half as many matches as there are competitors
      {
        m = new Match(&*red, &*blue); // create a match
        if(m->run() == 0) // run it and kill the loser; advance iterator positions for next match
        {
          cGen.erase((++blue).base()); // blue is a reverse iterator, so kill (++blue).base() to kill/increment simultaneously
          red++;
        }
        else
        {
          cGen.erase(red++); // red is a forward iterator, nothing special here
          blue++;
        }
        totalPoints += m->wp + m->lp;
        numPlays += 2;
        delete m;
      }
    }

    // Elite get to breed the next generation
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

// this is sort of a hack but it's the only way i could get the linker to link the implementation files without creating a library; probably will create one in the future and make it a PROS library template
#include "../src/GameObject.cpp"
#include "../src/SensorWrapper.cpp"
#include "../src/Move.cpp"
#include "../src/Brain.cpp"
#include "../src/Match.cpp"

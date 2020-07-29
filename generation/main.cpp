#include <iostream>
#include <list>
#include <random>
#include <ctime>
#include <cmath>
using namespace std;

#include "AI.h"

#include <chrono>
using namespace std::chrono;

#include "CLI11.hpp"

#define GENERATION_NO_ROBOT

int main(int argc, char **argv)
{
  CLI::App app{"Generation, a program to breed a competent AI brain using an evolutional framework."};
  int POPULATION = 32, ELITE = 4, MUTATION_CHANCE = 20, GEN_MAX;
  string FPATH;
  app.add_option("-p", POPULATION, "Initial Population", true)->check([](const string &str){ if(ceil(log2(stoi(str))) != floor(log2(stoi(str)))) return str + string(" is not a power of 2"); else return string(); });
  app.add_option("-e", ELITE, "Elite Population", true)->check([](const string &str){ if(ceil(log2(stoi(str))) != floor(log2(stoi(str)))) return str + string(" is not a power of 2"); else return string(); });
  app.add_option("-m", MUTATION_CHANCE, "Mutation Chance", true)->check(CLI::Range(0, 100));
  app.add_option("-g", GEN_MAX, "Number of Generations to run")->required();
  app.add_option("-o", FPATH, "Directory to save to")->check(CLI::ExistingDirectory);
  CLI11_PARSE(app, argc, argv);
  cout << "64W Generation v1.0" << endl
       << "Starting " << GEN_MAX << " generation run with initial population " << POPULATION;
  if(FPATH.empty())
    cout << " (no save specified!)..." << endl;
  else
    cout << "..." << endl;

  // Seed random number generators
  srand(time(0));
  arma::arma_rng::set_seed_random();

  // Initialize Generation 0
  const int N_INPUTS = 3;
  const int N_HIDDEN = 1;

  list<Brain> cGen; // current generation
  int roundSize;
  int midx, fidx;
  list<Brain>::iterator mother, father;
  list<Brain>::iterator red;
  list<Brain>::reverse_iterator blue;

  const int PREDESIGNED = 1;
  arma::colvec predesigned[PREDESIGNED] = { {1.0,.7,.2} };
  for(int i = 0; i < PREDESIGNED; i++)
    cGen.push_front(Brain(arma::mat(predesigned[i]), arma::mat{1}, arma::mat{0})); // seed current generation with predesigned brains
  for(int i = PREDESIGNED; i < POPULATION; i++)
    cGen.push_front(Brain(N_INPUTS, N_HIDDEN));

  for(int gen = 0; gen < GEN_MAX; gen++)
  {
    cout << "Gen " << gen << " in progress...";
    high_resolution_clock::time_point start = high_resolution_clock::now();
    int totalPoints = 0, numPlays = 0;

    // Run elimination brackets (single elimination)
    while(cGen.size() > ELITE)
    {
      roundSize = cGen.size();
      red = cGen.begin();
      blue = cGen.rbegin();
      cout << " r" << roundSize << "...";
      for(int i = 0; i < roundSize/2; i++) // run half as many matches as there are competitors
      {
        Match m(&*red, &*blue); // set red and blue teams
        if(m.run() == RED_ALLIANCE) // run it and kill the loser
        {
          cGen.erase(next(blue).base());
          red++;
        }
        else
        {
          cGen.erase(red);
          blue++;
        }
        totalPoints += m.wp + m.lp;
        numPlays += 2;
        m.reset();
      }
    }

    if(gen == GEN_MAX - 1 && !FPATH.empty())
    {
      // Save elite to file
      cout << " saving  ...";
      list<Brain>::iterator iter = cGen.begin();
      for(int i = 0; i < cGen.size(); i++)
        iter++->save(FPATH + "/brain" + to_string(i));
    }
    else
    {
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
        cGen.emplace_back(&*mother, &*father); // make a child
        if(rand()%100 < MUTATION_CHANCE) // decide whether the child should be mutant
          cGen.back().mutate();
      }
    }

    high_resolution_clock::time_point stop = high_resolution_clock::now();
    milliseconds duration = duration_cast<milliseconds>(stop - start);
    cout << " complete in " << duration.count() / 1000.0 << " seconds. Avg points scored in a match: " << (double)totalPoints/numPlays << endl;
  }

  return 0;
}

// tell the linker to link the implementation files without creating a library; probably will create one in the future and make it a PROS library template
#include "../src/Brain.cpp"
#include "../src/Container.cpp"
#include "../src/Goal.cpp"
#include "../src/Match.cpp"
#include "../src/Move.cpp"
#include "../src/MoveDerived.cpp"
#include "../src/Robot.cpp"
#include "../src/SensorWrapper.cpp"

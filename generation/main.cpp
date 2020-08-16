#ifdef GENERATION_NO_ROBOT // this source file is only for the training program

#include <iostream>
#include <list>
#include <random>
#include <ctime>
#include <cmath>
#include <fstream>
#include <experimental/filesystem>
using namespace std;
namespace fs = std::experimental::filesystem;

#include "AI.h"

#include <chrono>
using namespace std::chrono;

#include "CLI11.hpp"

template<typename T> void shuffle(list<T> &);

int main(int argc, char **argv)
{
  CLI::App app{"Generation, a program to breed a competent AI brain using an evolutional framework."};
  int POPULATION = 32, ELITE = 4, MUTATION_CHANCE = 20, GEN_MAX, RAND = 4;
  string OFPATH, IFPATH;
  bool SEXUAL = false;
  app.add_option("-p", POPULATION, "Initial Population", true)->check([](const string &str){ if(ceil(log2(stoi(str))) != floor(log2(stoi(str)))) return str + string(" is not a power of 2"); else return string(); });
  app.add_option("-e", ELITE, "Elite Population", true)->check([](const string &str){ if(ceil(log2(stoi(str))) != floor(log2(stoi(str)))) return str + string(" is not a power of 2"); else return string(); });
  app.add_option("-m", MUTATION_CHANCE, "Mutation Chance", true)->check(CLI::Range(0, 100));
  app.add_option("-r", RAND, "Number of Random brains to generate each generation"); // TODO: check data
  app.add_option("-g", GEN_MAX, "Number of Generations to run")->required();
  app.add_option("-o", OFPATH, "Directory to save to")->check(CLI::ExistingDirectory);
  app.add_option("-i", IFPATH, "Directory to read initial population from")->check(CLI::ExistingDirectory);
  app.add_flag("--sexual", SEXUAL, "Use sexual reproduction over asexual reproduction (not yet implemented)");
  CLI11_PARSE(app, argc, argv);
  cout << "64W Generation v1.0" << endl
       << "Starting " << GEN_MAX << " generation run with initial population " << POPULATION;
  if(OFPATH.empty())
    cout << " (no save specified!)";
  cout << "..." << endl << endl;

  high_resolution_clock::time_point overallStart = high_resolution_clock::now();

  // Seed random number generators
  srand(time(0));
  arma::arma_rng::set_seed_random();

  // Initialize Generation 0
  const int N_INPUTS = MoveData().vectorize().n_elem;

  list<Brain *> cGen; // current generation
  int roundSize;
  int midx, fidx;
  list<Brain *>::iterator mother, father;
  list<Brain *>::iterator red;
  list<Brain *>::reverse_iterator blue;

  int numBrains = 0;
  if(!IFPATH.empty())
  {
    cout << "Loading brains from " << '"' << IFPATH << '"' << "... ";
    for(const auto &entry : fs::recursive_directory_iterator(IFPATH))
    {
      if(numBrains < POPULATION)
      {
        Brain *b = Brain::dynamic_load(entry.path().string());
        if(b != NULL)
        {
          cGen.push_front(b);
          numBrains++;
        }
        else
          cout << "unrecognized file type " << '"' << entry.path().extension() << '"' << "; skipping " << entry.path() << endl;
      }
    }
    cout << "loaded " << numBrains << " brains" << endl;
  }
  cout << "Randomly generating " << POPULATION - numBrains << " brains to fill array... ";
  for(int i = numBrains; i < POPULATION; i++)
    cGen.push_front(Brain::random(N_INPUTS));
  cout << "done" << endl;

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
        Match m(*red, *blue); // set red and blue teams
        if(m.run() == RED_ALLIANCE) // run it and kill the loser
        {
          delete *blue;
          blue = make_reverse_iterator(cGen.erase(next(blue).base()));
          ++red;
        }
        else
        {
          delete *red;
          red = cGen.erase(red);
          ++blue;
        }
        totalPoints += m.wp + m.lp;
        numPlays += 2;
      }
    }

    if(gen == GEN_MAX - 1 && !OFPATH.empty())
    {
      // Save elite to file
      cout << " saving  ...";
      list<Brain *>::iterator iter = cGen.begin();
      for(int i = 0; i < cGen.size(); i++)
        (*iter++)->save(OFPATH + "/brain" + to_string(i)); // TODO: better file naming pattern
    }
    else
    {
      // Elite get to breed the next generation
      cout << " breeding...";
      if(SEXUAL)
      {
        while(cGen.size() < POPULATION - RAND)
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
          cGen.push_back(Brain::breed(*mother, *father)); // make a child
          if(rand()%100 < MUTATION_CHANCE) // decide whether the child should be mutant
            cGen.back()->mutate();
        }
        while(cGen.size() < POPULATION)
          cGen.push_back(Brain::random(N_INPUTS));
      }
      else
      {
        while(cGen.size() < POPULATION - RAND)
        {
          mother = cGen.begin();
          advance(mother, rand()%ELITE);
          cGen.push_back((*mother)->clone());
          cGen.back()->mutate();
        }
        while(cGen.size() < POPULATION)
          cGen.push_back(Brain::random(N_INPUTS));
      }

      shuffle(cGen);
    }

    high_resolution_clock::time_point stop = high_resolution_clock::now();
    milliseconds duration = duration_cast<milliseconds>(stop - start);
    cout << " complete in " << duration.count() / 1000.0 << " seconds. Avg points scored in a match: " << (double)totalPoints/numPlays << endl;
  }

  high_resolution_clock::time_point overallStop = high_resolution_clock::now();
  milliseconds duration = duration_cast<milliseconds>(overallStop - overallStart);
  cout << GEN_MAX << " generation run complete in " << duration.count() / 1000.0 << " seconds." << endl;

  return 0;
}

template<typename T> void shuffle(list<T> &lst) // shuffle contents of a list
{
  vector<reference_wrapper<const T>> vec(lst.begin(), lst.end());
  shuffle(vec.begin(), vec.end(), mt19937{random_device{}()});
  list<T> shuffled_list{vec.begin(), vec.end()};
  lst.swap(shuffled_list);
}

// tell the linker to link the implementation files without creating a library; probably will create one in the future and make it a PROS library template
#include "../src/Ball.cpp"
#include "../src/Container.cpp"
#include "../src/Goal.cpp"
#include "../src/Match.cpp"
#include "../src/Move.cpp"
#include "../src/MoveContainer.cpp"
#include "../src/MoveDerived.cpp"
#include "../src/MoveSet.cpp"
#include "../src/Robot.cpp"
#include "../src/SensorWrapper.cpp"

#include "../src/Brain.cpp"
#include "../src/SMP.cpp"
#include "../src/SP.cpp"

#endif // GENERATION_NO_ROBOT

#include "main.h"

// Globals
// Motor objects


// Sensor objects


// Mutexes


// Other objects


// Other variables


// Function prototypes


// Function implementations
void initialize()
{
	cout << "Robot Online" << endl << "64W Competition Program Rev. " << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH << VERSION_INFO << "-" << VERSION_YEAR << " with ";
	if (__cplusplus == 201703L) std::cout << "C++17\n";
  else if (__cplusplus == 201402L) std::cout << "C++14\n";
  else if (__cplusplus == 201103L) std::cout << "C++11\n";
  else if (__cplusplus == 199711L) std::cout << "C++98\n";
  else std::cout << "pre-standard C++\n";
	cout << "Begin Initialization" << endl;

	cout << "Initialization Complete" << endl;
}

void disabled() {}

void competition_initialize() {}

void opcontrol()
{
	Brain brain(9, 3);
	brain.load("/usd/brain0.brn");
	double umax = 0; int umaxidx;
	Move *possibleMoves;
	int numPossibleMoves;
	while(true)
	{
		// capture vision data, compute all possible moves
		possibleMoves = Move::getAllPossibleMoves(); // TODO: implement!
		numPossibleMoves = Move::numExistentObjects;
		mat X(numPossibleMoves, 9);
		// fill x with vision data (maybe make a motor that can spin the depth camera to see all the objects on the field?)
		mat U = brain.integrate(X);
		for(int m = 0; m < numPossibleMoves; m++)
		{
			if(U(m) > umax)
			{
				umax = U(m);
				umaxidx = m;
			}
		}
		possibleMoves[umaxidx].execute(); // Do the move that the AI thinks is the best strategically
		delete possibleMoves;
	}
}

void autonomous()
{
  cout << endl << "Entering autonomous" << endl;

	cout << "Autonomous Routine Complete" << endl;
}

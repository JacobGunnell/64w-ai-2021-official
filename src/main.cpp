#include "main.h"
#include "Hardware.h"

// Globals
shared_ptr<ChassisController> Chassis = ChassisControllerBuilder()
	.withMotors(1, -10, 11, -20)
	.withDimensions(AbstractMotor::gearset::green, {{4_in, 11.5_in}, imev5GreenTPR}) // TODO: update dimensions
	.build();
shared_ptr<XDriveModel> Drive = dynamic_pointer_cast<XDriveModel>(Chassis->getModel());

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
	Brain brain;
	brain.load(BRAINFILE);
	double umax = 0; int umaxidx;
	Move **possibleMoves;
	int len;
	while(true)
	{
		// capture vision data, compute all possible moves
		SensorWrapper s(NULL, 0); // TODO: implement constructor to interface with Sensor Fusion API
		len = Move::getNumExistentMoves();
		possibleMoves = Move::getAllPossibleMoves(s);
		len = Move::getNumExistentMoves() - len;
		arma::mat U = brain.integrate(Move::toMatrix(possibleMoves, len));
		for(int m = 0; m < len; m++)
		{
			if(U(m) > umax)
			{
				umax = U(m);
				umaxidx = m;
			}
		}
		possibleMoves[umaxidx]->execute(); // Do the move that the AI thinks is the best strategically
		delete possibleMoves;
	}
}

void autonomous()
{
  cout << endl << "Entering autonomous" << endl;

	cout << "Autonomous Routine Complete" << endl;
}

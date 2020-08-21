#include "main.h"
#include "Hardware.h"
#include "GUI.h"

// Globals
shared_ptr<ChassisController> Chassis = ChassisControllerBuilder()
	.withMotors(1, -10, 11, -20)
	.withDimensions(AbstractMotor::gearset::green, {{4_in, 11.5_in}, imev5GreenTPR}) // TODO: update dimensions
	.build();
shared_ptr<XDriveModel> Drive = dynamic_pointer_cast<XDriveModel>(Chassis->getModel());

Robot bigRobot, smallRobot;
Brain *brain;

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

	gui_loading_start();

	cout << "Creating internal robot objects...";
	bigRobot = Robot(T_MASTER, RED_ALLIANCE, 0, 0, 0, 4, 50, static_cast<double>(Chassis->getGearsetRatioPair().internalGearset)); // TODO: read from sensors
	smallRobot = Robot(T_SLAVE, RED_ALLIANCE, 0, 0, 0, 3, 50);
	cout << "done" << endl;

	cout << "Loading brain from " << BRAINFILE << "..."; // TODO: implement on-screen selector (maybe have it read from a default.pref for default brain?)
	Brain *brain = Brain::dynamic_load(BRAINFILE);
	if(brain == NULL) // missing brain
	{
		cout << "failed!" << endl;
		cout << "Generating backup brain...";
		brain = new SP(arma::colvec{1.0, .7, .3}); // TODO: better backup brain
		cout << "done" << endl;
		gui_error(string("Failed to load brainfile at ") + BRAINFILE + ", generated backup in place");
	}
	else
		cout << "done" << endl;

	gui_loading_stop();
	gui_main();

	cout << "Initialization Complete" << endl;
}

void disabled() {}

void competition_initialize() {}

void opcontrol()
{
	double umax = 0; int umaxidx;
	SensorWrapper s;
	while(true)
	{
		// capture vision data, compute all possible moves
		// TODO: create seperate task for updating s with latest sensor data
		//s.setPOV(s.findContained(&bigRobot));
		MoveContainer possibleMoves(s, -1); // TODO: implement time factor
		arma::mat Umaster = brain->integrate(Move::toMatrix(possibleMoves, s));
		for(int m = 0; m < Umaster.n_elem; m++)
		{
			if(Umaster(m) > umax)
			{
				umax = Umaster(m);
				umaxidx = m;
			}
		}
		possibleMoves[umaxidx]->execute(); // Do the move that the AI thinks is the best strategically
	}

	delete brain;
}

void autonomous()
{
  cout << endl << "Entering autonomous" << endl;

	cout << "Autonomous Routine Complete" << endl;
}

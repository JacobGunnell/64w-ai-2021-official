#include "Match.h"

const int Match::numGoals = 9;
const int Match::numRedRobots = 2; // TODO: implement 2 on 2
const int Match::numBlueRobots = 2;
const int Match::numRobots = Match::numRedRobots + Match::numBlueRobots;
const int Match::numBalls = 32;
const int Match::defaultFieldSize = numGoals + numRobots + numBalls;

Match::Match(Brain *redBrain, Brain *blueBrain)
{
  red = redBrain->clone();
  blue = blueBrain->clone();
  wp = 0;
  lp = 0;
  field = defaultField();
  fieldSize = defaultFieldSize;
  generator = default_random_engine(std::chrono::system_clock::now().time_since_epoch().count());
}

Match::Match(const Match &cpy)
{
  red = cpy.red->clone();
  blue = cpy.blue->clone();
  wp = cpy.wp;
  lp = cpy.lp;
  field = new GameObject*[cpy.fieldSize];
  for(int i = 0; i < cpy.fieldSize; i++)
    field[i] = cpy.field[i]->clone();
  generator = default_random_engine(std::chrono::system_clock::now().time_since_epoch().count());
}

Match::~Match()
{
  delete red;
  delete blue;
  for(int i = 0; i < fieldSize; i++)
    delete field[i];
  delete [] field;
}

Alliance Match::run()
{
  Robot **redrobots = getRedRobots(field);
  Robot **bluerobots = getBlueRobots(field);
  double redtime = 120.0;
  double bluetime = 120.0;
  while(redtime > 0 && bluetime > 0)
  {
    while(redtime >= bluetime)
      redtime -= makemove(redrobots, red, redtime) + .1;
    while(bluetime >= redtime)
      bluetime -= makemove(bluerobots, blue, bluetime) + .1;
  }

  int pred = score(RED_ALLIANCE);
  int pblue = score(BLUE_ALLIANCE);
  if(pred > pblue)
  {
    wp = pred;
    lp = pblue;
    return RED_ALLIANCE;
  }
  else if(pblue > pred)
  {
    wp = pblue;
    lp = pred;
    return BLUE_ALLIANCE;
  }
  else
  {
    wp = pred;
    return NEITHER_ALLIANCE;
  }
}

int Match::score(Alliance a)
{
  Color c = static_cast<Color>(a);
  int score = 0;

  Goal **goals = getGoals(field);
  for(int i = 0; i < numGoals; i++)
    score += goals[i]->numBalls(c); // each scored Ball of your alliance color is worth 1 point

  for(int i = 0; i < 8; i++)
    if(goals[Goal::connectableRowIndices[i][0]]->topColor() == c &&
    goals[Goal::connectableRowIndices[i][1]]->topColor() == c &&
    goals[Goal::connectableRowIndices[i][2]]->topColor() == c)
      score += 6; // 6 points for each Connected Row

  return score;
}

void Match::reset()
{
  wp = 0;
  lp = 0;
  for(int i = 0; i < defaultFieldSize; i++)
    delete field[i];
  delete [] field;
  field = defaultField();
}

double Match::makemove(Robot **bots, Brain *brn, double timeRemaining)
{
  if(bots == NULL)
    return 0;
  if(bots[0] == NULL || bots[1] == NULL)
    return 0;
  if(brn == NULL)
    return 0;
  if(timeRemaining <= 0)
    return 0;

  double umax = 0; int umaxidx;
  MoveContainer possibleMoves(bots[0]->getViewableWrapper(field, fieldSize), timeRemaining);

  arma::mat U = brn->integrate(Move::toMatrix(possibleMoves, bots[0]));
  if(U.n_elem != possibleMoves.getLen())
    return 0;
  for(int m = 0; m < U.n_elem; m++)
  {
    if(U(m) > umax)
    {
      umax = U(m);
      umaxidx = m;
    }
  }

  double estTime;
  if(possibleMoves[umaxidx] != NULL)
    estTime = possibleMoves[umaxidx]->getData(bots[0]).t;
  else
    return 0;
  normal_distribution<double> dist(estTime, .01*estTime); // introduce noise with mean t and standard deviation proportional to t
  double actualTime = estTime + dist(generator);
  if(actualTime <= timeRemaining)
  {
    possibleMoves[umaxidx]->vexecute(bots[0]);
    return actualTime < 0 ? actualTime : 0; // on the off chance that the gaussian noise screws it up, don't let time be negative
  }
  else
    return timeRemaining;
}

GameObject **Match::defaultField()
{
  GameObject **field = new GameObject*[defaultFieldSize]; // 32 balls, 9 goals, 4 robots
  Goal **goals = getGoals(field);
  Robot **robots = getRobots(field);
  Ball **balls = getBalls(field);
  int gidx = 0, ridx = 0, bidx = 0;

  // Goals / balls in goals
  goals[gidx++] = new Goal{-66.351, 66.351,
    static_cast<Ball *>(balls[bidx++] = new Ball{RED}),
    static_cast<Ball *>(balls[bidx++] = new Ball{BLUE})};
  goals[gidx++] = new Goal{0, 66.351,
    static_cast<Ball *>(balls[bidx++] = new Ball{RED}),
    static_cast<Ball *>(balls[bidx++] = new Ball{BLUE}),
    static_cast<Ball *>(balls[bidx++] = new Ball{RED})};
  goals[gidx++] = new Goal{66.351, 66.351,
    static_cast<Ball *>(balls[bidx++] = new Ball{BLUE}),
    static_cast<Ball *>(balls[bidx++] = new Ball{RED})};
  goals[gidx++] = new Goal{-66.351, 0,
    static_cast<Ball *>(balls[bidx++] = new Ball{RED}),
    static_cast<Ball *>(balls[bidx++] = new Ball{BLUE})};
  goals[gidx++] = new Goal{0, 0};
  goals[gidx++] = new Goal{66.351, 0,
    static_cast<Ball *>(balls[bidx++] = new Ball{BLUE}),
    static_cast<Ball *>(balls[bidx++] = new Ball{RED})};
  goals[gidx++] = new Goal{-66.351, -66.351,
    static_cast<Ball *>(balls[bidx++] = new Ball{RED}),
    static_cast<Ball *>(balls[bidx++] = new Ball{BLUE})};
  goals[gidx++] = new Goal{0, -66.351,
    static_cast<Ball *>(balls[bidx++] = new Ball{BLUE}),
    static_cast<Ball *>(balls[bidx++] = new Ball{RED}),
    static_cast<Ball *>(balls[bidx++] = new Ball{BLUE})};
  goals[gidx++] = new Goal{66.351, -66.351,
    static_cast<Ball *>(balls[bidx++] = new Ball{BLUE}),
    static_cast<Ball *>(balls[bidx++] = new Ball{RED})};

  // Robots / Preloads
  robots[ridx++] = new Robot{T_MASTER, RED_ALLIANCE, -60, 36, 90, 4, 50,
    static_cast<Ball *>(balls[bidx++] = new Ball{RED})};
  robots[ridx++] = new Robot{T_SLAVE, RED_ALLIANCE, -60, -36, 90, 3, 50,
    static_cast<Ball *>(balls[bidx++] = new Ball{RED})};
  robots[ridx++] = new Robot{T_MASTER, BLUE_ALLIANCE, 60, 36, -90, 4, 50,
    static_cast<Ball *>(balls[bidx++] = new Ball{BLUE})};
  robots[ridx++] = new Robot{T_SLAVE, BLUE_ALLIANCE, 60, -36, -90, 3, 50,
    static_cast<Ball *>(balls[bidx++] = new Ball{BLUE})};

  // Balls on field
  balls[bidx++] = new Ball{0, 8.799, RED};
  balls[bidx++] = new Ball{0, -8.799, BLUE};
  balls[bidx++] = new Ball{8.799, 0, RED};
  balls[bidx++] = new Ball{-8.799, 0, BLUE};
  balls[bidx++] = new Ball{0, 36, RED};
  balls[bidx++] = new Ball{0, -36, BLUE};
  balls[bidx++] = new Ball{60, 60, BLUE};
  balls[bidx++] = new Ball{60, -60, BLUE};
  balls[bidx++] = new Ball{-60, 60, RED};
  balls[bidx++] = new Ball{-60, -60, RED};

  return field;
}

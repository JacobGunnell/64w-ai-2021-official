#include "Match.h"

Match::Match(Brain *redBrain, Brain *blueBrain) : red(redBrain), blue(blueBrain)
{
  wp = 0;
  lp = 0;
  field = defaultField();
  generator = default_random_engine(std::chrono::system_clock::now().time_since_epoch().count());
}

Match::Match(const Match &cpy)
{
  red = cpy.red;
  blue = cpy.blue;
  wp = cpy.wp;
  lp = cpy.lp;
  if(cpy.field != NULL)
    field = new SensorWrapper(*cpy.field);
  else
    field = defaultField();
  generator = default_random_engine(std::chrono::system_clock::now().time_since_epoch().count());
}

Match::~Match()
{
  field->clear();
  delete field;
}

Alliance Match::run()
{
  vector<Robot *> redrobots = field->getRobots(RED_ALLIANCE);
  vector<Robot *> bluerobots = field->getRobots(BLUE_ALLIANCE);
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
    wp = lp = pred;
    return NEITHER_ALLIANCE;
  }
}

int Match::score(const SensorWrapper &f, Alliance a)
{
  Color c = static_cast<Color>(a);
  int score = 0;

  vector<Goal *> goals = f.getGoals();
  for(int i = 0; i < goals.size(); i++)
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
  field->clear();
  delete field;
  field = defaultField();
}

double Match::makemove(vector<Robot *> bots, Brain *brn, double timeRemaining)
{
  if(bots[0] == NULL || bots[1] == NULL)
    return 0;
  if(brn == NULL)
    return 0;
  if(timeRemaining <= 0)
    return 0;

  double umax = 0; int umaxidx = 0;
  field->pov = field->findContained(bots[0]); // TODO: delete
  //SensorWrapper s = field /*bots[0]->getViewableWrapper(field) + bots[1]->getViewableWrapper(field)*/;
  MoveContainer possibleMoves(*field, timeRemaining); // TODO: use viewable wrapper
  if(possibleMoves.empty())
    return 0;

  arma::mat U = brn->integrate(Move::toMatrix(possibleMoves, *field));
  for(int m = 0; m < U.n_elem; m++)
  {
    if(U(m) >= umax)
    {
      umax = U(m);
      umaxidx = m;
    }
  }

  double estTime = possibleMoves[umaxidx]->getData(*field).t;
  normal_distribution<double> dist(estTime, .01*estTime); // introduce noise with mean t and standard deviation proportional to t
  double actualTime = dist(generator);
  if(actualTime <= timeRemaining)
  {
    possibleMoves[umaxidx]->vexecute(*field);
    return actualTime < 0 ? 0 : actualTime; // on the off chance that the gaussian noise screws it up, don't let time be negative
  }
  else
    return timeRemaining;
}

SensorWrapper *Match::defaultField()
{
  SensorWrapper *f = new SensorWrapper;
  f->balls.reserve(32);
  f->goals.reserve(9);
  f->robots.reserve(4);
  Ball *t1, *t2, *t3; // temporaries for upto 3 balls in goal

  // Goals / balls in goals
  f->balls.push_back(t1 = new Ball{RED});
  f->balls.push_back(t2 = new Ball{BLUE});
  f->goals.push_back(new Goal{-66.351, 66.351, t1, t2});

  f->balls.push_back(t1 = new Ball{RED});
  f->balls.push_back(t2 = new Ball{BLUE});
  f->balls.push_back(t3 = new Ball{RED});
  f->goals.push_back(new Goal{0, 66.351, t1, t2, t3});

  f->balls.push_back(t1 = new Ball{BLUE});
  f->balls.push_back(t2 = new Ball{RED});
  f->goals.push_back(new Goal{66.351, 66.351, t1, t2});

  f->balls.push_back(t1 = new Ball{RED});
  f->balls.push_back(t2 = new Ball{BLUE});
  f->goals.push_back(new Goal{-66.351, 0, t1, t2});

  f->goals.push_back(new Goal{0, 0});

  f->balls.push_back(t1 = new Ball{BLUE});
  f->balls.push_back(t2 = new Ball{RED});
  f->goals.push_back(new Goal{66.351, 0, t1, t2});

  f->balls.push_back(t1 = new Ball{RED});
  f->balls.push_back(t2 = new Ball{BLUE});
  f->goals.push_back(new Goal{-66.351, -66.351, t1, t2});

  f->balls.push_back(t1 = new Ball{BLUE});
  f->balls.push_back(t2 = new Ball{RED});
  f->balls.push_back(t3 = new Ball{BLUE});
  f->goals.push_back(new Goal{0, -66.351, t1, t2, t3});

  f->balls.push_back(t1 = new Ball{BLUE});
  f->balls.push_back(t2 = new Ball{RED});
  f->goals.push_back(new Goal{66.351, -66.351, t1, t2});

  // Robots / Preloads
  f->balls.push_back(t1 = new Ball{RED});
  f->robots.push_back(new Robot{T_MASTER, RED_ALLIANCE, -60.0, 36.0, 90, 4, 50, t1});

  f->balls.push_back(t1 = new Ball{RED});
  f->robots.push_back(new Robot{T_SLAVE, RED_ALLIANCE, -60.0, -36.0, 90, 3, 50, t1});

  f->balls.push_back(t1 = new Ball{BLUE});
  f->robots.push_back(new Robot{T_MASTER, BLUE_ALLIANCE, 60.0, 36.0, -90, 4, 50, t1});

  f->balls.push_back(t1 = new Ball{BLUE});
  f->robots.push_back(new Robot{T_SLAVE, BLUE_ALLIANCE, 60.0, -36.0, -90, 3, 50, t1});

  // Balls on field
  f->balls.push_back(new Ball{0.0, 8.799, RED});
  f->balls.push_back(new Ball{0.0, -8.799, BLUE});
  f->balls.push_back(new Ball{8.799, 0.0, RED});
  f->balls.push_back(new Ball{-8.799, 0.0, BLUE});
  f->balls.push_back(new Ball{0.0, 36.0, RED});
  f->balls.push_back(new Ball{0.0, -36.0, BLUE});
  f->balls.push_back(new Ball{60.0, 60.0, BLUE});
  f->balls.push_back(new Ball{60.0, -60.0, BLUE});
  f->balls.push_back(new Ball{-60.0, 60.0, RED});
  f->balls.push_back(new Ball{-60.0, -60.0, RED});

  return f;
}

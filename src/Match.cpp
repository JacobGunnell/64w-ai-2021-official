#include "Match.h"

const int Match::numGoals = 9;
const int Match::numRedRobots = 1; // TODO: implement 2 on 2
const int Match::numBlueRobots = 1;
const int Match::numRobots = Match::numRedRobots + Match::numBlueRobots;
const int Match::numBalls = 32;
const int Match::defaultFieldSize = numGoals + numRobots + numBalls;

Match::Match(Brain *redBrain, Brain *blueBrain)
{
  red = new Brain(*redBrain);
  blue = new Brain(*blueBrain);
  wp = 0;
  lp = 0;
  field = defaultField();
  fieldSize = defaultFieldSize;
}

Match::Match(const Match &cpy)
{
  red = new Brain(*cpy.red);
  blue = new Brain(*cpy.blue);
  wp = cpy.wp;
  lp = cpy.lp;
  field = new GameObject*[cpy.fieldSize];
  for(int i = 0; i < cpy.fieldSize; i++)
    field[i] = cpy.field[i]->clone();
}

Match::~Match()
{
  delete red;
  delete blue;
  for(int i = 0; i < defaultFieldSize; i++)
    delete field[i];
  delete [] field;
}

Alliance Match::run()
{
  // TODO: simulate a match
  Robot **redrobots = getRedRobots(field);
  Robot **bluerobots = getBlueRobots(field);
  double redtime = 120.0;
  double bluetime = 120.0;
  while(redtime > 0 && bluetime > 0)
  {
    while(redtime >= bluetime)
    {
      makemove(redrobots, red);
    }
    while(bluetime >= redtime)
    {
      makemove(bluerobots, blue);
    }
  }

  int pred = score(RED_ALLIANCE);
  int pblue = score(BLUE_ALLIANCE);
  if(pred > pblue)
  {
    wp = pred;
    lp = pblue;
    return RED_ALLIANCE;
  }
  else
  {
    wp = pblue;
    lp = pred;
    return BLUE_ALLIANCE;
  }
}

int Match::score(Alliance a)
{
  Color c = static_cast<Color>(a);
  int score = 0;

  Goal **goals = getGoals(field);
  for(int i = 0; i < numGoals; i++)
    score += goals[i]->numBalls(c); // each scored Ball of your alliance color is worth 1 point

  int connectableRowIndices[8][3] = {{0, 1, 2},
                                     {3, 4, 5},
                                     {6, 7, 8},
                                     {0, 3, 6},
                                     {1, 4, 7},
                                     {2, 5, 8},
                                     {0, 4, 8},
                                     {2, 4, 6}};
  for(int i = 0; i < 8; i++)
    if(goals[connectableRowIndices[i][0]]->topColor() == c &&
    goals[connectableRowIndices[i][1]]->topColor() == c &&
    goals[connectableRowIndices[i][2]]->topColor() == c)
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
}

void Match::makemove(Robot **bots, Brain *brn)
{
  double umax = 0; int umaxidx;
	Move **possibleMoves;
	int len;
  len = Move::getNumExistentMoves();
  possibleMoves = Move::getAllPossibleMoves(bots[0]->getViewableWrapper(field, defaultFieldSize));
  len = Move::getNumExistentMoves() - len;
  mat U = brn->integrate(Move::getAllPossibleMovesMatrix(possibleMoves, len));
  for(int m = 0; m < len; m++)
  {
    if(U(m) > umax)
    {
      umax = U(m);
      umaxidx = m;
    }
  }
  possibleMoves[umaxidx]->vexecute(bots[0]); // TODO: implement did-this-move-work?
  for(int i = 0; i < len; i++)
    delete possibleMoves[i];
  delete [] possibleMoves;
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
  robots[ridx++] = new Robot{-60, 36, 90, 4, RED_ALLIANCE, 50,
    static_cast<Ball *>(balls[bidx++] = new Ball{RED})};
  robots[ridx++] = new Robot{-60, -36, 90, 4, RED_ALLIANCE, 50,
    static_cast<Ball *>(balls[bidx++] = new Ball{RED})};
  robots[ridx++] = new Robot{60, 36, -90, 4, BLUE_ALLIANCE, 50,
    static_cast<Ball *>(balls[bidx++] = new Ball{BLUE})};
  robots[ridx++] = new Robot{60, -36, -90, 4, BLUE_ALLIANCE, 50,
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

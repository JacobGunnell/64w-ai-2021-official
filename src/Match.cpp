#include "Match.h"

const int Match::defaultFieldSize = 45;
const int Match::numGoals = 9;
const int Match::numRedRobots = 2;
const int Match::numBlueRobots = 2;
const int Match::numRobots = Match::numRedRobots + Match::numBlueRobots;
const int Match::numBalls = 32;

Match::Match(Brain *redBrain, Brain *blueBrain)
{
  red = redBrain;
  blue = blueBrain;
  wp = 0;
  lp = 0;
  field = defaultField();
}

Alliance Match::run()
{
  // simulate a match
  int red = score(RED_ALLIANCE);
  int blue = score(BLUE_ALLIANCE);
  if(red > blue)
  {
    wp = red;
    lp = blue;
    return RED_ALLIANCE;
  }
  else
  {
    wp = blue;
    lp = red;
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
    if(goals[connectableRowIndices[i][0]]->top()->getColor() == c &&
    goals[connectableRowIndices[i][1]]->top()->getColor() == c &&
    goals[connectableRowIndices[i][2]]->top()->getColor() == c)
      score += 6; // 6 points for each Connected Row

  return score;
}

void Match::reset()
{
  wp = 0;
  lp = 0;
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

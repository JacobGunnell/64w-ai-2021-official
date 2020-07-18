#include "Match.h"

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
}

void Match::reset()
{
  wp = 0;
  lp = 0;
}

GameObject **Match::defaultField()
{
  GameObject **field = new GameObject*[45]; // 32 balls, 9 goals, 4 robots
  int idx = 0;

  // Goals / balls in goals
  field[idx++] = new Goal{0, 0};
  field[idx] = new Goal{66.351, 0,
    static_cast<Ball *>(field[idx+1] = new Ball{BLUE}),
    static_cast<Ball *>(field[idx+2] = new Ball{RED})};
    idx += 3;
  field[idx] = new Goal{-66.351, 0,
    static_cast<Ball *>(field[idx+1] = new Ball{RED}),
    static_cast<Ball *>(field[idx+2] = new Ball{BLUE})};
    idx += 3;
  field[idx] = new Goal{0, 66.351,
    static_cast<Ball *>(field[idx+1] = new Ball{RED}),
    static_cast<Ball *>(field[idx+2] = new Ball{BLUE}),
    static_cast<Ball *>(field[idx+3] = new Ball{RED})};
    idx += 4;
  field[idx] = new Goal{0, -66.351,
    static_cast<Ball *>(field[idx+1] = new Ball{BLUE}),
    static_cast<Ball *>(field[idx+2] = new Ball{RED}),
    static_cast<Ball *>(field[idx+3] = new Ball{BLUE})};
    idx += 4;
  field[idx] = new Goal{66.351, 66.351,
    static_cast<Ball *>(field[idx+1] = new Ball{BLUE}),
    static_cast<Ball *>(field[idx+2] = new Ball{RED})};
    idx += 3;
  field[idx] = new Goal{-66.351, 66.351,
    static_cast<Ball *>(field[idx+1] = new Ball{RED}),
    static_cast<Ball *>(field[idx+2] = new Ball{BLUE})};
    idx += 3;
  field[idx] = new Goal{66.351, -66.351,
    static_cast<Ball *>(field[idx+1] = new Ball{BLUE}),
    static_cast<Ball *>(field[idx+2] = new Ball{RED})};
    idx += 3;
  field[idx] = new Goal{-66.351, -66.351,
    static_cast<Ball *>(field[idx+1] = new Ball{RED}),
    static_cast<Ball *>(field[idx+2] = new Ball{BLUE})};
    idx += 3;

  // Balls on field
  field[idx++] = new Ball{0, 8.799, RED};
  field[idx++] = new Ball{0, -8.799, BLUE};
  field[idx++] = new Ball{8.799, 0, RED};
  field[idx++] = new Ball{-8.799, 0, BLUE};
  field[idx++] = new Ball{0, 36, RED};
  field[idx++] = new Ball{0, -36, BLUE};
  field[idx++] = new Ball{60, 60, BLUE};
  field[idx++] = new Ball{60, -60, BLUE};
  field[idx++] = new Ball{-60, 60, RED};
  field[idx++] = new Ball{-60, -60, RED};

  // Robots / Preloads
  field[idx] = new Robot{-60, 36, 90, 4, RED_ALLIANCE, 50,
    static_cast<Ball *>(field[idx+1] = new Ball{RED})};
    idx += 2;
  field[idx] = new Robot{-60, -36, 90, 4, RED_ALLIANCE, 50,
    static_cast<Ball *>(field[idx+1] = new Ball{RED})};
    idx += 2;
  field[idx] = new Robot{60, 36, -90, 4, BLUE_ALLIANCE, 50,
    static_cast<Ball *>(field[idx+1] = new Ball{BLUE})};
    idx += 2;
  field[idx] = new Robot{60, -36, -90, 4, BLUE_ALLIANCE, 50,
    static_cast<Ball *>(field[idx+1] = new Ball{BLUE})};
    idx += 2;

  return field;
}

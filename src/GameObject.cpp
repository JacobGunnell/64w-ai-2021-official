#include "GameObject.h"

double GameObject::distFrom(int xCoord, int yCoord)
{
  return sqrt((x - xCoord)*(x - xCoord) + (y - yCoord)*(y - yCoord));
}

GameObject **GameObject::defaultField()
{
  GameObject **field = new GameObject*[45]; // 32 balls, 9 goals, 4 robots
  int idx = 0;

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

#ifndef ROBOT_H
#define ROBOT_H


#include "Container.h"
#include "Ball.h"
#include <cmath>
#ifndef PI
#define PI 3.14159265358979323846
#endif

enum Alliance {RED_ALLIANCE=0, BLUE_ALLIANCE=1, NEITHER_ALLIANCE=-1};
Alliance operator!(const Alliance &);
enum Type {T_MASTER, T_SLAVE};

class SensorWrapper;

class Robot final : public Container // TODO: ensure that opposing alliance's balls are ejected when pushed past slot 1 (trapdoor indexer)
{
public:
  Robot() : Container(0, 0, 0) {}
  Robot(Type type, Alliance alliance, double xcoord, double ycoord, double heading_, int ballcapacity, double fov, double speed = (200.0/60.0) * 4.0*PI) : Container(xcoord, ycoord, ballcapacity), heading(heading_), _alliance(alliance), _type(type), _fov(fov), avgSpeed(speed) {}
  Robot(Type type, Alliance alliance, double xcoord, double ycoord, double heading_, int ballcapacity, double fov, Ball *b, double speed = (200.0/60.0) * 4.0*PI) : Container(xcoord, ycoord, ballcapacity), heading(heading_), _alliance(alliance), _type(type), _fov(fov), avgSpeed(speed) { pushBall(b); }

  Robot *clone() override { return new Robot(*this); }

  Alliance getAlliance() const { return _alliance; }
  Type getType() const { return _type; }
  double getFOV() const { return _fov; }
  void moveTo(double x_, double y_, double h_) { x = x_; y = y_; heading = h_; }
  void moveTo(double x_, double y_) { GameObject::moveTo(x_, y_); }
  void moveTo(GameObject &g) { GameObject::moveTo(g); }

  bool pushBall(Ball *) override;
  bool ejectBall(int);

  SensorWrapper &getViewableWrapper(GameObject **, const int);
  SensorWrapper &getViewableWrapper(SensorWrapper &);

  double heading;
  double avgSpeed; // rough estimate of robot speed in inches per second

private:
  Alliance _alliance;
  Type _type;
  double _fov;
};

#include "SensorWrapper.h"

#endif // ROBOT_H

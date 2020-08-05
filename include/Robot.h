#ifndef ROBOT_H
#define ROBOT_H


#include "Container.h"
#include "SensorWrapper.h"
#include <cmath>
#ifndef PI
#define PI 3.14159265358979323846
#endif

enum Alliance {RED_ALLIANCE=0, BLUE_ALLIANCE=1, NEITHER_ALLIANCE=-1};
enum Type {T_MASTER, T_SLAVE};

class Robot final : public Container
{
public:
  Robot(Type type, Alliance alliance, double xcoord, double ycoord, double heading_, int ballcapacity, double fov, double speed = (200.0/60.0) * 4.0*PI) : Container(xcoord, ycoord, ballcapacity), heading(heading_), _alliance(alliance), _type(type), _fov(fov), avgSpeed(speed) {}
  Robot(Type type, Alliance alliance, double xcoord, double ycoord, double heading_, int ballcapacity, double fov, Ball *b, double speed = (200.0/60.0) * 4.0*PI) : Container(xcoord, ycoord, ballcapacity), heading(heading_), _alliance(alliance), _type(type), _fov(fov), avgSpeed(speed) { balls.push_back(b); }
  ~Robot() = default;

  Robot *clone() override { return new Robot(*this); }

  Alliance getAlliance() const { return _alliance; }
  Type getType() const { return _type; }
  double getFOV() const { return _fov; }
  void moveTo(double x_, double y_, double h_) { x = x_; y = y_; heading = h_; }
  void moveTo(double x_, double y_) { x = x_; y = y_; }
  void moveTo(GameObject *g) { moveTo(g->x, g->y); }

  SensorWrapper getViewableWrapper(GameObject **, const int);

  double heading;
  double avgSpeed; // rough estimate of robot speed in inches per second

private:
  Alliance _alliance;
  Type _type;
  double _fov;
};

#endif // ROBOT_H

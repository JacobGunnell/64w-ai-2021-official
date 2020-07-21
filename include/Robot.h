#ifndef ROBOT_H
#define ROBOT_H


#include "Container.h"
#include "SensorWrapper.h"
#include "cmath"
#define PI 3.14159265

enum Alliance {RED_ALLIANCE=0, BLUE_ALLIANCE=1};

class Robot : public Container
{
public:
  Robot(double xcoord, double ycoord, double heading_, int ballcapacity, Alliance alliance, double fov) : Container(xcoord, ycoord, ballcapacity), heading(heading_), _alliance(alliance), _fov(fov) {}
  Robot(double xcoord, double ycoord, double heading_, int ballcapacity, Alliance alliance, double fov, Ball *b) : Container(xcoord, ycoord, ballcapacity), heading(heading_), _alliance(alliance), _fov(fov) { balls.push_back(b); }

  Alliance getAlliance() const { return _alliance; }
  void moveTo(double x_, double y_, double h_) { x = x_; y = y_; heading = h_; }
  void moveTo(double x_, double y_) { x = x_; y = y_; }

  SensorWrapper getViewableWrapper(GameObject **, const int);

  double heading;

private:
  Alliance _alliance;
  double _fov;
};

#endif // ROBOT_H

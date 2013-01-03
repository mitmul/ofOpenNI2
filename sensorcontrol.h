#ifndef SENSORCONTROL_H
#define SENSORCONTROL_H

#include <NiTE.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;
using namespace openni;
using namespace nite;

typedef vector<vector<Point3f> > Skeletons;

class SensorControl
{
  public:
    SensorControl();

    bool getDeviceInitializeState();

    Skeletons getSkeletons(const bool convert = false);
    DepthPixel* getDepth();
    char* getColor();

    int getColorWidth();
    int getColorHeight();
    int getDepthWidth();
    int getDepthHeight();

    void setRegistration(const bool fit_to_color);

  private:
    void outputError(const string &what);
    void setupDepth();
    void setupColor();

    Device device;
    VideoStream depth;
    VideoStream color;
    UserTracker user_tracker;
    Skeletons skeletons;

    bool initialize_finished;
};

#endif // SENSORCONTROL_H

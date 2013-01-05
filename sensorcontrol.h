#ifndef SENSORCONTROL_H
#define SENSORCONTROL_H

#include <NiTE.h>
#include <opencv.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;
using namespace openni;
using namespace cv;
using namespace nite;

typedef vector<vector<nite::Point3f> > Skeletons;

class SensorControl
{
  public:
    SensorControl(const string &file_name = "");
    ~SensorControl();

    Skeletons getSkeletons(const bool convert = false);
    DepthPixel* getDepthPixels();
    Mat getDepthImage(const bool convert_to_8bit = false);
    char* getColorPixels();
    Mat getColorImage();
    vector<UserId*> getUserMasks();
    vector<Point3d> getPoints();

    void startRecording();
    void stopRecording();

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
    UserTracker *user_tracker;
    Skeletons skeletons;

    Recorder *recorder;
    string oni_name;
};

#endif // SENSORCONTROL_H

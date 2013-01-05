#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/signals2.hpp>
#include <ofMain.h>
#include <ofAppGlutWindow.h>
#include <opencv.hpp>
#include <vector>
#include "testapp.h"
#include "sensorcontrol.h"

void slotColor(const cv::Mat &color);
void slotDepth(const cv::Mat &depth);
void slotPoint(const vector<cv::Point3d> &point);
void slotSendColor();
void slotSendDepth();
void slotSendPoint();
void slotClose();

testApp *of_widget;
SensorControl *sensor;

boost::signals2::signal<void (const cv::Mat&)> sig_color;
boost::signals2::signal<void (const cv::Mat&)> sig_depth;
boost::signals2::signal<void (const vector<cv::Point3d>&)> sig_point;

int main(int argc, char *argv[])
{
  sensor = new SensorControl();

  of_widget = new testApp();
  sig_color.connect(&slotColor);
  sig_depth.connect(&slotDepth);
  sig_point.connect(&slotPoint);
  of_widget->sig_color.connect(&slotSendColor);
  of_widget->sig_depth.connect(&slotSendDepth);
  of_widget->sig_point.connect(&slotSendPoint);
  of_widget->sig_close.connect(&slotClose);

  ofAppGlutWindow window;
  ofSetupOpenGL(&window, 1000, 600, OF_WINDOW);
  ofRunApp(of_widget);

  delete of_widget;
  delete sensor;

  return 0;
}

void slotColor(const cv::Mat &color)
{
  of_widget->slotColor(color);
}

void slotDepth(const cv::Mat &depth)
{
  of_widget->slotDepth(depth);
}

void slotPoint(const vector<Point3d> &point)
{
  of_widget->slotPoint(point);
}

void slotSendColor()
{
  cv::Mat color = sensor->getColorImage();
  sig_color(color);
}

void slotSendDepth()
{
  cv::Mat depth = sensor->getDepthImage(true);
  sig_depth(depth);
}

void slotSendPoint()
{
  vector<cv::Point3d> point = sensor->getPoints();
  sig_point(point);
}

void slotClose()
{
  delete sensor;
}

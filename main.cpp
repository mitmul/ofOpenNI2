#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/signals2.hpp>
#include <ofMain.h>
#include <ofAppGlutWindow.h>
#include <opencv.hpp>
#include "testapp.h"
#include "sensorcontrol.h"

void getSensor();
cv::Mat getDepth();
cv::Mat getColor();
void slotColor(const cv::Mat &color);
void slotDepth(const cv::Mat &depth);

testApp *of_widget;
SensorControl *sensor;

boost::signals2::signal<void (const cv::Mat&)> sig_color;
boost::signals2::signal<void (const cv::Mat&)> sig_depth;

int main(int argc, char *argv[])
{
  boost::thread sensor_thread(&getSensor);

  of_widget = new testApp();
  sig_color.connect(&slotColor);
  sig_depth.connect(&slotDepth);

  ofAppGlutWindow window;
  ofSetupOpenGL(&window, 1024,768, OF_WINDOW);
  ofRunApp(of_widget);

  delete of_widget;

  return 0;
}

void getSensor()
{
  sensor = new SensorControl();

  while(1)
  {
    cv::Mat color = getColor();
    cv::Mat depth = getDepth();

    sig_color(color);
    sig_depth(depth);
  }

  delete sensor;
}

cv::Mat getDepth()
{
  cv::Mat depth(sensor->getDepthHeight(), sensor->getDepthWidth(), CV_16UC1, sensor->getDepth());
  depth.convertTo(depth, CV_8UC1, 255.0 / 10000.0);
  return depth;
}

cv::Mat getColor()
{
  cv::Mat color(sensor->getColorHeight(), sensor->getColorWidth(), CV_8UC3, sensor->getColor());
  cv::cvtColor(color, color, cv::COLOR_BGR2RGB);
  return color;
}

void slotColor(const cv::Mat &color)
{
  of_widget->slotColor(color);
}

void slotDepth(const cv::Mat &depth)
{
  of_widget->slotDepth(depth);
}

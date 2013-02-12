#pragma once

#include <ofMain.h>
#include <opencv.hpp>
#include <OpenNI.h>
#include "sensorcontrol.h"

class testApp : public ofBaseApp
{
  public:
    testApp();
    ~testApp();

    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    void slotColor(const cv::Mat &color);
    void slotDepth(const cv::Mat &depth);
    void slotPoint(const vector<cv::Point3d> &point);

  protected:
    SensorControl *sensor;
    cv::Mat depth_image;
    cv::Mat color_image;
    vector<cv::Point3d> world_point;

    ofEasyCam camera;
    ofMesh mesh;

    int trans_x, trans_y;
    double scale;
};

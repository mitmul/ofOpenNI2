#pragma once

#include <ofMain.h>
#include <opencv.hpp>
#include <boost/signals2.hpp>
#include <OpenNI.h>

class testApp : public ofBaseApp{

  public:
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

    boost::signals2::signal<void ()> sig_depth;
    boost::signals2::signal<void ()> sig_color;
    boost::signals2::signal<void ()> sig_point;
    boost::signals2::signal<void ()> sig_close;

  private:
    cv::Mat depth_image;
    cv::Mat color_image;
    vector<cv::Point3d> world_point;

    ofEasyCam camera;
    ofMesh mesh;

    int trans_x, trans_y;
    double scale;
};

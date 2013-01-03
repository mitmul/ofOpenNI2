#include "testapp.h"

void testApp::setup()
{
  ofBackground(0, 0, 0);
  ofSetFrameRate(60);
}

void testApp::update()
{

}

void testApp::draw()
{
  ofCircle(mouseX, mouseY, 5.0f);
}

void testApp::keyPressed(int key)
{

}

void testApp::keyReleased(int key)
{

}

void testApp::mouseMoved(int x, int y)
{

}

void testApp::mouseDragged(int x, int y, int button)
{

}

void testApp::mousePressed(int x, int y, int button)
{

}

void testApp::mouseReleased(int x, int y, int button)
{

}

void testApp::windowResized(int w, int h)
{

}

void testApp::gotMessage(ofMessage msg)
{

}

void testApp::slotColor(const cv::Mat &color)
{
  cv::imshow("Color", color);
}

void testApp::slotDepth(const cv::Mat &depth)
{
  cv::imshow("Depth", depth);
}

void testApp::dragEvent(ofDragInfo dragInfo)
{

}

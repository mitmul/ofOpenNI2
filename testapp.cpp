#include "testapp.h"

testApp::testApp()
{
  sensor = new SensorControl();
}

testApp::~testApp()
{
  delete sensor;
}

void testApp::setup()
{
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_POINT_SMOOTH);
  glPointSize(3);

  trans_x = 0;
  trans_y = 0;
  scale = 2.0;
}

void testApp::update()
{
  slotColor(sensor->getColorImage());
  slotDepth(sensor->getDepthImage(true));
  slotPoint(sensor->getPoints());
}

void testApp::draw()
{
  ofBackgroundGradient(ofColor::gray, ofColor::black, OF_GRADIENT_CIRCULAR);

  camera.begin();
  ofScale(scale, scale, scale);
  ofRotateY(180);
  ofTranslate(-color_image.cols + trans_x, -color_image.rows + trans_y);
  mesh.draw();
  camera.end();
}

void testApp::keyPressed(int key)
{
  switch(key)
  {
  // left
  case 356:
    trans_x += 100;
    break;

    // up
  case 357:
    trans_y += 100;
    break;

    // right
  case 358:
    trans_x -= 100;
    break;

    // down
  case 359:
    trans_y -= 100;
    break;

    // w
  case 119:
    scale -= 1.0;
    break;

    // z
  case 122:
    scale += 1.0;
    break;

    // esc
  case 27:
    break;
  }
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
  try
  {
    color_image = color.clone();
    cv::imshow("Color", color);

    cout << "slotColor" << endl;
  }
  catch(std::exception &ex)
  {
    cerr << "testApp::slotColor()"
         << ex.what() << endl;
  }
}

void testApp::slotDepth(const cv::Mat &depth)
{
  try
  {
    depth_image = depth.clone();
    cv::imshow("Depth", depth);

    cout << "slotDepth" << endl;
  }
  catch(std::exception &ex)
  {
    cerr << "testApp::slotDepth()"
         << ex.what() << endl;
  }
}

void testApp::slotPoint(const vector<cv::Point3d> &point)
{
  try
  {
    world_point = point;

    mesh.clear();
    mesh.setMode(OF_PRIMITIVE_POINTS);

    for(int y = 0; y < color_image.rows; ++y)
    {
      for(int x = 0; x < color_image.cols; ++x)
      {
        // RGB画像から色を取得
        cv::Vec3b c = color_image.at<cv::Vec3b>(y, x);
        ofColor color(c[2], c[1], c[0]);

        // 三次元点
        cv::Point3d pos = world_point[y * color_image.cols + x];

        mesh.addColor(color);
        mesh.addVertex(ofVec3f(pos.x, pos.y, pos.z));
      }
    }

    cout << "slotPoint" << endl;
  }
  catch(std::exception &ex)
  {
    cerr << "testApp::slotPoint()"
         << ex.what() << endl;
  }
}

void testApp::dragEvent(ofDragInfo dragInfo)
{

}


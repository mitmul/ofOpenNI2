#include "sensorcontrol.h"

SensorControl::SensorControl(const string &file_name)
  : oni_name(file_name),
    recorder(NULL),
    user_tracker(NULL)
{
  openni::Status rc = openni::STATUS_OK;

  rc = OpenNI::initialize();
  outputError("After initialization");

  // デバイスの起動（もしくはファイルから読み込み）
  char* uri;
  if(!file_name.empty())
    uri = file_name.c_str();
  else
    uri = ANY_DEVICE;
  const char *deviceURI = uri;

  rc = device.open(deviceURI);
  if(rc != openni::STATUS_OK)
  {
    outputError("Device open failed");
    OpenNI::shutdown();
  }

  setupDepth();
  setupColor();

  setRegistration(true);

  if(oni_name.empty())
  {
    NiTE::initialize();
    user_tracker = new UserTracker();
    rc = (openni::Status)user_tracker->create();
    if(rc != openni::STATUS_OK)
    {
      outputError("User tracker create failed");
      OpenNI::shutdown();
    }
  }
}

SensorControl::~SensorControl()
{
  if(recorder != NULL)
  {
    stopRecording();
    recorder->destroy();
    delete recorder;
  }

  depth.stop();
  color.stop();
  depth.destroy();
  color.destroy();
  device.close();
  OpenNI::shutdown();

  if(user_tracker != NULL)
  {
    delete user_tracker;
  }
  NiTE::shutdown();
}

Skeletons SensorControl::getSkeletons(const bool convert)
{
  Skeletons skeletons;

  UserTrackerFrameRef user_frame;
  user_tracker->readFrame(&user_frame);
  const nite::Array<UserData> &users = user_frame.getUsers();

  for(int i = 0; i < users.getSize(); ++i)
  {
    const UserData& user = users[i];

    if(user.isNew())
    {
      user_tracker->startSkeletonTracking(user.getId());
    }
    else if(!user.isLost())
    {
      vector<nite::Point3f> user_skeleton;

      const Skeleton& skeleton = user.getSkeleton();

      if(skeleton.getState() == SKELETON_TRACKED)
      {
        for(int j = 0; j < 15; ++j)
        {
          const SkeletonJoint& joint = skeleton.getJoint((JointType)j);
          if(joint.getPositionConfidence() >= 0.7f)
          {
            const nite::Point3f& position = joint.getPosition();

            if(convert)
            {
              float x, y;
              user_tracker->convertJointCoordinatesToDepth(position.x, position.y, position.z, &x, &y);

              nite::Point3f pos(x, y, position.z);
              user_skeleton.push_back(pos);
            }
            else
            {
              user_skeleton.push_back(position);
            }
          }
        }
      }

      skeletons.push_back(user_skeleton);
    }
  }

  return skeletons;
}

DepthPixel *SensorControl::getDepthPixels()
{
  DepthPixel *depth_pixel;
  VideoStream *stream = &depth;

  int ready_index;
  OpenNI::waitForAnyStream(&stream, 1, &ready_index);

  if(ready_index == 0)
  {
    VideoFrameRef depth_frame;
    depth.readFrame(&depth_frame);

    if(depth_frame.isValid())
    {
      depth_pixel = (DepthPixel*)depth_frame.getData();
    }
  }

  return depth_pixel;
}

char *SensorControl::getColorPixels()
{
  char *color_pixel;

  VideoStream *stream = &color;

  int ready_index;
  OpenNI::waitForAnyStream(&stream, 1, &ready_index);

  if(ready_index == 0)
  {
    VideoFrameRef color_frame;
    color.readFrame(&color_frame);

    if(color_frame.isValid())
    {
      color_pixel = (char*)color_frame.getData();
    }
  }

  return color_pixel;
}

vector<UserId *> SensorControl::getUserMasks()
{
  vector<UserId *> user_masks;

  UserTrackerFrameRef user_frame;
  user_tracker->readFrame(&user_frame);

  VideoFrameRef depth_frame = user_frame.getDepthFrame();
  if(depth_frame.isValid())
  {
    VideoMode mode = depth_frame.getVideoMode();
    DepthPixel *depth = (DepthPixel *)depth_frame.getData();
    UserId *label = const_cast<UserId *>(user_frame.getUserMap().getPixels());
    user_masks.push_back(label);
  }

  return user_masks;
}

vector<Point3d> SensorControl::getPoints()
{
  vector<Point3d> points;

  VideoFrameRef depth_frame;
  depth.readFrame(&depth_frame);

  if(depth_frame.isValid())
  {
    DepthPixel *depth_pixel = (DepthPixel *)depth_frame.getData();
    VideoMode mode = depth.getVideoMode();

    for(int y = 0; y < mode.getResolutionY(); ++y)
    {
      for(int x = 0; x < mode.getResolutionX(); ++x)
      {
        float xpos, ypos, zpos;
        DepthPixel pixel = depth_pixel[y * mode.getResolutionX() + x];
        CoordinateConverter::convertDepthToWorld(depth, x, y, pixel, &xpos, &ypos, &zpos);

        Point3d point(xpos, ypos, zpos);
        points.push_back(point);
      }
    }
  }

  return points;
}

void SensorControl::startRecording()
{
  recorder = new Recorder();
  recorder->create("sensor.oni");
  recorder->attach(depth, true);
  recorder->attach(color, true);
  recorder->start();
}

void SensorControl::stopRecording()
{
  recorder->stop();
}

int SensorControl::getColorWidth()
{
  return color.getVideoMode().getResolutionX();
}

int SensorControl::getColorHeight()
{
  return color.getVideoMode().getResolutionY();
}

int SensorControl::getDepthWidth()
{
  return depth.getVideoMode().getResolutionX();
}

int SensorControl::getDepthHeight()
{
  return depth.getVideoMode().getResolutionY();
}

void SensorControl::setRegistration(const bool fit_to_color)
{
  if(fit_to_color)
  {
    device.setImageRegistrationMode(IMAGE_REGISTRATION_DEPTH_TO_COLOR);
  }
  else
  {
    device.setImageRegistrationMode(IMAGE_REGISTRATION_OFF);
  }
}

void SensorControl::outputError(const string &what)
{
  cout << what << endl << OpenNI::getExtendedError() << endl;
}

void SensorControl::setupDepth()
{
  openni::Status rc = openni::STATUS_OK;

  // 解像度など
  VideoMode depth_mode;
  depth_mode.setPixelFormat(PIXEL_FORMAT_DEPTH_1_MM);
  depth_mode.setResolution(640, 480);
  depth_mode.setFps(30);

  // デプス初期化
  rc = depth.create(device, SENSOR_DEPTH);
  if(rc == openni::STATUS_OK)
  {
    if(oni_name.empty())
    {
      rc = depth.setVideoMode(depth_mode);
      if(rc != openni::STATUS_OK)
      {
        outputError("Couldn't set depth video mode");
        depth.destroy();
      }
    }

    rc = depth.start();
    if(rc != openni::STATUS_OK)
    {
      outputError("Couldn't start depth stream");
      depth.destroy();
    }
  }
  else
  {
    outputError("Couldn't find depth stream");
  }
}

void SensorControl::setupColor()
{
  openni::Status rc = openni::STATUS_OK;

  // 解像度など
  VideoMode color_mode;
  color_mode.setPixelFormat(PIXEL_FORMAT_RGB888);
  color_mode.setResolution(640, 480);
  color_mode.setFps(30);

  // カラー初期化
  rc = color.create(device, SENSOR_COLOR);
  if(rc == openni::STATUS_OK)
  {
    if(oni_name.empty())
    {
      rc = color.setVideoMode(color_mode);
      if(rc != openni::STATUS_OK)
      {
        outputError("Couldn't set color video mode");
        color.destroy();
      }
    }

    rc = color.start();
    if(rc != openni::STATUS_OK)
    {
      outputError("Couldn't start color stream");
      color.destroy();
    }
  }
  else
  {
    outputError("Couldn't find color stream");
  }
}

Mat SensorControl::getDepthImage(const bool convert_to_8bit)
{
  cv::Mat image(getDepthHeight(), getDepthWidth(), CV_16UC1, getDepthPixels());
  if(convert_to_8bit)
  {
    image.convertTo(image, CV_8U, 255.0 / (double)depth.getMaxPixelValue());
  }
  return image;
}

Mat SensorControl::getColorImage()
{
  Mat image(getColorHeight(), getColorWidth(), CV_8UC3, getColorPixels());
  cvtColor(image, image, COLOR_BGR2RGB);

  return image;
}

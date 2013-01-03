#include "sensorcontrol.h"

SensorControl::SensorControl()
  : initialize_finished(false)
{
  openni::Status rc = openni::STATUS_OK;

  rc = OpenNI::initialize();
  outputError("After initialization");

  // デバイスの起動
  const char* deviceURI = ANY_DEVICE;
  rc = device.open(deviceURI);
  if(rc != openni::STATUS_OK)
  {
    outputError("Device open failed");
    OpenNI::shutdown();
  }

  setupDepth();
  setupColor();
  setRegistration(true);

  NiTE::initialize();
  rc = (openni::Status)user_tracker.create();
  if(rc != openni::STATUS_OK)
  {
    outputError("User tracker create failed");
    OpenNI::shutdown();
  }

  initialize_finished = true;
}

bool SensorControl::getDeviceInitializeState()
{
  return initialize_finished;
}

Skeletons SensorControl::getSkeletons(const bool convert)
{
  Skeletons skeletons;

  UserTrackerFrameRef user_frame;
  user_tracker.readFrame(&user_frame);
  const nite::Array<UserData> &users = user_frame.getUsers();

  for(int i = 0; i < users.getSize(); ++i)
  {
    const UserData& user = users[i];

    if(user.isNew())
    {
      user_tracker.startSkeletonTracking(user.getId());
    }
    else if(!user.isLost())
    {
      vector<Point3f> user_skeleton;

      const Skeleton& skeleton = user.getSkeleton();

      if(skeleton.getState() == SKELETON_TRACKED)
      {
        for(int j = 0; j < 15; ++j)
        {
          const SkeletonJoint& joint = skeleton.getJoint((JointType)j);
          if(joint.getPositionConfidence() >= 0.7f)
          {
            const Point3f& position = joint.getPosition();

            if(convert)
            {
              float x, y;
              user_tracker.convertJointCoordinatesToDepth(position.x, position.y, position.z, &x, &y);

              Point3f pos(x, y, position.z);
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

DepthPixel *SensorControl::getDepth()
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

char *SensorControl::getColor()
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
    rc = depth.setVideoMode(depth_mode);
    if(rc != openni::STATUS_OK)
    {
      outputError("Couldn't set depth video mode");
      depth.destroy();
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
    rc = color.setVideoMode(color_mode);
    if(rc != openni::STATUS_OK)
    {
      outputError("Couldn't set color video mode");
      color.destroy();
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

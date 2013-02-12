#include <QApplication>
#include <ofAppGlutWindow.h>

#include "mainwindow.h"
#include "sensorcontrol.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  ofPtr<ofAppGlutWindow> window(new ofAppGlutWindow);
  ofSetupOpenGL(window, 1280, 800, OF_WINDOW);

  ofPtr<MainWindow> main_window(new MainWindow);
  ofRunApp(main_window);

  return a.exec();
}

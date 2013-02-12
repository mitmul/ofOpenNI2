TEMPLATE = app

QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS_WARN_ON += "-Wno-unused-parameter"
QMAKE_CXXFLAGS += -fpermissive
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3

SOURCES += main.cpp \
    testapp.cpp \
    sensorcontrol.cpp \
    mainwindow.cpp

HEADERS += \
    testapp.h \
    sensorcontrol.h \
    mainwindow.h

# OpenCV 32bit
LIBS += -L/opt/local/lib \
  -lopencv_calib3d \
  -lopencv_ml \
  -lopencv_contrib \
  -lopencv_nonfree \
  -lopencv_core \
  -lopencv_objdetect \
  -lopencv_features2d \
  -lopencv_photo \
  -lopencv_flann \
  -lopencv_stitching \
  -lopencv_gpu \
  -lopencv_ts \
  -lopencv_highgui \
  -lopencv_video \
  -lopencv_imgproc \
  -lopencv_videostab \
  -lopencv_legacy
INCLUDEPATH += /opt/local/include/opencv \
  /opt/local/include/opencv2

# boost 32bit
INCLUDEPATH += /opt/local/include
LIBS += -L/opt/local/lib \
  -lboost_chrono \
  -lboost_date_time \
  -lboost_filesystem \
  -lboost_graph \
  -lboost_iostreams \
  -lboost_locale \
  -lboost_math_c99 \
  -lboost_math_c99f \
  -lboost_math_c99l \
  -lboost_math_tr1 \
  -lboost_math_tr1f \
  -lboost_math_tr1l \
  -lboost_prg_exec_monitor \
  -lboost_program_options \
  -lboost_python \
  -lboost_random \
  -lboost_regex \
  -lboost_serialization \
  -lboost_signals \
  -lboost_system \
  -lboost_thread \
  -lboost_timer \
  -lboost_unit_test_framework \
  -lboost_wave \
  -lboost_wserialization

# OpenNI/NiTE
INCLUDEPATH += /opt/local/OpenNI-2.1.0/Include \
  /opt/local/NiTE-2.0.0/Include
LIBS += -L/opt/local/OpenNI-2.1.0/Redist \
  -lOpenNI2 \
  -L/opt/local/OpenNI-2.1.0/Redist/OpenNI2/Drivers \
  -lOniFile \
  -lPS1080 \
  -L/opt/local/NiTE-2.0.0/Redist \
  -lNiTE2

# openFrameworks
INCLUDEPATH += /opt/local/of_v0073_osx_release/libs/openFrameworks \
  /opt/local/of_v0073_osx_release/libs/openFrameworks/3d \
  /opt/local/of_v0073_osx_release/libs/openFrameworks/app \
  /opt/local/of_v0073_osx_release/libs/openFrameworks/communication \
  /opt/local/of_v0073_osx_release/libs/openFrameworks/events \
  /opt/local/of_v0073_osx_release/libs/openFrameworks/gl \
  /opt/local/of_v0073_osx_release/libs/openFrameworks/graphics \
  /opt/local/of_v0073_osx_release/libs/openFrameworks/math \
  /opt/local/of_v0073_osx_release/libs/openFrameworks/sound \
  /opt/local/of_v0073_osx_release/libs/openFrameworks/types \
  /opt/local/of_v0073_osx_release/libs/openFrameworks/utils \
  /opt/local/of_v0073_osx_release/libs/openFrameworks/video \
  /opt/local/of_v0073_osx_release/libs/glew/include \
  /opt/local/of_v0073_osx_release/libs/glut/include \
  /opt/local/of_v0073_osx_release/libs/cairo/include/cairo \
  /opt/local/of_v0073_osx_release/libs/tess2/include \
  /opt/local/of_v0073_osx_release/libs/poco/include \
  /opt/local/of_v0073_osx_release/libs/fmodex/include
LIBS += -framework Accelerate \
  -framework AppKit \
  -framework Cocoa \
  -framework IOKit \
  -framework QTKit \
  -framework CoreVideo \
  -framework AGL \
  -framework ApplicationServices \
  -framework AudioToolbox \
  -framework Carbon \
  -framework CoreAudio \
  -framework CoreFoundation \
  -framework CoreServices \
  -framework OpenGL \
  -framework QuickTime
LIBS += /opt/local/of_v0073_osx_release/libs/openFrameworksCompiled/lib/osx/openFrameworks.a
LIBS += /opt/local/of_v0073_osx_release/libs/glew/lib/osx/glew.a
LIBS += /opt/local/of_v0073_osx_release/libs/tess2/lib/osx/tess2.a
LIBS += /opt/local/of_v0073_osx_release/libs/poco/lib/osx/PocoCrypto.a
LIBS += /opt/local/of_v0073_osx_release/libs/poco/lib/osx/PocoData.a
LIBS += /opt/local/of_v0073_osx_release/libs/poco/lib/osx/PocoDataODBC.a
LIBS += /opt/local/of_v0073_osx_release/libs/poco/lib/osx/PocoDataSQLite.a
LIBS += /opt/local/of_v0073_osx_release/libs/poco/lib/osx/PocoFoundation.a
LIBS += /opt/local/of_v0073_osx_release/libs/poco/lib/osx/PocoNet.a
LIBS += /opt/local/of_v0073_osx_release/libs/poco/lib/osx/PocoNetSSL.a
LIBS += /opt/local/of_v0073_osx_release/libs/poco/lib/osx/PocoUtil.a
LIBS += /opt/local/of_v0073_osx_release/libs/poco/lib/osx/PocoXML.a
LIBS += /opt/local/of_v0073_osx_release/libs/poco/lib/osx/PocoZip.a
LIBS += /opt/local/of_v0073_osx_release/libs/cairo/lib/osx/cairo-script-interpreter.a
LIBS += /opt/local/of_v0073_osx_release/libs/cairo/lib/osx/cairo.a
LIBS += /opt/local/of_v0073_osx_release/libs/cairo/lib/osx/pixman-1.a
LIBS += /opt/local/of_v0073_osx_release/libs/fmodex/lib/osx/libfmodex.dylib
QMAKE_LFLAGS += -F/opt/local/of_v0073_osx_release/libs/glut/lib/osx/
LIBS += -framework GLUT

FORMS += \
    mainwindow.ui

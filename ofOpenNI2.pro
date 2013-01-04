TEMPLATE = app
CONFIG += console
CONFIG -= qt

QMAKE_CXXFLAGS_WARN_ON += "-Wno-unused-parameter"
QMAKE_CXXFLAGS += -fpermissive

SOURCES += main.cpp \
    testapp.cpp \
    sensorcontrol.cpp

HEADERS += \
    testapp.h \
    sensorcontrol.h

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
INCLUDEPATH += /opt/local/OpenNI/include \
  /opt/local/NiTE/include
LIBS += -L/opt/local/OpenNI/lib \
  -lOpenNI2 \
  -L/opt/local/OpenNI/lib/OpenNI2/Drivers \
  -lOniFile \
  -lPS1080 \
  -L/opt/local/NiTE/lib \
  -lNiTE2

# openFrameworks
INCLUDEPATH += /opt/local/openFrameworks/openFrameworks \
  /opt/local/openFrameworks/openFrameworks/3d \
  /opt/local/openFrameworks/openFrameworks/app \
  /opt/local/openFrameworks/openFrameworks/communication \
  /opt/local/openFrameworks/openFrameworks/events \
  /opt/local/openFrameworks/openFrameworks/gl \
  /opt/local/openFrameworks/openFrameworks/graphics \
  /opt/local/openFrameworks/openFrameworks/math \
  /opt/local/openFrameworks/openFrameworks/sound \
  /opt/local/openFrameworks/openFrameworks/types \
  /opt/local/openFrameworks/openFrameworks/utils \
  /opt/local/openFrameworks/openFrameworks/video \
  /opt/local/openFrameworks/glew/include \
  /opt/local/openFrameworks/glut/include \
  /opt/local/openFrameworks/cairo/include/cairo \
  /opt/local/openFrameworks/tess2/include \
  /opt/local/openFrameworks/poco/include \
  /opt/local/openFrameworks/fmodex/include
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
LIBS += /opt/local/openFrameworks/openFrameworksCompiled/lib/osx/openFrameworks.a
LIBS += /opt/local/openFrameworks/glew/lib/osx/glew.a
LIBS += /opt/local/openFrameworks/tess2/lib/osx/tess2.a
LIBS += /opt/local/openFrameworks/poco/lib/osx/PocoCrypto.a
LIBS += /opt/local/openFrameworks/poco/lib/osx/PocoData.a
LIBS += /opt/local/openFrameworks/poco/lib/osx/PocoDataODBC.a
LIBS += /opt/local/openFrameworks/poco/lib/osx/PocoDataSQLite.a
LIBS += /opt/local/openFrameworks/poco/lib/osx/PocoFoundation.a
LIBS += /opt/local/openFrameworks/poco/lib/osx/PocoNet.a
LIBS += /opt/local/openFrameworks/poco/lib/osx/PocoNetSSL.a
LIBS += /opt/local/openFrameworks/poco/lib/osx/PocoUtil.a
LIBS += /opt/local/openFrameworks/poco/lib/osx/PocoXML.a
LIBS += /opt/local/openFrameworks/poco/lib/osx/PocoZip.a
LIBS += /opt/local/openFrameworks/cairo/lib/osx/cairo-script-interpreter.a
LIBS += /opt/local/openFrameworks/cairo/lib/osx/cairo.a
LIBS += /opt/local/openFrameworks/cairo/lib/osx/pixman-1.a
LIBS += /opt/local/openFrameworks/fmodex/lib/osx/libfmodex.dylib
QMAKE_LFLAGS += -F/opt/local/openFrameworks/glut/lib/osx/
LIBS += -framework GLUT

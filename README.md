OpenNI2 & NiTE2 with openFrameworks (OSX Mountain Lion)
======================

Requirement
------

### Qt 4.7.4 (32bit build) ###
1. Get 10.6SDK from http://yoppa.org/blog/4025.html
2. $git clone git://gitorious.org/qt/digia-qt.git
3. $./configure -arch i386 -sdk ~/Download/MacOSX10.6.sdk -carbon
4. $make
5. $make install

### OpenCV2.3.1 or newer (32bit Build) ###
1. Get OpenCV sources http://sourceforge.net/projects/opencvlibrary/files/
2. $mkdir build
3. $cd build
4. $ccmake ../
5. Set some params as below:
	+ CMAKE_INSTALL_PREFIX=/opt/local
	+ CMAKE_OSX_ARCHITECTURES=i386
	+ CMAKE_C_FLAGS=-m32
	+ CMAKE_CXX_FLAGS=-m32
	+ WITH_FFMPEG=OFF
6. Press [c] & Press [g] & Press [q]
7. $make -j8
8. $sudo make install

### boost 1.52 (32bit Build) ###
1. Get boost from http://www.boost.org/users/download/
2. $./bootstrap.sh toolset=darwin address-model=32 architecture=x86
3. $sudo ./bjam install --prefix=/opt/local --libdir=/opt/local/lib address-model=32 architecture=x86

### OpenNI2 & NiTE2 (OSX) ###
1. Get them from http://www.openni.org/openni-sdk/
2. Copy files under Redist dir to /opt/local/OpenNI/lib or /opt/local/NiTE/lib and files under Include dir to /opt/local/OpenNI/include or /opt/local/NiTE/include
3. $install_name_tool -id /opt/local/OpenNI/lib/libOpenNI2.dylib libOpenNI2.dylib4. $install_name_tool -id /opt/local/OpenNI/lib/OpenNI2/Drivers/libOniFile.dylib libOniFile.dylib5. $install_name_tool -id /opt/local/OpenNI/lib/OpenNI2/Drivers/libPS1080.dylib libPS1080.dylib6. $install_name_tool -id /opt/local/NiTE/lib/libNiTE2.dylib libNiTE2.dylib7. $install_name_tool -change libOpenNI2.dylib /opt/local/OpenNI/lib/libOpenNI2.dylib libNiTE2.dylib

### openFrameworks (v0073) ###
1. Build with XCode
2. Copy libs folder to /opt/local and rename the folder "openFrameworks"
3. $install_name_tool -id /opt/local/openFrameworks/fmodex/lib/osx libfmodex.dylib libfmodex.dylib
4. $install_name_tool -id /opt/local/openFrameworks/glut/lib/osx/GLUT.framework/GLUT GLUT
 
Before Run
----------------
+ Copy below files to executable file dir
	+ All boost dylib files
	+ All files under OpenNI-2.0.0/Redist
	+ All files under NiTE-2.0.0/Redist
+ Make "lib" dir under executable file dir and copy all OpenCV dylib files to the "lib" dir
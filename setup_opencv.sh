    #!/bin/bash
	sudo apt-get install -y libgstreamer1.0-0 gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad \
                       gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-tools gstreamer1.0-x \
                       gstreamer1.0-alsa gstreamer1.0-gl gstreamer1.0-pulseaudio gstreamer1.0-opencv autoconf automake \
                       autopoint libtool libgstrtspserver-1.0-dev gstreamer1.0-rtsp build-essential \
                       pkg-config gtk-doc-tools libglib2.0-dev libgstreamer1.0-dev \
                       libgstreamer-plugins-base1.0-dev checkinstall libssl-dev ffmpeg \
                       libtbb-dev libssl-dev
    PATHPROJECT=$PWD
    rm -rf /tmp/build_opencv
    mkdir /tmp/build_opencv
    cd /tmp/build_opencv
    wget https://github.com/opencv/opencv/archive/4.5.5.zip
	unzip 4.5.5.zip
	rm -rf 4.5.5.zip
    mkdir opencv-4.5.5/build
    cd opencv-4.5.5/build
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_STANDARD=20 -DBUILD_SHARED_LIBS=ON\
          -DOPENCV_ENABLE_NONFREE=ON -DBUILD_PERF_TESTS=OFF -DBUILD_TESTS=OFF -DBUILD_ZLIB=ON\
          -DBUILD_OPENEXR=OFF -DBUILD_JPEG=ON -DBUILD_OPENJPEG=ON -DBUILD_PNG=ON -DBUILD_WEBP=ON\
          -DBUILD_PACKAGE=OFF -DCMAKE_CONFIGURATION_TYPES="Release" -DBUILD_JAVA=OFF -DBUILD_opencv_python3=OFF\
          -DBUILD_opencv_python_bindings_generator=OFF -DBUILD_opencv_python_tests=OFF -DWITH_FFMPEG=ON\
          -DWITH_GSTREAMER=ON -DWITH_GTK=ON -DWITH_OPENGL=OFF -DWITH_1394=OFF -DWITH_ADE=OFF -DWITH_OPENEXR=OFF\
          -DWITH_PROTOBUF=OFF -DWITH_QUIRC=OFF -DWITH_TIFF=OFF -DWITH_V4L=OFF -DWITH_VA=OFF -DWITH_VA_INTEL=OFF\
          -DWITH_VTK=OFF -DWITH_OPENCL=OFF -DCMAKE_INSTALL_PREFIX=$PATHPROJECT ..
    make -j`nproc`
    sudo make install
    sudo chown $USER:$USER $PATHPROJECT/lib -R
    sudo chown $USER:$USER $PATHPROJECT/include -R
    rm -rf /tmp/build_opencv
    sudo rm -rf $PATHPROJECT/bin
    sudo rm -rf $PATHPROJECT/share
    sudo rm -rf $PATHPROJECT/cmake

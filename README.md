This repository contains minimal code to create a native Android command-line application that loads and uses ART virtual machine.

More details can be found at https://gershnik.github.io/2021/03/26/load-art-from-native.html

To build and run:

* Make sure you have an emulator running or device connected.

* Run the following, substituting 
  * your NDK location for `$ANDROID_NDK_PATH`
  * `Release` or `Debug` etc. for `$BUILD_TYPE` 
  * `x86_64`, `x86`, `armeabi-v7a` or `arm64-v8a` for `$NDK_ARCH`
  * If desired change `ANDROID_PLATFORM` value to something bigger than 19

```bash
mkdir -p build
cd build
cmake .. 
    -DCMAKE_BUILD_TYPE:STRING=$BUILD_TYPE \
    -DCMAKE_TOOLCHAIN_FILE:FILEPATH=$ANDROID_NDK_PATH/build/cmake/android.toolchain.cmake \
    -DANDROID_ABI:STRING=$NDK_ARCH \
    -DANDROID_PLATFORM:STRING=19 \
    -DANDROID_STL:STRING=c++_static
cmake --build . --config $BUILD_TYPE --target run
```


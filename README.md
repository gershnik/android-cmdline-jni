This repository contains minimal code to create a native Android command-line application that loads and uses ART virtual machine.

More details can be found at https://gershnik.github.io/2021/03/26/load-art-from-native.html

To build and run:

* Make sure you have an emulator running or device connected.

* Run the following substituting your NDK location for `$ANDROID_NDK_PATH` and `Release` or `Debug` etc. for `$BUILD_TYPE` 

```bash
mkdir -p build
cd build
cmake .. 
    -DCMAKE_BUILD_TYPE:STRING=$BUILD_TYPE \
    -DCMAKE_TOOLCHAIN_FILE:FILEPATH=$ANDROID_NDK_PATH/build/cmake/android.toolchain.cmake \
    -DANDROID_ABI:STRING=x86_64 \
    -DANDROID_PLATFORM:STRING=19 \
    -DANDROID_STL:STRING=c++_static
cmake --build . --config $BUILD_TYPE --target run
```


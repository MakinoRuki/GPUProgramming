CMakeLists.txt -> cmake -> Makefile -> make.
cmake 一般在 /usr/bin/cmake
cmake -G Ninja -H. -Bbuild
cmake -G Ninja -H. -BRelease -DCMAKE_BUILD_TYPE=Release

cmake
make + target

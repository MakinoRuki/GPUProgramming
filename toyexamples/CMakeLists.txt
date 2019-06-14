cmake_minimum_required(VERSION 2.8)

add_subdirectory(hellosuba)
add_subdirectory(hellosubb)
add_subdirectory(cudalib)
add_executable(HelloWorld
  helloworld.cpp
)
target_link_libraries(HelloWorld HelloBotA HelloBotB VectorAdd)

add_subdirectory(FFT)
add_executable(2DFFTMain
  2dfft_main.cpp
)
target_link_libraries(2DFFTMain 2DFFT)

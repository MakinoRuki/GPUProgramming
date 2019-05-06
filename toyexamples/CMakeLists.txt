cmake_minimum_required(VERSION 2.8)

add_subdirectory(hellosuba)
add_subdirectory(hellosubb)
add_subdirectory(cudalib)
add_executable(HelloWorld
  helloworld.cpp
)
target_link_libraries(HelloWorld HelloBotA HelloBotB VectorAdd)

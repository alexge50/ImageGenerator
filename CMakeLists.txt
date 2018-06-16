cmake_minimum_required(VERSION 3.8)
project(Noise_Generator)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp PerlinNoise.h Image.cpp Image.h)


add_executable(Noise_Generator ${SOURCE_FILES})
target_link_libraries(Noise_Generator m dl freeimage freeimageplus)
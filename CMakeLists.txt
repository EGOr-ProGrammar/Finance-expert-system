cmake_minimum_required(VERSION 3.14)
project(FuzzyExpertSystem VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(FuzzyExpertSystem src/main.cpp)
target_include_directories(FuzzyExpertSystem PRIVATE include)

if(MSVC)
  target_compile_options(FuzzyExpertSystem PRIVATE /W4)
else()
  target_compile_options(FuzzyExpertSystem PRIVATE -Wall -Wextra)
endif()

target_link_options(FuzzyExpertSystem PRIVATE -static -static-libgcc -static-libstdc++)
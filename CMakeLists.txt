cmake_minimum_required(VERSION 3.14)
project(FuzzyExpertSystem VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Common library for core logic (Header-only based on the current structure)
add_library(FuzzyCore INTERFACE)
target_include_directories(FuzzyCore INTERFACE include)

# Expert Executable
add_executable(FuzzyExpertSystem_Expert src/expert_main.cpp)
target_link_libraries(FuzzyExpertSystem_Expert PRIVATE FuzzyCore)

# User Executable
add_executable(FuzzyExpertSystem_User src/user_main.cpp)
target_link_libraries(FuzzyExpertSystem_User PRIVATE FuzzyCore)

if(MSVC)
  target_compile_options(FuzzyExpertSystem_Expert PRIVATE /W4)
  target_compile_options(FuzzyExpertSystem_User PRIVATE /W4)
else()
  target_compile_options(FuzzyExpertSystem_Expert PRIVATE -Wall -Wextra)
  target_compile_options(FuzzyExpertSystem_User PRIVATE -Wall -Wextra)
endif()

# Global link options
target_link_options(FuzzyExpertSystem_Expert PRIVATE -static -static-libgcc -static-libstdc++)
target_link_options(FuzzyExpertSystem_User PRIVATE -static -static-libgcc -static-libstdc++)

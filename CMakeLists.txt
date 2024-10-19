cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(HTMLParser VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(htmp html_parser.cpp)

# Optionally, you can add installation rules
install(TARGETS htmp DESTINATION bin)


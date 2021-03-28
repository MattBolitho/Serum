cmake_minimum_required(VERSION 3.13)

project(Serum VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)

include_directories(ThirdParty/catch)

add_executable(Serum.Tests
	Serum.Tests/src/Serum.Tests.cpp)
cmake_minimum_required(VERSION 3.13)

project(Serum VERSION 0.2)

set(CMAKE_CXX_STANDARD 17)

include_directories(ThirdParty/catch)
include_directories(Serum/include)
include_directories(Serum.Tests/include)

add_executable(Serum.Tests
	Serum.Tests/src/SerumExceptionTests.cpp
	Serum.Tests/src/Internal/TypeTraitsTests.cpp
	Serum.Tests/src/Bindings/BindingKeyTests.cpp
	Serum.Tests/src/Bindings/ConstantBindingTests.cpp
	Serum.Tests/src/Bindings/FunctionBindingTests.cpp
	Serum.Tests/src/Bindings/ResolverBindingTests.cpp
	Serum.Tests/src/SerumContainerTests.cpp
	Serum.Tests/src/Serum.Tests.cpp)
# cmake version
cmake_minimum_required(VERSION 4.0)

project(pdfvault)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_CXX_FLAGS "-O3 -Wall")

file(GLOB CPP_SOURCE
	"${PROJECT_SOURCE_DIR}/src/*.cpp"
	"${PROJECT_SOURCE_DIR}/src/*/*.cpp"
)

include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(main ${CPP_SOURCE})


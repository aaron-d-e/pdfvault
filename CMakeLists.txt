# cmake version
cmake_minimum_required(VERSION 3.10)

project(pdfvault C)

#C version
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

# Find required packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(MUPDF REQUIRED mupdf)
pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4)

#compiler flags
set(CMAKE_C_FLAGS "-O3 -Wall")

#lsp looks at header libraries
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#includes .c files in src folder
file(GLOB C_SOURCE
	"${PROJECT_SOURCE_DIR}/src/*.c"
)

include_directories(
	${PROJECT_SOURCE_DIR}/src/
	${MUPDF_INCLUDE_DIRS}
)

add_executable(main ${C_SOURCE})

target_link_libraries(main 
	${MUPDF_LIBRARIES}
	PkgConfig::GTK4
	m
)

target_compile_options(main PRIVATE ${MUPDF_CFLAGS_OTHER})


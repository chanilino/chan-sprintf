cmake_minimum_required(VERSION 3.0)
project(CHAN_SPRINTF_TESTS)

set(PROFILE_FLAGS
#	"-pg"
)
set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O3 -g -pthread ${PROFILE_FLAGS}")  

set (CMAKE_EXE_LINKER_FLAGS "${PROFILE_FLAGS}")  
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

INCLUDE(FindPkgConfig)
pkg_check_modules(CHECK REQUIRED check)
if (CHECK_FOUND)
	message("check found")
else(CHECK_FOUND)
	message("check not found")
endif(CHECK_FOUND)


include_directories("./")
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../include ${CMAKE_CURRENT_BINARY_DIR}/c_sprintf)
include_directories( 
	"./"
	"${CMAKE_CURRENT_SOURCE_DIR}/../include"
	)

set(
	LIB_DEP_C_PRINTF
	${CHECK_LIBRARIES}
)

add_executable(tests-printf tests-printf.c test-suite-bench-printf.c test-suite-functional-printf.c)
target_link_libraries(tests-printf ${LIB_DEP_C_PRINTF})



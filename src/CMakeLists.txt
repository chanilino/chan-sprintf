cmake_minimum_required(VERSION 3.0)
project(chan_printf)

set(PROFILE_FLAGS
#	"-pg"
)
set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O3 -g ${PROFILE_FLAGS}")  

if (CMAKE_COMPILER_IS_GNUC)
  set ( CMAKE_EXE_LINKER_FLAGS "-pthread ${PROFILE_FLAGS}")  
endif ()

add_library(chanprintf_obj OBJECT  c_printf.c c_printf.h number_convertion.h )

set_property(TARGET chanprintf_obj PROPERTY POSITION_INDEPENDENT_CODE 1)

add_library(chanprintf_shared SHARED $<TARGET_OBJECTS:chanprintf_obj>)
add_library(chanprintf_static STATIC $<TARGET_OBJECTS:chanprintf_obj>)
set_target_properties(chanprintf_shared PROPERTIES OUTPUT_NAME chanprintf CLEAN_DIRECT_OUTPUT 1)
set_target_properties(chanprintf_static PROPERTIES OUTPUT_NAME chanprintf CLEAN_DIRECT_OUTPUT 1)

set(
	LIB_DEP_CHANLOG
)
include_directories("./")
target_link_libraries(chanprintf_shared ${LIB_DEP_CHANLOG})
target_link_libraries(chanprintf_static ${LIB_DEP_CHANLOG})


install(TARGETS chanprintf_shared chanprintf_static 
		LIBRARY DESTINATION "lib"
		ARCHIVE DESTINATION "lib"
)

install(FILES c_printf.h DESTINATION "include")


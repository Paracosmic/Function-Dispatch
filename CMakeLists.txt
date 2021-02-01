# CMake entry point
cmake_minimum_required (VERSION 3.8)
project (FunctionDispatch LANGUAGES CXX)




if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()



# On Visual 2005 and above, this module can set the debug working directory
cmake_policy(SET CMP0026 OLD)

if(INCLUDE_DISTRIB)
	add_subdirectory(distrib)
endif(INCLUDE_DISTRIB)



include_directories(

	
)


add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

add_library(FuncLib STATIC 
FunctionHandle.h 
ToString.h
TransformArgument.h
TupleString.h
TupleUtility.h
Function.cpp
Function.h
Function_Tuple.h 
FunctionHandle.cpp
)


set_target_properties(FuncLib PROPERTIES
         LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})


set(ALL_LIBS
	FuncLib
)

file(GLOB helloworld_SRC
    "*.h"
    "*.cpp"
)

file(GLOB testproject
   
    "MainTest.cpp"
)


add_executable(TestProject ${testproject})

target_link_libraries(TestProject
	PUBLIC ${ALL_LIBS}
)
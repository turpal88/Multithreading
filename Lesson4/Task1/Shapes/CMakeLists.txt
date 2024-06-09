cmake_minimum_required(VERSION 3.20)
project(Lesson3_Task2 VERSION 1.0)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN yes)

#set(BUILD_SHARED_LIBS ON)
set(BUILD_SHARED_LIBS OFF)

add_library(Shapes)

set_property(TARGET Shapes PROPERTY CXX_STANDARD 20)

set(headers ${CMAKE_CURRENT_SOURCE_DIR}/src/headers/shape.h 
${CMAKE_CURRENT_SOURCE_DIR}/src/headers/transform.h)

set(sources ${CMAKE_CURRENT_SOURCE_DIR}/src/sources/shape.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/sources/transform.cpp)

list(APPEND ${sources} ${headers})

target_sources(Shapes PRIVATE ${sources})

target_include_directories(Shapes PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/headers)



if(BUILD_SHARED_LIBS)
target_compile_definitions(Shapes PUBLIC "USE_SHARED_LIB")
endif()

include(GenerateExportHeader)
if(BUILD_SHARED_LIBS)
set(export_file_name "export_shared.h")
else()
#message("Library is static")
    set(export_file_name "export_static.h")
endif()

generate_export_header(Shapes
EXPORT_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR}/src/headers/${export_file_name}
EXPORT_MACRO_NAME API_SHAPES

)

#set(binary_dir ${PROJECT_SOURCE_DIR}/install)
#set(CMAKE_BINARY_DIR  ${binary_dir})

install(TARGETS Shapes DESTINATION ${PROJECT_SOURCE_DIR}/install)


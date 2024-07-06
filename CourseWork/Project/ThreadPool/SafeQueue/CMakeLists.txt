cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN yes)
#set(BUILD_SHARED_LIBS OFF)
#set(BUILD_SHARED_LIBS ON)
add_library(SafeQueue INTERFACE)
set_property(TARGET SafeQueue PROPERTY CXX_STANDARD 20)

#include(GenerateExportHeader)
#generate_export_header(SafeQueue
#EXPORT_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR}/headers/${export_file_name}
#EXPORT_MACRO_NAME API_SAFE_QUEUE

#)

set(headers ${CMAKE_CURRENT_SOURCE_DIR}/headers/safe_queue.h)
#set(export_file_name "export_interface.h")
#list(APPEND ${headers} ${CMAKE_CURRENT_SOURCE_DIR}/headers/${export_file_name})
target_sources(SafeQueue PRIVATE ${headers})

target_include_directories(SafeQueue INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/headers)







install(TARGETS SafeQueue DESTINATION ${PROJECT_SOURCE_DIR}/install)
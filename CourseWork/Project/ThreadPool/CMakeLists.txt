cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN yes)
#set(BUILD_SHARED_LIBS OFF)
set(BUILD_SHARED_LIBS ON)
add_library(ThreadPool)
set_property(TARGET ThreadPool PROPERTY CXX_STANDARD 20)
set(headers ${CMAKE_CURRENT_SOURCE_DIR}/headers/thread_pool.h)
set(sources ${CMAKE_CURRENT_SOURCE_DIR}/source/thread_pool.cpp)
list(APPEND ${sources} ${headers})
target_sources(ThreadPool PRIVATE ${sources})
add_subdirectory(SafeQueue)
target_include_directories(ThreadPool PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/headers ${CMAKE_CURRENT_SOURCE_DIR}/SafeQueue/headers)
target_link_libraries(ThreadPool PRIVATE SafeQueue)

if(BUILD_SHARED_LIBS)
target_compile_definitions(ThreadPool PUBLIC "USE_SHARED_LIB")
endif()

include(GenerateExportHeader)
if(BUILD_SHARED_LIBS)
set(export_file_name "export_shared.h")
else()

    set(export_file_name "export_static.h")
endif()

generate_export_header(ThreadPool
EXPORT_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR}/headers/${export_file_name}
EXPORT_MACRO_NAME API_THREAD_POOL

)

list(APPEND ${sources} ${CMAKE_CURRENT_SOURCE_DIR}/headers/${export_file_name})
install(TARGETS ThreadPool DESTINATION ${PROJECT_SOURCE_DIR}/install)
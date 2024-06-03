cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN yes)
#set(BUILD_SHARED_LIBS ON)
#set(BUILD_SHARED_LIBS OFF)




#if(DEFINED USE_SHARED_LIB)
    #set(BUILD_SHARED_LIBS ${USE_SHARED_LIB})
#endif()
#configure_file (config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/src/headers/config.h @ONLY)
#install(FILES config.h DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/src/headers)
add_library(ForEach_Parallel INTERFACE)
set_target_properties(ForEach_Parallel PROPERTIES LINKER_LANGUAGE CXX)
#if(BUILD_SHARED_LIBS)
#set(BUILD_SHARED_LIBS ${USE_SHARED_LIB})
#target_compile_definitions(SelectionSort PUBLIC "USE_SHARED_LIB")
#else()
#set(BUILD_SHARED_LIBS OFF)
#endif()

#message("BUILD_SHARED_LIBS = ${BUILD_SHARED_LIBS}")

#include(GenerateExportHeader)

#if(BUILD_SHARED_LIBS)
#set(export_file_name "export_shared.h")

#message("Library is dynamic")
#else()
#message("Library is static")
#    set(export_file_name "export_static.h")
#endif()

#generate_export_header(SelectionSort
#EXPORT_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR}/src/headers/${export_file_name}
#EXPORT_MACRO_NAME API_SELECTION_SORT

#)

set(headers ${CMAKE_CURRENT_SOURCE_DIR}/src/headers/export.h
 ${CMAKE_CURRENT_SOURCE_DIR}/src/headers/for_each_parallel.h)
 
#set(sources ${CMAKE_CURRENT_SOURCE_DIR}/src/sources/selection_sort.cxx ${headers})

target_sources(ForEach_Parallel PRIVATE ${headers})


target_include_directories(ForEach_Parallel INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src/headers)
#set(USE_SHARED_LIB 1)





#list(APPEND headers ${CMAKE_CURRENT_SOURCE_DIR}/src/headers/${export_file_name})
#list(APPEND sources ${CMAKE_CURRENT_SOURCE_DIR}/src/headers/${export_file_name})

install(TARGETS ForEach_Parallel DESTINATION ${PROJECT_SOURCE_DIR}/install)

#target_compile_definitions(SelectionSort
#   PUBLIC
#      "$<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:USE_STATIC_LIB")
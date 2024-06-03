cmake_minimum_required(VERSION 3.20)
project(Lesson3_Task2 VERSION 1.0)

set(CMAKE_BUILD_TYPE Debug)
add_subdirectory(ForEach_Parallel)
add_subdirectory(Accumulate_function)
add_executable(LT3_2)
set_target_properties(LT3_2 PROPERTIES LINKER_LANGUAGE CXX)
#set(headers ${CMAKE_SOURCE_DIR}/src/headers/lt3_1.h src/headers/selection_sort.h)
set(sources ${CMAKE_CURRENT_SOURCE_DIR}/src/sources/lt3_2.cxx)
target_sources(LT3_2 PRIVATE ${sources})

target_include_directories(LT3_2 PRIVATE 
${PROJECT_SOURCE_DIR}/ForEach_Parallel/src/headers
${PROJECT_SOURCE_DIR}/AccumulateFunction/src/headers)

target_link_libraries(LT3_2 PRIVATE ForEach_Parallel AccumulateFunction)



install(TARGETS LT3_2 DESTINATION ${PROJECT_SOURCE_DIR}/install)
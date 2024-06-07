cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN yes)

add_library(MultiplyFunction INTERFACE)

set_target_properties(MultiplyFunction PROPERTIES LINKER_LANGUAGE CXX)

set(headers ${CMAKE_CURRENT_SOURCE_DIR}/src/headers/multiply_function.h)


target_sources(MultiplyFunction PRIVATE ${headers})

#target_link_libraries(ForEachParallel INTERFACE AccumulateFunction)

target_include_directories(MultiplyFunction INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src/headers)


#target_include_directories(ForEachParallel PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/AccumulateFunction/src/headers)

install(TARGETS MultiplyFunction DESTINATION ${PROJECT_SOURCE_DIR}/install)
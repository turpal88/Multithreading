cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN yes)

add_library(AccumulateFunction INTERFACE)

set_target_properties(AccumulateFunction PROPERTIES LINKER_LANGUAGE CXX)

set(headers ${CMAKE_CURRENT_SOURCE_DIR}/src/headers/accumulate_function.h)


target_sources(AccumulateFunction PRIVATE ${headers})

#target_link_libraries(ForEachParallel INTERFACE AccumulateFunction)

target_include_directories(AccumulateFunction INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src/headers
${PROJECT_SOURCE_DIR}/ForEachParallel/src/headers)


#target_include_directories(ForEachParallel PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/AccumulateFunction/src/headers)

install(TARGETS AccumulateFunction DESTINATION ${PROJECT_SOURCE_DIR}/install)
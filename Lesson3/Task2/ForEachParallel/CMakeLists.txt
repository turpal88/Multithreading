cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN yes)

add_library(ForEachParallel INTERFACE)

set_target_properties(ForEachParallel PROPERTIES LINKER_LANGUAGE CXX)

set(headers ${CMAKE_CURRENT_SOURCE_DIR}/src/headers/for_each_parallel.h)


target_sources(ForEachParallel PRIVATE ${headers})

#target_link_libraries(ForEachParallel INTERFACE AccumulateFunction)

target_include_directories(ForEachParallel INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src/headers)


#target_include_directories(ForEachParallel PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/AccumulateFunction/src/headers)

install(TARGETS ForEachParallel DESTINATION ${PROJECT_SOURCE_DIR}/install)

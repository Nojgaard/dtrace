add_subdirectory(parse)
add_subdirectory(dtrace)

add_library(graph_aut aut.cpp)
target_link_libraries(graph_aut gmp bliss)

add_library(graph_io io.cpp)
target_link_libraries(graph_io ${Boost_LIBRARIES})

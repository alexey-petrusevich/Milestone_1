# minimum version of CMAKE
cmake_minimum_required(VERSION 3.10)

# project name
project(eau2)

# any flags
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set source and binary directories
set(CMAKE_BINARY_DIR ../bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

# create subdirectories for tests
add_custom_target(make_bin_application ALL COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/test)
add_custom_target(make_bin_application ALL COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/test/application)
add_custom_target(make_bin_application ALL COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/test/collections)
add_custom_target(make_bin_application ALL COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/test/collections/arrays)
add_custom_target(make_bin_application ALL COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/test/collections/maps)
add_custom_target(make_bin_application ALL COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/test/dataframe)
add_custom_target(make_bin_application ALL COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/test/dataframe/columns)
add_custom_target(make_bin_application ALL COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/test/dataframe/fielders)
add_custom_target(make_bin_application ALL COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/test/dataframe/rowers)
add_custom_target(make_bin_application ALL COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/test/dataframe/visitors)
add_custom_target(make_bin_application ALL COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/test/kvstore)
add_custom_target(make_bin_application ALL COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/test/network)
add_custom_target(make_bin_application ALL COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/test/serialization)
add_custom_target(make_bin_application ALL COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/test/sorer)


# set the path to include directories
include_directories(../include)

# compile libraries

# application
add_library(application_lib STATIC ../src/application/application.cpp)
add_library(demo_lib STATIC ../src/application/demo.cpp)
add_library(trivial_lib STATIC ../src/application/trivial.cpp)

# collections 
# (arrays)
add_library(array_lib STATIC ../src/collections/arrays/array.cpp)
add_library(int_array_lib STATIC ../src/collections/arrays/int_array.cpp)
add_library(double_array_lib STATIC ../src/collections/arrays/double_array.cpp)
add_library(bool_array_lib STATIC ../src/collections/arrays/bool_array.cpp)
add_library(coltype_array_lib STATIC ../src/collections/arrays/coltype_array.cpp)
add_library(column_array_lib STATIC ../src/collections/arrays/column_array.cpp)

# (maps)
add_library(byte_map_lib STATIC ../src/collections/maps/byte_map.cpp)
add_library(keyvalue_bytes_lib STATIC ../src/collections/maps/keyvalue_bytes.cpp)
add_library(keyvalue_lib STATIC ../src/collections/maps/keyvalue.cpp)
add_library(map_lib STATIC ../src/collections/maps/map.cpp)

# dataframe
# (columns)
add_library(bool_column_lib STATIC ../src/dataframe/columns/bool_column.cpp)
add_library(column_lib STATIC ../src/dataframe/columns/column.cpp)
add_library(double_column_lib STATIC ../src/dataframe/columns/double_column.cpp)
add_library(int_column_lib STATIC ../src/dataframe/columns/int_column.cpp)
add_library(string_column_lib STATIC ../src/dataframe/columns/string_column.cpp)

# (fielders)
add_library(fielder_lib STATIC ../src/dataframe/fielders/fielder.cpp)
add_library(print_fielder_lib STATIC ../src/dataframe/fielders/print_fielder.cpp)

# (rowers)
add_library(multiply_rower_lib STATIC ../src/dataframe/rowers/multiply_rower.cpp)
add_library(parallel_multiply_rower_lib STATIC ../src/dataframe/rowers/parallel_multiply_rower.cpp)
add_library(parallel_sum_rower_lib STATIC ../src/dataframe/rowers/parallel_sum_rower.cpp)
add_library(rower_lib STATIC ../src/dataframe/rowers/rower.cpp)
add_library(sum_rower_lib STATIC ../src/dataframe/rowers/sum_rower.cpp)

# (visitors)
add_library(add_row_visitor_lib STATIC ../src/dataframe/visitors/add_row_visitor.cpp)
add_library(fill_row_visitor_lib STATIC ../src/dataframe/visitors/fill_row_visitor.cpp)
add_library(visitor_lib STATIC ../src/dataframe/visitors/visitor.cpp)

# (other)
add_library(coltypes_lib STATIC ../src/dataframe/coltypes.cpp)
add_library(dataframe_lib STATIC ../src/dataframe/dataframe.cpp)
add_library(handle_rower_thread_lib STATIC ../src/dataframe/handle_rower_thread.cpp)
add_library(row_lib STATIC ../src/dataframe/row.cpp)
add_library(schema_lib STATIC ../src/dataframe/schema.cpp)

# kvstore
add_library(key_lib STATIC ../src/kvstore/key.cpp)
add_library(kvstore_lib STATIC ../src/kvstore/kvstore.cpp)

# serialization
add_library(serializer_lib STATIC ../src/serialization/serializer.cpp)
add_library(deserializer_lib STATIC ../src/serialization/deserializer.cpp)

# sorer
add_library(sorer_lib STATIC ../src/sorer/sorer.cpp)
add_library(helpers_lib STATIC ../src/sorer/helpers.cpp)

# utils
add_library(counter_lib STATIC ../src/utils/counter.cpp)
add_library(helper_lib STATIC ../src/utils/helper.cpp)
add_library(lock_lib STATIC ../src/utils/lock.cpp)
add_library(object_lib STATIC ../src/utils/object.cpp)
add_library(strbuf_lib STATIC ../src/utils/strbuf.cpp)
add_library(string_lib STATIC ../src/utils/string.cpp)
add_library(thread_lib STATIC ../src/utils/thread.cpp)


# link any libraries

# application
target_link_libraries(application_lib kvstore_lib object_lib)
target_link_libraries(demo_lib application_lib)
target_link_libraries(trivial_lib application_lib)

# collections

# (arrays)
target_link_libraries(array_lib object_lib string_lib)
target_link_libraries(bool_array_lib array_lib)
target_link_libraries(coltype_array_lib array_lib coltypes_lib)
target_link_libraries(column_array_lib array_lib column_lib schema_lib)
target_link_libraries(double_array_lib array_lib)
target_link_libraries(int_array_lib array_lib)

# (maps)
target_link_libraries(byte_map_lib object_lib keyvalue_bytes_lib deserializer_lib)
target_link_libraries(keyvalue_bytes_lib key_lib object_lib deserializer_lib)
target_link_libraries(keyvalue_lib object_lib)
target_link_libraries(map_lib object_lib keyvalue_lib)

# dataframe

# (columns)
target_link_libraries(bool_column_lib bool_array_lib column_lib)
target_link_libraries(column_lib fielder_lib object_lib string_lib visitor_lib bool_column_lib double_column_lib int_column_lib string_column_lib coltypes_lib)
target_link_libraries(double_column_lib double_array_lib column_lib)
target_link_libraries(int_column_lib int_array_lib column_lib)
target_link_libraries(string_column_lib array_lib column_lib)

# (fielders)
target_link_libraries(fielder_lib object_lib string_lib)
target_link_libraries(print_fielder_lib fielder_lib)

# (rowers)
target_link_libraries(multiply_rower_lib rower_lib)
target_link_libraries(parallel_multiply_rower_lib rower_lib)
target_link_libraries(parallel_sum_rower_lib rower_lib)
target_link_libraries(rower_lib object_lib row_lib)
target_link_libraries(sum_rower_lib rower_lib)

# (visitors)
target_link_libraries(add_row_visitor_lib visitor_lib row_lib)
target_link_libraries(fill_row_visitor_lib visitor_lib row_lib)
target_link_libraries(visitor_lib bool_column_lib double_column_lib int_column_lib string_column_lib)

# (other)
target_link_libraries(coltypes_lib helpers_lib)
target_link_libraries(dataframe_lib column_array_lib column_lib key_lib kvstore_lib object_lib string_lib row_lib rower_lib schema_lib serializer_lib deserializer_lib handle_rower_thread_lib add_row_visitor_lib fill_row_visitor_lib)
target_link_libraries(handle_rower_thread_lib thread_lib rower_lib)
target_link_libraries(row_lib column_array_lib object_lib string_lib fielder_lib schema_lib)
target_link_libraries(schema_lib coltype_array_lib object_lib)

# kvstore
target_link_libraries(key_lib object_lib)
target_link_libraries(kvstore_lib byte_map_lib dataframe_lib lock_lib thread_lib)

# serialization
target_link_libraries(deserializer_lib object_lib string_lib)
target_link_libraries(serializer_lib object_lib string_lib)

# sorer
target_link_libraries(sorer_lib array_lib dataframe_lib object_lib helpers_lib)

# utils
target_link_libraries(counter_lib object_lib)
target_link_libraries(lock_lib object_lib)
target_link_libraries(object_lib helper_lib)
target_link_libraries(strbuf_lib object_lib string_lib)
target_link_libraries(string_lib object_lib)
target_link_libraries(thread_lib object_lib string_lib)


# tests

# serialization
add_executable(test_serialization ../test/serialization/test_serialization.cpp)
target_link_libraries(test_serialization deserializer_lib serializer_lib)

# sorer
add_executable(test_sorer ../test/sorer/test_sorer.cpp)
target_link_libraries(test_sorer sorer_lib helper_lib)


cmake_minimum_required(VERSION 3.0)
project(MysqlConn)
#include_directories(/home/zxe/Documents/JSONCPP/jsoncpp/include/json)
include_directories(
  ./ 
  /home/zxe/Documents/JSONCPP/jsoncpp/include/json
)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC_LIST)
add_executable(main ${SRC_LIST})
link_libraries(/home/zxe/Documents/JSONCPP/jsoncpp-Sandbox/jsoncpp-build/lib)
target_link_libraries(main libmysqlclient.so libjsoncpp.so)


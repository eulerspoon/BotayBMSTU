cmake_minimum_required(VERSION 3.22.1)
set(project "ScheduleParser")
project(${project})
set(CMAKE_CXX_STANDARD 17)
set(${project}_SOURCES
ScheduleParser.cpp)
set(${project}_HEADERS
ScheduleParser.hpp)
set(${project}_SOURCE_LIST
${${project}_SOURCES}
${${project}_HEADERS})
add_library(${project}
STATIC
${${project}_SOURCE_LIST})
find_package(OpenSSL REQUIRED)
if (OPENSSL_FOUND)
  target_include_directories(${PROJECT_NAME} PUBLIC ${OPENSSL_INCLUDE_DIR})
  
  target_link_libraries(${PROJECT_NAME} OpenSSL::SSL OpenSSL::Crypto)

  message(STATUS "Found OpenSSL ${OPENSSL_VERSION}")

else()

  message(STATUS "OpenSSL Not Found")

endif()
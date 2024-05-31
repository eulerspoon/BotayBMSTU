cmake_minimum_required(VERSION 3.22)

set(project "BotayBMSTU")
project(${project})

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/ScheduleParser/Schedule.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

set(${project}_SOURCES
	main.cpp
	app.cpp
	ScheduleParser/ScheduleParser.cpp)

set(${project}_HEADERS
	app.hpp
	Interface/Interface.hpp
	Interface/Button.hpp
	Interface/Textbox.hpp
	ScheduleParser/ScheduleParser.hpp)

set(${project}_SOURCE_LIST    
        ${${project}_SOURCES}    
        ${${project}_HEADERS})
# add_subdirectory(ScheduleParser)

add_executable(${project} ${${project}_SOURCE_LIST})

add_subdirectory(ScheduleParser)

target_link_libraries(${project} sfml-graphics ScheduleParser)

install(TARGETS ${project})

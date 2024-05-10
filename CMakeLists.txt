cmake_minimum_required(VERSION 3.22)

set(project "BotayBMSTU")
project(${project})

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(${project}_SOURCES
	main.cpp
	app.cpp
	Interface/Button.cpp
	Interface/Textbox.cpp
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

add_executable(${project} ${${project}_SOURCE_LIST})

target_link_libraries(${project} sfml-graphics)

install(TARGETS ${project})

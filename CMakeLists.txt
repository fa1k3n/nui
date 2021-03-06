cmake_minimum_required(VERSION 3.5.1)

project(NUI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

find_package(Boost 1.58.0 REQUIRED )
message(STATUS "Using Boost include: ${Boost_INCLUDE_DIRS}")
include_directories(${Boost_INCLUDE_DIRS})

set(SIGNALS_INC ${CMAKE_SOURCE_DIR}/external/signals/include)
include_directories(${SIGNALS_INC})

set(NUI_INC ${CMAKE_SOURCE_DIR}/include)
set(CORE_INC ${NUI_INC}/nui/core)
set(WIDGETS_INC ${NUI_INC}/nui/widgets)

include_directories(${CORE_INC})
include_directories(${WIDGETS_INC})

set(NUI_SRC ${CMAKE_SOURCE_DIR}/src)
set(WIDGETS_SRC ${NUI_SRC}/widgets)
set(CORE_SRC ${NUI_SRC}/core)

set(WIDGETS_INC_FILES 
	${WIDGETS_INC}/NUILabel
	${WIDGETS_INC}/NUIRow.hpp   
                ${WIDGETS_INC}/NUIWidget.hpp
	${WIDGETS_INC}/NUIWindow
)

set(CORE_INC_FILES 
	${CORE_INC}/NUIApp
	${CORE_INC}/NUIObject
	${CORE_INC}/NUITypes.hpp
)

set(WIDGETS_SRC_FILES 
	${WIDGETS_SRC}/nuilabel.cpp
	${WIDGETS_SRC}/nuirow.cpp	
                ${WIDGETS_SRC}/NUIWidget.cpp
	${WIDGETS_SRC}/nuiwindow.cpp
)

set(CORE_SRC_FILES 
	${CORE_SRC}/nuiapp.cpp
	${CORE_SRC}/nuiobject.cpp
)


add_subdirectory("test")

add_library(nuicore ${CORE_SRC_FILES} ${CORE_INC_FILES})
target_link_libraries(nuicore ncurses)

add_library(nuiwidgets ${WIDGETS_SRC_FILES} ${WIDGETS_INC_FILES})
target_link_libraries(nuiwidgets ncurses)

add_executable(example EXCLUDE_FROM_ALL example/basic.cpp)
target_link_libraries(example nuicore nuiwidgets)



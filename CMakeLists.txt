cmake_minimum_required(VERSION 3.5.1)

project(NUI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(SIGNALS_INC ${CMAKE_SOURCE_DIR}/external/signals/include)
include_directories(${SIGNALS_INC})

set(NUI_INC ${CMAKE_SOURCE_DIR}/include)
set(GUI_INC ${NUI_INC}/nui/gui)

include_directories(${GUI_INC})

set(NUI_SRC ${CMAKE_SOURCE_DIR}/src)
set(GUI_SRC ${NUI_SRC}/gui)

set(GUI_INC_FILES 
	${GUI_INC}/NUIApp
	${GUI_INC}/NUILabel
	${GUI_INC}/NUIObject
	${GUI_INC}/NUIWindow
	${GUI_INC}/NUIPoint.hpp
	${GUI_INC}/NUIRow.hpp
	${GUI_INC}/NUIColor.hpp
)

set(GUI_SRC_FILES 
	${GUI_SRC}/nuiapp.cpp
	${GUI_SRC}/nuilabel.cpp
	${GUI_SRC}/nuiobject.cpp
	${GUI_SRC}/nuiwindow.cpp
	${GUI_SRC}/nuirow.cpp
)

add_library(nuigui ${GUI_SRC_FILES} ${GUI_INC_FILES})
target_link_libraries(nuigui ncurses pthread)

add_executable(example EXCLUDE_FROM_ALL example/basic.cpp)
target_link_libraries(example nuigui)



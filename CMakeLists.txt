cmake_minimum_required(VERSION 3.5.1)

project(NUI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(BOOST_INC ${CMAKE_SOURCE_DIR}/external/boost_1_66_0)
include_directories(${BOOST_INC})

set(SIGNALS_INC ${CMAKE_SOURCE_DIR}/include)
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

	${CMAKE_SOURCE_DIR}/include/signals/signal.hpp
)

add_library(nuigui ${GUI_SRC_FILES} ${GUI_INC_FILES})
target_link_libraries(nuigui ncurses pthread)

add_executable(nuitest test/nuitest.cpp)
target_link_libraries(nuitest nuigui)



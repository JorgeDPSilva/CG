cmake_minimum_required(VERSION 3.5)

# Project Name
PROJECT(generator)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME}
					src/main.cpp
					src/main.hpp
					src/figures/box/box.cpp
					src/figures/box/box.hpp
					src/figures/cone/cone.cpp
					src/figures/cone/cone.hpp
					src/figures/plane/plane.cpp
					src/figures/plane/plane.hpp
					src/figures/sphere/sphere.cpp
					src/figures/sphere/sphere.hpp
					src/write/write.cpp
					src/write/write.hpp
					src/classes/point.cpp
					src/classes/point.hpp
					src/classes/index.cpp
					src/classes/index.hpp
					src/patches/patches.cpp
					src/patches/patches.hpp
								)

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

if  (WIN32)

	message(STATUS "Toolkits_DIR set to: " ${TOOLKITS_FOLDER})
	set(TOOLKITS_FOLDER "" CACHE PATH "Path to Toolkits folder")

	if (NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")
		message(ERROR ": GLUT not found")
	endif (NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")

	include_directories(${TOOLKITS_FOLDER}/glut )
	target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES}
										  ${TOOLKITS_FOLDER}/glut/glut32.lib)

	if (EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll" )
		file(COPY ${TOOLKITS_FOLDER}/glut/glut32.dll DESTINATION ${CMAKE_BINARY_DIR})
	endif(EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll" )

	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

else (WIN32) #Linux and Mac

	set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wdeprecated-declarations")
	add_definitions("-DGL_SILENCE_DEPRECATION")
	find_package(GLUT REQUIRED)
	include_directories(${GLUT_INCLUDE_DIR})
	link_directories(${GLUT_LIBRARY_DIRS})
	add_definitions(${GLUT_DEFINITIONS})

	target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
	if(NOT GLUT_FOUND)
	   message(ERROR ": GLUT not found!")
	endif(NOT GLUT_FOUND)

endif(WIN32)








project(zpp)
SET(PROJECT_NAME zpp)
cmake_minimum_required(VERSION 3.17)

if(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
SET(PROJECT_STATIC_RUNTIME FALSE CACHE BOOL "Use statically linked standard/runtime libraries?")

if(CMAKE_COMPILER_IS_GNUCXX OR APPLE)
    if(PROJECT_STATIC_RUNTIME)
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14 -static")
    else()
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")
    endif()
endif()

SET (CMAKE_CXX_FLAGS_DEBUG "-g -D_DEBUG_")
SET (CMAKE_CXX_FLAGS_RELEASE "-O4 -DNDEBUG")

find_package(TMXLITE REQUIRED)
find_package(SFML 2.5 REQUIRED COMPONENTS system window graphics network audio)

include_directories(
        ${TMXLITE_INCLUDE_DIR}
        ${SFML_INCLUDE_DIR}
        /usr/local/include
        ${CMAKE_SOURCE_DIR}/include
)



set(PROJECT_SRC src/zpp.cpp src/GameManager.cpp src/HUD.cpp
                src/world/Map.cpp src/world/Polygon.cpp src/Utils.cpp
                src/characters/Link.cpp src/characters/Character.cpp src/characters/NPCs/Flame.cpp
                src/characters/enemies/Enemy.cpp src/characters/enemies/Octorok.cpp
)

if(WIN32)
    add_executable(${PROJECT_NAME} WIN32 ${PROJECT_SRC})
else()
    add_executable(${PROJECT_NAME} ${PROJECT_SRC})
endif()

target_link_libraries(${PROJECT_NAME}
        ${TMXLITE_LIBRARIES}
        ${SFML_LIBRARIES})

#install executable
install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION .)

#install game data
install(DIRECTORY assets
        DESTINATION .)
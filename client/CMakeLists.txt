cmake_minimum_required(VERSION 3.12)

project(sf_chat_client)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if ( CMAKE_COMPILER_IS_GNUCC )
   set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()
if ( MSVC )
   set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W4")
endif()

set(CHAT_LIBRARIES)

set(Qt5Modules Core Widgets Sql)

foreach(QtModule IN LISTS Qt5Modules)
 list(APPEND CHAT_LIBRARIES Qt5::${QtModule})
endforeach(QtModule)

find_package(Qt5 COMPONENTS ${Qt5Modules} REQUIRED LinguistTools)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE HEADERS_FILES src/*.h)
file(GLOB_RECURSE RC_FILES src/*.qrc)
file(GLOB_RECURSE UI_FILES src/*.ui)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

qt5_wrap_ui(QUI ${UI_FILES})
qt5_add_resources(QRC ${RC_FILES})

add_executable(Chat ${SRC_FILES} ${HEADERS_FILES} ${RC_FILES} ${UI_FILES})

target_link_libraries(Chat
 PUBLIC
 ${CHAT_LIBRARIES}
 )

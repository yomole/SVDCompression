cmake_minimum_required(VERSION 3.0)
project(SVDCompression)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")

set(SFML_DIR lib/SFML-2.5.1/lib/cmake/SFML)
find_package(SFML REQUIRED system window graphics network audio)
include_directories(lib/SFML-2.5.1/include)
find_package(Python COMPONENTS Interpreter Development)
include_directories(lib/Python/include)
set(python_LIBRARIES lib/Python/DLLs)
include_directories(lib/numpy/core/include)
set(pybind11_DIR lib/pybind11/share/cmake/pybind11)
find_package(pybind11 REQUIRED)
include_directories(lib/pybind11/include)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")
set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${dir}/bin")

set(sources
        res/src/main.cpp
        res/src/ui/Button.cpp
        res/src/ui/Button.h
        res/src/ui/super/UIElement.cpp
        res/src/ui/super/UIElement.h
        res/src/managers/AssetManager.cpp
        res/src/managers/AssetManager.h
        res/src/managers/SceneManager.cpp
        res/src/managers/SceneManager.h
        res/src/ui/super/SpriteBased.cpp
        res/src/ui/super/SpriteBased.h
        res/src/ui/ProgressBar.cpp
        res/src/ui/ProgressBar.h
        res/src/commands/Commands.cpp
        res/src/commands/Commands.h
        res/src/python/PythonScript.cpp
        res/src/python/PythonScript.h
        res/src/ui/scene/Scene.cpp
        res/src/ui/scene/Scene.h
        res/src/ui/Checkbox.cpp
        res/src/ui/Checkbox.h)

add_executable(SVDCompression ${sources})

#MAKE SURE TO INCLUDE -mwindows and -lsfml-main TO REMOVE THE CONSOLE WINDOW WHEN IN GUI.
target_link_libraries(SVDCompression sfml-system sfml-window sfml-graphics sfml-network sfml-audio ${Python_LIBRARIES})
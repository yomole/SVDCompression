if (WIN32)
    cmake_minimum_required(VERSION 3.0)
endif()

if(APPLE)
    cmake_minimum_required(VERSION 3.5)
    include(CMakePackageConfigHelpers)

endif()

project(SVDCompression)

set(CMAKE_CXX_STANDARD 17)

if (WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif(WIN32)

#https://stackoverflow.com/questions/9160335/os-specific-instructions-in-cmake-how-to

if (APPLE)
    message("Detected macOS. Using macOS libraries...")

    set(pybind11_DIR lib/pybind11/share/cmake/pybind11)
    set(python_LIBRARIES lib/Python/DLLs)

    set(SFML_DIR "lib/SFML-2.5.1OSX/Frameworks/SFML.framework/Resources/CMake")

    link_directories("lib/SFML-2.5.1OSX/lib")
    include_directories("lib/SFML-2.5.1OSX/include")
    include_directories(lib/Python/includeOSX)
    include_directories(lib/pybind11OSX/include)
    include_directories(lib/numpy/core/include)

endif(APPLE)

if(WIN32)
    message("Detected Windows. Using Windows libraries...")

    set(pybind11_DIR lib/pybind11/share/cmake/pybind11)
    set(SFML_DIR lib/SFML-2.5.1/lib/cmake/SFML)
    set(python_LIBRARIES lib/Python/DLLs)

    include_directories(lib/SFML-2.5.1/include)
    include_directories(lib/Python/include)
    include_directories(lib/pybind11/include)
    include_directories(lib/numpy/core/include)

endif(WIN32)

find_package(Python COMPONENTS Interpreter Development)
find_package(pybind11 CONFIG REQUIRED)

if(WIN32)
    find_package(SFML REQUIRED system window graphics network audio)
endif(WIN32)

if(APPLE)
    find_package(SFML 2.5.1 COMPONENTS REQUIRED system window graphics network audio)
endif(APPLE)


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
        res/src/ui/Checkbox.h
        res/src/ui/viewer/ImageViewer.cpp
        res/src/ui/viewer/ImageViewer.h
        res/src/huffman-coding/Huffman.cpp
        res/src/huffman-coding/Huffman.h)

add_executable(SVDCompression ${sources})

#MAKE SURE TO INCLUDE -mwindows and -lsfml-main TO REMOVE THE CONSOLE WINDOW WHEN IN GUI.
target_link_libraries(SVDCompression sfml-graphics sfml-window sfml-system pybind11::embed ${Python_LIBRARIES})
cmake_minimum_required(VERSION 3.0)
project(SVDCompression)

set(CMAKE_CXX_STANDARD 17)
set(SFML_DIR lib/SFML-2.5.1/lib/cmake/SFML)

find_package(SFML REQUIRED system window graphics network audio)
include_directories(lib/SFML-2.5.1/include)

set(sources
        main.cpp
        res/scripts/ui/Button.cpp
        res/scripts/ui/Button.h
        res/scripts/ui/super/UIElement.cpp
        res/scripts/ui/super/UIElement.h
        res/scripts/managers/AssetManager.cpp
        res/scripts/managers/AssetManager.h
        res/scripts/managers/UIElementManager.cpp
        res/scripts/managers/UIElementManager.h
        res/scripts/ui/super/SpriteBased.cpp
        res/scripts/ui/super/SpriteBased.h
        res/scripts/ui/super/TextBased.cpp
        res/scripts/ui/super/TextBased.h
        res/scripts/ui/ProgressBar.cpp
        res/scripts/ui/ProgressBar.h res/scripts/commands/Commands.cpp res/scripts/commands/Commands.h)

add_executable(SVDCompression ${sources})
target_link_libraries(SVDCompression sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
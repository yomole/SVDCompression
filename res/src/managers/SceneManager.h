#pragma once

//INCLUDE STATEMENTS:
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include "../ui/scene/Scene.h"

//USING STATEMENTS:
using std::invalid_argument;
using std::unordered_map;
using sf::RenderWindow;
using sf::Mouse;
using sf::Vector2i;
using sf::Vector2f;

//Forward Declare Scenes.
class Scene;

///Handles each UI element in the application.
class SceneManager {
    static RenderWindow* window; ///< The pointer to the renderwindow object used for the application.
    static unordered_map<string, Scene> scenes; ///< A list of individual scenes with UI elements.
    static Scene* currentView; ///< The current scene on the screen.
public:

    /// @brief Creates a scene manager and assigns it a RenderWindow.
    /// @param window The renderwindow to assign to the scene manager.
    explicit SceneManager(RenderWindow* window);

    /// @brief Creates a blank scene.
    /// @param sceneName the name of the scene to be created and referenced to by Scene Manager.
    static bool addScene(const string& sceneName);

    /// @brief Changes the scene to a different one.
    /// @param sceneName the name of the scene to change to.
    static bool changeScene(const string& sceneName);

    /// @brief Gets the scene with the associated name.
    /// @param sceneName the name of the scene to access.
    /// @returns a reference to a scene.
    static Scene& getScene(const string& sceneName);

    /// @brief Draws all elements in the current scene on the screen.
    static void drawAll();

    /// @brief Activates the button underneath the mouse in the current scene.
    /// @param mouseLocation a Vector2f containing the X and Y position of the mouse.
    static void activateElement(const Vector2i& mouseLocation);

};


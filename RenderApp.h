#pragma once


#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <unordered_set>
#include <array>

namespace TetrisTT
{
  /**top-level class that manages the program's main loop. */
  class RenderApp
  {
  private:

    //tracks the current set of pressed keys.
    std::unordered_set<sf::Keyboard::Key> m_keysDown;

    //ordered list of all Drawables currently being rendered. The key is
    //the "RenderId", a monotonically increasing integer, starting from 1.
    std::vector<std::shared_ptr<sf::Drawable>> m_renderList;

    sf::RenderWindow m_mainWindow;

    /**List of all keys that we actively scan state for.*/
    const std::array<sf::Keyboard::Key, 5> KEY_SCAN_LIST{ sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Space};

  public:

    //method runs indefinitely.
    void run();

    RenderApp(int windowX, int windowY, const char* title );

    virtual ~RenderApp();

    /**Adds a drawable to the render list.*/
    void addDrawable(std::shared_ptr<sf::Drawable>& drawable);

    /**Removes a drawable from the render list. Does an erase on the underlying vector
     *of drawables, and should not be done when iterating over the drawables.*/
    bool removeDrawable(std::shared_ptr<sf::Drawable>& drawable);

  protected:

    /**Fired when a key on the keyboard transitions to down.*/
    virtual void onKeyDown(sf::Keyboard::Key keydown) {};

    /**Fired when a key on the keyboard transitions to up. */
    virtual void onKeyUp(sf::Keyboard::Key keyup) {};

    /**Game logic callback. Return false to exit program.*/
    virtual bool gameLogic() { return true; }

    sf::Color m_clearColor;

  private:

    void updateInputs();
  };
}




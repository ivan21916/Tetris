#include "RenderApp.h"

namespace TetrisTT
{
  void RenderApp::run()
  {
    while (m_mainWindow.isOpen())
    {
      sf::Event event;
      while (m_mainWindow.pollEvent(event))
      {
        if (event.type == sf::Event::Closed)
        {
          m_mainWindow.close();
        }
      }

      updateInputs();

      if (!gameLogic())
      {
        m_mainWindow.close();
        return;
      }

      m_mainWindow.clear(m_clearColor);

      for (auto it : m_renderList)
      {
        m_mainWindow.draw(*it);
      }

      m_mainWindow.display();
    }
  }

  RenderApp::RenderApp(int windowX, int windowY, const char* title) : 
    m_mainWindow(sf::VideoMode(windowX, windowY), title)
  {
  }

  RenderApp::~RenderApp()
  {
    //free all Drawables.
    m_renderList.clear();
  }

  void RenderApp::addDrawable(std::shared_ptr<sf::Drawable>& drawable)
  {
    removeDrawable(drawable); //double registrations not permitted.
    m_renderList.push_back(drawable);
  }

  bool RenderApp::removeDrawable(std::shared_ptr<sf::Drawable>& drawable)
  {
    auto drawableIt = std::find(m_renderList.begin(), m_renderList.end(), drawable);
    bool present = drawableIt != m_renderList.end();
    if (present)
    {
      m_renderList.erase(drawableIt);
    }

    return present;
  }

  void RenderApp::updateInputs()
  {
    for (auto key : KEY_SCAN_LIST)
    {
      bool isPressed = sf::Keyboard::isKeyPressed(key);
      bool wasPressed = m_keysDown.find(key) != m_keysDown.end();

      if (isPressed && !wasPressed)
      {
        onKeyDown(key);
        m_keysDown.insert(key);
      }
      else if (!isPressed && wasPressed)
      {
        onKeyUp(key);
        m_keysDown.erase(key);
      }
    }
  }
}

#include "Tetris.h"
#include "VectorMath.h"
#include <iostream>
#include <ctime>

#define MATH_PI    3.14159265358979323846

namespace TetrisTT
{
  Tetris::Tetris() : RenderApp(
    BLOCK_SIZE_PIXELS*BOARD_SIZE_WIDTH_BLOCKS+2*WINDOW_X_MARGIN_PIXELS,
    BLOCK_SIZE_PIXELS*BOARD_SIZE_HEIGHT_BLOCKS, 
    "Tetris Tech Test" )
  {
    m_clearColor = WINDOW_COLOR;

    initializeBoard();
    // Create vector of tetrimino shapes.
    TetriminoShapes tetriminoshapes;
    m_TetriminoShapesList.push_back(tetriminoshapes.tetrimino_shape1);
    m_TetriminoShapesList.push_back(tetriminoshapes.tetrimino_shape2);
    m_TetriminoShapesList.push_back(tetriminoshapes.tetrimino_shape3);
    m_TetriminoShapesList.push_back(tetriminoshapes.tetrimino_shape4);
    m_TetriminoShapesList.push_back(tetriminoshapes.tetrimino_shape5);
    m_TetriminoShapesList.push_back(tetriminoshapes.tetrimino_shape6);
    m_TetriminoShapesList.push_back(tetriminoshapes.tetrimino_shape7);

    // Create vector of tetrimino shapes matrix.
    for (std::vector<int> tetrimino : m_TetriminoShapesList)
    {
      m_TetriminoShapesMatrix.push_back(tetrimino);
    }

    // Create vector of RGB colors.
    m_ColorList.push_back(sf::Color(200, 20, 40));
    m_ColorList.push_back(sf::Color(40, 200, 20));
    m_ColorList.push_back(sf::Color(20, 40, 200));
  }

  void Tetris::Init()
  {
    std::cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << std::endl;
    for (int i = 0; i < 18; i++)
    { 
      if(i==2) std::cout << "XX  Welcome to my Tetris game! XX " << std::endl;
      if(i==4) std::cout << "XX  Use left and right arrow   XX " << std::endl;
      if(i==5) std::cout << "XX  keys to move tetrimninos.  XX " << std::endl;
      if(i==7) std::cout << "XX  Use up arrow key to rotate XX " << std::endl;
      if(i==8) std::cout << "XX  the tetriminos clockwise.  XX " << std::endl;
      if(i==10) std::cout << "XX  Press space to place the   XX " << std::endl;
      if(i==11) std::cout << "XX  tetriminos at the bottom.  XX " << std::endl;
      if(i==13) std::cout << "XX    Enjoy    the     game!   XX " << std::endl;
      if(i==15) std::cout << "XX             by Ivan Chiang  XX " << std::endl;
      else std::cout << "XX                             XX" << std::endl; 
    }
    std::cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << std::endl;

    m_IsInit = false;
  }

  void Tetris::CreateTetrimino()
  {
    int32_t currentShape = rand() % 7;
    int32_t currrentColor = rand() % 3;
    SetCurrentShape(currentShape);
    int8_t x, y;
    for (y = 0; y < 4; y++)
    {
      for (x = 0; x < 4; x++)
      {
        if (m_TetriminoShapesList[m_CurrentShape][static_cast<unsigned __int64>(y) * 4 + x] != 0)
        {
          sf::RectangleShape* pixel = new sf::RectangleShape(sf::Vector2f((float)BLOCK_SIZE_PIXELS, (float)BLOCK_SIZE_PIXELS));
          // Push the pixels into vector.
          if (pixel != nullptr) m_PixelList.push_back(pixel);
          if (pixel != nullptr) pixel->setFillColor(m_ColorList[currrentColor]);
          m_blockTilePos = sf::Vector2i(m_CurrentPosX + x, m_CurrentPosY + y);
          // Push the current position of pixels into vector.
          m_CurrentBlockPos.push_back(m_blockTilePos);
          if (pixel != nullptr) pixel->setPosition(tileToWindow(m_blockTilePos));
          m_block = std::shared_ptr<sf::RectangleShape>(pixel);
          // Push the pointer of pixels into vector.
          m_CurrentBlock.push_back(m_block);
          std::shared_ptr<sf::Drawable> insertPtr = std::static_pointer_cast<sf::Drawable>(m_block);
          addDrawable(insertPtr);
          // Push the drawables into vector.
          m_DrawableList.push_back(insertPtr);
          // Cope the current shape to the matrix.
          m_TetriminoShapesMatrix[m_CurrentShape][static_cast<unsigned __int64>(y) * 4 + x] = m_TetriminoShapesList[m_CurrentShape][static_cast<unsigned __int64>(y) * 4 + x];
        }
        else m_TetriminoShapesMatrix[m_CurrentShape][static_cast<unsigned __int64>(y) * 4 + x] = 0;
      }
    }
    m_IsReadyToCreate = false;
  }

  void Tetris::CreateNextTetrimino()
  {
    // Reset the location to the top middle before create next tetrimino.
    m_CurrentPosX = 3;
    m_CurrentPosY = 0;
    CreateTetrimino();
  }

  void Tetris::SetCurrentShape(uint8_t currentShape)
  {
    m_CurrentShape = currentShape;
  }

  bool Tetris::IsBottomCollided()
  {
    int8_t x, y;
    for (y = 0; y < 4; y++)
    {
      for (x = 0; x < 4; x++)
      {
        if ((m_TetriminoShapesMatrix[m_CurrentShape][static_cast<unsigned __int64>(y) * 4 + x] != 0 && m_CurrentPosY + y + 1 > BOARD_SIZE_HEIGHT_BLOCKS)
            || (m_TetriminoShapesMatrix[m_CurrentShape][static_cast<unsigned __int64>(y) * 4 + x] != 0 && m_OccupiedPosition[m_CurrentPosY + y][m_CurrentPosX + x] == 8))
        {
          SavePosition(m_CurrentPosX, m_CurrentPosY - 1);
          return true;
        }
      }
    }
    return false;
  }

  bool Tetris::IsReachBottom()
  {
    uint8_t x, y;
    for (y = 0; y < 4; y++)
    {
      for (x = 0; x < 4; x++)
      {
         //If tetrimino reach bottom boundary.
        if (m_TetriminoShapesMatrix[m_CurrentShape][static_cast<unsigned __int64>(y) * 4 + x] != 0 && m_CurrentPosY + y + 1 > BOARD_SIZE_HEIGHT_BLOCKS)
        {
          return true;
        }
        // If tetrimino collide with another tetrimino.
        if (m_TetriminoShapesMatrix[m_CurrentShape][static_cast<unsigned __int64>(y) * 4 + x] != 0 && m_OccupiedPosition[m_CurrentPosY + y][m_CurrentPosX + x] == 8)
        {
          return true;
        }
      }
    }
    return false;
  }
  
  enum Tetris::BoundState Tetris::SideCollision()
  {
    uint8_t x, y;
    for (y = 0; y < 4; y++)
    {
      for (x = 0; x < 4; x++)
      {
        //Reach left or right board boundary.
        if (m_TetriminoShapesMatrix[m_CurrentShape][static_cast<unsigned __int64>(y) * 4 + x] > 0)
        {
          // Left board boundary.
          if (m_CurrentPosX + x - 1 < 0) return left;
          // RIght board boundary.
          if (m_CurrentPosX + x + 1 >= BOARD_SIZE_WIDTH_BLOCKS) return right;
          // Left exist tetrimino.
          if (m_OccupiedPosition[m_CurrentPosY + y][m_CurrentPosX + x - 1] == 8) return left;
          // Right exist tetrimino.
          if (m_OccupiedPosition[m_CurrentPosY + y][m_CurrentPosX + x + 1] == 8) return right;

        }
      }
    }
    return none;
  }

  void Tetris::SavePosition(int currentPosX, int currentPosY)
  {
    int x, y;
    for (y = 0; y < 4; y++)
    {
      for (x = 0; x < 4; x++)
      {
        // Save the last position before reaching bottom.
        if (m_TetriminoShapesMatrix[m_CurrentShape][static_cast<unsigned __int64>(y) * 4 + x] != 0)
        {
          m_LastPosition.push_back(sf::Vector2i(currentPosX + x, currentPosY + y));
          for (size_t i = m_LastPosition.size() - 4; i < m_LastPosition.size(); i++)
          {
            m_OccupiedPosition[m_LastPosition[i].y][m_LastPosition[i].x] = 8;
          }
        }
      }
    }
  }

  void Tetris::PausePosition()
  {
    if (!m_LastPosition.empty() && !m_PixelList.empty())
    {
      // Suspend tetriminos which have collided.
      for (size_t i = 0; i < m_LastPosition.size(); i++)
      {
        if(m_PixelList[i] != nullptr) m_PixelList[i]->setPosition(tileToWindow(m_LastPosition[i]));
      }
    }
  }

  void Tetris::SetDeltaTime()
  {
    m_DeltaTime = m_Clock.getElapsedTime().asSeconds();
    m_Clock.restart();
  }

  void Tetris::TetriminoFall()
  {
    m_Timer += m_DeltaTime;
    if (m_Timer > m_Delay)
    {
      for (size_t i = m_CurrentBlockPos.size() - 4; i < m_CurrentBlockPos.size(); i++)
      {
        m_CurrentBlockPos[i] += sf::Vector2i(0, 1);
        m_PixelList[i]->setPosition(tileToWindow(m_CurrentBlockPos[i]));
      }
      m_CurrentPosY += 1;
      m_Timer = 0;
    }
  }

  void Tetris::DropToBottom()
  {
    // Press space to place the tetrimino at bottom.
    while (!IsReachBottom())
    {
      for (size_t i = m_CurrentBlockPos.size() - 4; i < m_CurrentBlockPos.size(); i++)
      {
        m_CurrentBlockPos[i] += sf::Vector2i(0, 1);
        m_PixelList[i]->setPosition(tileToWindow(m_CurrentBlockPos[i]));
      }
      m_CurrentPosY += 1;
    }
  }

  void Tetris::Rotate()
  {
    uint8_t x, y, i;
    // Create position matrix of next rotation. 
    for (y = 0; y < 4; y++)
    {
      for (x = 0; x < 4; x++)
      {
        i = 3 - y + (x * 4);
        m_CurrentRotation[i] = m_TetriminoShapesMatrix[m_CurrentShape][static_cast<unsigned __int64>(y) * 4 + x];
      }
    }
    // Copy current rotation matrix to current tetrimino matrix.
    for (y = 0; y < 4; y++)
    {
      for (x = 0; x < 4; x++)
      {
        m_TetriminoShapesMatrix[m_CurrentShape][static_cast<unsigned __int64>(y) * 4 + x] = m_CurrentRotation[y * 4 + x];
      }
    }

    std::vector< sf::Vector2i> currentPos;
    // Save current position after rotation.
    for (y = 0; y < 4; y++)
    {
      for (x = 0; x < 4; x++)
      {
        if (m_CurrentRotation[y * 4 + x] != 0)
        {
          currentPos.push_back(sf::Vector2i(m_CurrentPosX + x, m_CurrentPosY + y));
        }
      }
    }
    uint8_t n = 0;
    // Update the new position of tetrimino.
    for (size_t i = m_PixelList.size() - 4; i < m_PixelList.size(); i++)
    {
      m_PixelList[i]->setPosition(tileToWindow(currentPos[n]));
      m_CurrentBlockPos[i] = currentPos[n++];
    }
  }

  bool Tetris::IsAbleToRotate() 
  {
    int nextRotation[16];
    uint8_t x, y, i;
    // Create a matrix of next rotation.
    for (y = 0; y < 4; y++)
    {
      for (x = 0; x < 4; x++)
      {
        i = 3 - y + (x * 4);
        nextRotation[i] = m_TetriminoShapesMatrix[m_CurrentShape][static_cast<unsigned __int64>(y) * 4 + x];
      }
    }
    for (y = 0; y < 4; y++)
    {
      for (x = 0; x < 4; x++)
      {
        if (nextRotation[4 * y + x] > 0)
        {
          // Check if collide with another tetrimino.
          if (m_OccupiedPosition[m_CurrentPosY + y][m_CurrentPosX + x] == 8) return false;
          // Check if collide with left or right boundary.
          if (m_CurrentPosX + x  <  0 || m_CurrentPosX + x >= BOARD_SIZE_WIDTH_BLOCKS) return false;
          // Check if collide with bottom boundary.
          if (m_CurrentPosY + y >= BOARD_SIZE_HEIGHT_BLOCKS) return false;
        }
      }
    }
    return true;
  }

  bool Tetris::IsRawFull()
  {
    int x, y, flag = 0; 
    m_EliminateLines = 0;
    // Check if the row is ready to eliminate.
    for (y = 0; y < BOARD_SIZE_HEIGHT_BLOCKS; y++)
    {
      for (x = 0; x < BOARD_SIZE_WIDTH_BLOCKS ; x++)
      {
        // No row is full.
        if (m_OccupiedPosition[y][x] != 8)
        {
          flag = 1;
        }
      }
      // At least one row is full.
      if (flag == 0)
      {
        m_CountEliminateHeight = y;
        m_TotalEliminateLines++;
        m_EliminateLines++;
        return true;
      }
      flag = 0;
    }
    return false;
  }

  void Tetris::EliminateLines()
  {
    // Update position for collision detection.
    for (int64_t y = m_CountEliminateHeight; y >= 0; y--)
    {
      for (int64_t x = BOARD_SIZE_WIDTH_BLOCKS - 1; x >= 0 ; x--)
      {    
        if(y != 0) m_OccupiedPosition[y][x] = m_OccupiedPosition[y-1][x];
        else m_OccupiedPosition[y][x] = 0;
      }
    }
    // Set the new position of tetriminos after eliminate the lines.
    for (size_t i = 0; i < m_LastPosition.size(); i++)
    {
      if (m_LastPosition[i].y == m_CountEliminateHeight) removeDrawable(m_DrawableList[i]);
      if(m_LastPosition[i].y <= m_CountEliminateHeight) m_LastPosition[i].y += 1;
    }
    std::cout << "Your scores: " << m_TotalEliminateLines << std::endl;
  }

  bool Tetris::IsGameOver()
  {
    for (uint8_t y = 0; y < 4; y++)
    {
      for (uint8_t x = 0; x < 4; x++)
      {
        if (m_TetriminoShapesMatrix[m_CurrentShape][static_cast<unsigned __int64>(y) * 4 + x] != 0 && m_OccupiedPosition[m_CurrentPosY + y][m_CurrentPosX + x] == 8)
        {
          std::cout << "Game Over!" << std::endl;
          return true;
        }
      }
    }
    return false;
  }

  void Tetris::initializeBoard()
  {
    float boardx = (float)(BLOCK_SIZE_PIXELS * BOARD_SIZE_WIDTH_BLOCKS);
    float boardy = (float)(BLOCK_SIZE_PIXELS * BOARD_SIZE_HEIGHT_BLOCKS);

    sf::RectangleShape* pBoard = new sf::RectangleShape(sf::Vector2f(boardx, boardy));
    pBoard->setFillColor(sf::Color::Black);
    pBoard->setPosition(tileToWindow(sf::Vector2i(0, 0)));
    m_board.reset(pBoard);

    addDrawable(m_board);
  }

  sf::Vector2f Tetris::tileToWindow(sf::Vector2i tileCoords) const
  {
    sf::Vector2i result = vec2Mul(tileCoords, sf::Vector2i(BLOCK_SIZE_PIXELS, BLOCK_SIZE_PIXELS));
    result.x += WINDOW_X_MARGIN_PIXELS;

    return sf::Vector2f((float)result.x, (float)result.y);
  }

  void Tetris::onKeyUp(sf::Keyboard::Key keyup)
  {
    sf::Vector2i offset(
      //horizontal displacement
      keyup == sf::Keyboard::Left ? -1 :
      keyup == sf::Keyboard::Right ? 1 : 0,
      //vertical displacement
      keyup == sf::Keyboard::Down ? 1 : 0
    );
    // If tetrimino collide with right or left boundary.
    if (offset.x == -1 && SideCollision() == BoundState::left) return;
    if (offset.x == 1 && SideCollision() == BoundState::right) return;
    // Press space to place the tetrimino at bottom.
    if (keyup == sf::Keyboard::Space) DropToBottom();
    if (keyup == sf::Keyboard::Up)
    {
      if(IsAbleToRotate()) Rotate();
    }

    if (offset.x != 0 || offset.y != 0)
    {
        int64_t i = 0;
        // Move the pixels based on different offsets.
        for (std::shared_ptr<sf::RectangleShape> block : m_CurrentBlock)
        {
          m_CurrentBlockPos[i] += offset;
          block->setPosition(tileToWindow(m_CurrentBlockPos[i]));
          i++;
        }
        if (offset.x == 1) m_CurrentPosX += 1;
        else if (offset.x == -1) m_CurrentPosX -= 1;
        if (offset.y == 1) m_CurrentPosY += 1;
        else if (offset.y == -1) m_CurrentPosY -= 1;
    }
  }

  bool Tetris::gameLogic()
  {
    // Initialize the game.
    if (m_IsInit) Init();

    // Create tetrimino.
    if(m_IsReadyToCreate) CreateTetrimino();

    // Create next tetrimino after current tetrimino collided.
    if (IsBottomCollided()) CreateNextTetrimino();

    // Suspend all the collided tetriminos.
    PausePosition();

    // Reset the delta time for every loop.
    SetDeltaTime();

    // Make tetrimino fall by tick.
    TetriminoFall();

    // Eliminate the lines at least one row is full.
    if (IsRawFull()) EliminateLines();

    // Game is over while tetrimino exceed the top boundary.
    if (IsGameOver()) return false;

    return true;
  }
}


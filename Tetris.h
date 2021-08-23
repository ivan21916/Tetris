#pragma once
#include "RenderApp.h"

#include <SFML/Main.hpp>
#include <array>

namespace TetrisTT
{
  struct TetriminoShapes
  {
    // "I" shape tetrimino.
    std::vector<int> tetrimino_shape1 = {
       1, 1, 1, 1,
       0, 0, 0, 0,
       0, 0, 0, 0,
       0, 0, 0, 0
    };
    // "O" shape tetrimino.
    std::vector<int> tetrimino_shape2 = {
       0, 2, 2, 0,
       0, 2, 2, 0,
       0, 0, 0, 0,
       0, 0, 0, 0
    };
    // "T" shape tetrimino.
    std::vector<int> tetrimino_shape3 = {
       0, 3, 0, 0,
       3, 3, 3, 0,
       0, 0, 0, 0,
       0, 0, 0, 0
    };
    // "J" shape tetrimino.
    std::vector<int> tetrimino_shape4 = {
       4, 0, 0, 0,
       4, 4, 4, 0,
       0, 0, 0, 0,
       0, 0, 0, 0
    };
    // "L" shape tetrimino.
    std::vector<int> tetrimino_shape5 = {
       0, 0, 5, 0,
       5, 5, 5, 0,
       0, 0, 0, 0,
       0, 0, 0, 0
    };
    // "S" shape tetrimino.
    std::vector<int> tetrimino_shape6 = {
       0, 6, 6, 0,
       6, 6, 0, 0,
       0, 0, 0, 0,
       0, 0, 0, 0
    };
    // "Z" shape tetrimino.
    std::vector<int> tetrimino_shape7 = {
       7, 7, 0, 0,
       0, 7, 7, 0,
       0, 0, 0, 0,
       0, 0, 0, 0
    };
  };

  class Tetris : public RenderApp
  {

  private:

    sf::Vector2i m_blockTilePos;
    std::vector<sf::Vector2i> m_CurrentBlockPos;
    std::shared_ptr<sf::RectangleShape> m_block;
    std::vector<std::shared_ptr<sf::RectangleShape>> m_CurrentBlock;
    std::shared_ptr<sf::Drawable> m_board;

  public:

    static constexpr int BLOCK_SIZE_PIXELS = 32;
    static constexpr int BOARD_SIZE_WIDTH_BLOCKS = 10;
    static constexpr int BOARD_SIZE_HEIGHT_BLOCKS = 20;
    static constexpr int WINDOW_X_MARGIN_PIXELS = 200;

    const sf::Color WINDOW_COLOR{ 0xEF, 0xEB, 0xD4 };

    Tetris();

    // The states of boundary collisioin.
    enum BoundState {left, right, none};

    void Init(); // Initialize the game.
    void CreateTetrimino(); // Create (first) tetrimino.
    void CreateNextTetrimino(); // Create next tetrimino.
    void SetCurrentShape(uint8_t currentShape); // Set current tetrimino shape.
    bool IsBottomCollided(); // Check if the tetrimino collide with bottom boundary or another tetrimino, if true then save position.
    bool IsReachBottom(); // Check if the tetrimino collide with bottom boundary or another tetrimino. 
    enum BoundState SideCollision(); // Return the type of tetrimino side collision.
    void SavePosition(int currentPosX, int currentPosY); // Save last position before tetrimino collide.
    void PausePosition(); // Suspend the tetrimino which has bottom collided.
    void SetDeltaTime(); // Set delta time for tick.
    void TetriminoFall(); // Make tetimino fall by tick.
    void DropToBottom(); // Press space to place the tetrimino at bottom. 
    void Rotate(); // Rotate the tetrmino clockwise with 90 degrees.
    bool IsAbleToRotate(); // Check if the tetrimino is allowed to rotate.
    bool IsRawFull(); // Check if any rows is full.
    void EliminateLines(); // Eliminate the rows/lines if it is full.
    bool IsGameOver(); // Game is over.

  protected:

    virtual void onKeyUp(sf::Keyboard::Key keyup);

    virtual bool gameLogic();

  private:

    sf::Vector2f tileToWindow(sf::Vector2i tileCoords) const;
   
    void initializeBoard();
    // Vector of all tetrimino shapes matrix.
    std::vector<std::vector<int>> m_TetriminoShapesMatrix;
    // Vector of tetrimino shapes.
    std::vector<std::vector<int>> m_TetriminoShapesList;
    // Vector of RGB colors.
    std::vector<sf::Color> m_ColorList;
    // Vevtor of all pixels.
    std::vector<sf::RectangleShape*> m_PixelList;
    // Vector of all drawables.
    std::vector<std::shared_ptr<sf::Drawable>>  m_DrawableList;
    // Vector of last positioin before collosion.
    std::vector<sf::Vector2i> m_LastPosition;
    // Array of pixels position inside the board.
    int m_OccupiedPosition[BOARD_SIZE_HEIGHT_BLOCKS][BOARD_SIZE_WIDTH_BLOCKS] = { 0 };


    // Current X position of top left matrix, start from the middle of the board.
    int32_t m_CurrentPosX = 3;
    // Current Y position of top left matrix, start from the top of the board.
    int32_t m_CurrentPosY = 0;
    // Current tetrimino shape.
    uint8_t m_CurrentShape;
    // Array of current rotation matrix.
    int m_CurrentRotation[16] = { 0 };
    // If the game start.
    bool m_IsInit = true;
    // If ready to create the next tetrimino.
    bool m_IsReadyToCreate = true;
    // If tetrimino is allowed to rotate.
    bool m_IsAllowToRotate = true;
    // Clock object to handle time.
    sf::Clock m_Clock;
    // Frame rate independent deltatime.
    float m_DeltaTime;
    // Delay time till next tetrimino.
    float m_Delay = 1.0f;
    // Timer for elapsed time.
    float m_Timer = 0.0f;
    // Count the eliminate lines in one tick.
    uint32_t m_EliminateLines = 0;
    // Count the total eliminate lines.
    uint32_t m_TotalEliminateLines = 0;
    // Count the height of eliminate line.
    uint32_t m_CountEliminateHeight = 0;

  };
}




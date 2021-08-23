#include <SFML/Graphics.hpp>

#include "Tetris.h"

int main()
{
     TetrisTT::Tetris tetrisGame;

     srand((unsigned int)time(NULL));
     //this will block until app is complete.
     tetrisGame.run();


     return 0;
}
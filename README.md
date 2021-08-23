# Storm Flag Engineering Tech Test

## Overview 
The goal of the test is to design and implement code for the classic game "Tetris". You will be extending a game framework provided in this package.

This excercise should take about 8 hours of actual programming time, but you will have several days to plan and complete your work.

If you put in at least 4 hours of time and cannot complete a full implementation due to other commitments, please say so and submit your solution even at a partially fuctional state. (Please do make sure it builds and starts playing though!)

## Basic Design Requirements
Your main focus should be on making a solid working implementation "Tetris", controlled with a keyboard. The core game rules include the following features:

* Tetriminos fall from the top of the board. A Tetrimino is one of these 7 fundamental shapes made of 4 connected square blocks:
    █       █       █ 
    █       █       █      ██     ███     ██     ██
    █      ██       ██     ██      █     ██       ██
    █
* When one tetrimino grounds on the board, a new random tetrimino is generated at the top.
* Tetriminos can be rotated 90 degrees by the player by pressing the UP key. 
* Tetriminos can be stepped downward by the player by pressing the DOWN key.
* Tetriminos can be moved left or right by the player by pressing the LEFT or RIGHT keys. 
* If a tetrimino grounding on the board completes any rows, those rows are deleted, and all the tiles above those rows move downward. 
* If a tetrimino grounds on the board and extends above the top row, tetriminos stop falling, and some sort of GAME OVER message appears. 


## Procedure
To complete this tech test, you will need to extend the provided game framework. The existing framework shows basic rendering of a tetris play area, and a single tile, along with keyboard input handling logic to move the tile. To get set up to work on this project you will need to do the following:

1. Save this package to a work folder on your machine (e.g. "c:\SF\techtest") 
2. Install [Visual Studio 2019](https://visualstudio.microsoft.com/downloads/) (Community Edition is fine). 
3. Open the provided TetrisTechTest.sln in Visual Studio, and Build the solution. 
4. You should be able to immediately run the game framework and see a red tile, which you can move with the keyboard arrow keys.
5. If you have trouble getting the initial solution to run, please send us a message so we can help! We don't want you spending all your coding time on tools setup. 



## Submitting Your Test
Please copy your entire tech test directory (excluding binary build artifacts) into the "SOLUTION" folder in the Google Drive folder we shared with you.


## What You Can And Can't Use

**Things to Use**: You may consult any online reference documentation you wish. Please do not look at the code for another implementation of Tetris and do not directly copy any code from the web for your solution.

**Things Not to Use**: You should not use other people as a resource for this test, even for advice. You should not depend on any other modules besides SFML (all the code you add should be your own). 



## FAQ

**Can I change any of the core logic in the TetrisTechTest namespace?** : Absolutely. Change anything you like. 

**What platforms can I develop on?** : This test has only been validated on Windows 10. If you wish to attempt it on Linux or OSX, let us know first. 

**How do I run outside the game outside of Visual Studio?** : If you wish to do this for whatever reason, you'll need to copy the dlls in `\3rdparty\SFML-2.5.1\lib` into your build folder.


**How long should this take?** : You should be able to come up with a reasonable minimal solution in around 8 hours. In our test runs of the assignment, we have completed it in less than this time. However, we understand that you have other commitments and you could run out of time. If you have a partial running solution and run out of time, please submit your answers and tell us how long you spent on the test and how far you got.

**Can I share my solution with my Family/Friends/The World?** : Please keep your solution off the internet and do not share the code with anyone. Since we use this test to evaluate candidates, it really helps us to not have old solutions floating around online. Otherwise, of course, you can have a friend play test your version of Tetris

**Can I use git/svn/other version control to organize my work?** : If you are comfortable with version control, we encourage you to do this. You don't need to strip out any .git or .svn directories from your solution before you submit it to us (obviously don't put the solution in a public github repository). But double-check that your final solution is what is in the working directory before you send it to us!

"# Tetris" 

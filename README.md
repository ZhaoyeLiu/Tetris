# Tetris
This C++ code is a tetris game design based on two-dimensional array.
The program is designed based on a 12×22 classic and standard Tetris map size. It supports player controls using the left and right arrow keys to move randomly appearing tetrominoes left and right, the down arrow key to make the block drop quickly to the bottom, and the spacebar to rotate the block. These controls allow the full operation of the Tetris game. Additionally, the program includes a preview feature for the next falling block, a scoring system, and a Tetris gameplay introduction.

## Topic
Tetris Game Program Design

## Development Tools
IDE: Dev-Cpp 5.11
Programming Language: C++

## Requirements Analysis
The basic requirements for the Tetris game include:
1. Implementing the seven standard tetromino shapes that appear randomly.
2. Enabling natural falling, left-right movement, fast drop, and rotation of tetrominoes.
3. Ensuring keyboard interaction for these movements.
4. Preventing tetrominoes from exceeding the map boundaries, overlapping existing blocks, or penetrating the ground.
5. Detecting full rows and awarding points accordingly.

## General Design
The game adopts a 12×22 standard Tetris map. Players can move blocks left or right using the arrow keys, drop them quickly using the down arrow key, and rotate them using the spacebar. The program also features a preview of the next block, a scoring system (one point per cleared line), and a brief introduction to Tetris gameplay.

## Data Structure & Storage
The program mainly utilizes a 2D array data structure.

## Algorithm Design
This program is based on the combination of a 2D array and the Tetris game map, integrating the block coordinates with the Tetris grid coordinates.

A 12×22 2D array is established, where two linear functions map the array’s indices to the actual coordinates of the blocks on the console. (For visual aesthetics, the blocks and the map are not generated starting from the console’s coordinate origin but are shifted. Therefore, only two linear functions are required to establish the mapping.) The first index of the array corresponds to the horizontal coordinate on the screen, while the second index corresponds to the vertical coordinate.

Array value definitions:

* A 0 in the array represents an empty space on the map, meaning there is neither a moving block nor a settled block.

* A 1 in the array indicates a moving block at the corresponding coordinate.

* A 2 in the array represents a settled block that has already fallen and stacked.

Each time a block moves, the game re-renders the entire map. The elements with values 1 or 2 are displayed as blocks, while elements with value 0 are displayed as empty spaces.

When a new block appears, it spawns at the top of the map. With each downward movement, the program checks whether there is a settled block (value 2) below it. If so, the falling block is considered to have landed, movement stops, and each occupied coordinate in the 2D array is updated to 2, converting the block into part of the stacked structure.

### Scoring Mechanism
Whenever a block stops moving, the program checks for completed rows. If all elements in a row contain 2, a point is awarded. The filled row and all rows above it are shifted downward by copying values from the row above. The map is then re-rendered to visually remove the full row from the screen.

### Game Over Condition
Each time a block stops moving, the program checks whether the highest row (row 21) contains any non-zero values. If so, it means the blocks have reached the top, and the game ends, exiting the program.

### User Controls
During the block’s fall, the program continuously detects keyboard inputs:

* Left Arrow: Sets the current block’s coordinates to 0, moves it one unit left, updates the new coordinates to 1, and re-renders the map.

* Right Arrow: Performs the same operation as left movement, but moves the block one unit right instead.

* Down Arrow: Continuously increases the vertical index until either:

  * It reaches a non-zero value below, or

  * It reaches the maximum vertical index (21).Once a block lands, it is converted into a settled block (value 2), and the map is re-rendered.

* Spacebar (Rotation):

  * The current block's coordinates are set to 0.

  * Based on the block type, it rotates counterclockwise.

  * The new coordinates are assigned 1.

  * The map is re-rendered, visually displaying the rotation.

**Author: Zhaoye Liu**

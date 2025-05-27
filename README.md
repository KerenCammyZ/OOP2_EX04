# Xonix-style Game – OOP2 Assignment 4

## Students Details
Keren Zaig,
Yissachar Welt
 
## General Description

This project implements a simplified version of the classic game *Xonix*, built in C++ using object-oriented programming principles and the SFML graphics library. The goal of the game is to claim territory by drawing paths and avoiding enemies.

## Project Files

- `main.cpp`: Initializes and starts the game by creating and running the `Controller`.
- `Controller.h / .cpp`: Manages the game flow, including window management, event handling, and game state updates.
- `Board.h / .cpp`: Represents the game board, including tile management and collision detection.
- `Player.h / .cpp`: Controls player movement, input, and interactions with the board.
- `Enemy.h / .cpp`: Implements the logic and behavior of enemy objects.
- `LevelManager.h / .cpp`: Loads and transitions between different game levels.
- `Tile.h / .cpp`: Abstract base class for board tiles.
- `EmptyTile.h / .cpp`, `FullTile.h / .cpp`: Specific tile types representing empty and filled territory.
- `Trail.h / .cpp`: Represents the trail the player leaves while moving outside the filled area.
- `MovingObject.h / .cpp`: Abstract class for movable entities (e.g., player, enemy).
- `GameObject.h / .cpp`: Base class for all visible game elements.
- `GlobalSizes.h`: Contains global constants used throughout the game.
- `resources/levels.txt`: A text file defining the layout and content of game levels.

## Key Data Structures

- `std::vector<std::vector<std::unique_ptr<Tile>>>`: 2D matrix representing the board's tiles.
- `std::vector<std::unique_ptr<Enemy>>`: A list of enemy instances on the board.
- `std::vector<std::unique_ptr<Trail>>`: The player’s current trail on the board.

## Notable Algorithms

- **Flood Fill Algorithm**: Used to determine which areas are enclosed by the player's trail and can be marked as captured.
- **Collision Detection**: Checks interactions between the player, enemies, and tiles to determine game events.
- **Level Parsing**: Reads and interprets level data from the `levels.txt` resource file.

## Design

- **Controller**: Central coordinator of the game. Handles game states, rendering loop, and user input.
- **Board**: Manages tile layout, collision logic, and area claiming.
- **Player / Enemy**: Derived from `MovingObject`, these classes encapsulate movement and interaction logic.
- **Tiles**: Polymorphic representation of different cell types (Empty, Full, Trail).
- **LevelManager**: Responsible for reading level definitions and initializing the board accordingly.
- **GameObject**: Shared base for all drawable and interactive entities, supporting polymorphic rendering and updates.

Objects interact mainly via method calls and shared pointers, promoting encapsulation and separation of concerns.

## Known Bugs

- Enemies may get stuck on FullTiles in the board.
- Enemies can sometimes return to the same direction they came from.
- If the player draws a very complicated shape, the whole board can be filled.

## Other Notes

- Enemy bugs sincerely add to the game mechanics in a positive way. 
    For example: It's easier to trap enemies and they have more rich behavior.
- The size of the screen must made of numbers that are multiples of 20 (tileSize).
- We added a progress bar at the bottom to easily show the user how much they have until they complete the level.

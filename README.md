README FILE
---------------------------------------------------
GENERAL INFORMATION 
- This game was coded in C++, using Visual Studio 2022 version 4.8.09032.
- This game was created by Daniel Steele - a Plymouth University student.
- This Game is called Knights Adventure.
- Although the .exe isn't included in the Github folder, It will be in the final DLE upload. 
  
- It's a text-based dungeon-crawling adventure game where the player has to find their way through multiple different rooms to escape the dungeon.
- Along the way, they will encounter many themed rooms, obstacles, Items, and even treasures. 
- The game is designed to intrigue the player and to think about different possibilities, and what outcome may happen.
---------------------------------------------------
CONTROLS 

- This game is controlled primarily using the keys 1,2,3 and 4.
- The game will also ask the user for their character's name at the start, which the program uses to reference the player.
- 
---------------------------------------------------
EXTRAS
- This game uses the following include files:
#include <iostream>
#include <stdio.h>
#include <thread>  // enables text to sleep (pause for a set number of seconds before continuing to output to the console)
#include <chrono>  // for duration of sleep
#include <cctype>  // for checking for numerical and character inputs (isdigit) 
#include <fstream> // enables the program to read text files 

using namespace std; 

- This game also references Player.h to refer to Player attributes, such as their name, how many coins they have collected and whether or not they hold a specific item. 

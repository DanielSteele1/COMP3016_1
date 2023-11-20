#include <iostream>
#include <stdio.h>
#include <string>
#include <thread>  // sleep
#include <chrono>  // for duration of sleep
#include <cctype> // for checking for numerical and charecter inputs (isdigit) 
#include <limits>
#include <fstream> // read text files 

#include "Player.h"


using namespace std; 

class Player;
class Game;
class MainMenu;
class CreditsMenu;

//REMINDER   -  FINISH ALL ROOMS( JUST MAKE 5 ) - 

// Player Class - this class controls every stat the player has, such as thier name, amount of coins, health etc. 

Player::Player() : coins(0), health(100) {}

// stores the players name
string Player::getName() const {
    return name;
}

void Player::setName(const std::string& playerName) {
    name = playerName;
}

int Player::getCoins() const{
    
     return coins;
}

void Player::addCoins(int amount) {
    coins += amount;
}

// this is the overall amount of coins a player has at one time ( use overallCoinAmount() )
void Player::overallCoinAmount() const {

    cout << " Current Coins: " << getCoins() << endl;
}

void Player::takeDamage(int damage) {

   health -= damage;

   if (health <= 0) {  // if health reaches 0, player dies

     handlePlayerDeath();
   }
}
 //this enables the users current health to be shown ( use gethealth() ) 
 int Player::getHealth() const {

        return health;    
}

 void Player::handlePlayerDeath() {
     
    // call this when the player dies 
     
     cout << " " << endl; 
     cout << " You Died! Game Over. " << endl;
     cout << " " << endl;
     
     cout << " Press enter to continue: " << endl;
     
     cin.ignore(numeric_limits<streamsize>::max(), '\n');  // User has to press enter to return to the menu screen. 
     cin.get();
     
     system("cls");
 }

// heals the player by a certain amount specified 
    void Player::heal(int amount) {

        health += amount;
    }

//  Error Checking
int getPlayerChoice() {
    string playerChoice;

    bool isNumeric = true;
    cin >> playerChoice;

    for (char c : playerChoice) {

        if (!isdigit(c)) {

            isNumeric = false;
            break;
        }
    }

    if (isNumeric) {
        int choice = stoi(playerChoice);
        if (choice >= 1 && choice <= 4) {
            return choice;
        }
    }
    return -1;

}

// Main Menu
class MainMenu {
public:
    void display() {
        system("cls");
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
        fstream inputFile("TitleMenu.txt");

        if (!inputFile.is_open()) {

            cout << "Error Loading Game File: ' TitleMenu ' " << endl;
        }

        string line;
        while (getline(inputFile, line)) {

            cout << line << endl;

        }
        inputFile.close();
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    }
};

class Game {
public:

    // gameActive =  Game Is Initiated - Player has started the game
    // setting gameActive to false will end the game.
    //
    // foundCoins is what's used to give the player coins. Naturally, they start with 0.
    // hasSword states whether or not the player picked up the sword in one of the rooms.
    // chestChoice is specifically for whether the player opens a chest later on in the game. 

    Game() : gameActive(true), hasSword (false), hasKey (false), chestChoice(0), foundCoins(0) { }

    // call this when i need to display the players health 
    void displayPlayerHealth() {

        cout << "Current Health " << player.getHealth() << endl;

    }

    void setHasSword(bool value) {
        hasSword = value;
    }

    void setHasKey(bool value) {
        hasKey = value;
    }
    void start() {

        cout << " " << endl;
        cout << " " << endl;

        string playerName;
        cout << "Please input your name" << endl;

        cout << " " << endl;
        cout << " " << endl;

        cin >> playerName;

        // sets the players name to a name of thier liking
        player.setName(playerName);

        cout << "Welcome, " << player.getName() << "!" << endl;

        this_thread::sleep_for(std::chrono::milliseconds(2000));

        system("cls");

        cout << "------------------------------------------------------------------------------------------------------------------------ " << endl;

        // read start.txt file here 

        fstream inputFile("start.txt");

        if (!inputFile.is_open()) {

            cout << "Error Loading Game File: ' Start ' " << endl;
        }

        string line;
        while (getline(inputFile, line)) {

            cout << line << endl;

        }

        inputFile.close();

        cout << "       You think it's " << player.getName() << endl;

        cout << "       You see a crack in the old broken down stone cell wall. You decide to : " << endl;

        cout << " " << endl;
        cout << "------------------------------------------------------------------------------------------------------------------------ " << endl;

        int playerChoice;

        do {
            // options

            cout << " " << endl;
            cout << " " << endl;

            cout << "1. Check the crack in the cell wall" << endl;
            cout << "2. Look around the cell " << endl;
            cout << "3. Wait for someone to rescue you " << endl;
            cout << "4. Quit game to main menu " << endl;

            cout << "      " << endl;
            cout << "      " << endl;

            cout << "Enter your choice (1 - 4): ";
            playerChoice = getPlayerChoice();

            cout << "------------------------------------------------------------------------------------------------------------------------" << endl;

            if (playerChoice != -1) {
                switch (playerChoice) {
                case 1:
                    cout << "You Check the crack in the cell wall" << endl;
                    this_thread::sleep_for(std::chrono::milliseconds(500));
                    cout << "There's an old crumbled brick in the wall. You push it and the wall crumbles away, revealing a hidden passage! " << endl;
                    cout << "    " << endl;

                    cout << "You proceed into the next room. . . " << endl;
                    cout << "    " << endl;

                    cout << "Press Enter to progess... " << endl;

                    cout << " " << endl;
                    cout << " " << endl;

                    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;

                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // User has to press enter to return to the menu screen. 
                    cin.get();

                    Room2(); // onto room 2

                    break;

                case 2:

                    cout << " " << endl;

                    cout << "You look around the cell.  " << endl;

                    this_thread::sleep_for(std::chrono::milliseconds(1000));

                    cout << " " << endl;
                    cout << "You spot some old rags on the floor, no doubt from past prisoners who met thier doom here. " << endl;
                    cout << " " << endl;
                    cout << "In one of the pockets, you find a small pouch containing 10 coins. lucky you! " << endl;
                    // plus 10 coins 
                    foundCoins = 10;  // this is how many coins have just been found
                    player.addCoins(foundCoins); // we're adding the found coins to the players overall coin collection. 

                    this_thread::sleep_for(std::chrono::milliseconds(1000));

                    cout << " " << endl;
                    cout << " + 10 Coins " << endl;
                    cout << " " << endl;

                    player.overallCoinAmount();  // showing the player how many coins they now have overall 
                    cout << " " << endl;

                    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;

                    break;

                case 3:

                    cout << " " << endl;

                    cout << "You decide to wait for someone to rescue you." << endl;

                    this_thread::sleep_for(std::chrono::milliseconds(2000));
                    cout << "You wait a bit ... " << endl;

                    this_thread::sleep_for(std::chrono::milliseconds(2000));

                    cout << "You wait a little longer ... " << endl;

                    this_thread::sleep_for(std::chrono::milliseconds(2000));

                    cout << "You wait a lot longer ... " << endl;

                    this_thread::sleep_for(std::chrono::milliseconds(3000));

                    cout << "You've waited a long time. But you think to yourself you're determined to keep going. You tell yourself that sooner or later, someone will come to your rescue." << endl;

                    this_thread::sleep_for(std::chrono::milliseconds(3000));

                    cout << " " << endl;
                    cout << "You've waited too long. Your body has had enough and you die of starvation (and boredom)" << endl;

                    cout << " " << endl;

                    player.overallCoinAmount(); // show them thier coins

                    player.takeDamage(100);  // kills the player 

                    system("cls");

                    cout << " " << endl;

                    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
                    MainMenu();

                    gameActive = false; // player dies, loop back to the main menu after telling the user they just died. 

                    break;
                case 4:
                    cout << "Quitting Game to Menu . . . " << endl;

                    this_thread::sleep_for(std::chrono::milliseconds(1000));

                    MainMenu();
                    gameActive = false;

                    break;

                default:
                    cout << "Invalid Choice, Please try an option in the list. " << endl;

                    cout << " " << endl;
                    cout << " " << endl;
                    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
                }
            }

        } while (gameActive);

        cout << " " << endl;

        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;

    }
private: 
    Player player;
    string playerName;


    // BELOW IS EVERY ROOM THE PLAYER WILL INTERACT WITH, WITH THE EXCEPTION OF THE STARTING CELL (which is included in the main Game Class above) 

    void Room2() 
    {
        system("cls");

        // read Room2.txt file here 

        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;

        fstream inputFile("Room2.txt");

        if (!inputFile.is_open()) {

            cout << "Error Loading Game File: ' Room 2 ' " << endl;
        }

        string line;
        while (getline(inputFile, line)) {

            cout << line << endl;

        }

        inputFile.close();

        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;

        int playerChoice;
        do {
            // options
             
            cout << " " << endl;
            cout << " " << endl;

            cout << "1. Check the forge " << endl;
            cout << "2. look around the workbench" << endl;
            cout << "3. Sneak through to the door (right) " << endl;
            cout << "4. Quit game to main menu " << endl;

            cout << "      " << endl;
            cout << "      " << endl;

            // collect players choice 

            cout << "Enter your choice (1 - 4): ";
            playerChoice = getPlayerChoice();

            cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
            if (playerChoice != -1) {
                switch (playerChoice) {
                case 1:

                    cout << "You decide to check the forge. " << endl;
                    cout << " " << endl;

                    this_thread::sleep_for(std::chrono::milliseconds(1000));

                    cout << "There's alot of tools and weapons here in some barrels, some are even complete." << endl;
                    cout << " " << endl;
                    this_thread::sleep_for(std::chrono::milliseconds(1000));

                    cout << "Amongst the various tools, you find a rusty steel sword poking out of the pile. Looks like it's only got one swing left." << endl;
                    cout << " " << endl;

                    cout << "You decide to take it. " << endl;
                    cout << " " << endl;

                    cout << "* Item Found: Sword * " << endl;

                    // player took the sword
                     setHasSword(true);
                    this_thread::sleep_for(std::chrono::milliseconds(1000));

                    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;

                    break;

                case 2:

                    cout << "You look around to the workbench" << endl;
                    cout << " " << endl;

                    this_thread::sleep_for(std::chrono::milliseconds(1000));

                    cout << "On the workbench, you find some steel ingots, a small pouch, a key and a note. " << endl;
                    cout << " " << endl;
                    this_thread::sleep_for(std::chrono::milliseconds(1000));

                    cout << "The note reads: " << endl;
                    cout << " " << endl;
                    cout << " =================================================================================================" << endl;
                    cout << " Dear Maelstrom Sovereign, Overlord of the Ebonland, I hope you this note gets to you quickly." << endl;
                    cout << " As requested, enclosed to you is the new key for the ________ room." << endl;
                    cout << " " << endl;
                    cout << " P.S please make sure not to lose this one ... this is the 3rd Key iv had to make this week." << endl;
                    cout << " " << endl;
                    cout << " [Blacksmith's Signature] " << endl;
                    cout << " " << endl;
                    cout << " =================================================================================================" << endl;

                    cout << "  " << endl;
                    this_thread::sleep_for(std::chrono::milliseconds(1000));

                    cout << "After reading the note, you decide to take the key. It may become useful later in you're journey.  " << endl;
                    this_thread::sleep_for(std::chrono::milliseconds(1000));

                    cout << " " << endl;
                    cout << "You also find 5 coins in the small pouch! nice!" << endl;

                    foundCoins = 5;  // this is how many coins have just been found
                    player.addCoins(foundCoins); // we're adding the found coins to the players overall coin collection. 

                    this_thread::sleep_for(std::chrono::milliseconds(1000));

                    cout << " " << endl;
                    cout << " + 5 Coins " << endl;
                    cout << " " << endl;
                    cout << "* Item Found: Key * " << endl;

                    setHasKey(true);
                    player.overallCoinAmount();  // showing the player how many coins they now have overall 
                    cout << "  " << endl;

                    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
                    break;

                case 3:

                    cout << "You sneak around the corner and proceed through the old wooden door to the right. " << endl;
                    cout << " " << endl;

                    this_thread::sleep_for(std::chrono::milliseconds(1000));

                    cout << "Just before you leave the room, you hear footsteps behind you. You don't stick around to find out who's they were. " << endl;
                    cout << " " << endl;

                    this_thread::sleep_for(std::chrono::milliseconds(1000));

                    cout << "You proceed into the next room. . . " << endl;
                    cout << "    " << endl;
                    // Jump to the next room 
                    cout << "Press Enter to progess . . . " << endl;

                    cout << " " << endl;
                    cout << " " << endl;

                    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;

                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // User has to press enter to return to the menu screen. 
                    cin.get();

                    Room3(); // player proceeds to room 3

                    break;

                case 4:

                    cout << "Quitting Game to Menu . . . " << endl;

                    this_thread::sleep_for(std::chrono::milliseconds(1000));

                    MainMenu();
                    gameActive = false;

                    break;

                default:
                    cout << "Invalid Choice, Please try an option in the list. " << endl;

                    cout << " " << endl;
                    cout << " " << endl;
                    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;

                }
            }
        } while (gameActive);

        cout << " " << endl;

        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;

    }

    void Room3() 
    {
        system("cls");

        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
        fstream inputFile("Room3.txt");

        if (!inputFile.is_open()) {

            cout << "Error Loading Game File: ' Room 3 ' " << endl;
        }

        string line;
        while (getline(inputFile, line)) {

            cout << line << endl;
        }

        inputFile.close();
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;

        int playerChoice;
        int chestChoice;

        do {
            // options

            cout << " " << endl;
            cout << " " << endl;

            cout << "1. Explore the ruins " << endl;
            cout << "2. Carefully walk the wooden bridge (left)" << endl;
            cout << "3. Check the stone door (right) " << endl;
            cout << "4. Quit game to main menu " << endl;

            cout << "      " << endl;
            cout << "      " << endl;

            // collect players choice 
            cout << "Enter your choice (1 - 4): ";
            playerChoice = getPlayerChoice();

            cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
            if (playerChoice != -1) {
                switch (playerChoice) {
                case 1:

                    cout << "You decide to explore the ruins further. " << endl;
                    cout << " " << endl;

                    this_thread::sleep_for(std::chrono::milliseconds(1000));

                    cout << "As you delve deeper into the moss covered and decrepit ruins you discover an old chest, sealed with a rusty lock. " << endl;
                    cout << " " << endl;
                    this_thread::sleep_for(std::chrono::milliseconds(1000));

                    cout << "You think you could use the sword to open the lock, but it might break in the process. " << endl;
                    cout << " " << endl;

                    cout << "Open it? " << endl;
                    cout << " " << endl;

                    cout << "1. Open" << endl;
                    cout << "2. Don't Open" << endl;

                    cin >> chestChoice;

                    cout << "      " << endl;
                    cout << "      " << endl;

                    switch (chestChoice) {
                    case 1:
                        cout << "You decide to open the chest.  " << endl;

                        if (hasSword) {
                            cout << "As you swing your sword to crack the lock, your sword shatters onto the ground. You can no longer use it.   " << endl;
                            this_thread::sleep_for(std::chrono::milliseconds(1000));
                            cout << "But inside the chest is a stash of diamonds and gold! Jackpot!  " << endl;
                            cout << "      " << endl;
                            foundCoins = 20;
                            player.addCoins(foundCoins); // we're adding the found coins to the player's overall coin collection. 
                            this_thread::sleep_for(std::chrono::milliseconds(1000));

                            setHasSword(false);

                            cout << " * Item Broken: Sword * " << endl;
                            cout << " " << endl;
                            cout << " + 20 Coins " << endl;
                            cout << " " << endl;

                            player.overallCoinAmount();  // showing the player how many coins they now have overall 
                        }
                        else {
                            cout << "You open the chest, but without a sword, you can't break the lock. " << endl;
                        }

                        break;

                    case 2:
                        cout << "You decide not to open the chest, and decide to head back to the ruins enterance. " << endl;

                        break;

                    default:
                        cout << "Invalid choice. Please choose 1 or 2." << endl;

                        break;
                    }

                    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
                    break;

                case 2:

                    cout << "You decide to carefully walk the wooden bridge. " << endl;
                    cout << " " << endl;

                    this_thread::sleep_for(std::chrono::milliseconds(1000));

                    cout << "As you inch towards the other side, a few rotten slats of wood fall. " << endl;
                    this_thread::sleep_for(std::chrono::milliseconds(1000));

                    cout << "  " << endl;
                    cout << "Suddenly, the entire bridge collapses! You fall and drown in the deep waters below. " << endl;
                    cout << "  " << endl;

                    player.overallCoinAmount(); // show them thier coins
                    player.takeDamage(100); // kills the player 

                    system("cls");

                    this_thread::sleep_for(std::chrono::milliseconds(1000));

                    MainMenu();
                    gameActive = false;

                    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
                    
                    break;
                case 3:

                    inputFile.close();

                    cout << "You decide to check the stone door.  " << endl;
                    cout << " " << endl;

                    this_thread::sleep_for(std::chrono::milliseconds(1000));

                    cout << "You walk up to the cold stone entrance. There's a description engraved into the door - oddly, it's in what looks to be an old version of english. " << endl;
                    cout << "   " << endl;

                    this_thread::sleep_for(std::chrono::milliseconds(1000));

                    cout << "It reads:  " << endl;
                    cout << " =================================================================================================" << endl;
                    cout << " " << endl;
                    cout << "              He that wole have passage through this dore mot taketh sum damage."                   << endl;
                    cout << " " << endl;
                    cout << " =================================================================================================" << endl;
                    this_thread::sleep_for(std::chrono::milliseconds(1000));
                    cout << " " << endl;
                    cout << "You can't quite understand the text, but decide to open the door anyway. " << endl;
                    this_thread::sleep_for(std::chrono::milliseconds(1000));
                    cout << " " << endl;
                    cout << "As you open the door, you suddenly feel alot weaker, but manage to get thought to the next room. " << endl;
                    cout << " " << endl;

                    player.takeDamage(60);  // damages player

                    displayPlayerHealth();  //displays players health

                    cout << "Despite being hurt, you manage to slowly walk into the next room. . . " << endl;
                    cout << "    " << endl;
                    // Jump to the next room 
                    cout << "Press Enter to progess . . . " << endl;

                    cout << " " << endl;
                    cout << " " << endl;

                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // User has to press enter to return to the menu screen. 
                    cin.get();

                    // proceeds to room 4
                    Room4();

                    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;

                    break;

                case 4:

                    cout << "Quitting Game to Menu . . . " << endl;

                    this_thread::sleep_for(std::chrono::milliseconds(1000));

                    gameActive = false;
                    MainMenu();
                    break;
                    
                default:
                    cout << "Invalid Choice, Please try an option in the list. " << endl;

                    cout << " " << endl;
                    cout << " " << endl;
                    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
                }
            }
        } while (gameActive);

        cout << " " << endl;

        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    }

    void Room4() 
    {
        // this room is a Library - one shelf has a hidden passage inside revealing the treasure room. 

        system("cls");

        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
        fstream inputFile("Room4.txt");

        if (!inputFile.is_open()) {

            cout << "Error Loading Game File: ' Room 4 ' " << endl;
        }

        string line;
        while (getline(inputFile, line)) {

            cout << line << endl;
        }

        inputFile.close();

        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;

        int playerChoice;

        do {
            // options

            cout << " " << endl;
            cout << " " << endl;

            cout << "1. Move to the middle of the library  " << endl;
            cout << "2. Explore the deep labyrinth of bookshelves (left) " << endl;
            cout << "3. Check the alchemists workshop " << endl;
            cout << "4. Quit game to main menu " << endl;

            cout << "      " << endl;
            cout << "      " << endl;

            // collect players choice 
            cout << "Enter your choice (1 - 4): ";
            playerChoice = getPlayerChoice();

            cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
            if (playerChoice != -1) {
                switch (playerChoice) {
                case 1:

                    cout << "You decide to move to the middle of the library, focusing on the oak reading table.  " << endl;
                    this_thread::sleep_for(std::chrono::milliseconds(1000));
                    cout << " " << endl;

                    cout << "On the oak reading table, there are many scriptures and books lying in a messy pile. " << endl;
                    cout << " " << endl;

                    cout << "You get curious, and decide to pick up a book and give it a read. " << endl;
                    cout << " " << endl;
                    cout << "But, as you do, you notice that under the pile was a small button. it's triggered as you move the pile. " << endl;
                    cout << " " << endl;
                    cout << "There's a tense few seconds of silence, before circular winding stairs start rising out of the floor!  " << endl;
                    cout << " " << endl;
                    cout << "You decide to climb the stairs and investigate. " << endl;
                    cout << " " << endl;

                    cout << "Press Enter to progess . . . " << endl;

                    cout << " " << endl;
                    cout << " " << endl;

                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // User has to press enter to return to the menu screen. 
                    cin.get();

                    // player enters the final room - room 5
                    Room5();

                    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
                    break;

                case 2:

                    cout << "You decide to explore the deep labyrinth of bookshelves " << endl;
                    cout << " " << endl;
                    this_thread::sleep_for(std::chrono::milliseconds(1000));
                    cout << " " << endl;
                    cout << "To begin with, being amonsgst dusty bookshelves, it's very easy to know how far you've been." << endl;
                    this_thread::sleep_for(std::chrono::milliseconds(1000));
                    cout << " " << endl;
                    cout << "But the more you head down the winding nerverending corridoors, you foggier and foggier it gets. " << endl;
                    this_thread::sleep_for(std::chrono::milliseconds(2000));
                    cout << " " << endl;
                    cout << "And the harder it is to find you're way.  " << endl;
                    this_thread::sleep_for(std::chrono::milliseconds(2000));
                    cout << " " << endl;
                    cout << "Eventually, you resort to finding your way around with your fingers, brushing against any surface hoping to find a way out. " << endl;
                    cout << " " << endl;
                    cout << "You notice a groove in one of the books. It feels like a keyhole. " << endl;
                    cout << " " << endl;

                    if (hasKey) {
                        
                        cout << "You remember the key you collected earlier, and decide to use it in the hole . . .  " << endl;
                        this_thread::sleep_for(std::chrono::milliseconds(2000));
                        cout << " " << endl;
                        cout << "To your surprise, it fits! You clamber inside the room to escape the fog." << endl;

                        setHasKey(false);
                        cout << " * Item Broken: Key * " << endl;
                        cout << " " << endl;
                        cout << "Press Enter to progess . . . " << endl;

                        cout << " " << endl;
                        cout << " " << endl;

                        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // User has to press enter to return to the menu screen. 
                        cin.get();

                        // player finds the trearure room! 
                        TreasureRoom();

                    }
                    else {
                        cout << "You notice the lock in the book, but you don't have a key ...  " << endl;

                        cout << "You've spent too long in the fog. You inhale too much, and perish. " << endl;
                        cout << " " << endl;

                        player.overallCoinAmount(); // show them thier coins
                        player.takeDamage(100); // kills the player 

                        system("cls");

                        this_thread::sleep_for(std::chrono::milliseconds(1000));

                        MainMenu();
                        gameActive = false;
                    }
                   
                    break;

                    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;

                    break;
                case 3:

                    cout << "You decide to check the alchemists workshop " << endl;
                    cout << " " << endl;
                    this_thread::sleep_for(std::chrono::milliseconds(1000));

                    cout << "As you enter the alchemists workshop, you notice the air is alot thicker and more dense in here,    " << endl;
                    cout << "most likely due to all the brewing and growing of herbs that once went on in this myseterious place." << endl;
                    cout << " " << endl;
                    this_thread::sleep_for(std::chrono::milliseconds(1000));
                    cout << "in the walls of this room are shelves full of old beakers and other glassware, as well as what looks like a few potions." << endl;
                    cout << " " << endl;
                    cout << "You wonder how they've survived intact this long. Maybe due to some sort of ancient magic. " << endl;
                    cout << " " << endl;
                    cout << "Regardless, you still feel weak from that stone door, so you decide to drink a bottle . . . " << endl;

                    this_thread::sleep_for(std::chrono::milliseconds(2000));
                    cout << " " << endl;
                    cout << "You feel strenghened! " << endl;
                    cout << " " << endl;

                    cout << " * Healed: 30 Health Points * " << endl;
                    cout << " " << endl;

                    player.heal(30);

                    displayPlayerHealth();

                    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;

                    break;

                case 4:

                    cout << "Quitting Game to Menu . . . " << endl;

                    this_thread::sleep_for(std::chrono::milliseconds(1000));

                    gameActive = false;
                    MainMenu();
                    break;

                default:
                    cout << "Invalid Choice, Please try an option in the list. " << endl;

                    cout << " " << endl;
                    cout << " " << endl;
                    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
                }
            }
        } while (gameActive);

        cout << " " << endl;

        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    }

    void Room5()
    {
        // This is the last room, after they have completed this room, they can escape!

        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
        fstream inputFile("Room5.txt");

        if (!inputFile.is_open()) {

            cout << "Error Loading Game File: ' Room 5 ' " << endl;
        }

        string line;
        while (getline(inputFile, line)) {

            cout << line << endl;
        }

        inputFile.close();

        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;

        int playerChoice;

        do {
            // options

            cout << " " << endl;
            cout << " " << endl;

            cout << "1. Enter the fiery door (left) " << endl;
            cout << "2. Enter the green,luscious door (middle) " << endl;
            cout << "3. Enter the door of pure darkness (right) " << endl;
            cout << "4. Quit game to main menu " << endl;

            cout << "      " << endl;
            cout << "      " << endl;

            // collect players choice 
            cout << "Enter your choice (1 - 4): ";
            playerChoice = getPlayerChoice();

            cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
            if (playerChoice != -1) {
                switch (playerChoice) {
                case 1:

                    cout << "You decide to enter the door made of fire. " << endl;
                    cout << " " << endl;

                    cout << "You think to yourself that the most dangourous paths are often also the most rewarding. " << endl;
                    cout << " " << endl;
                    this_thread::sleep_for(std::chrono::milliseconds(1000));

                    cout << "Inside the door is a huge lava lake, with stepping stones made of rock to get the other side. " << endl;
                    cout << " " << endl;
                    cout << "On the other side of the lake, you see what you think is the exit. All you have to do is get to the other side. " << endl;
                    cout << " " << endl;
                    this_thread::sleep_for(std::chrono::milliseconds(1000));

                    cout << "You begin hopping from one rock to the next, carefully dodging the lava, and your death. " << endl;
                    cout << " " << endl;
                    this_thread::sleep_for(std::chrono::milliseconds(1000));

                    cout << "Suddenly an earthquiake occurs, and then the lava starts to rise. You quickly try to escape, but it's no use. " << endl;
                    cout << " " << endl;
                    cout << " " << endl;
                    this_thread::sleep_for(std::chrono::milliseconds(1000));

                    cout << "You're cooked alive. " << endl;
                    cout << " " << endl;
                    this_thread::sleep_for(std::chrono::milliseconds(1000));

                    player.overallCoinAmount(); // show them thier coins
                    player.takeDamage(100); // kills the player 

                    system("cls");

                    this_thread::sleep_for(std::chrono::milliseconds(1000));

                    gameActive = false;
                    MainMenu();
                    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
                    
                    break;
                case 2:

                    cout << "You decide to enter the door made of moss and earth. " << endl;
                    cout << " " << endl;

                    cout << "This looks like the safest passage, and due to the amount of vegatation, you deduce that the light must be coming from somwhere. " << endl;
                    cout << " " << endl;
                    this_thread::sleep_for(std::chrono::milliseconds(1000));

                    cout << "The door closes behind you, there's no turning back now.  " << endl;
                    cout << " " << endl;
                    cout << "As you move closer into the corridoor, you notice something is wrong with the dense vegatation lining the walls. " << endl;
                    cout << " " << endl;
                    this_thread::sleep_for(std::chrono::milliseconds(1000));

                    cout << "The further down the corridoor you move, the more foul the plants get. At first, there were beautiful plants and flowers. " << endl;
                    cout << " " << endl;
                    this_thread::sleep_for(std::chrono::milliseconds(1000));

                    cout << "Not anymore, they turn darker, almost red in colour, like blood. Some now have spikes, others are sticky, designed to catch live prey. " << endl;
                    cout << " " << endl;
                    cout << "You start seeing huge carnivorous plants all around. " << endl;
                    this_thread::sleep_for(std::chrono::milliseconds(1000));

                    cout << "Suddenly, a carnivorous plant turns towards you, and swallows you whole. There's no escape. You're slowly digested. " << endl;
                    cout << " " << endl;
                    this_thread::sleep_for(std::chrono::milliseconds(1000));

                    player.overallCoinAmount(); // show them thier coins
                    player.takeDamage(100); // kills the player 

                    system("cls");

                    this_thread::sleep_for(std::chrono::milliseconds(1000));

                    gameActive = false;
                    MainMenu();

                    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
                    break;
                case 3:

                    cout << "You decide enter the door of pure darkness.  " << endl;
                    cout << " " << endl;

                    cout << "You think it must be a trick, and this must be the correct way out. but you're terrified.  " << endl;
                    cout << " " << endl;

                    cout << "As you delve further and further down the corridoor, you see ghastly figures appear before you.  " << endl;
                    cout << " " << endl;
                    this_thread::sleep_for(std::chrono::milliseconds(1000));

                    cout << "Some call out your name, warning you to turn back. " << endl;
                    cout << " " << endl;
                    this_thread::sleep_for(std::chrono::milliseconds(2000));
                    cout << "You try to turn back, but it's too late. the door is sealed shut. " << endl;
                    cout << " " << endl;

                    cout << "With no other choice left, you run down the corridoor, staring death in it's face.  " << endl;
                    cout << " " << endl;
                    this_thread::sleep_for(std::chrono::milliseconds(1000));

                    cout << "As you're running, you suddenly see a light. It's the exit! " << endl;
                    cout << " " << endl;

                    cout << "* GAME OVER - YOU ESCAPED! *" << endl;
                    cout << " " << endl;

                    cout << "Your game Stats: " << endl;
                    player.overallCoinAmount();  // showing the player how many coins they now have overall 
                    cout << " " << endl;
                    displayPlayerHealth();

                    cout << "Press Enter to Continue . . . " << endl;

                    cout << " " << endl;
                    cout << " " << endl;

                    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;

                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // User has to press enter to return to the menu screen. 
                    cin.get();

                    // player wins the game!
                    beatenGame(); 

                    break;
                case 4:

                    cout << "Quitting Game to Menu . . . " << endl;

                    this_thread::sleep_for(std::chrono::milliseconds(1000));

                    gameActive = false;
                    MainMenu();
                    break;
                default:
                    cout << "Invalid Choice, Please try an option in the list. " << endl;

                    cout << " " << endl;
                    cout << " " << endl;
                    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
                }
            }
        } while (gameActive);

        cout << " " << endl;
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    }

    void TreasureRoom() 
    {
        // Treasure! 
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
        fstream inputFile("TreasureRoom.txt");

        if (!inputFile.is_open()) {

            cout << "Error Loading Game File: ' Treasure Room ' " << endl;
        }

        string line;
        while (getline(inputFile, line)) {

            cout << line << endl;
        }

        inputFile.close();

        foundCoins = 80;
        player.addCoins(foundCoins);// we're adding the found coins to the player's overall coin collection. 
        this_thread::sleep_for(std::chrono::milliseconds(1000));

        cout << " " << endl;
        cout << " + 80 Coins " << endl;
        cout << " " << endl;

        player.overallCoinAmount();  // showing the player how many coins they now have overall 
        displayPlayerHealth();

        cout << "Press Enter to progess . . . " << endl;

        cout << " " << endl;
        cout << " " << endl;

        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // User has to press enter to return to the menu screen. 
        cin.get();

        Room4(); // player goes back to room 4
    }

    // player has won the game! 
    void beatenGame() {
        system("cls");

        fstream inputFile("GameBeaten.txt");

        if (!inputFile.is_open()) {

            cout << "Error Loading Game File: ' Game Beaten ' " << endl;
        }

        string line;
        while (getline(inputFile, line)) {

            cout << line << endl;
        }

        inputFile.close();

        cout << " " << endl;

        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // User has to press enter to return to the menu screen. 
        cin.get();
        gameActive = false;
        MainMenu();

    }

    private:
        bool hasSword;
        bool hasKey;
        int chestChoice;
        bool gameActive = true;
        int foundCoins = 0;
        int heal;
};

class CreditsMenu {
public:
    void display() {
        // Display the credits menu

        system("cls");

        fstream inputFile("CreditsMenu.txt");

        if (!inputFile.is_open()) {

            cout << "Error Loading Game File: ' Room 3 ' " << endl;
        }

        string line;
        while (getline(inputFile, line)) {

            cout << line << endl;
        }

        inputFile.close();

        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // User has to press enter to return to the menu screen. 
        cin.get();
    }
};

int main() {
    MainMenu mainMenu;
    bool quit = false;

    while (!quit) {

        mainMenu.display();
        int MenuChoice;
        cin >> MenuChoice; // Get the user's menu choice

        switch (MenuChoice) {
        case 1: {
            Game game;
            game.start();
            break;
        }
        case 2: {
            CreditsMenu creditsMenu;
            creditsMenu.display();
            break;
        }
        case 3: {

            // Quitting animation (ends the program)
            system("cls");
            cout << " Quitting . . . . " << endl;
            this_thread::sleep_for(std::chrono::milliseconds(1000));
            cout << "         Quitting . . . . " << endl;
            this_thread::sleep_for(std::chrono::milliseconds(1000));
            cout << "                 Quitting . . . . " << endl;
            this_thread::sleep_for(std::chrono::milliseconds(1000));
            cout << "                          Quitting . . . . " << endl;
            this_thread::sleep_for(std::chrono::milliseconds(1000));
            cout << " ------- Thanks for playing! -------- " << endl;
            this_thread::sleep_for(std::chrono::milliseconds(1000));
            quit = true;

            break;
        }
        default: {
            cout << "Invalid choice. Please try again." << endl;
            cout << " " << endl;
            cout << " " << endl;
        }
        }
    }
    return 0;
}
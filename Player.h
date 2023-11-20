#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

class Player {
public:
    Player();

    std::string getName() const;
    void setName(const std::string& newName);

    void addCoins(int amount);
    int getCoins() const;

    void overallCoinAmount() const;

    void takeDamage(int damage);
    int getHealth() const;
    void heal(int amount);
    void handlePlayerDeath();

private:
    std::string name;
    int health;
    int coins;
};

#endif

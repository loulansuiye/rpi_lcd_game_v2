//
// Created by alfar on 20/10/2021.
//

#include "Player.h"
#include <iostream>
Player::Player() {

    Player::health = 5;
    Player::x = 0;
    Player::y = 0;


}

Player::Player(int x, int y) {

    Player::health = 5;
    Player::x = x;
    Player::y = y;


}

Player::~Player() {
}

int Player::getHealth() const {
    return health;
}

int Player::getX() const {


    return Player::x;
}

void Player::setX(int x) {
    Player::x = x;
}

int  Player::getY() const {
    return Player::y;
}

void Player::setY(int y) {
    Player::y = y;
}

void Player::printStats() {
    std::cout << "|--------------|" << std::endl
              << "|Player Stats: |"<< std::endl
              << "|Health: " << getHealth() << "     |"<< std::endl
              << "|X: "<< getX() << "          |"<< std::endl
              << "|Y: " << getY() << "          |" << std::endl
              << "|--------------|" << std::endl;
}

void Player::setHealth(int health) {
    Player::health = health;
}

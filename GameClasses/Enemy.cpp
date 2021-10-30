//
// Created by inkredibleme on 22/10/21.
//

#include "Enemy.h"
#include "cstdlib"

Enemy::Enemy() {

    health = 1;
    x = 15;
    y = (rand() % 2);

}

Enemy::~Enemy() {

}

int Enemy::getHealth() const {
    return health;
}

void Enemy::setHealth(int health) {
    Enemy::health = health;
}

int Enemy::getX() const {
    return x;
}

void Enemy::setX(int x) {
    Enemy::x = x;
}

int Enemy::getY() const {
    return y;
}

void Enemy::setY(int y) {
    Enemy::y = y;
}

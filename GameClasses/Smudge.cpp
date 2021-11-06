//
// Created by inkredibleme on 06/11/21.
//

#include "Smudge.h"

Smudge::~Smudge() {

}

Smudge::Smudge(){

    Smudge::x = 14;
    Smudge::y = 0;

    Smudge::alive = false;

}

int Smudge::getX() const {
    return x;
}

void Smudge::setX(int x) {
    Smudge::x = x;
}

int Smudge::getY() const {
    return y;
}

void Smudge::setY(int y) {
    Smudge::y = y;
}

bool Smudge::isAlive() const {
    return alive;
}

void Smudge::setAlive(bool alive) {
    Smudge::alive = alive;
}

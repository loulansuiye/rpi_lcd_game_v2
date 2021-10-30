//
// Created by inkredibleme on 30/10/21.
//

#include "Item.h"

Item::Item(int x, int y, int type) : x(x), y(y), type(type) {

    Item::x = x;
    Item::y = y;
    Item::type = type;

}

Item::~Item() {

}

int Item::getX() const {
    return x;
}

void Item::setX(int x) {
    Item::x = x;
}

int Item::getY() const {
    return y;
}

void Item::setY(int y) {
    Item::y = y;
}

int Item::getType() const {
    return type;
}

void Item::setType(int type) {
    Item::type = type;
}

//
// Created by inkredibleme on 30/10/21.
//

#include "Item.h"

Item::Item() {
    Item::created = false;
    Item::x = 0;
    Item::y = 0;
    Item::type = 4;
}

Item::Item(int x, int y, int type) : x(x), y(y), type(type) {

    Item::created= true;
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

bool Item::isCreated() const {
    return created;
}

void Item::setCreated(bool created) {
    Item::created = created;
}

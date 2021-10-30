//
// Created by inkredibleme on 30/10/21.
//

#ifndef RPI_LCD_GAME_ITEM_H
#define RPI_LCD_GAME_ITEM_H


class Item {
private:
    int x, y;
    int type; //Boost, Time, Enemy

public:
    Item(int x, int y, int type);
    ~Item();

    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);

    int getType() const;

    void setType(int type);

};




#endif //RPI_LCD_GAME_ITEM_H

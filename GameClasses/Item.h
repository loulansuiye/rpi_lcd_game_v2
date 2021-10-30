//
// Created by inkredibleme on 30/10/21.
//

#ifndef RPI_LCD_GAME_ITEM_H
#define RPI_LCD_GAME_ITEM_H


class Item {
private:
    bool created;
    int x, y;
    int type; //Boost=0, Time=1, Enemy=2

public:
    Item();
    Item(int x, int y, int type);
    ~Item();

    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);

    int getType() const;

    void setType(int type);

    bool isCreated() const;

    void setCreated(bool created);
};




#endif //RPI_LCD_GAME_ITEM_H

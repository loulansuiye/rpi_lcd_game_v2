//
// Created by inkredibleme on 06/11/21.
//

#ifndef RPI_LCD_GAME_SMUDGE_H
#define RPI_LCD_GAME_SMUDGE_H


class Smudge {
private:
    int x, y;
    bool alive;

public:
    Smudge();
    ~Smudge();

    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);

    bool isAlive() const;

    void setAlive(bool alive);


};


#endif //RPI_LCD_GAME_SMUDGE_H

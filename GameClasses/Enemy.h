//
// Created by inkredibleme on 22/10/21.
//

#ifndef RPI_LCD_GAME_ENEMY_H
#define RPI_LCD_GAME_ENEMY_H


class Enemy {
private:
    int health;
    int x, y;

public:
    Enemy();
    ~Enemy();

    int getHealth() const;

    void setHealth(int health);

    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);
};


#endif //RPI_LCD_GAME_ENEMY_H

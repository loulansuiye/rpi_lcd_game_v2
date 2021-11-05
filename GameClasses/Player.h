//
// Created by alfar on 20/10/2021.
//

#ifndef RPI_LCDULTRA_PLAYER_H
#define RPI_LCDULTRA_PLAYER_H


class Player {
private:
    int health;
    int x;
    int y;
public:
    Player();
    Player(int x, int y);
    ~Player();

    void setHealth(int health);

    int getHealth() const;

    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);

    void printStats();
};


#endif //RPI_LCDULTRA_PLAYER_H

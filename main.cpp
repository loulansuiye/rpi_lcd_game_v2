#include <cstdlib>
#include <cstdio>
#include<cstring>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <pcf8574.h>
#include <lcd.h>
#include <ctime>
#include <iostream>
#include <thread>


#include "GameClasses/Player.h"
#include "GameClasses/Item.h"

int pcf8574_address = 0x27;        // PCF8574T:0x27, PCF8574AT:0x3F
#define BASE 64         // BASE any number above 64
//Define the output pins of the PCF8574, which are directly connected to the LCD1602 pin.
#define RS      (BASE+0)
#define RW      (BASE+1)
#define EN      (BASE+2)
#define LED     (BASE+3)
#define D4      (BASE+4)
#define D5      (BASE+5)
#define D6      (BASE+6)
#define D7      (BASE+7)

#define buttonPlayPin 1
#define buttonEndPin 0

#define ITEM_ARRAY_SIZE 100

int lcdhd;// used to handle LCD
Item items[ITEM_ARRAY_SIZE];
int currentItem = 0;
int backTime = 1250;


void printTextToLCD(const char *s);


//mine functions ^-^
void printTextToLCD(const char *s) {

    lcdPosition(lcdhd, 0, 0);
    lcdPrintf(lcdhd, s);
}

void makeCustomCharacters() {
    unsigned char empty[] = {
            0x00,
            0x00,
            0x00,
            0x00,
            0x00,
            0x00,
            0x00,
            0x00
    };

    unsigned char player[] = {
            0x0E,
            0x0A,
            0x0E,
            0x1F,
            0x04,
            0x04,
            0x0A,
            0x0A
    };
    lcdCharDef(lcdhd, 0, empty);
    lcdCharDef(lcdhd, 1, player);
}

void writeCustomCharacter(int pos) {

    lcdPutchar(lcdhd, pos);

}
//-


int detectI2C(int addr) {
    int _fd = wiringPiI2CSetup(addr);
    if (_fd < 0) {
        printf("Error address : 0x%x \n", addr);
        return 0;
    } else {
        if (wiringPiI2CWrite(_fd, 0) < 0) {
            printf("Not found device in address 0x%x \n", addr);
            return 0;
        } else {
            printf("Found device in address 0x%x \n", addr);
            return 1;
        }
    }
}

void drawItems(bool *hasChanged) {

    if (*hasChanged) {


        for (int i = 0; i < currentItem; ++i) {

            if (items[i].isCreated()) {
                lcdPosition(lcdhd, items[i].getX(), items[i].getY());
                switch (items[i].getType()) {
                    case 0: //Boost
                        lcdPuts(lcdhd, ">");
                        break;
                    case 1: //Health
                        lcdPuts(lcdhd, "+");
                        break;
                    case 2: //Enemy
                        lcdPuts(lcdhd, "-");
                        break;

                }
            }

        }
    }

}

void drawPlayer(Player *player, bool *run, bool *hasChanged) {

    if (*hasChanged) {


        int ph = player->getHealth();
        player->printStats();


        lcdClear(lcdhd);

        int phy = 1;

        if(player->getX()<=3 && player->getY()==1){
            phy=0;
        }

        lcdPosition(lcdhd, 0,phy);

        std::string sh = "H:" + std::to_string(ph);

        //const char * psh = "H:" + sh;

        lcdPrintf(lcdhd, sh.c_str());

        /*lcdPosition(lcdhd, player->getX(), 0);
        writeCustomCharacter(0);
        lcdPosition(lcdhd, player->getX() + 1, 0);
        writeCustomCharacter(0);

        lcdPosition(lcdhd, player->getX(), 1);
        writeCustomCharacter(0);
        lcdPosition(lcdhd, player->getX() + 1, 1);
        writeCustomCharacter(0);*/
        lcdPosition(lcdhd, player->getX(), player->getY());

        writeCustomCharacter(1);

        drawItems(hasChanged);

        *hasChanged = false;
    }

    return;
}

void createItem() {

    int *type = new int;
    int *x = new int;
    int *y = new int;

    int randType = rand() % 4;
    int randX = rand() % 10 + 3;
    int randY = rand() % 2;

    *type = randType;
    *x = randX;
    *y = randY;
    bool valid = false;
    if(currentItem == 0){
        valid = true;
    }
    while(!valid) {
        for (int i = 0; i < currentItem; ++i) {

            if (items[i].isCreated()) {
                if ((*x == items[i].getX()) && (*y == items[i].getY())) {

                    valid = false;
                    *x = rand() % 10 + 3;
                    *y = rand() % 2;

                }else{
                    valid = true;
                }
            } else {
                valid = true;
            }
        }
    }


    switch (*type) {
        case 0:
            std::cout << "[Item spawning] Creating Boost" << std::endl;
            break;
        case 1:
            std::cout << "[Item spawning] Creating Time" << std::endl;
            break;
        case 2:
            std::cout << "[Item spawning] Creating Enemy" << std::endl;
            break;
        case 3:
            std::cout << "[Item spawning] Not spawning anything" << std::endl;
            break;
    }

    if (*type < 4) {

        items[currentItem].setX(*x);
        items[currentItem].setY(*y);
        items[currentItem].setType(*type);
        items[currentItem].setCreated(true);


        currentItem++;
    }


    delete type;
    delete x;
    delete y;

    return;
}

void checkForItem(Player * player){

    for (int i = 0; i < currentItem; ++i) {

        if (items[i].isCreated()) {
            if((player->getX() == items[i].getX()) && (player->getY() == items[i].getY())){
                //Player has touched an item.

                switch (items[i].getType()) {

                    case 0: //boost
                        backTime += 500;
                        break;
                    case 1: //health
                        player->setHealth(player->getHealth()+1);
                        break;
                    case 2: //enemy
                        player->setHealth(player->getHealth()-1);
                        break;

                }

                items[i].setCreated(false);


            }
        }
    }
}
void movePlayerBackwards(Player *player, bool *run, bool *hasChanged) {

    while (*run) {

        delay(backTime);

        if (backTime > 200) {
            backTime -= 25;
        }
        std::cout << "Time: " << backTime << std::endl;

        createItem();

        player->setX(player->getX() - 1);
        checkForItem(player);
        if (player->getX() < 0) {
            *run = false;
            break;
        }

        *hasChanged = true;
    }

    return;

}

void drawLoopAsync(Player *player, bool *run, bool *hasChanged) {

    while (*run) {

        if (*hasChanged) {


            drawPlayer(player, run, hasChanged);


        }

    }

    return;

}

void gameLoopAsync(Player *player, bool *run, bool *hasChanged) {
    while (*run) {

        if(player->getHealth() == 0){
            *run = false;
            break;
        }
        if (digitalRead(buttonPlayPin) == LOW) { //button is pressed
            if (player->getY() == 0) {
                player->setY(1);
            } else {
                player->setY(0);
            }


            checkForItem(player);

            *hasChanged = true;
            delay(250);
        }

        if (digitalRead(buttonEndPin) == LOW) { //button is pressed

            if(player->getX()<15){

                player->setX(player->getX() + 1);
            }

            checkForItem(player);

            *hasChanged = true;

            //drawPlayer(player);
            delay(250);
            //printf("End\n");
            //break;
        }

    }
    return;
}

int main() {

    // Set randomizer string based on time
    srand(time(NULL));

    printf("Program is starting ...\n");

    for (int i = 0; i < ITEM_ARRAY_SIZE; ++i) {

        items[i] = Item();

    }

    wiringPiSetup();

    pinMode(buttonPlayPin, INPUT);
    pinMode(buttonEndPin, INPUT);
    pullUpDnControl(buttonPlayPin, PUD_UP);
    pullUpDnControl(buttonEndPin, PUD_UP);

    if (detectI2C(0x27)) {
        pcf8574_address = 0x27;
    } else if (detectI2C(0x3F)) {
        pcf8574_address = 0x3F;
    } else {
        printf("No correct I2C address found, \n"
               "Please use command 'i2cdetect -y 1' to check the I2C address! \n"
               "Program Exit. \n");
        return -1;
    }
    pcf8574Setup(BASE, pcf8574_address);//initialize PCF8574
    for (int i = 0; i < 8; i++) {
        pinMode(BASE + i, OUTPUT);     //set PCF8574 port to output mode
    }
    digitalWrite(LED, HIGH);     //turn on LCD backlight
    digitalWrite(RW, LOW);

    //allow writing to LCD
    lcdhd = lcdInit(2, 16, 4, RS, EN, D4, D5, D6, D7, 0, 0, 0,
                    0);// initialize LCD and return “handle” used to handle LCD
    if (lcdhd == -1) {
        printf("lcdInit failed !");
        return 1;
    }

    makeCustomCharacters();
    lcdClear(lcdhd);
    lcdPosition(lcdhd, 0, 0);
    bool on = true;
    bool *run = &on;
    bool changed = true;
    bool *hasChanged = &changed;

    Player *player = new Player(2, 0);

    printTextToLCD("...");
    delay(500);
    printTextToLCD("Start");
    delay(250);
    lcdPosition(lcdhd, 0, 1);
    lcdPuts(lcdhd, "By Ink");
    delay(1000);
    lcdClear(lcdhd);
    lcdPosition(lcdhd, 0, 0);
    delay(250);

    std::thread gameLoopThread(gameLoopAsync, player, run, hasChanged);

    std::thread drawThread(drawLoopAsync, player, run, hasChanged);

    std::thread backwardsThread(movePlayerBackwards, player, run, hasChanged);


    gameLoopThread.join();
    backwardsThread.join();
    drawThread.join();


    printTextToLCD("End");
    delay(500);
    printTextToLCD("End.");
    delay(500);
    printTextToLCD("End..");
    delay(500);
    printTextToLCD("End...");
    delay(250);
    lcdClear(lcdhd);
    digitalWrite(LED, LOW);


    return 0;
}

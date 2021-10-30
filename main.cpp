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
#include "GameClasses/Enemy.h"

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


int lcdhd;// used to handle LCD
void printTextToLCD(const char *s);


//mine functions ^-^
void printTextToLCD(const char *s){

    lcdPosition(lcdhd,0,0);
    lcdPrintf(lcdhd,s);
}
void makeCustomCharacters(){
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
    lcdCharDef(lcdhd,0,empty);
    lcdCharDef(lcdhd, 1, player);
}

void writeCustomCharacter(int pos){

    lcdPutchar(lcdhd,pos);

}
//-


int detectI2C(int addr){
    int _fd = wiringPiI2CSetup (addr);
    if (_fd < 0){
        printf("Error address : 0x%x \n",addr);
        return 0 ;
    }
    else{
        if(wiringPiI2CWrite(_fd,0) < 0){
            printf("Not found device in address 0x%x \n",addr);
            return 0;
        }
        else{
            printf("Found device in address 0x%x \n",addr);
            return 1 ;
        }
    }
}

void drawPlayer(Player * p){

    p->printStats();

    lcdClear(lcdhd);

    lcdPosition(lcdhd,p->getX() ,0);
    writeCustomCharacter(0);
    lcdPosition(lcdhd,p->getX() +1,0);
    writeCustomCharacter(0);

    lcdPosition(lcdhd,p->getX() ,1);
    writeCustomCharacter(0);
    lcdPosition(lcdhd,p->getX() +1,1);
    writeCustomCharacter(0);
    lcdPosition(lcdhd,p->getX() ,p->getY() );

    writeCustomCharacter(1);

}
void movePlayerBackwards(Player * player, bool * run){

    int time = 2000;
    while (*run){

        delay(time);


        player->setX(player->getX()-1);

        if(player->getX()<0){
            *run = false;
            break;
        }

        drawPlayer(player);
    }

    return;

}

void gameLoopAsync(Player * player, bool * run){
    while (*run) {

        if (digitalRead(buttonPlayPin) == LOW) { //button is pressed
            if (player->getY() ==0){
                player->setY(1);
            }else{
                player->setY(0);
            }
            drawPlayer(player);
            printf("Press\n");
            delay(250);
        }

        if (digitalRead(buttonEndPin) == LOW) { //button is pressed

            player->setX(player->getX()+1);

            drawPlayer(player);
            delay(250);
            //printf("End\n");
            //break;
        }

    }
    return;
}

int main(){

    printf("Program is starting ...\n");

    wiringPiSetup();

    pinMode(buttonPlayPin, INPUT);
    pinMode(buttonEndPin, INPUT);
    pullUpDnControl(buttonPlayPin, PUD_UP);
    pullUpDnControl(buttonEndPin, PUD_UP);

    if(detectI2C(0x27)){
        pcf8574_address = 0x27;
    }else if(detectI2C(0x3F)){
        pcf8574_address = 0x3F;
    }else{
        printf("No correct I2C address found, \n"
               "Please use command 'i2cdetect -y 1' to check the I2C address! \n"
               "Program Exit. \n");
        return -1;
    }
    pcf8574Setup(BASE,pcf8574_address);//initialize PCF8574
    for(int i=0;i<8;i++){
        pinMode(BASE+i,OUTPUT);     //set PCF8574 port to output mode
    }
    digitalWrite(LED,HIGH);     //turn on LCD backlight
    digitalWrite(RW,LOW);

    //allow writing to LCD
    lcdhd = lcdInit(2,16,4,RS,EN,D4,D5,D6,D7,0,0,0,0);// initialize LCD and return “handle” used to handle LCD
    if(lcdhd == -1){
        printf("lcdInit failed !");
        return 1;
    }

    makeCustomCharacters();
    lcdClear(lcdhd);
    lcdPosition(lcdhd,0,0);
    bool on = true;
    bool * run = &on;

    Player * player = new Player();

    printTextToLCD("...");
    delay(500);
    printTextToLCD("Start");
    delay(250);
    lcdPosition(lcdhd,0,1);
    lcdPuts(lcdhd,"By Ink");
    delay(1000);
    lcdClear(lcdhd);
    lcdPosition(lcdhd,0,0);
    drawPlayer(player);
    delay(250);

    std::thread gameLoopThread(gameLoopAsync, player, run);

    std::thread backwardsThread(movePlayerBackwards, player, run);


    gameLoopThread.join();
    backwardsThread.join();



    printTextToLCD("End");
    delay(500);
    printTextToLCD("End.");
    delay(500);
    printTextToLCD("End..");
    delay(500);
    printTextToLCD("End...");
    delay(250);
    lcdClear(lcdhd);
    digitalWrite(LED,LOW);


    return 0;
}

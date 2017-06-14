#ifndef GAME_H
#define GAME_H

#include <QString>
#include <QObject>
#include <ctime>
#include <stdlib.h>
#include <QVector>

#pragma execution_character_set("utf-8")

class Game{
public:
    //游戏装态
    static const int READY = 0;    //准备
    static const int PLAYING = 1;  //游戏中
    static const int PAUSE = 2;    //暂停
    static const int WIN = 3;
    static const int LOST = 4;

    //最大的地图数
    static const int MAX_X=100;
    static const int MAX_Y=100;

    //
    //游戏难度
    static const int EASY=1;     //简单
    static const int MIDDLE=2;   //中等
    static const int HARD=3;     //大师
    Game();
    ~Game();
    QString getDifficult();
    bool isPlaying();
    bool startGame();
    int getScore() {return Game::GameScore;}
    int getLevel() {return Game::GameLevel;}
    int getTip() {return Game::GameTips;}
    int getReset() {return Game::GameReset;}
    int getSize() {return Game::sizeX*Game::sizeY;}
    int getSizeX() {return Game::sizeX;}
    int getSizeY() {return Game::sizeY;}
    int* getMap() {return Game::map;}
    int* getMyMap() {return Game::myMap[0];}
    bool canGetTip();
    bool canGetRandom();
    void random();
    void reset();
    bool isWin();
    void setLose() {Game::GameStatus=Game::LOST;}
    bool Game::canLink(int startX,int startY,int nextX,int nextY);
private:
    int GameDifficult;
    int GameStatus;
    int GameTips;
    int GameScore;
    int GameLevel;
    int GameReset;
    int sizeX;
    int sizeY;
    int map[MAX_X*MAX_Y];
    int myMap[MAX_X][MAX_Y];
    int used[MAX_X+2][MAX_X+2];
    QVector<int>Dir_FirstVertical;
    QVector<int>Dir_NextVertical;
    QVector<int>Dir_FirstLevel;
    QVector<int>Dir_NextLevel;
    QVector<int>Dir;
    void find_left(int posX,int posY);
    void find_right(int posX,int posY);
    void find_top(int posX,int posY);
    void find_buttom(int posX,int posY);
    bool linkOk(int startX,int startY,int nextX,int nextY,int step=0);
};
#endif

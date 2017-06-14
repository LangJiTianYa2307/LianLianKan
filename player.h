#ifndef _PLAYER_H
#define _PLAYER_H

#include <QMediaPlayer>
#include <QUrl>
#include <QString>

class Player{
private:
    QMediaPlayer *player;
public:
    Player();
    Player(QString path);
    ~Player();
    void Start();
    void Restart();
};

#endif

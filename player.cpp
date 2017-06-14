#include "player.h"

Player::Player(QString path)
{

}

Player::Player()
{

}

Player::~Player()
{
}

void Player::Start()
{
    player=new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("C:/Users/Administrator/Documents/LianLianKan/Sounds/backgrand.mp3"));
    player->setVolume(100);
    player->play();
}

void Player::Restart()
{
}

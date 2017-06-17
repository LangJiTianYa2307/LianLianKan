#include "game.h"
#include <QtGlobal>
#include <QDebug>

Game::Game()
{
    GameDifficult=Game::EASY;
    GameStatus=Game::READY;
    GameTips=5;
    GameScore=0;
    GameLevel=1;
    GameReset=3;
    sizeX=4;
    sizeY=4;
    memset(map,0,sizeof(map));
    memset(myMap,0,sizeof(myMap));
    memset(used,0,sizeof(used));
}

Game::~Game()
{

}

QString Game::getDifficult()
{
    if(Game::EASY==GameDifficult)
    {
        return QString(QObject::tr("简单"));
    }
    if(Game::MIDDLE==GameDifficult)
    {
        return QString(QObject::tr("中等"));
    }
    if(Game::HARD==GameDifficult)
    {
        return QString(QObject::tr("困难"));
    }
}

bool Game::isPlaying()
{
    return Game::GameStatus==Game::PLAYING ? true:false;
}

bool Game:: startGame()
{
    if(Game::GameStatus==Game::PLAYING)
        return false;
    Game::GameStatus=Game::PLAYING;
    int save[100*100];
    int j=0;
    for(int i=0;i<Game::sizeX*Game::sizeY;i+=2)
    {
        save[i]=j%25+1;
        save[i+1]=j%25+1;
        ++j;
    }
    srand(time(NULL));
    for(int i=0;i<Game::sizeX*Game::sizeY;i++)
    {
        int x=rand()%(Game::sizeX*Game::sizeY);
        int a=save[i];
        save[i]=save[x];
        save[x]=a;
    }
    for(int i=0;i<Game::sizeX*Game::sizeY;i++)
        Game::map[i]=save[i];
    for(int i=0;i<Game::sizeY;i++)
    {
        for(int j=0;j<Game::sizeX;j++)
        {
            Game::myMap[i][j]=save[i*Game::sizeX+j];
           // qDebug()<<myMap[i][j];
        }
      //  qDebug()<<"EE";
    }
    return true;
}

bool Game::canGetRandom()
{
    if(Game::GameReset>0)
    {
        Game::GameReset--;
        return true;
    }
    return false;
}

bool Game::canGetTip()
{
    if(Game::GameTips>0)
    {
        Game::GameTips--;
        return true;
    }
    return false;
}

void Game::reset()
{
    Game::GameScore=0;
    Game::GameStatus=Game::READY;
    Game::GameTips=5;
    Game::GameReset=3;
}

void Game::random()
{
    int save[Game::MAX_X*Game::MAX_Y];
    int k=0;
    for(int i=0;i<Game::sizeY;i++)
        for(int j=0;j<Game::sizeX;j++)
        {
            if(Game::myMap[i][j]!=0)
                save[k++]=Game::myMap[i][j];
        }
    srand(time(0));
    for(int i=0;i<k;i++)
    {
        int x=rand()%k;
        int temp=save[i];
        save[i]=save[x];
        save[x]=temp;
    }
    for(int i=0;i<Game::sizeY;i++)
    {
        for(int j=0;j<Game::sizeX;j++)
            if(Game::myMap[i][j]!=0)
            {
                Game::myMap[i][j]=save[--k];
               // qDebug()<<Game::myMap[j][i];
            }
    }
}

bool Game::isWin()
{
    for(int i=0;i<Game::sizeX;i++)
        for(int j=0;j<Game::sizeY;j++)
        {
            if(Game::myMap[i][j]!=0)
                return false;
        }
    Game::GameStatus=Game::WIN;
    return true;
}

void Game::find_left(int posX,int posY)
{
    posX-=1;
    if(posX==-1)
    {
        Game::Dir.push_back(posX);
        return;
    }
    if(Game::used[posY+1][posX+1]==0)
    {
        Game::Dir.push_back(posX);
        Game::find_left(posX,posY);
    }
    else
    {
        return;
    }
}

void Game::find_right(int posX,int posY)
{
    posX+=1;
    if(posX==Game::sizeX+1)
    {
        Game::Dir.push_back(posX);
        return;
    }
    if(Game::used[posY+1][posX+1]==0)
    {
        Game::Dir.push_back(posX);
        Game::find_right(posX,posY);
    }
    else
    {
        return;
    }
}

void Game::find_top(int posX,int posY)
{
    posY-=1;
    if(posY==-1)
    {
        Game::Dir.push_back(posY);
        return;
    }
    if(Game::used[posY+1][posX+1]==0)
    {
        Game::Dir.push_back(posY);
        Game::find_top(posX,posY);
    }
    else
    {
        return;
    }
}

void Game::find_buttom(int posX,int posY)
{
    posY+=1;
    if(posY==Game::sizeY+1)
    {
        Game::Dir.push_back(posY);
        return;
    }
    if(Game::used[posY+1][posX+1]==0)
    {
        Game::Dir.push_back(posY);
        Game::find_buttom(posX,posY);
    }
    else
        return;
}

bool Game::canLink(int startX,int startY,int nextX,int nextY)
{
    for(int i=0;i<Game::sizeY;i++)
        for(int j=0;j<Game::sizeX;j++)
            Game::used[i+1][j+1]=Game::myMap[i][j];
//    for(int i=0;i<sizeY+2;i++)
//        for(int j=0;j<sizeX+2;j++)
//            qDebug()<<used[i][j];
    if(Game::myMap[startY][startX]==Game::myMap[nextY][nextX])
    {
        if(Game::linkOk(startX,startY,nextX,nextY,0))
            return true;
        else
        {
            //有拐点的水平方向判断
            Game::find_left(startX,startY);
            Game::find_right(startX,startY);
            Game::Dir_FirstLevel=Game::Dir;
            Game::Dir_FirstLevel.push_back(startX);
//            qDebug()<<"-----------";
//            for(int i=0;i<Dir_FirstLevel.size();i++)
//                qDebug()<<Dir_FirstLevel[i];
//            qDebug()<<"-----------";

            Game::Dir.erase(Dir.begin(),Dir.end());

            Game::find_left(nextX,nextY);
            Game::find_right(nextX,nextY);
            Game::Dir_NextLevel=Game::Dir;

            Game::Dir_NextLevel.push_back(nextX);

//            qDebug()<<"-----------";
//            for(int i=0;i<Dir_NextLevel.size();i++)
//                qDebug()<<Dir_NextLevel[i];
//            qDebug()<<"-----------";

            Game::Dir.erase(Dir.begin(),Dir.end());
            for(int i=0;i<Game::Dir_FirstLevel.size();i++)
                for(int j=0;j<Game::Dir_NextLevel.size();j++)
                    if(Game::Dir_FirstLevel[i]==Game::Dir_NextLevel[j])
                        if(Game::linkOk(Game::Dir_FirstLevel[i],startY,Game::Dir_NextLevel[j],nextY,1))
                        {
                            Game::myMap[startY][startX]=0;
                            Game::myMap[nextY][nextX]=0;
                            Game::Dir_FirstLevel.erase(Dir_FirstLevel.begin(),Dir_FirstLevel.end());
                            Game::Dir_NextLevel.erase(Dir_NextLevel.begin(),Dir_NextLevel.end());
                            return true;
                        }
            //有拐点的垂直方向判断
            Game::find_top(startX,startY);
            Game::find_buttom(startX,startY);
            Game::Dir_FirstVertical=Game::Dir;
            Game::Dir_FirstVertical.push_back(startY);
            qDebug()<<"-----------";
            for(int i=0;i<Dir_FirstVertical.size();i++)
                qDebug()<<Dir_FirstVertical[i];
            qDebug()<<"-----------";


            Game::Dir.erase(Dir.begin(),Dir.end());

            Game::find_top(nextX,nextY);
            Game::find_buttom(nextX,nextY);
            Game::Dir_NextVertical=Game::Dir;
            Game::Dir_NextVertical.push_back(nextY);

            qDebug()<<"-----------";
            for(int i=0;i<Dir_NextVertical.size();i++)
                qDebug()<<Dir_NextVertical[i];
            qDebug()<<"-----------";

            Game::Dir.erase(Dir.begin(),Dir.end());

            for(int i=0;i<Game::Dir_FirstVertical.size();i++)
                for(int j=0;j<Game::Dir_NextVertical.size();j++)
                    if(Game::Dir_FirstVertical[i]==Game::Dir_NextVertical[j])
                        if(Game::linkOk(startX,Dir_FirstVertical[i],nextX,Dir_FirstVertical[j],1))
                        {
                            Game::myMap[startY][startX]=0;
                            Game::myMap[nextY][nextX]=0;
                            Game::Dir_FirstVertical.erase(Dir_FirstVertical.begin(),Dir_FirstVertical.end());
                            Game::Dir_NextVertical.erase(Dir_NextVertical.begin(),Dir_NextVertical.end());
                            return true;
                        }
            return false;
        }

    }
    return false;
}

//判断是否能直连
bool Game::linkOk(int startX,int startY,int nextX,int nextY,int step)
{
    //竖直连
    if(startX==nextX)
    {
        if(startY<nextY)
            if(startY+1==nextY)
            {
                if(step==0)
                {
                    Game::myMap[startY][startX]=0;
                    Game::myMap[nextY][nextX]=0;
                }
                Game::GameScore+=20;
                return true;
            }
            else
                for(int i=startY+1;i<nextY;i++)
                    if(Game::myMap[i][startX]!=0)
                        return false;
                    else
                    {
                        if(step==0)
                        {
                            Game::myMap[startY][startX]=0;
                            Game::myMap[nextY][nextX]=0;
                        }
                        Game::GameScore+=20;
                        return true;
                    }
        else
        {
            if(nextY+1==startY)
            {
                if(step==0)
                {
                    Game::myMap[startY][startX]=0;
                    Game::myMap[nextY][nextX]=0;
                }
                Game::GameScore+=20;
                return true;
            }
            else
                for(int i=nextY+1;i<startY;i++)
                    if(Game::myMap[i][startX]!=0)
                        return false;
                    else
                    {
                        if(step==0)
                        {
                            Game::myMap[startY][startX]=0;
                            Game::myMap[nextY][nextX]=0;
                        }
                        Game::GameScore+=20;
                        return true;
                    }
         }
    }
    //横直连
    if(startY==nextY)
    {
        if(startX<nextX)
            if(startX+1==nextX)
            {
                if(step==0)
                {
                    Game::myMap[startY][startX]=0;
                    Game::myMap[nextY][nextX]=0;
                }
                Game::GameScore+=20;
                return true;
            }
            else
                for(int i=startX+1;i<nextX;i++)
                    if(Game::myMap[startY][i]!=0)
                        return false;
                    else
                    {
                        if(step==0)
                        {
                            Game::myMap[startY][startX]=0;
                            Game::myMap[nextY][nextX]=0;
                        }
                        Game::GameScore+=20;
                        return true;
                    }
        else
        {
            if(nextX+1==startX)
            {
                if(step==0)
                {
                    Game::myMap[startY][startX]=0;
                    Game::myMap[nextY][nextX]=0;
                }
                Game::GameScore+=20;
                return true;
            }
            else
                for(int i=nextX+1;i<startX;i++)
                    if(Game::myMap[startY][i]!=0)
                        return false;
                    else
                    {
                        if(step==0)
                        {
                            Game::myMap[startY][startX]=0;
                            Game::myMap[nextY][nextX]=0;
                        }
                        Game::GameScore+=20;
                        return true;
                    }
        }
    }
    return false;
}


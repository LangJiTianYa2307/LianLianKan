#include "mainwindow.h"
#include "ui_mainwindow.h"
#pragma execution_character_set("utf-8")

#include <QSize>
#include <QString>
#include <QMessageBox>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置窗口大小
    this->resize(QSize(1080,800));
    //播放背景音乐
    player=new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("C:/Users/Administrator/Documents/LianLianKan/Sounds/duoyuandouyaozaiyiqi.mp3"));
    player->setVolume(100);
    player->play();
    //选择音乐
    sel=new QMediaPlayer;
    sel->setMedia(QUrl::fromLocalFile("C:/Users/Administrator/Documents/LianLianKan/Sounds/select.mp3"));
    sel->setVolume(100);
    //消除音乐
    pair=new QMediaPlayer;
    pair->setMedia(QUrl::fromLocalFile("C:/Users/Administrator/Documents/LianLianKan/Sounds/pair.wav"));
    pair->setVolume(100);
    startX=70;
    startY=100;
    size=60;
    MainWindow::flag=false;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete player;
    delete sel;
    delete pair;
    MainWindow::delImage();
}

void MainWindow::on_actionTui_triggered()
{
    exit(0);
}

void MainWindow::on_actionG_triggered()
{
    QMessageBox::information(this, "About", QString(QObject::tr("连连看:\t1.0\n作者:\tJames\n")));
}

void MainWindow::on_actionKaishi_triggered()
{
    ui->lblDifficulty->setText(newGame.getDifficult());
    ui->lblLevel->setText(QString::number(newGame.getLevel()));
    ui->lblReset->setText(QString::number(newGame.getReset()));
    ui->lblScore->setText(QString::number(newGame.getScore()));
    ui->lblTip->setText(QString::number(newGame.getTip()));
    ui->pbrTime->setValue(100);
    if(newGame.isPlaying())
    {
         QMessageBox::information(this, tr("警告"), QString(QObject::tr("游戏正在运行")));
         return;
    }
    MainWindow::delImage();
    MainWindow::flag=false;
    newGame.reset();
    newGame.startGame();
    int x=startX,y=startY;
  //  newGame.random();
    int *map=newGame.getMap();
//    int *mymap=newGame.getMyMap();
//    qDebug()<<mymap[0];
//    qDebug()<<mymap[1];
//    qDebug()<<mymap[2];
//    qDebug()<<mymap[3];
//    qDebug()<<mymap[4];
    for(int i=0;i<newGame.getSize();i++)
    {
        MainWindow::image[i]=new QPushButton(this);
        image[i]->setGeometry(x+size*(i%newGame.getSizeX()),y+size*(i/newGame.getSizeX()),size,size);
        QString ch(":/image/Images/");
        ch = ch + QString::number(map[i]) + QString (".jpg");
        QPixmap pixmap (ch);
        QIcon icon (pixmap);
        image[i]->setIcon(icon);
        image[i]->setIconSize(QSize (size-5, size-5));
        image[i]->show();
        image[i]->setAutoFillBackground(true);
        image[i]->setPalette(QPalette(Qt::lightGray));      //设置选中颜色
        connect(image[i],SIGNAL(clicked()),this,SLOT(image_clicked()));
    }
}

void MainWindow::on_actionChognx_triggered()
{
    MainWindow::delImage();
    MainWindow::flag=false;
    newGame.reset();
    newGame.startGame();
    ui->lblLevel->setText(QString::number(newGame.getLevel()));
    ui->lblReset->setText(QString::number(newGame.getReset()));
    ui->lblScore->setText(QString::number(newGame.getScore()));
    ui->lblTip->setText(QString::number(newGame.getTip()));
    ui->pbrTime->setValue(100);
    int x=startX,y=startY;
    int *map=newGame.getMap();
    for(int i=0;i<newGame.getSize();i++)
    {
        MainWindow::image[i]=new QPushButton(this);
        image[i]->setGeometry(x+size*(i%newGame.getSizeX()),y+size*(i/newGame.getSizeX()),size,size);
        QString ch(":/image/Images/");
        ch = ch + QString::number(map[i]) + QString (".jpg");
        QPixmap pixmap (ch);
        QIcon icon (pixmap);
        image[i]->setIcon(icon);
        image[i]->setIconSize(QSize (size-5, size-5));
        image[i]->show();
        image[i]->setAutoFillBackground(true);
        image[i]->setPalette(QPalette(Qt::lightGray));      //设置选中颜色
        connect(image[i],SIGNAL(clicked()),this,SLOT(image_clicked()));
    }
}

//提示
void MainWindow::on_pushButton_clicked(bool checked)
{
    if(!newGame.isPlaying())
        return;
    if(!newGame.canGetTip())
        return;
    ui->lblTip->setText(QString::number(newGame.getTip()));
}

//重排
void MainWindow::on_pushButton_2_clicked(bool checked)
{
    if(!newGame.isPlaying())
        return;
    if(!newGame.canGetRandom())
        return;
    ui->lblReset->setText(QString::number(newGame.getReset()));
    MainWindow::resetImage();
}

void MainWindow::resetImage()
{
    newGame.random();
    int* map=newGame.getMyMap();
//    qDebug()<<"erererererer";
//    qDebug()<<map[0];
//    qDebug()<<map[1];
//    qDebug()<<map[2];
//    qDebug()<<map[3];
//    qDebug()<<map[4];
    for(int i=0;i<newGame.getSizeY();i++)
    {
        for(int j=0;j<newGame.getSizeX();j++)
        {
            if(map[i*newGame.MAX_Y+j] != 0)
            {
                QString ch(":/image/Images/");
                ch = ch + QString::number(map[i*newGame.MAX_Y+j]) + QString (".jpg");
                QPixmap pixmap (ch);
                QIcon icon (pixmap);
                image[i*newGame.getSizeX()+j]->setIcon(icon);
            }
        }
    }
}

void MainWindow::image_clicked()
{
    QPushButton *imageNext=(QPushButton *)sender();
    imageNext->setPalette(QPalette(Qt::green));
    if(MainWindow::flag)
    {
       if(MainWindow::imageFirst==imageNext)
           return;
       int FirstX=(imageFirst->geometry().x()-MainWindow::startX)/MainWindow::size;
       int FirstY=(imageFirst->geometry().y()-MainWindow::startY)/MainWindow::size;
       int NextX=(imageNext->geometry().x()-MainWindow::startX)/MainWindow::size;
       int NextY=(imageNext->geometry().y()-MainWindow::startY)/MainWindow::size;
       if(newGame.canLink(FirstX,FirstY,NextX,NextY))
       {
            pair->play();
            delete MainWindow::imageFirst;
            delete imageNext;
            MainWindow::imageFirst=NULL;
            imageNext=NULL;
            MainWindow::flag=false;
       }
       else
       {
           sel->play();
           MainWindow::imageFirst->setPalette(QPalette(Qt::lightGray));
           MainWindow::imageFirst=imageNext;
       }
    }
    else
    {
        sel->play();
        MainWindow::flag=true;
        MainWindow::imageFirst=imageNext;
    }
    ui->lblScore->setText(QString::number(newGame.getScore()));
    if(newGame.isWin())
    {
        QMessageBox::information(this,"Win",QString(QObject::tr("分数："))+QString(QString::number(newGame.getScore())));
    }
}

void MainWindow::delImage()
{
    int *map=newGame.getMyMap();
    for(int i=0;i<newGame.getSizeY();i++)
        for(int j=0;j<newGame.getSizeX();j++)
        {
            if(map[i*newGame.MAX_X+j]!=0)
                delete image[i*newGame.getSizeX()+j];
            image[i*newGame.getSizeX()+j]=NULL;
        }
}

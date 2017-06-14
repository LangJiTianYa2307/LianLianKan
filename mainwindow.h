#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QPushButton>
#include <QUrl>
#include "game.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void resetImage();
    void delImage();
private slots:
    void on_actionTui_triggered();
    void on_actionKaishi_triggered();
    void on_actionChognx_triggered();
    void on_actionG_triggered();
    void on_pushButton_clicked(bool checked);
    void on_pushButton_2_clicked(bool checked);
    void image_clicked();
private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QMediaPlayer *sel;
    QMediaPlayer *pair;
    Game newGame;
    QPushButton *image[100*100];
    int startX;
    int startY;
    int size;
    bool flag;
    QPushButton *imageFirst;
};

#endif // MAINWINDOW_H

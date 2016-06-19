#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <iostream>
#include <QLabel>


#include <gameitem.h>
#include <land.h>
#include <bird.h>
#include <birdyellow.h>
#include <birdpink.h>
#include <birdgreen.h>
#include <obstacle.h>
#include <pig.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Bird *birdie[4];
    Pig *pigs[3];
    obstacle *obs[3];

    //b2Vec2 *pigpos[2];

    float pigx[3];
    float pigy[3];

    int count=0;
    int birdnum=0;
    int shotmode=0;
    int countv=0;
    int firstScore;
    int i=0,pignum=3;
    int obsnum=3;
    int judgeobs[3]={0},judgepig[3]={0};
    int countresult=0;

    QGraphicsPixmapItem *result;

    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);
signals:
    // Signal for closing the game
    void quitGame();

private slots:
    void tick();
    // For debug slot
    void QUITSLOT();
    void judgebirdv();
    void judgepigpos();
    void judgeobsv();
    void judgeresult();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer;
    QTimer birdtimer;
    QTimer pigtimer;

};

#endif // MAINWINDOW_H

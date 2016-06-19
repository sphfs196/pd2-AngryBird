#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Enable the event Filter
    qApp->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{
    // Setting the QGraphicsScene
    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());
    ui->graphicsView->setScene(scene);

    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));
    // Setting world's Size
    GameItem::setGlobalSize(QSizeF(32,18),size());
    // Create ground (You can edit here)

    itemList.push_back(new Land(0,19,0,0,QPixmap(":/image/001.jpg").scaled(960,540),world,scene));
    itemList.push_back(new Land(16,1,32,3,QPixmap(":/ground.png").scaled(width(),height()/6.0),world,scene));
    itemList.push_back(new Land(16,20,32,3,QPixmap(":/ground.png").scaled(width(),height()/6.0),world,scene));
    itemList.push_back(new Land(-3,5,3,32,QPixmap(":/ground.png").scaled(height()/6.0,width()),world,scene));
    itemList.push_back(new Land(33,5,3,32,QPixmap(":/ground.png").scaled(height()/6.0,width()),world,scene));

    QGraphicsPixmapItem *shot = new QGraphicsPixmapItem;
    QPixmap shot_img;
    shot_img.load(":/image/Slingshot_2.png");
    shot_img = shot_img.scaled(150,150,Qt::KeepAspectRatio);
    shot->setPixmap(shot_img);
    shot->setPos(150,320);
    scene->addItem(shot);

    QGraphicsPixmapItem *restart = new QGraphicsPixmapItem;
    QPixmap restart_img;
    restart_img.load(":/image/restart.png");
    restart_img = restart_img.scaled(80,80,Qt::KeepAspectRatio);
    restart->setPixmap(restart_img);
    restart->setPos(785,10);
    scene->addItem(restart);

    QGraphicsPixmapItem *exit = new QGraphicsPixmapItem;
    QPixmap exit_img;
    exit_img.load(":/image/exit.png");
    exit_img = exit_img.scaled(150,150,Qt::KeepAspectRatio);
    exit->setPixmap(exit_img);
    exit->setPos(750,110);
    scene->addItem(exit);

    // Create bird (You can edit here)

    birdie[0] = new Bird(6.0f,7.0f,1.0f,&timer,QPixmap(":/bird.png").scaled(width()/32*2,height()/18*2),world,scene);//scaled:設定圖在原本世界的大小!!->
    birdie[1] = new birdyellow(50.0f,900.0f,1.0f,&timer,QPixmap(":/image/black1.png").scaled(width()/32*2,height()/18*2),world,scene);
    birdie[2] = new birdpink(60.0f,900.0f,1.0f,&timer,QPixmap(":/image/pink.png").scaled(width()/32*2,height()/18*2),world,scene);
    birdie[3] = new birdgreen(70.0f,900.0f,1.0f,&timer,QPixmap(":/image/ice.png").scaled(width()/32*2,height()/18*2),world,scene);

    // Setting the Velocity
    //birdie->setLinearVelocity(b2Vec2(0,0));

    //create obstacle
    /*
    obs[0] = new obstacle(17.5f,2.0f,2.0f,6.0f,&timer,QPixmap(":/image/wood.png").scaled(width()/32.0*2,height()/18.0*6),world,scene);
    obs[1] = new obstacle(27.0f,5.0f,2.0f,6.0f,&timer,QPixmap(":/image/wood.png").scaled(2/32.0*960,6/18.0*540),world,scene);
    obs[2] = new obstacle(22.0f,9.0f,16.0f,1.5f,&timer,QPixmap(":/image/thinwood.png").scaled(width()/32.0*16,height()/18.0*1.5),world,scene);
    */
    obs[0] = new obstacle(13.5f,2.0f,2.0f,6.0f,&timer,QPixmap(":/image/wood.png").scaled(width()/32.0*2,height()/18.0*6),world,scene);
    obs[1] = new obstacle(23.0f,5.0f,2.0f,6.0f,&timer,QPixmap(":/image/wood.png").scaled(2/32.0*960,6/18.0*540),world,scene);
    obs[2] = new obstacle(23.0f,7.0f,10.0f,1.5f,&timer,QPixmap(":/image/thinwood.png").scaled(width()/32.0*10,height()/18.0*1.5),world,scene);

    //create enemy
    /*
    pigs[0] = new Pig(27.0f,10.5f,1.0f,&timer,QPixmap(":/image/pig4.png").scaled(width()/32*2,height()/18*2),world,scene);
    pigs[1] = new Pig(21.0f,4.0f,1.0f,&timer,QPixmap(":/image/pig3.png").scaled(width()/32*2,height()/18*2),world,scene);
    */
    pigs[0] = new Pig(23.0f,10.5f,1.0f,&timer,QPixmap(":/image/pig4.png").scaled(width()/32*2,height()/18*2),world,scene);
    pigs[1] = new Pig(17.0f,4.0f,1.0f,&timer,QPixmap(":/image/pig3.png").scaled(width()/32*2,height()/18*2),world,scene);
    pigs[2] = new Pig(25.0f,4.0f,1.0f,&timer,QPixmap(":/image/pig3.png").scaled(width()/32*2,height()/18*2),world,scene);


    //score
    firstScore = 0;
    QString scoreNum;
    scoreNum =QString::number(firstScore);
    ui->label_2->setText(scoreNum);


    // Timer
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    //connect(this,SIGNAL)
    timer.start(100/6);

    //judge bird's v
    connect(&birdtimer,SIGNAL(timeout()),this,SLOT(judgebirdv()));
    birdtimer.start(10);

    //get the origin pos of pigs-->if != origin pos -->judge to delete or not
    /*
    pigpos[0]=b2Vec2(pigs[0]->g_body->GetPosition().x,pigs[1]->g_body->GetPosition().y);
    pigpos[1]=b2Vec2(pigs[1]->g_body->GetPosition().x,pigs[1]->g_body->GetPosition().y);
    */

    for(i=0;i<pignum;++i)
    {
        pigx[i]=float(pigs[i]->g_body->GetPosition().x);
        pigy[i]=float(pigs[i]->g_body->GetPosition().y);
    }

    connect(&pigtimer,SIGNAL(timeout()),this,SLOT(judgepigpos()));
    connect(&pigtimer,SIGNAL(timeout()),this,SLOT(judgeobsv()));    connect(&pigtimer,SIGNAL(timeout()),this,SLOT(judgeresult()));

    pigtimer.start(10);
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
    QPointF mousepos = mouseEvent->pos();

    if(event->type() == QEvent::MouseButtonPress)
    {
        if(float((mousepos.x())*32/960) >= 26.0 && float((mousepos.x())*32/960) <= 29.0)
        {
            if(float(18.0-(mousepos.y())*18/540) >= 15.0 && float(18.0-(mousepos.y())*18/540) <= 18.0)
            {
                firstScore = 0;
                QString scoreNum;
                scoreNum =QString::number(firstScore);
                ui->label_2->setText(scoreNum);

                count=0;
                birdnum=0;
                shotmode=0;
                countv=0;
                countresult=0;
                scene->removeItem(result);

                for(i=0;i<3;i++)
                {
                    judgeobs[i]=0;
                    judgepig[i]=0;
                }

                //put the birds back

                delete birdie[0];
                delete birdie[1];
                delete birdie[2];
                delete birdie[3];

                birdie[0] = new Bird(6.0f,7.0f,1.0f,&timer,QPixmap(":/bird.png").scaled(width()/32*2,height()/18*2),world,scene);//scaled:設定圖在原本世界的大小!!->
                birdie[1] = new birdyellow(50.0f,900.0f,1.0f,&timer,QPixmap(":/image/black1.png").scaled(width()/32*2,height()/18*2),world,scene);
                birdie[2] = new birdpink(60.0f,900.0f,1.0f,&timer,QPixmap(":/image/pink.png").scaled(width()/32*2,height()/18*2),world,scene);
                birdie[3] = new birdgreen(70.0f,900.0f,1.0f,&timer,QPixmap(":/image/ice.png").scaled(width()/32*2,height()/18*2),world,scene);


                //put the obs back
                delete obs[0];
                delete obs[1];
                delete obs[2];

                obs[0] = new obstacle(13.5f,2.0f,2.0f,6.0f,&timer,QPixmap(":/image/wood.png").scaled(width()/32.0*2,height()/18.0*6),world,scene);
                obs[1] = new obstacle(23.0f,5.0f,2.0f,6.0f,&timer,QPixmap(":/image/wood.png").scaled(2/32.0*960,6/18.0*540),world,scene);
                obs[2] = new obstacle(23.0f,7.0f,10.0f,1.5f,&timer,QPixmap(":/image/thinwood.png").scaled(width()/32.0*10,height()/18.0*1.5),world,scene);

                //put the pigs back
                delete pigs[0];
                delete pigs[1];
                delete pigs[2];

                pigs[0] = new Pig(23.0f,10.5f,1.0f,&timer,QPixmap(":/image/pig4.png").scaled(width()/32*2,height()/18*2),world,scene);
                pigs[1] = new Pig(17.0f,4.0f,1.0f,&timer,QPixmap(":/image/pig3.png").scaled(width()/32*2,height()/18*2),world,scene);
                pigs[2] = new Pig(25.0f,4.0f,1.0f,&timer,QPixmap(":/image/pig3.png").scaled(width()/32*2,height()/18*2),world,scene);

                std::cout << "restart !" << std::endl ;
            }
        }

        if(float((mousepos.x())*32/960) >= 25.0 && float((mousepos.x())*32/960) <= 30.0)
        {
            if(float(18.0-(mousepos.y())*18/540) >= 12.5 && float(18.0-(mousepos.y())*18/540) <= 14.0)
            {
                close();
                emit quitGame();
                std::cout << "exit !" << std::endl ;
            }
        }


        if(shotmode==1)
        {
            birdie[birdnum]->ability();
        }

        if(count==0)
        {
            if(float(mousepos.x()*32/960) < 7.0)
            {
                //world->SetGravity(b2Vec2(0.0f,0.0f));
                count=1;
                std::cout << "Press !" << std::endl ;
            }
        }
        return true;
    }
    if(event->type() == QEvent::MouseMove)
    {
        if(count==1)
        {
            birdie[birdnum]->g_body->SetTransform(b2Vec2(float((mousepos.x())*32/960),float(18.0-(mousepos.y())*18/540)),birdie[birdnum]->g_body->GetAngle());
            std::cout << "Move !" << std::endl ;
            //std::cout << (18.0-(QCursor::pos().y()-(540/2))*18/540) << std::endl ;
            std::cout << float((mousepos.x())*32/960) << std::endl ;

        }
        //std::cout << float(18.0-(mousepos.y())*18/540) << std::endl ;
            return true;
    }
    if(event->type() == QEvent::MouseButtonRelease)
    {
        if(shotmode==0 && count==1)
        {
            count=2;
            shotmode=1;
            birdie[birdnum]->bodydef.awake = true;
            //world->SetGravity(b2Vec2(0.0f,-9.8f));
            if(float((mousepos.x())*32/960-3) < 5)
            {
                birdie[birdnum]->setLinearVelocity(b2Vec2( 4*(6.0 - float((mousepos.x())*32/960)), 4*(7.0 - float(18.0-(mousepos.y())*18/540))));
            }

            //判斷當運動狀態為休眠-->清掉上一隻,birdnum++;
            std::cout << "Release !" << std::endl ;
            //std::cout << mousepos.x() << std::endl ;
        }
        return true;
    }
    return false;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    emit quitGame();
}

void MainWindow::tick()
{
    world->Step(1.0/60.0,6,2);
    scene->update();
}

void MainWindow::QUITSLOT()
{
    // For debug
    std::cout << "Quit Game Signal receive !" << std::endl ;
}

void MainWindow::judgebirdv()
{
    //std::cout << shotmode << std::endl ;
    if(shotmode==1)
    {
        if(abs(float(birdie[birdnum]->g_body->GetLinearVelocity().x)) < 0.000001 && abs(float(birdie[birdnum]->g_body->GetLinearVelocity().y)) < 0.000001)
        {
            countv++;
            if(countv==200)
            {
                countv=0;
                count=0;
                shotmode=0;
                if(birdnum<3)
                {
                    birdnum++;
                    birdie[birdnum]->g_body->SetTransform(b2Vec2(6.0f,7.0f),birdie[birdnum]->g_body->GetAngle());
                    birdie[birdnum-1]->g_body->SetTransform(b2Vec2(15.0f,40.0f),birdie[birdnum-1]->g_body->GetAngle());

                    //刪掉上一隻鳥鳥!!
                }
            }
        }
    }
}

void MainWindow::judgepigpos()
{
    if(shotmode==1)
    {
        for(i=0;i<pignum;++i)
        {
            float px=float(pigs[i]->g_body->GetPosition().x);
            float py=float(pigs[i]->g_body->GetPosition().y);
            float pvx=float(pigs[i]->g_body->GetLinearVelocity().x);
            float pvy=float(pigs[i]->g_body->GetLinearVelocity().y);

            if((px != pigx[i] || py != pigy[i]) && judgepig[i] == 0)
            {
                if((sqrt((px-pigx[i])*(px-pigx[i])+(py-pigy[i])*(py-pigy[i])) > 2.0) && (abs(pvx) > 3.0 || abs(pvy) > 3.0))
                {
                    judgepig[i]++;

                    pigs[i]->g_body->SetTransform(b2Vec2(15.0f,40.0f),pigs[i]->g_body->GetAngle());
                    firstScore=firstScore+1000;
                    QString scoreNum;
                    scoreNum= scoreNum + QString::number(firstScore);
                    ui->label_2->setText(scoreNum);
                    std::cout << "pigs bye !" << std::endl ;

                    //std::cout << "firstscore="<<firstScore << std::endl ;
                }
            }
        }
    }
}

void MainWindow::judgeobsv()
{
    if(shotmode==1)
    {
        for(i=0;i<obsnum;++i)
        {
            float obsvx=float(obs[i]->g_body->GetLinearVelocity().x);
            float obsvy=float(obs[i]->g_body->GetLinearVelocity().y);
            if((abs(obsvx) > 3.0 || abs(obsvy) > 3.0) && judgeobs[i] == 0)
            {
                obs[i]->g_body->SetTransform(b2Vec2(15.0f,40.0f),obs[i]->g_body->GetAngle());

                judgeobs[i]=1;
                firstScore=firstScore+500;
                QString scoreNum;
                scoreNum= scoreNum + QString::number(firstScore);
                ui->label_2->setText(scoreNum);
                std::cout << "obs bye !" << std::endl ;
            }
        }
    }
}

void MainWindow::judgeresult()
{
    if(birdnum==3 && shotmode==1)
    {
        if(float(birdie[3]->g_body->GetLinearVelocity().x) < 0.000001 && float(birdie[3]->g_body->GetLinearVelocity().y) < 0.000001)
        {
            countresult++;
            if(countresult==10)
            {
                std::cout << "countresult = "<< countresult << std::endl ;

                if(firstScore < 1000)
                {
                    result = new QGraphicsPixmapItem;
                    QPixmap result_img;
                    result_img.load(":/image/fail.png");
                    result_img = result_img.scaled(600,600,Qt::KeepAspectRatio);
                    result->setPixmap(result_img);
                    result->setPos(120,70);
                    scene->addItem(result);
                }
                else if(firstScore > 1000)
                {
                    result = new QGraphicsPixmapItem;
                    QPixmap result_img;
                    result_img.load(":/image/win.png");
                    result_img = result_img.scaled(600,600,Qt::KeepAspectRatio);
                    result->setPixmap(result_img);
                    result->setPos(120,70);
                    scene->addItem(result);
                }
                else if(firstScore == 1000)
                {
                    result = new QGraphicsPixmapItem;
                    QPixmap result_img;
                    result_img.load(":/image/win.png");
                    result_img = result_img.scaled(600,600,Qt::KeepAspectRatio);
                    result->setPixmap(result_img);
                    result->setPos(120,70);
                    scene->addItem(result);
                }

                //disconnect(&pigtimer,SIGNAL(timeout()),this,SLOT(judgeresult()));
                //std::cout << "birdnum = "<< firstScore << std::endl ;
            }
        }

    }
}


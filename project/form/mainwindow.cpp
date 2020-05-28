#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"
#include "dronewindow.h"
#include "trajectoryWindow.h"
#include "form/missionwindow.h"
#include "include/SerializableCollection.h"
#include <windows.h>
#include <iostream>
#include <qdebug.h>
#include <QFileInfo>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);

    myDrones = new SerializableCollection<Drone>("drones.json","drones");
    myDrones->load();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::setUser(User *u)
{
	_user = u;
}


void MainWindow::on_btnDroneWindow_clicked()
{
    DroneWindow *dW = new DroneWindow(myDrones,_user);
    //dW->setUser(_user);
	dW->show();
    //this->close();
}

void MainWindow::on_btn_TrajectoryWindow_clicked()
{

	MissionProcess *mp = new MissionProcess();
    mp->setStartPoint(Point( 45.75, 4.91, 000)); //Paris -> Lyon
    mp->setEndPoint(Point(48.8566,2.46 , 500));
    mp->setAltitude(1000.0);
    //DiscreteMap *dm = new DiscreteMap(*mp);
    //MapInfo *map = new MapInfo(mp->getStartPoint(),mp->getEndPoint());
    //dm->setMap(map);
    //map->setDefaultAltitude(1000);

    SerializableCollection<Drone> myDrones("drones.json","drones");
    myDrones.load();
    mp->setActiveDrone(myDrones.getMap()->first());
    //qDebug() << myDrones.getMap()->first()->toQString();

    mp->activateTrajectoryInput();

    TrajectoryWindow *tW = new TrajectoryWindow(*mp->getMap());
    tW->show();
    //this->close();
}

void MainWindow::on_btnMissionWindow_clicked()
{
    missionWindow *mW = new missionWindow();
    mW->show();
    //this->close();
}


void MainWindow::on_pushButton_clicked()
{
//    QString quoteEscaped = "\"";
//    qDebug() << quoteEscaped;
//    Point start = Point(ui->lineEdit_lati->text().toDouble(), ui->lineEdit_longi->text().toDouble(),0.0);
//    Point end = Point(ui->lineEdit_lati_2->text().toDouble(), ui->lineEdit_longi_2->text().toDouble(),0.0);
//    double dist = Point::computeDistance(start, end);
//    qDebug() << "distance" << dist;
//    dist = MapInfo::GetBestZoomLevel(dist*2.0);
//    qDebug() << "zoom" << dist;
//    QString param = quoteEscaped + ui->lineEdit_lati->text() + quoteEscaped + " " + quoteEscaped + ui->lineEdit_longi->text() + quoteEscaped + " " + quoteEscaped + QString::number(dist) + quoteEscaped ;
//    QByteArray ba = param.toLocal8Bit();
//    const char *c_str2 = ba.data();
//    std::cout << param.toStdString();
//    //qDebug() << "param" << param;
//    //ShellExecuteA(NULL,"open","D:\\dev\\selenium\\test build\\roboto.jar",c_str2,0,SW_NORMAL);
//    ShellExecuteA(NULL,"open","roboto.jar",c_str2,0,SW_NORMAL);
}

void MainWindow::on_pushButton_traj_clicked()
{
//    double altitude = 1000.0;

//    Point start = Point(ui->lineEdit_lati->text().toDouble(), ui->lineEdit_longi->text().toDouble(),0.0);
//    Point end = Point(ui->lineEdit_lati_2->text().toDouble(), ui->lineEdit_longi_2->text().toDouble(),0.0);
//    double distance = Point::computeDistance(start, end);

//    double zoomLevel = distance;
//    QDir directory = QDir();
//    QStringList images = directory.entryList(QStringList() << "*.png" << "*.png",QDir::Files);
//    QString fileNameImg = "";
//    foreach(QString filename, images) {
//        fileNameImg=filename;
//        zoomLevel = filename.split(".")[0].toDouble();
//    }
//    distance = zoomLevel;
//    qDebug() << "ZOOM= " << zoomLevel;
//    //distance = 3845740; url not corrected

//    Point pLeft = start.Destination(270,distance);
//    Point pRight = start.Destination(90,distance);
//    Point pBottom = start.Destination(180,distance/2.0);

//    qDebug() << "start" << start.ToQString();
//    qDebug() << "end" << end.ToQString();
//    qDebug() << "left" << pLeft.ToQString();
//    qDebug() << "right" << pRight.ToQString();
//    qDebug() << "bottom" << pBottom.ToQString();


//    MapInfo *map = new MapInfo(start,end);//new MapInfo(pLeft.GetLongitude(),pRight.GetLongitude(),pBottom.GetLatitude(),altitude,fileNameImg);
//    qDebug() << map->ToQString();
//    MissionProcess *mp = new MissionProcess();
//    mp->setStartPoint(start); //Paris -> Lyon
//    mp->setEndPoint(end);

//    DiscreteMap *dm = new DiscreteMap(*mp);
//    dm->setMap(map);
//    map->setDefaultAltitude(1000);

//    dm->addPoint(pBottom);
//    dm->addPoint(pLeft);
//    dm->addPoint(pRight);

//    SerializableCollection<Drone> myDrones("drones.json","drones");
//    myDrones.load();
//    mp->setActiveDrone(myDrones.getMap()->first());
//    //qDebug() << myDrones.getMap()->first()->toQString();

//    double km = (40000.0/pow(2.0,09.0)) * 2.0;
//    qDebug() << "km" << km;

//    TrajectoryWindow *tW = new TrajectoryWindow(*dm);

//    qDebug() << "start" << start.ToQString();
//    qDebug() << "end" << end.ToQString();
//    qDebug() << "left" << pLeft.ToQString();
//    qDebug() << "right" << pRight.ToQString();
//    qDebug() << "bottom" << pBottom.ToQString();

//    tW->show();


}

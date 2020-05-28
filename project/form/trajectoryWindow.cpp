#include "trajectoryWindow.h"
#include "ui_trajectoryWindow.h"


#include <QDebug>
#include <QStyle>
#include <QDesktopWidget>
#include <QPushButton>
#include <QDir>



TrajectoryWindow::TrajectoryWindow(DiscreteMap & dm,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TrajectoryWindow)
{

    ui->setupUi(this);

    this->setWindowState(Qt::WindowMaximized);
    //setContentsMargins(0,0,0,0);

    _drawer = new drawer(dm,this);
    //qDebug() << _drawer->pos();
    MapInfo* map = dm.getMap();

    QPoint currentPos = QPoint(0,dm.getMap()->pixmap().height()+20);
    int standardWidth = 50;
    int standardOffset = 10;

    //first line
//    CreateLabel("Left and right longitude", currentPos,standardWidth);
//    currentPos.setX(currentPos.x() + standardWidth + standardOffset);
//    CreateLabel(QString::number(map->longitudeLeft()), currentPos,standardWidth);
//    currentPos.setX(currentPos.x() + standardWidth + standardOffset);
//    CreateLabel(QString::number(map->longitudeRight()), currentPos,standardWidth);
//    currentPos.setX(currentPos.x() + standardWidth + standardOffset);
//    CreateLabel("Latitude bottom", currentPos,standardWidth);
//    currentPos.setX(currentPos.x() + standardWidth + standardOffset);
//    CreateLabel(QString::number(map->latitudeBottom()), currentPos,standardWidth);
//    currentPos.setX(currentPos.x() + standardWidth + standardOffset);
//    CreateLabel("Altitude default", currentPos,standardWidth + 30);
//    currentPos.setX(currentPos.x() + standardWidth + standardOffset + 30);
//    CreateLabel(QString::number(map->defaultAltitude()), currentPos,standardWidth);

    //second line
//    currentPos.setY(currentPos.y()+50);
//    currentPos.setX(0);
    CreateLabel("Detail", currentPos,standardWidth);
    currentPos.setX(currentPos.x() + standardWidth + standardOffset);
    _posX = new QLabel(this);
    _posX->setText("0");
    _posX->setFixedWidth(standardWidth);
    _posX->move(currentPos);
    currentPos.setX(currentPos.x() + standardWidth + standardOffset);
    _posY = new QLabel(this);
    _posY->setText("0");
    _posY->setFixedWidth(standardWidth);
    _posY->move(currentPos);
    currentPos.setX(currentPos.x() + standardWidth + standardOffset);

    _posZ = new QLineEdit(this);
    _posZ->setText("0");
    _posZ->setMaximumWidth(standardWidth);
    _posZ->move(currentPos);
    currentPos.setX(currentPos.x() + standardWidth + standardOffset);

    _fuelUse = new QLabel(this);
    _fuelUse->setText("0");
    _fuelUse->setFixedWidth(standardWidth);
    _fuelUse->move(currentPos);
    currentPos.setX(currentPos.x() + standardWidth + standardOffset);

    _time = new QLabel(this);
    _time->setText("0");
    _time->setFixedWidth(standardWidth);
    _time->move(currentPos);
    currentPos.setX(currentPos.x() + standardWidth + standardOffset);

    _angle = new QLabel(this);
    _angle->setText("0");
    _angle->setFixedWidth(standardWidth);
    _angle->move(currentPos);
    currentPos.setX(currentPos.x() + standardWidth + standardOffset);

    connect(_drawer,SIGNAL(signalPointSelected(double, double, double, double, double, double)),this,SLOT(OnSelectPoint(double, double, double, double, double, double)));

    QPushButton * validatePoint = new QPushButton("Change",this);
    validatePoint->move(currentPos);

    currentPos.setX(currentPos.x() + standardWidth + standardOffset);

    connect(validatePoint,SIGNAL(clicked()), this,SLOT(SendSignalZChanged()));
    connect(this,SIGNAL(signalZChanged(double)), _drawer,SLOT(OnZChanged(double)));
}

TrajectoryWindow::~TrajectoryWindow()
{
    delete ui;
    delete _drawer;
}

void TrajectoryWindow::OnSelectPoint(double x, double y, double z, double fuel, double time, double angle)
{
    _posX->setText(QString::number(x));
    _posY->setText(QString::number(y));
    _posZ->setText(QString::number(z));
    _fuelUse->setText(QString::number(fuel));
    _time->setText(QString::number(time));
    _angle->setText(QString::number(angle));
}

void TrajectoryWindow::CreateLabel(QString text, QPoint pos, int width)
{
    QLabel * label = new QLabel(this);
    label->setText(text);
    label->setFixedWidth(width);
    label->move(pos);
}

void TrajectoryWindow::SendSignalZChanged()
{
    bool isNumber = false;
    _posZ->text().toDouble(&isNumber);
    if (isNumber)
        emit signalZChanged(_posZ->text().toDouble());
}

void TrajectoryWindow::closeEvent( QCloseEvent* event )
{
    QDir directory = QDir();
    QStringList images = directory.entryList(QStringList() << "*.png" ,QDir::Files);
    QString fileNameImg = "";
    foreach(QString filename, images) {
        QFile(filename).remove();
    }
}

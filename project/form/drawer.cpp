#include "drawer.h"
#include "ui_drawer.h"

#include <QMenu>
#include <QPainter>
#include <QLabel>
#include <QDebug>
#include <QInputDialog>
#include <QMouseEvent>
#include <QDrag>
#include <QDebug>
#include <QMimeData>
#include <QMessageBox>
#include <QThread>
#include <QDir>

drawer::drawer(DiscreteMap & dMap,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::drawer),
    _dMap(dMap)
{
    ui->setupUi(this);
    this->setAcceptDrops(true);


    _watcher.addPath(QDir::currentPath());

    //QObject::connect(&watcher, SIGNAL(fileChanged(QString)), this, SLOT(IsLoaded(QString)));
    QObject::connect(&_watcher, SIGNAL(directoryChanged(QString)), this, SLOT(IsLoaded(QString)));

    //this->layout()->setSpacing(0);

    //setContentsMargins(0,0,0,0);

    this->move(0,0);

    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);


    this->setBackgroundRole(QPalette::Dark);

    this->setMinimumWidth(_dMap.getMap()->pixmap().width());
    this->setMinimumHeight(_dMap.getMap()->pixmap().height());
    AddControls();
}

drawer::~drawer()
{
    delete ui;
}



void drawer::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen(Qt::red, 2);
    painter.setPen(pen);


    //painter.drawPixmap(0, 0, _dMap.getMap()->pixmap());
    _dMap.Draw(painter,pen);

    //painter.drawLine(0,0,800,800);
    //drawLine(painter,pen);

}


void drawer::ShowContextMenu(const QPoint & pos)
{
    _lastAddedPoint = pos;
    QMenu contexMenu("Menu point",this);

    QAction addPoint("add point", this );
    if(_dMap.CheckPointAllowed(pos))
    {
        contexMenu.addAction(&addPoint);
        connect(&addPoint,SIGNAL(triggered()),this,SLOT(AddPoint()));
    }
    QAction deletePoint("delete point", this);
    if(_lastSelectedIndex != 0 && _lastSelectedIndex != _dMap.GetPointCount()-1)
    {
        contexMenu.addAction(&deletePoint);
        connect(&deletePoint,SIGNAL(triggered()),this,SLOT(DeletePoint()));
    }

    QAction exportTrajectory("export trajectory", this );
    QAction verify("verify trajectory", this );
    if(_dMap.IsTrajectoryCalculated() && _dMap.IsTrajectoryVerified() == TRAJECTORY_ERROR::NONE)
    {
        contexMenu.addAction(&exportTrajectory);
        connect(&exportTrajectory,SIGNAL(triggered()),this,SLOT(ExportTrajectory()));
    }
    else {
        contexMenu.addAction(&verify);
        connect(&verify,SIGNAL(triggered()),this,SLOT(VerifyTrajectory()));
    }

    contexMenu.exec(mapToGlobal(pos));//;+PointUi::_offsetToWholeWindow));
}

void drawer::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->source() == this) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        event->acceptProposedAction();
    }
    //qDebug() << "drag enter";
}

void drawer::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->source() == this) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        event->acceptProposedAction();
    }
    QPoint dropPos = event->pos();
    Point worldPos = _dMap.getMap()->GetWorldPos(dropPos);
    worldPos.SetAltitude(_dMap.getPoint(_lastSelectedIndex).GetAltitude());
    emit signalPointSelected(worldPos.GetLatitude(),worldPos.GetLongitude(),worldPos.GetAltitude(),0.0,0.0,0.0);
    //qDebug() << "drag move";
}

void drawer::dropEvent(QDropEvent *event)
{
    if (event->source() == this) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        event->acceptProposedAction();
    }
    if(! _dMap.CheckPointAllowed(event->pos()))
    {
        event->ignore();
        return;
    }
    QPoint dropPos = event->pos();
    Point worldPos = _dMap.getMap()->GetWorldPos(dropPos);
    worldPos.SetAltitude(_dMap.getPoint(_lastSelectedIndex).GetAltitude());
    _dMap.modPoint(_lastSelectedIndex,worldPos);
    AddControls();
    //qDebug() << "drop event";
}

void drawer::on_drawer_customContextMenuRequested(const QPoint &pos)
{
    ShowContextMenu(pos);
}

void drawer::SendSignalPointSelected(double x, double y, double z, double fuel, double time, double angle)
{
    emit signalPointSelected(x,y,z,fuel,time,angle);
}

void drawer::mousePressEvent(QMouseEvent *event)
{
    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if (!child)
    {
        return;
    }
    //selection detail
    unsigned int previousSelected = _lastSelectedIndex;


    _lastSelectedIndex = child->text().toUInt();
    ControlPoint cp = _dMap.getCPoint(_lastSelectedIndex);
    SendSignalPointSelected(cp.GetLatitude(),cp.GetLongitude(), cp.GetAltitude(), cp.GetFuelUse(), cp.GetTimeToReach(), cp.GetTurnAngle());

    if(_lastSelectedIndex == 0 || _lastSelectedIndex == _dMap.GetPointCount()-1)
        return;
    if(_lastSelectedIndex != previousSelected)
    {
        qDebug() << "blocked";
        return;
    }
    qDebug() << "pass";
    //    //drag and drop

    QMimeData *mimeData = new QMimeData;

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->exec();

}

void drawer::AddControls()
{
    //clear existing controls
    QList<QLabel*> list = this->findChildren<QLabel*>();
    for(unsigned int i = 0; i < list.size();i++)
        delete list[i];

    _dMap.AddControls(this);

    this->update();

}

void drawer::AddPoint()
{
    _lastSelectedIndex = _dMap.addPoint(_dMap.getMap()->GetWorldPos(_lastAddedPoint));
    ControlPoint cp = _dMap.getCPoint(_lastSelectedIndex);
    SendSignalPointSelected(cp.GetLatitude(),cp.GetLongitude(), cp.GetAltitude(), cp.GetFuelUse(), cp.GetTimeToReach(), cp.GetTurnAngle());
    AddControls();
}

void drawer::DeletePoint()
{
    if(_lastSelectedIndex != 0 && _lastSelectedIndex != _dMap.GetPointCount()-1)
    {
        _dMap.deletePoint(_lastSelectedIndex);
        _lastSelectedIndex = _lastSelectedIndex-1;
        AddControls();
    }
}

void drawer::ExportTrajectory()
{
    bool ok = false;
    double step = QInputDialog::getDouble(this,"step","step",10,0,10000.0,2,&ok);
    if(ok)
        _dMap.exportTrajectory(step);
}

void drawer::VerifyTrajectory()
{
    _dMap.verifyTrajectory();

    QMessageBox msgBox;
    switch (_dMap.IsTrajectoryVerified()) {
        case TRAJECTORY_ERROR::NONE:
            msgBox.setText("Trajectory is ok.");
        break;
        case TRAJECTORY_ERROR::NOT_ENOUGH_AUTONOMY:
            msgBox.setText("Not enough autonomy.");
        break;
        case TRAJECTORY_ERROR::NOT_ENOUGH_FUEL:
            msgBox.setText("Not enough range.");
        break;
        case TRAJECTORY_ERROR::TURN_TOO_STEEP:
            msgBox.setText("Turn too steep.");
        break;
        case TRAJECTORY_ERROR::UKNOWN:
            msgBox.setText("Trajectory uknown error.");
        break;
    }

    msgBox.exec();
}

void drawer::OnZChanged(double z)
{
    Point currentSelected = _dMap.getPoint(_lastSelectedIndex);
    currentSelected.SetAltitude(z);
    _dMap.modPoint(_lastSelectedIndex, currentSelected);
}

void drawer::IsLoaded(QString fileName)
{
    QThread::sleep(2);

    _dMap.UpdateWithLastImage();

    AddControls();
}

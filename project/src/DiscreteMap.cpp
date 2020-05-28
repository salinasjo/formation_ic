#include "include/DiscreteMap.h"
#include <QLabel>
#include <iostream>

using namespace std;


//DiscreteMap::DiscreteMap( MissionProcess & mp):_path(mp.getStartPoint(),mp.getEndPoint()),_missionInfo(mp)
//{
//    _map = new MapInfo(mp.getStartPoint(),mp.getEndPoint());
//    _map->setDefaultAltitude(mp.getAltitude());
//}
DiscreteMap::DiscreteMap(const Point & start, const  Point & end, const Drone & drone, double altitude):_path(start,end)
{
    _start = start;
    _end  = end;
    _drone = drone;
    _map = new MapInfo(start,end);
    _map->setDefaultAltitude(altitude);
}

DiscreteMap::~DiscreteMap()
{
    //cout  << endl << "Destruction Discrete map" << endl;
}

void DiscreteMap::UpdateWithLastImage()
{
    _map->UpdateWithImage(_start);
}


unsigned int DiscreteMap::addPoint(Point p,ControlPointType cpt){
//    if( (this->isPointAllowedZone()) && (this->isPointAllowedAngle()) && (this->isPointAllowedRanged()) )
//    {}
    return _path.AddNextPoint(p,cpt);
}

void DiscreteMap::modPoint(unsigned int index,Point p){
    if(index >= _path.Count())
    {
        FileDump::WriteLine("index not found in trajectory " + toString());
        index = 0;
    }
    _path.ModifyPoint(index).Set(p);
}

Point DiscreteMap::getPoint(unsigned int index) const
{
    if(index >= _path.Count())
    {
        FileDump::WriteLine("index not found in trajectory " + toString());
        index = 0;
    }
    return _path.GetPointInfo(index);
}

ControlPoint DiscreteMap::getCPoint(unsigned int index) const
{
    if(index >= _path.Count())
    {
        FileDump::WriteLine("index not found in trajectory " + toString());
        index = 0;
    }
    return _path.GetPointInfo(index);
}

void DiscreteMap::deletePoint(unsigned int index){
    if(index >= _path.Count())
    {
        FileDump::WriteLine("index not found in trajectory " + toString());
        index = 0;
    }
    _path.DeletePoint(index);
}

unsigned int DiscreteMap::GetPointCount() const
{
    return _path.Count();
}

bool DiscreteMap::isPointAllowedZone(Point) const{
    return true;
}

bool DiscreteMap::isPointAllowedAngle(Point) const{
     return true;
}

bool DiscreteMap::isPointAllowedRanged(Point p) const{
    if(CheckDrone())
        return Point::computeDistance(p,_path.GetOrigin()) <= _drone.getDroneType().getMaxRangeMeter();
    return  false;
}

bool DiscreteMap::isPointAllowedRanged(QPoint qp) const{
    Point p = _map->GetWorldPos(qp);
    return isPointAllowedZone(p);
}


void DiscreteMap::computeTrajectory(){

}

void DiscreteMap::exportTrajectory(double step) const
{
    _path.Export(step);
}

void DiscreteMap::verifyTrajectory()
{
    _path.CalculateCPInfos(_drone.getDroneType().getMaxRangeMeter(),
                           _drone.getDroneType().getCruiseSpeed());
}


void DiscreteMap::infos(){
    cout << "Please use qdebug() of toqString instead of info in discretemap" << endl;
}

std::string DiscreteMap::toString() const
{
    return toQString().toStdString();
}

QString DiscreteMap::toQString() const
{
    QString res = "DiscreteMap ";
    res += " Start = ";
    res += _start.ToQString();
    res += " End = ";
    res += _end.ToQString();
    res += " Drone = ";
    res += QString::number(_drone.getid());
    res += " Map = ";
    res += _map->ToQString();
    res+= " Trajectory = ";
    res += _path.ToQString();
    return res;
}

void DiscreteMap::Draw(QPainter &painter, QPen &pen)
{
    _map->Draw(painter,pen);

    _path.Draw(painter,pen,_map);

    if(CheckDrone())
        _drone.Draw(painter,pen,_map,_path.GetOrigin());

}




void DiscreteMap::AddControls(QWidget *owner)
{
    QLabel * currentbutton = nullptr;

    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Button,Qt::blue);

    QPoint screenPosition;

    for(unsigned int i = 0; i < _path.Count();i++)
    {
        screenPosition = _map->GetScreenPos(_path.GetPointInfo(i));
        currentbutton = new QLabel(QString::number(i),owner);
        currentbutton->resize(10,10);
        currentbutton->move( screenPosition.x()-currentbutton->size().width()/2,screenPosition.y()-currentbutton->size().height()/2); //QT Shitty coordinate system top left is center
        currentbutton->setAutoFillBackground(true);
        currentbutton->setPalette(*palette);
        currentbutton->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
        currentbutton->update();
        currentbutton->show();
    }

}

bool DiscreteMap::CheckDrone() const
{
//    if(_missionInfo.getActiveDrone() == nullptr)
//    {
//        FileDump::WriteLine("no drone in "+toString());
//        return false;
//    }
    return true;
}

bool DiscreteMap::CheckPointAllowed(Point p) const
{
    return isPointAllowedZone(p) && isPointAllowedAngle(p) && isPointAllowedRanged(p);
}

bool DiscreteMap::CheckPointAllowed(QPoint qp) const
{
    Point p = _map->GetWorldPos(qp);
    return CheckPointAllowed(p);
}

bool DiscreteMap::IsTrajectoryCalculated() const
{
    return _path.isVerified();
}

TRAJECTORY_ERROR DiscreteMap::IsTrajectoryVerified() const
{
    if(_path.GetTotalTime() > _drone.getDroneType().getAutonomy()*60.0)
        return  TRAJECTORY_ERROR::NOT_ENOUGH_AUTONOMY;
    if(_path.GetTotalFuel() > _drone.getDroneType().getMaxRangeMeter())
        return  TRAJECTORY_ERROR::NOT_ENOUGH_FUEL;
    if(_path.GetMaxAngle() < _drone.getDroneType().getWingType().getMaxAngle())
        return  TRAJECTORY_ERROR::TURN_TOO_STEEP;

    return TRAJECTORY_ERROR::NONE;
}


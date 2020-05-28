#include "include/Trajectory.h"

#include <sstream>
#include <algorithm>
#include <math.h>

Trajectory::Trajectory():_totalTime(0),_totalFuel(0)
{
    //ctor
    FileDump::WriteLine("Trajectory created without origin and destination " + ToString());
    _isVerified = false;
}

double Trajectory::GetMaxAngle() const
{
    return _maxAngle;
}

void Trajectory::SetMaxAngle(double maxAngle)
{
    _maxAngle = maxAngle;
}

bool Trajectory::isVerified() const
{
    return _isVerified;
}

Trajectory::Trajectory(Point origin, Point destination):_totalTime(0),_totalFuel(0)
{
    _chainedPoints.push_back( ControlPoint(ControlPointType::ORIGIN, origin) );
    _chainedPoints.push_back( ControlPoint(ControlPointType::DESTINATION, destination) );
    _isVerified = false;
}

ControlPoint Trajectory::GetOrigin() const
{
    return _chainedPoints.at(0);
}

ControlPoint Trajectory::GetDestination() const
{
    return _chainedPoints.at(_chainedPoints.size()-1);
}

ControlPoint Trajectory::GetPointInfo(unsigned int position) const
{
     return _chainedPoints.at(position);
}

void Trajectory::Export(double step) const
{
    FileDump::SetFileToTrajectory();
    FileDump::ClearFile();
    FileDump::WriteLine("------------------------");
    if(!_isVerified)
        FileDump::WriteLine("TRAJECTORY NOT VERIFIED");
    FileDump::WriteLine("Start export trajectory " + ToString());
    if(step <= 0.0)
    {
        FileDump::WriteLine("Step negative in export trajectory " + ToString());
        step = 1.0;
    }
    //parametric segment :
    //A = (x0,y0,z0) and B = (x1,y1,z1)
    //[A,B] = (x0,y0,z0) + t*(x1-x0, y1-y0, z1-z0)
    //with t = [0,1] -> 0 = A et 1 = B
    //TLDR:     [A,B] = (x0,y0,z0) + t*(x1-x0, y1-y0, z1-z0)
    //          [A,B] = A + t*(B-A)
    //          ->From A and follow vector AB by proportion t
    Point A;
    Point B;
    Point X; //point that follows the trajectory
    Point BminusA;

    FileDump::WriteLine("Start Point " + GetOrigin().ToString());
    for (unsigned int cpIndex=0; cpIndex < _chainedPoints.size()-1;cpIndex++) {
        A.Set(_chainedPoints[cpIndex]);
        B.Set(_chainedPoints[cpIndex+1]);
        BminusA = B-A;
        //we need to set the [0,1] t to the step
        double distance = Point::computeDistance(A,B);//A.DistanceWithAltitude(B);
        double stepT = step/distance;
        //for each stepcount = every step
        X = A; //start at A
        for (double t = 0.0; t <= 1.0;t+=stepT) {
            X = A + t*BminusA;
            //X.SetAltitude(A.z() + t*BminusA.z());  //altitude is not of the same unit
            FileDump::WriteLine("Intermediary Point " + X.ToString());
        }
        FileDump::WriteLine("Step Point " + B.ToString());
    }

    FileDump::WriteLine("------------------------");
    FileDump::SetFileToError();

}


std::string Trajectory::ToString() const
{
    std::stringstream ss;
    ss << "Trajectory " << this << " Time=" << _totalTime << " fuelUse=" << _totalFuel << " points=" << _chainedPoints.size();
    for(unsigned int i = 0; i < _chainedPoints.size();i++)
    {
        ss << std::endl;
        ss << "----Point = " << _chainedPoints[i].ToString();
    }
    return ss.str();
}

QString Trajectory::ToQString() const
{
    return QString::fromStdString(ToString());
}


bool Trajectory::IsPointInList(unsigned int position) const
{
    if(position >= _chainedPoints.size())
        FileDump::WriteLine("position does not exist in " + ToString());
    else
        return true;
    return false;
}

bool Trajectory::IsPointOrigin(unsigned int position) const
{
    if(position == 0)
        FileDump::WriteLine("unauthorized access to origin of " + ToString());
    else
        return false;
    return true;
}

bool Trajectory::IsPointDestination(unsigned int position) const
{
    if(position == _chainedPoints.size()-1)
        FileDump::WriteLine("unauthorized access to destination of " + ToString());
    else
        return false;
    return true;
}

void Trajectory::AddPointAt(Point p, ControlPointType cpt, unsigned int position)
{
    if(!IsPointDestination(position) && !IsPointOrigin(position) &&  IsPointInList(position))
    {
        _chainedPoints.insert(_chainedPoints.begin()+position,ControlPoint(cpt,p));
    }
    _isVerified = false;
}


ControlPoint& Trajectory::ModifyPoint(unsigned int position)
{
    _isVerified = false;
    return _chainedPoints.at(position);
}

void Trajectory::DeletePoint(unsigned int position)
{
    if(!IsPointDestination(position) && !IsPointOrigin(position) &&  IsPointInList(position))
    {
        _chainedPoints.erase(_chainedPoints.begin()+position);
    }
    _isVerified = false;
}

unsigned int Trajectory::AddNextPoint(Point p, ControlPointType cpt)
{
    _chainedPoints.push_back(ControlPoint(cpt,p));
    std::iter_swap(_chainedPoints.end() - 2, _chainedPoints.end() - 1 ); //destination must be last
    _isVerified = false;
    return _chainedPoints.size()-2;

}

void Trajectory::SwitchPoint(unsigned int position1, unsigned int position2)
{
    if(!IsPointDestination(position1) && !IsPointOrigin(position1) &&  IsPointInList(position1))
    {
        if(!IsPointDestination(position2) && !IsPointOrigin(position2) &&  IsPointInList(position2))
        {
            std::iter_swap(_chainedPoints.begin() + position1, _chainedPoints.begin() + position2  );
        }
    }
    _isVerified = false;
}

void Trajectory::CalculateCPInfos(double maxRange, double speedInKmH)
{
    double distance = 0.0;
    double speedInMM = speedInKmH*1000.0/60.0; //meter per min
    double minAngle = 360.0;
    for(unsigned int i = 0; i < Count()-1;i++)
    {
        distance += Point::computeDistance(_chainedPoints[i],_chainedPoints[i+1]);
        _chainedPoints[i+1].SetFuelUse(distance/maxRange);
        _chainedPoints[i+1].SetTimeToReach(distance/speedInMM);
        if(i>0)
        {
            _chainedPoints[i].SetTurnAngle(Point::AngleABC(_chainedPoints[i-1],_chainedPoints[i],_chainedPoints[i+1]));
            if(minAngle > _chainedPoints[i].GetTurnAngle())
                minAngle = _chainedPoints[i].GetTurnAngle();
        }
    }
    _totalFuel = distance/maxRange;
    _totalTime = distance/speedInMM;
    _maxAngle = minAngle;
    _isVerified = true;
}

void Trajectory::Draw(QPainter &painter, QPen &pen, const MapInfo * map)
{
    pen.setWidth(8);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawPoint(map->GetScreenPos(_chainedPoints[0]));

    for(unsigned int i = 1; i < Count()-1;i++)
    {
        pen.setWidth(8);
        pen.setColor(Qt::green);
        painter.setPen(pen);
        painter.drawPoint(map->GetScreenPos(_chainedPoints[i]));
        pen.setWidth(2);
        painter.setPen(pen);
        painter.drawLine(map->GetScreenPos(_chainedPoints[i]),map->GetScreenPos(_chainedPoints[i-1]));
    }
    pen.setWidth(2);
    pen.setColor(Qt::green);
    painter.setPen(pen);
    painter.drawLine(map->GetScreenPos(_chainedPoints[Count()-1]),map->GetScreenPos(_chainedPoints[Count()-2]));

    pen.setWidth(8);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawPoint(map->GetScreenPos(_chainedPoints[Count()-1]));
}


Trajectory::~Trajectory()
{
    //dtor
}

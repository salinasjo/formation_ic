#include "include/ControlPoint.h"

#include <sstream>

ControlPoint::ControlPoint():Point(),_timeToReach(0),_fuelUse(0),_turnAngle(360),_contolPointType(ControlPointType::AUTOMATIC)
{
    //ctor
}

double ControlPoint::GetTurnAngle() const
{
    return _turnAngle;
}

void ControlPoint::SetTurnAngle(double turnAngle)
{
    _turnAngle = turnAngle;
}

ControlPoint::ControlPoint(ControlPointType cptype):Point(),_timeToReach(0),_fuelUse(0),_turnAngle(360),_contolPointType(cptype)
{

}

ControlPoint::ControlPoint(ControlPointType cptype, Point p):Point(p),_timeToReach(0),_fuelUse(0),_turnAngle(360),_contolPointType(cptype)
{

}

ControlPoint::ControlPoint(ControlPointType cptype, double x, double y, double z):Point(x,y,z),_timeToReach(0),_fuelUse(0),_turnAngle(360),_contolPointType(cptype)
{

}

ControlPoint::ControlPoint(const ControlPoint & other):Point(other)
{
    _contolPointType = other.GetControlPointType();
    _timeToReach = other.GetTimeToReach();
    _fuelUse = other.GetFuelUse();
    _turnAngle = other.GetTurnAngle();
}

ControlPoint& ControlPoint::operator=(const ControlPoint & other)
{
    if(this != &other)
    {
        Set(other.GetLatitude(), other.GetLongitude(), other.GetAltitude());
        _contolPointType = other.GetControlPointType();
        _timeToReach = other.GetTimeToReach();
        _fuelUse = other.GetFuelUse();
        _turnAngle = other.GetTurnAngle();
    }
    return *this;
}

void ControlPoint::SetTimeToReach(double val)
{
    if (val >= 0.0)
        _timeToReach = val;
    else
        FileDump::WriteLine("timeToReach set negative in " + ToString());
}

void ControlPoint::SetFuelUse(double val)
{
    if (val >= 0.0)
        _fuelUse = val;
    else
        FileDump::WriteLine("fuelUse set negative in " + ToString());
}


std::string ControlPoint::ToString() const
{
    std::stringstream ss;
    ss << Point::ToString();
    ss << " ControlPoint " <<  " Time=" << _timeToReach << " fuelUse=" << _fuelUse << " type=" << ControlPoint::ToStringControlPointType(_contolPointType);
    return ss.str();
}

QString ControlPoint::ToQString() const
{
    return  QString::fromStdString(ToString());
}

std::string ControlPoint::ToStringControlPointType(ControlPointType cpt)
{
    switch(cpt)
    {
        case (ControlPointType::AUTOMATIC):
            return "Automatic";
            break;
        case (ControlPointType::MANUAL):
            return "Manual";
            break;
        case (ControlPointType::ORIGIN):
            return "Origin";
            break;
        case (ControlPointType::DESTINATION):
            return "Destination";
            break;
    }
    FileDump::WriteLine("unrecognized ControlPointType");
    return "UKNOWN CONTROLPOINTTYPE";
}

ControlPoint::~ControlPoint()
{
    //dtor
}


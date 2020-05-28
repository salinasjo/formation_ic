#ifndef CONTROLPOINT_H
#define CONTROLPOINT_H

#include "Point.h"
#include "FileDump.h"
#include <string>
#include <QPoint>
enum ControlPointType { MANUAL, AUTOMATIC, ORIGIN, DESTINATION };

class ControlPoint : public Point
{


    public:

        ~ControlPoint() override;
        ControlPoint(ControlPointType);
        ControlPoint(ControlPointType, Point);
        ControlPoint(ControlPointType, double, double, double);
        ControlPoint(const ControlPoint & other);
        ControlPoint& operator=(const ControlPoint & other);


        double GetTimeToReach() const { return _timeToReach; }
        void SetTimeToReach(double val);
        double GetFuelUse() const { return _fuelUse; }
        void SetFuelUse(double val);
        ControlPointType GetControlPointType() const { return _contolPointType; }
        void SetControlPointType(ControlPointType cpt) { _contolPointType = cpt;}

        void UpdateInfos(float timeToReach, float fuelUse) { SetTimeToReach(timeToReach); SetFuelUse(fuelUse);}

        std::string ToString() const override;
        QString ToQString() const override;
        static std::string ToStringControlPointType(ControlPointType cpt);


        double GetTurnAngle() const;
        void SetTurnAngle(double turnAngle);

protected:
        ControlPoint();  //no typeless control point
        double _timeToReach;
        double _fuelUse;
        double _turnAngle;
        ControlPointType _contolPointType;

    private:


};

#endif // CONTROLPOINT_H

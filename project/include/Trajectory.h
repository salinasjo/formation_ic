#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include "Point.h"
#include "ControlPoint.h"
#include "FileDump.h"
#include "mapinfo.h"
#include <vector>
#include <QPainter>

class Trajectory
{
    public:
        Trajectory(Point, Point);
        ~Trajectory();

        double GetTotalTime() const { return _totalTime; }
        //void Set_totalTime(float val) { _totalTime = val; } computed from control points
        double GetTotalFuel() const { return _totalFuel; }
        //void Set_totalFuel(float val) { _totalFuel = val; } computed from control points

        ControlPoint GetOrigin() const;
        ControlPoint GetDestination() const;
        ControlPoint GetPointInfo(unsigned int position) const;
        ControlPoint& ModifyPoint(unsigned int position);

        void DeletePoint(unsigned int position);
        unsigned int AddNextPoint(Point p, ControlPointType cpt);
        void AddPointAt(Point p, ControlPointType cpt, unsigned int position);
        void SwitchPoint(unsigned int position1, unsigned int position2);
        void CalculateCPInfos(double maxRange, double speedInKmH);
        void Draw(QPainter &painter, QPen &pen, const MapInfo * map);

        std::string ToString() const;
        QString ToQString() const;

        unsigned int Count() const  {return _chainedPoints.size();}
        void Export(double step) const;

        bool isVerified() const;

        double GetMaxAngle() const;
        void SetMaxAngle(double maxAngle);

protected:
        Trajectory(); //trajectory must have start and finish


        double _totalTime;
        double _totalFuel;
        double _maxAngle;
        bool _isVerified = false;


    private:
        std::vector<ControlPoint> _chainedPoints;

        bool IsPointInList(unsigned int) const;
        bool IsPointOrigin(unsigned int) const;
        bool IsPointDestination(unsigned int) const;

};

#endif // TRAJECTORY_H

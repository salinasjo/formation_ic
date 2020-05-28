#ifndef DISCRETEMAP_H
#define DISCRETEMAP_H
#include "Trajectory.h"
//#include "WorldMap.h"
//#include "ForbiddenZones.h"
//#include "MissionProcess.h"
#include "Point.h"
#include "mapinfo.h"
#include "Drone.h"
#include <QPainter>

#define MAX_SIZE 10

class Weather{};

//class Trajectory{};
class ForbiddenZones{};
//class MissionProcess{};
//class Point{};
//class WorldMap{};

enum TRAJECTORY_ERROR {NOT_ENOUGH_FUEL, NOT_ENOUGH_AUTONOMY, TURN_TOO_STEEP, NONE, UKNOWN};

class DiscreteMap
{
    public:
        //DiscreteMap(MissionProcess&);
        DiscreteMap(const Point & start, const  Point & end, const Drone & drone, double altitude);
        virtual ~DiscreteMap();

        //bool getMapPath() { return _mapPath; }
        ForbiddenZones getForbidden() { return _forbidden; }
        MapInfo * getMap() { return _map; }
        //Trajectory getPath() { return _path; }
        //MissionProcess & getMissionInfo() { return _missionInfo; }
        Weather getWeather() { return _weather; }


        //void setMapPath(bool val) { _mapPath[MAX_SIZE][MAX_SIZE] = val; }
        void setForbidden(ForbiddenZones val) { _forbidden = val; }
        //void setPath(Trajectory val) { _path = val; }
//        void setMap(MapInfo * val) {
//            if(!val->IsInMap(_path.GetOrigin()) || !val->IsInMap(_path.GetDestination()))
//            {
//                FileDump::WriteLine("dicrete map updated with map outside of start or end point" + _missionInfo.toString());
//            }
//            _map = val;
//        }
        //void setMisionInfo(MissionProcess val) { _missionInfo = val; }
        void setWeather(Weather val) { _weather = val; }

         void UpdateWithLastImage();

        unsigned int addPoint(Point, ControlPointType cpt=ControlPointType::MANUAL);
        void modPoint(unsigned int,Point);
        Point getPoint(unsigned int index) const;
        ControlPoint getCPoint(unsigned int index) const;
        void deletePoint(unsigned int);
        unsigned int GetPointCount() const;
        void exportTrajectory(double step) const;
        void verifyTrajectory();

        bool CheckPointAllowed(Point) const;
        bool CheckPointAllowed(QPoint) const;
        bool IsTrajectoryCalculated() const;
        TRAJECTORY_ERROR IsTrajectoryVerified() const;

        void infos();
        std::string toString() const;
        QString toQString() const;

        void Draw(QPainter& painter,QPen& pen);
        void AddControls(QWidget* owner);

    protected:
        bool CheckDrone() const;
        bool isPointAllowedZone(Point) const;
        bool isPointAllowedAngle(Point) const;
        bool isPointAllowedRanged(Point) const;
        bool isPointAllowedRanged(QPoint) const;
        void computeTrajectory();

    private:
        bool _mapPath[MAX_SIZE][MAX_SIZE];
        ForbiddenZones _forbidden;
        MapInfo * _map = nullptr;
        Trajectory _path;
        //MissionProcess & _missionInfo;
        Point _start; //ref from mission process?
        Point _end; //ref from mission process?
        Drone _drone; //ref from mission process?
        Weather _weather;
};

#endif // DISCRETEMAP_H

#ifndef DRONE_H
#define DRONE_H

#include "DroneType.h"
#include "Point.h"
#include "MissionType.h"
#include "ISerializable.h"

#include <QFile>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QPainter>
#include "mapinfo.h"

class MissionProcess;
class Drone : public ISerializable
{
    public:
		Drone();
		Drone(Point, DroneType, MissionProcess* mp= nullptr);
		Drone(const Drone &);
		Drone& operator=(const Drone &);

		virtual ~Drone() override;

        int getid() const override { return _id; }
		DroneType getDroneType() const { return _droneType; }
		void setDroneType(DroneType val) { _droneType = val; }
		Point getGroundPosition() const { return _groundPosition; }
		void setGroundPosition(Point val) { _groundPosition = val; }
		MissionProcess* getCurrentMission() const { return _currentMission; }
		void setCurrentMission(MissionProcess *val) { _currentMission = val; }

        bool isAvailableAt(QDate);
        bool hasAltitude(MissionProcess*);
        bool hasWeightCapacity(MissionProcess*);
        bool hasRange(MissionProcess*);
        void rebase(Point);
        double distanceFromStart(MissionProcess*);


        void Draw(QPainter &painter, QPen &pen, const MapInfo * map, const Point & position);
        bool isAvailable();

//		static void write(QMap<int, Drone *> *map, QJsonObject &json);
//		static void read(QMap<int, Drone *> *map, const QJsonObject &json);
//		static bool saveDrones(QMap<int, Drone *> *map);
//		static bool loadDrones(QMap<int, Drone *> *map);
//		void readObject(const QJsonObject &json);
//		void writeObject(QJsonObject &json) const;

		QString toQString();
		std::string toString();

		// ISerializable interface
		void readObject(const QJsonObject &json) override;
		void writeObject(QJsonObject &json) const override;

		bool getDeleted() const;
		void setDeleted(bool deleted);


private:
		static int _CurrentId;
		int _id;
		DroneType _droneType;
		Point _groundPosition;
		MissionProcess *_currentMission=nullptr;
		bool _deleted=false;

		void setid(int val) { _id = val; }

};

#endif // DRONE_H

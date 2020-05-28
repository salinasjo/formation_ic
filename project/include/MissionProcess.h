#ifndef MISSIONPROCESS_H
#define MISSIONPROCESS_H

#include "Commander.h"
#include "MissionType.h"
#include "Operator.h"
#include "Point.h"
#include "Drone.h"
#include "DiscreteMap.h"

#include <QDate>
#include <QMap>
#include <QFile>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include "ISerializable.h"

using namespace std;

enum StatutValide {WAITING, VALIDATED, REFUSED };

class MissionProcess : public ISerializable {
	private:
		static int _CurrentId;
        int _id;
		MissionType _missionType;
		Drone *_activeDrone = nullptr;
        DiscreteMap * _map = nullptr;
		Operator _op;
        Commander _comm;

		Point _startPoint;
		Point _endPoint;
        QDate _startDate;

		bool _opValidated;
		StatutValide _commValidated;
		QString _commComment;

        double _altitude;
        float _weightCharge;

	protected:

	public:
		MissionProcess();//Move to protected when all ctors done

		MissionProcess(Operator &o);
		MissionProcess(const MissionProcess &mp);
        MissionProcess& operator=(const MissionProcess &mp);
        ~MissionProcess() override;

        int getid() const override;
        void setId(int id);
		MissionType getMissionType() const;
		void setMissionType(MissionType &missionType);
		Drone* getActiveDrone() const;
        void setActiveDrone(Drone *activeDrone);
        //void setStartPoint(Point &startPoint);
        //void setEndPoint(Point &endPoint);
		Operator getOp() const;
		void setOp(Operator &op);
		Commander getComm() const;
		void setComm(Commander &comm);

        //activate trajectory input when all mission general infos are there
        //recquire start,end,drone,altitude
        bool activateTrajectoryInput();

        QDate getStartDate() const;
        void setStartDate(const QDate &startDate);
		bool getOpValidated() const;
		void setOpValidated(bool opValidated);
		StatutValide getCommValidated() const;
		void setCommValidated(const StatutValide &commValidated);
		QString getCommComment() const;
		void setCommComment(const QString &commComment);
        double getAltitude() const;
        void setAltitude(const double &);
        float getWeightCharge() const;
        void setWeightCarge(const float &);


		//void selectDrone(Drone d);
        std::string toString() const;
        QString toQString() const;
        Point getStartPoint() const;
        void setStartPoint(Point startPoint);
        Point getEndPoint() const;
        void setEndPoint(Point endPoint);


        static bool saveMissions(QMap<int, MissionProcess *> *map);
        static bool loadMissions(QMap<int, MissionProcess *> *map);
        static void write(QMap<int, MissionProcess *> *map, QJsonObject &json);
        static void read(QMap<int, MissionProcess *> *map, const QJsonObject &json);
        void readObject(const QJsonObject &json);
        void writeObject(QJsonObject &json) const;

        DiscreteMap *getMap() const;
};

#endif // MISSIONPROCESS_H

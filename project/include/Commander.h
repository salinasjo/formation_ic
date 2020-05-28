#ifndef COMMANDER_H
#define COMMANDER_H
#include <list>
#include <QMap>

#include "User.h"
#include "Drone.h"


class Commander : public User
{

    public:
		explicit Commander();
		Commander(QString, QString, QString, QString);
		Commander(const Commander &);
		Commander operator=(const Commander &);
        virtual ~Commander();

        void missionValidation();
        void addDrone();
		bool addDrone(QMap<int, Drone *> *, Drone *);
        void modifyDrone();
		bool deleteDrone(QMap<int, Drone *> *, Drone *);

		std::string toString();

		void writeObject(QJsonObject &json) const;


    protected:

    private:
        // To replace with MissionProcess struct once defined
        list<int> _myMission;

};

#endif // COMMANDER_H

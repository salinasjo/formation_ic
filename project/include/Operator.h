#ifndef OPERATOR_H
#define OPERATOR_H
#include <list>
#include "User.h"


class MissionProcess;
class Operator : public User
{
    public:
		explicit Operator();
		Operator(QString, QString, QString, QString);
		Operator(const Operator &);
		Operator operator=(const Operator &);
		virtual ~Operator();

        void missionManagement();
        void missionTypeManagement();

		std::string toString();

		void writeObject(QJsonObject &json) const;


    protected:

    private:
        // To replace with MissionProcess struct once defined
        list<MissionProcess> _myMission;
};

#endif // OPERATOR_H

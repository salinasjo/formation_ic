#ifndef MISSIONTYPE_H
#define MISSIONTYPE_H
#include <iostream>
#include <QString>
#include <QJsonObject>

using namespace std;

class MissionType {
	private:
		QString _name;
		QString _description;
		float _payload;
        double _altitude;

	public:
		MissionType();
        MissionType(const QString &n, const QString &d, float p=0, double a=0);
		virtual ~MissionType();

		QString getName() const;
		void setName(const QString &);
		QString getDescription() const;
		void setDescription(const QString &);
		float getPayload() const;
		void setPayload(float);
        double getAltitude() const;
        void setAltitude(double);

		QString toString() const;

        void readObject(const QJsonObject &json);
        void writeObject(QJsonObject &json) const;
};

#endif // MISSIONTYPE_H

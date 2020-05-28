#ifndef WINGTYPE_H
#define WINGTYPE_H
#include <iostream>
#include <sstream>
#include <QString>
#include <QDebug>
#include <QJsonObject>

#include "FileDump.h"


using namespace std;

class WingType
{

    public:
		WingType();
		WingType(QString, float);
		WingType(const WingType &);
		WingType& operator=(const WingType &);
        virtual ~WingType();

		QString getName() const { return _name; }
		void setName(QString val) { _name = val; }
		float getMaxAngle() const { return _maxAngle; }
        void setMaxAngle(float val) { _maxAngle = val; }


		void readObject(const QJsonObject &json);
		void writeObject(QJsonObject &json) const;

        //Temporary to check the good creation
        void infos();
		QString toQString();
		std::string toString();

    protected:

    private:
		QString _name;
        float _maxAngle;
};

#endif // WINGTYPE_H

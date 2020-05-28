#include "include/MissionType.h"
#include <sstream>

QString MissionType::getName() const { return _name; }
void MissionType::setName(const QString &n) { _name = n; }

QString MissionType::getDescription() const { return _description; }
void MissionType::setDescription(const QString &d) { _description = d; }

float MissionType::getPayload() const { return _payload; }
void MissionType::setPayload(float p) { _payload = p; }

double MissionType::getAltitude() const { return _altitude; }
void MissionType::setAltitude(double a) { _altitude = a; }

QString MissionType::toString() const {
	QString qs;
	qs.push_back("Mission Type {");
	qs.push_back("\tName : " + getName());
	qs.push_back("\tDescription : " + getDescription());
	qs.push_back("\tPayload : " + QString::number(getPayload()) + " Kg");
	qs.push_back("\tAltitude : " + QString::number(getAltitude()) + " m");
	qs.push_back("}");
	return qs;
}

MissionType::MissionType() {}
MissionType::MissionType(const QString &n, const QString &d, float p, double a) {
    setName(n);
    setDescription(d);
    setPayload(p);
    setAltitude(a);
}

MissionType::~MissionType() {
    //cout << "Destruction MissionType" << endl;
}


void MissionType::readObject(const QJsonObject &json)
{
    if (json.contains("name"))
        setName(json["name"].toString());
    if (json.contains("description"))
        setDescription(json["description"].toString());
    if (json.contains("payload"))
        setPayload(json["payload"].toInt());
    if (json.contains("altitude"))
        setAltitude(json["altitude"].toDouble());
}

void MissionType::writeObject(QJsonObject &json) const
{
    json["name"] = _name;
    json["description"] = _description;
    json["payload"] = _payload;
    json["altitude"] = _altitude;
}

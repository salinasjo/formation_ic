#include "include/DroneType.h"

DroneType::DroneType()
{
    //ctor
}

DroneType::DroneType(float wc, double maxA, double maxR, float cspd, float autonomy, WingType wtype)
{
    setWeightCapacity(wc);
    setMaxAltitude(maxA);
    setMaxRange(maxR);
    setCruiseSpeed(cspd);
    setAutonomy(autonomy);
    setWingType(wtype);
}

DroneType::DroneType(const DroneType &dt) {
	_weightCapacity = dt.getWeightCapacity();
	_maxAltitude = dt.getMaxAltitude();
	_maxRange = dt.getMaxRange();
	_cruiseSpeed = dt.getCruiseSpeed();
	_autonomy = dt.getAutonomy();
	_wingType = dt.getWingType();
}
DroneType& DroneType::operator=(const DroneType &dt) {
	_weightCapacity = dt.getWeightCapacity();
	_maxAltitude = dt.getMaxAltitude();
	_maxRange = dt.getMaxRange();
	_cruiseSpeed = dt.getCruiseSpeed();
	_autonomy = dt.getAutonomy();
	_wingType = dt.getWingType();
	return *this;
}

void DroneType::readObject(const QJsonObject &json)
{
	if (json.contains("weightCapacity"))
		setWeightCapacity(json["weightCapacity"].toDouble());
	if (json.contains("maxAltitude") && json["maxAltitude"].isDouble())
		setMaxAltitude(json["maxAltitude"].toDouble());
	if (json.contains("maxRange") && json["maxRange"].isDouble())
		setMaxRange(json["maxRange"].toDouble());
	if (json.contains("cruiseSpeed"))
		setCruiseSpeed(json["cruiseSpeed"].toDouble());
	if (json.contains("autonomy"))
		setAutonomy(json["autonomy"].toDouble());
	if(json.contains("wingType") && json["wingType"].isObject()) {
		QJsonObject wingObject = json["wingType"].toObject();
		_wingType.readObject(wingObject);
	}
}

void DroneType::writeObject(QJsonObject &json) const
{
	json["weightCapacity"] = _weightCapacity;
	json["maxAltitude"] = _maxAltitude;
	json["maxRange"] = _maxRange;
	json["cruiseSpeed"] = _cruiseSpeed;
	json["autonomy"] = _autonomy;

	QJsonObject wingTypeObject;
	_wingType.writeObject(wingTypeObject);
	json["wingType"] = wingTypeObject;
}

//dtor
DroneType::~DroneType()
{
    //cout << "Destruction Drone Type" << endl;
}


void DroneType::infos()
{
	cout << "Capacite de port : " << getWeightCapacity() << endl
         << "Altitude maximale : " << getMaxAltitude() << endl
         << "Portee maximale : " << getMaxRange() << endl
         << "Vitesse de croisiere : " << getCruiseSpeed() << endl
         << "Autonomie : " << getAutonomy() << endl;
		 _wingType.infos();
}

std::string DroneType::toString() {
	stringstream oss;
	oss << "Drone Type {" << endl;
	oss << "\t\tPayload : " << getWeightCapacity() << " Kg" << endl;
	oss << "\t\tMax Altitude : " << getMaxAltitude() << " m" << endl;
	oss << "\t\tMax Range : " << getMaxRange() << " m" << endl;
	oss << "\t\tCruise Speed : " << getCruiseSpeed() << " Km/h" << endl;
	oss << "\t\tAutonomy : " << getAutonomy() << " h" << endl;
	oss << "\t\tWing Type : " << getWingType().toString() << endl;
	oss << "\t}";
	return oss.str();
}
QString DroneType::toQString() {
	QString qs;
	return qs.fromStdString(toString());
}

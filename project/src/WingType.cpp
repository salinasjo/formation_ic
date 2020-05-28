#include "include/WingType.h"

WingType::WingType()
{
    //ctor
}

WingType::WingType(QString n, float maxAng)
{
    setName(n);
    setMaxAngle(maxAng);
}

WingType::WingType(const WingType &wt)
{
	_name = wt.getName();
	_maxAngle = wt.getMaxAngle();
}
WingType& WingType::operator=(const WingType &wt) {
	_name = wt.getName();
	_maxAngle = wt.getMaxAngle();
	return *this;
}

void WingType::readObject(const QJsonObject &json)
{
	if (json.contains("name") && json["name"].isString())
		setName(json["name"].toString());
	if (json.contains("maxAngle"))
		setMaxAngle(json["maxAngle"].toDouble());
}

void WingType::writeObject(QJsonObject &json) const
{
	json["name"] = _name;
	json["maxAngle"] = _maxAngle;
}

//dtor
WingType::~WingType()
{
    //cout << "Destruction Wing Type" << endl;
}

void WingType::infos()
{
	//cout << "Drone a " << WingType::getName() << " avec angle de virage maximum de " << WingType::getMaxAngle() << " degres." << endl;
}

std::string WingType::toString() {
	stringstream oss;
	oss << "Wing Type {" << endl;
	oss << "\t\t\tName : " << getName().toStdString() << endl;
	oss << "\t\t\tMax Turning Angle : " << getMaxAngle() << " deg" << endl;
	oss << "\t\t}" << endl;
	return oss.str();
}

QString WingType::toQString() {
	return QString::fromStdString(toString());
}

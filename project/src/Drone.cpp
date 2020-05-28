#include "include/Drone.h"
#include "include/MissionProcess.h"



int Drone::_CurrentId = 0;

Drone::Drone()
{
    //ctor
}

Drone::Drone(Point p, DroneType dt, MissionProcess *mp)
{
	setid(++Drone::_CurrentId);
    setGroundPosition(p);
	setCurrentMission(mp);
    setDroneType(dt);
}

Drone::Drone(const Drone &d)
{
	_id = d.getid();
	_groundPosition = d.getGroundPosition();
	_currentMission = d.getCurrentMission();
	_droneType = d.getDroneType();
	_deleted = d.getDeleted();
}
Drone& Drone::operator=(const Drone &d) {
	_id = d.getid();
	_groundPosition = d.getGroundPosition();
	_currentMission = d.getCurrentMission();
	_droneType = d.getDroneType();
	_deleted = d.getDeleted();
	return *this;
}

//Check if the drone is available at selected date
bool Drone::isAvailableAt(QDate d)
{
    if(_currentMission == nullptr)
    {
        return true;
    }
     else
    {
        if(_currentMission->getStartDate() == d)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}

//Check if the drone matches the altitude of the mission
bool Drone::hasAltitude(MissionProcess *mpro)
{
    if(this->_droneType.getMaxAltitude() >= mpro->getAltitude())
    {
        return true;
    }
    else
    {
        return false;
    }
}

//Check if the drone has the weight capacity to support the mission's payload
bool Drone::hasWeightCapacity(MissionProcess * mpro)
{
    if(this->_droneType.getWeightCapacity() >= mpro->getWeightCharge())
    {
        return true;
    }
    else
    {
        return false;
    }
}


//Check if the drone has the range to link the start and end points
bool Drone::hasRange(MissionProcess *mpro)
{
    Point spoint = mpro->getStartPoint();
    Point epoint = mpro->getEndPoint();
    if(this->_droneType.getMaxRange() >= spoint.computeDistance(spoint, epoint))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Drone::rebase(Point p)
{
    _groundPosition = p;
}


bool Drone::isAvailable()
{
	if(_currentMission!=nullptr)
		return false;
	else {
		return true;
	}
}



// Distance between drone's ground position and mission's starting point
double Drone::distanceFromStart(MissionProcess *mpro)
{
   Point spointmiss = mpro->getStartPoint();
   double dist = Point::computeDistance(spointmiss, _groundPosition);

   return dist;

}

void Drone::Draw(QPainter &painter, QPen &pen, const MapInfo *map, const Point &position)
{
    pen.setWidth(2);
    pen.setColor(Qt::red);
    painter.setPen(pen);

    Point maxDestination = position.Destination(180,_droneType.getMaxRange()*1000.0);
    QPoint maxDestScreen = map->GetScreenPos(maxDestination);
    QPoint posScreen = map->GetScreenPos(position);
    int distPixel = round(QLineF(maxDestScreen,posScreen).length());
    painter.drawEllipse(posScreen, distPixel,distPixel );
}

void Drone::readObject(const QJsonObject &json)
{
	if (json.contains("id"))
		setid(json["id"].toInt());
	if(json.contains("droneType") && json["droneType"].isObject()) {
		QJsonObject droneTypeObject = json["droneType"].toObject();
		_droneType.readObject(droneTypeObject);
	}
	if(json.contains("groundPosition") && json["groundPosition"].isObject()) {
		QJsonObject positionObject = json["groundPosition"].toObject();
		if(!positionObject.isEmpty())
			_groundPosition.readObject(positionObject);
	}
	if(json.contains("currentMission") && json["currentMission"].isObject()) {
		QJsonObject missionObject = json["currentMission"].toObject();
		if(!missionObject.isEmpty())
			_currentMission->readObject(missionObject);
		else
			_currentMission = nullptr;
	}
	if(json.contains("deleted") && json["deleted"].isBool()) {
		setDeleted(json["deleted"].toBool());
	}
	_CurrentId = _id;
}

void Drone::writeObject(QJsonObject &json) const
{
	json["id"] = _id;

	QJsonObject droneTypeObject;
	_droneType.writeObject(droneTypeObject);
	json["droneType"] = droneTypeObject;
	QJsonObject positionObject;
	_groundPosition.writeObject(positionObject);
	json["groundPosition"] = positionObject;
	QJsonObject missionObject;
	if(_currentMission!=nullptr)
		_currentMission->writeObject(missionObject);
	json["currentMission"] = missionObject;
	json["deleted"] = _deleted;
}

bool Drone::getDeleted() const
{
    return _deleted;
}
void Drone::setDeleted(bool deleted)
{
    _deleted = deleted;
}

std::string Drone::toString() {
    stringstream oss;
    oss << "Drone {" << endl;
    oss << "\tID : " << getid() << endl;
	oss << "\tDrone Type : " + getDroneType().toString() << endl;
	oss << "\tGround Position : " + getGroundPosition().ToString() << endl;
	oss << boolalpha << "\tAvailable : " << isAvailable() << endl;
	oss << boolalpha << "\tDeleted : " << getDeleted() << endl;
	oss << "}" << endl;
	return oss.str();
}
QString Drone::toQString() {
	QString qs;
	return qs.fromStdString(toString());
}

//dtor
Drone::~Drone()
{
    //cout << "Destruction Drone" << endl;
}

/*
//Reading and Writing to File
bool Drone::loadDrones(QMap<int, Drone *> *map)
{
	QFile loadFile("drones.json");

	if(!loadFile.exists()) {
		qWarning("No such file : \"drones.json\"");
		return false;
	}
	if (!loadFile.open(QIODevice::ReadOnly)) {
		qWarning("Couldn't open load file.");
		return false;
	}

	QByteArray saveData = loadFile.readAll();

	QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

	read(map, loadDoc.object());

	qDebug() << "Loaded save for Drones using JSON..." << endl;

	loadFile.close();
	return true;
}
bool Drone::saveDrones(QMap<int, Drone *> *map)
{
	QFile saveFile("drones.json");

	if (!saveFile.open(QIODevice::WriteOnly)) {
		qWarning("Couldn't open save file.");
		return false;
	}

	QJsonObject dronesObject;
	write(map, dronesObject);
	QJsonDocument saveDoc(dronesObject);
	saveFile.write(saveDoc.toJson());

	qDebug() << "Saved Drones using JSON..." << endl;

	saveFile.close();
	return true;
}

void Drone::read(QMap<int, Drone *> *map, const QJsonObject &json)
{
	if (json.contains("drones") && json["drones"].isArray()) {
		QJsonArray droneArray = json["drones"].toArray();
		map->clear();
		for (int index = 0; index < droneArray.size(); ++index) {
			QJsonObject droneObject = droneArray[index].toObject();
			Drone *d = new Drone;
			d->readObject(droneObject);
			map->insert(d->getid(), d);
		}
	}
}

void Drone::write(QMap<int, Drone *> *map, QJsonObject &json)
{
	QJsonArray droneArray;
	for(Drone *d : map->values()) {
		QJsonObject droneObject;
		d->writeObject(droneObject);
		droneArray.append(droneObject);
	}
	json["drones"] = droneArray;
}
*/

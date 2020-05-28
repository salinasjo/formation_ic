#include "include/Drone.h"
#include "include/MissionProcess.h"
#include <cmath>
#include <sstream>
#include <QDebug>
#include <qfile.h>


int MissionProcess::_CurrentId = 0;

using namespace std;

MissionType MissionProcess::getMissionType() const { return _missionType; }
void MissionProcess::setMissionType(MissionType &missionType)
{
    _missionType = missionType;
    _altitude = this->_missionType.getAltitude();
    _weightCharge = this->_missionType.getPayload();
}

Drone *MissionProcess::getActiveDrone() const
{
    return _activeDrone;
}

void MissionProcess::setActiveDrone(Drone *activeDrone)
{
    _activeDrone = activeDrone;
    _activeDrone->setCurrentMission(this);
}



//DiscreteMap MissionProcess::getMap() const { return _map; }
//void MissionProcess::setMap(const DiscreteMap &map) { _map = map; }

Operator MissionProcess::getOp() const { return _op; }
void MissionProcess::setOp(Operator &op) { _op = op; }

Commander MissionProcess::getComm() const { return _comm; }
void MissionProcess::setComm(Commander &comm) { _comm = comm; }

bool MissionProcess::activateTrajectoryInput()
{
    if(_activeDrone==nullptr)
    {
        FileDump::WriteLine("no drone for creating trajectory in " + toString());
        return false;
    }

    _map = new DiscreteMap(_startPoint,_endPoint,*_activeDrone,_altitude);

    return true;
}

Point MissionProcess::getStartPoint() const { return _startPoint; }
void MissionProcess::setStartPoint(Point startPoint) { _startPoint = startPoint;}

Point MissionProcess::getEndPoint() const { return _endPoint; }
void MissionProcess::setEndPoint(Point endPoint) { _endPoint = endPoint; }

QDate MissionProcess::getStartDate() const { return _startDate; }
void MissionProcess::setStartDate(const QDate &startDate)
{
    QDate dday = QDate::currentDate();

    if(startDate < dday.addDays(1))
        {
            qDebug() << "Date invalide ! Au moins J+1";
        }
        else
        {
            _startDate = startDate;
        }
}


bool MissionProcess::getOpValidated() const { return _opValidated; }
void MissionProcess::setOpValidated(bool opValidated) { _opValidated = opValidated; }

StatutValide MissionProcess::getCommValidated() const { return _commValidated; }
void MissionProcess::setCommValidated(const StatutValide &commValidated) { _commValidated = commValidated; }

QString MissionProcess::getCommComment() const { return _commComment; }
void MissionProcess::setCommComment(const QString &commComment) { _commComment = commComment; }


double MissionProcess::getAltitude() const { return _altitude; }
void MissionProcess::setAltitude(const double &value) {
    _altitude = value;
    if(_map != nullptr)
    {
        if(_map->getMap() != nullptr)
            _map->getMap()->setDefaultAltitude(value);
    }
}

float MissionProcess::getWeightCharge() const { return _weightCharge; }
void MissionProcess::setWeightCarge(const float &value) {_weightCharge = value; }



string MissionProcess::toString() const
{
    return toQString().toStdString();
}

QString MissionProcess::toQString() const {
    QString qs;
    qs.push_back("Mission Process :");
    qs.push_back("-----------------");
    qs.push_back(_missionType.toString());
    qs.push_back("Operator : " + _op.getFirstName() + " " + _op.getLastName());
    if(_activeDrone != nullptr)
        qs.push_back("Drone : " + QString::number(_activeDrone->getid()) );
    qs.push_back(_startDate.toString());
    qs.push_back(_startPoint.ToQString());
    qs.push_back(_endPoint.ToQString());
    qs.push_back("-----------------");
    return qs;
}


//int MissionProcess::getId() const
//{
//    return _id;
//}

void MissionProcess::setId(int id)
{
    _id = id;
}

DiscreteMap *MissionProcess::getMap() const
{
    return _map;
}

MissionProcess::MissionProcess() {
    _activeDrone = nullptr;
    _id = ++MissionProcess::_CurrentId;
}
MissionProcess::MissionProcess(Operator &o) {
    setOp(o);
    _id = ++MissionProcess::_CurrentId;
}

MissionProcess::MissionProcess(const MissionProcess &mp)
{
	_op = mp.getOp();
	_comm = mp.getComm();
	_endPoint = mp.getEndPoint();
	_startPoint = mp.getStartPoint();
	_startDate = mp.getStartDate();
	_activeDrone = mp.getActiveDrone();
	_commComment = mp.getCommComment();
	_missionType = mp.getMissionType();
	_opValidated = mp.getOpValidated();
	_commValidated = mp.getCommValidated();
}



MissionProcess& MissionProcess::operator=(const MissionProcess &mp)
{
	_op = mp.getOp();
	_comm = mp.getComm();
	_endPoint = mp.getEndPoint();
	_startPoint = mp.getStartPoint();
	_startDate = mp.getStartDate();
	_activeDrone = mp.getActiveDrone();
	_commComment = mp.getCommComment();
	_missionType = mp.getMissionType();
	_opValidated = mp.getOpValidated();
	_commValidated = mp.getCommValidated();
	return *this;
}


MissionProcess::~MissionProcess() {
    //cout << "Destruction Mission Process" << endl;
}

int MissionProcess::getid() const
{
    return _id;
}


void MissionProcess::read(QMap<int, MissionProcess *> *map, const QJsonObject &json)
{
    if (json.contains("missions") && json["missions"].isArray()) {
        QJsonArray missionArray = json["missions"].toArray();
        map->clear();
        for (int index = 0; index < missionArray.size(); ++index) {
            QJsonObject missionObject = missionArray[index].toObject();
            MissionProcess *mp = new MissionProcess;
            mp->readObject(missionObject);
            map->insert(mp->getid(), mp);
        }
    }
}

void MissionProcess::write(QMap<int, MissionProcess *> *map, QJsonObject &json)
{
    QJsonArray missionArray;
    for (const MissionProcess *mp : map->values()) {
        QJsonObject missionObject;
        mp->writeObject(missionObject);
        missionArray.append(missionObject);
    }
    json["missions"] = missionArray;
}


void MissionProcess::readObject(const QJsonObject &json)
{
    if (json.contains("id"))
        setId(json["id"].toInt());
	if (json.contains("startPoint") && json["startPoint"].isObject()) {
		QJsonObject startObject = json["startPoint"].toObject();
		_startPoint.readObject(startObject);
	}
	if (json.contains("endPoint") && json["endPoint"].isObject()) {
		QJsonObject endObject = json["endPoint"].toObject();
		_endPoint.readObject(endObject);
	}
	if (json.contains("startDate") && json["startDate"].isObject()) {
		QJsonObject dateObject = json["startDate"].toObject();
		_startDate = QDate(dateObject.value("year").toInt(),
						   dateObject.value("month").toInt(),
						   dateObject.value("day").toInt());
	}
	if(json.contains("missionType") && json["missionType"].isObject()) {
        QJsonObject missionObject = json["missionType"].toObject();
        _missionType.readObject(missionObject);
    }
	_CurrentId = _id;
}

void MissionProcess::writeObject(QJsonObject &json) const
{
    json["id"] = _id;
	QJsonObject startObject;
	_startPoint.writeObject(startObject);
	json["startPoint"] = startObject;
	QJsonObject endObject;
	_endPoint.writeObject(endObject);
	json["endPoint"] = endObject;
	QJsonObject dateObject;
	dateObject.insert("day",_startDate.day());
	dateObject.insert("month",_startDate.month());
	dateObject.insert("year",_startDate.year());
	json["date"] = dateObject;

    QJsonObject missionTypeObject;
    _missionType.writeObject(missionTypeObject);
    json["missionType"] = missionTypeObject;
}


bool MissionProcess::loadMissions(QMap<int, MissionProcess *> *map)
{
    QFile loadFile("missions.json");

    if(!loadFile.exists()) {
        qWarning("No such file : \"missions.json\"");
        return false;
    }
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open load file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    read(map, loadDoc.object());

    qDebug() << "Loaded save for Missions using JSON..." << endl;

    loadFile.close();
    return true;
}


bool MissionProcess::saveMissions(QMap<int, MissionProcess *> *map)
{
    QFile saveFile("missions.json");

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QJsonObject gameObject;
    write(map, gameObject);
    QJsonDocument saveDoc(gameObject);
    saveFile.write(saveDoc.toJson());

    qDebug() << "Saved Missions using JSON..." << endl;

    saveFile.close();
    return true;
}

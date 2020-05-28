#include "include/Admin.h"
#include "include/Commander.h"
#include "include/Operator.h"


User::User()
{
    //ctor
}

User::User(QString ln, QString fn, QString log, QString pwd)
{
    setLastName(ln);
    setFirstName(fn);
    setLogin(log);
	setPassword(pwd);
}

User::User(const User &u)
{
	_lastName = u.getLastName();
	_firstName = u.getFirstName();
	_login = u.getLogin();
	_password = u.getPassword();
}

User &User::operator=(const User &u)
{
	if(this!=&u) {
		_lastName = u.getLastName();
		_firstName = u.getFirstName();
		_login = u.getLogin();
		_password = u.getPassword();
	}

	return *this;
}

void User::infos()
{
	//cout << "Utilisateur : " << getLogin() << ", de nom/prenom " << getLastName() << " " << getFirstName() << " et mot de passe : " << getPassword() << endl;
}


std::string User::toString() {

	return "User";
}

void User::write(QMap<QString, User *> *map, QJsonObject &json)
{
	QJsonArray userArray;
	for (const User *u : map->values()) {
		QJsonObject userObject;

		const Admin *a = dynamic_cast<const Admin*>(u);
		if(a!=nullptr) {
			a->writeObject(userObject);
		}

		const Commander *c = dynamic_cast<const Commander*>(u);
		if(c!=nullptr) {
			c->writeObject(userObject);
		}

		const Operator *o = dynamic_cast<const Operator*>(u);
		if(o!=nullptr) {
			o->writeObject(userObject);
		}

		userArray.append(userObject);
	}
	json["users"] = userArray;
}

void User::read(QMap<QString, User *> *map, const QJsonObject &json)
{
	if (json.contains("users") && json["users"].isArray()) {
		QJsonArray userArray = json["users"].toArray();
		map->clear();
		int i;
		for (int index = 0; index < userArray.size(); ++index) {
			QJsonObject userObject = userArray[index].toObject();
			QString uType = userObject["type"].toString();
			i = userType.indexOf(uType);
			switch(i) {
				case 0: {
					Admin *a = new Admin;
					a->readObject(userObject);
					map->insert(a->getLogin(), a);
				break;
				}
				case 1: {
					Operator *o = new Operator;
					o->readObject(userObject);
					map->insert(o->getLogin(), o);
				break;
				}
				case 2: {
					Commander *c = new Commander;
					c->readObject(userObject);
					map->insert(c->getLogin(), c);
				break;
				}
			}
		}
	}
}

bool User::saveUsers(QMap<QString, User *> *map)
{
	QFile saveFile("users.json");

	if (!saveFile.open(QIODevice::WriteOnly)) {
		qWarning("Couldn't open save file.");
		return false;
	}

	QJsonObject usersObject;
	write(map, usersObject);
	QJsonDocument saveDoc(usersObject);
	saveFile.write(saveDoc.toJson());

	qDebug() << "Saved Drones using JSON..." << endl;

	saveFile.close();
	return true;
}

bool User::loadUsers(QMap<QString, User *> *map)
{
	QFile loadFile("users.json");

	if(!loadFile.exists()) {
		qWarning("No such file : \"users.json\"");
		return false;
	}
	if (!loadFile.open(QIODevice::ReadOnly)) {
		qWarning("Couldn't open load file.");
		return false;
	}

	QByteArray saveData = loadFile.readAll();

	QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

	read(map, loadDoc.object());

	qDebug() << "Loaded save for Users using JSON..." << endl;

	loadFile.close();
	return true;
}

void User::readObject(const QJsonObject &json)
{
	if (json.contains("login") && json["login"].isString())
		setLogin(json["login"].toString());
	if (json.contains("password") && json["password"].isString())
		setPassword(json["password"].toString());
	if (json.contains("firstName") && json["firstName"].isString())
		setFirstName(json["firstName"].toString());
	if (json.contains("lastName") && json["lastName"].isString())
		setLastName(json["lastName"].toString());
}
//dtor
User::~User()
{
    //cout << "Destruction User" << endl;
}

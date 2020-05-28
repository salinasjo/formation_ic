#include "include/Commander.h"

Commander::Commander() : User()
{
    //ctor
}

Commander::Commander(QString ln, QString fn, QString log, QString pwd)
	:User(ln, fn, log, pwd)
{

}

Commander::Commander(const Commander &c)
	:User(c)
{

}

void Commander::missionValidation()
{

}

void Commander::addDrone()
{

}

bool Commander::addDrone(QMap<int, Drone *> *m, Drone *d)
{
	if(m->contains(d->getid())) {
		m->insert(d->getid(), d);
		return false;
	}
	else {
		m->insert(d->getid(), d);
		return true;
	}

}

void Commander::modifyDrone()
{

}

bool Commander::deleteDrone(QMap<int, Drone *> *m, Drone *d)
{
	if(m->contains(d->getid())) {
		d->setDeleted(true);
		return true;
	}
	return false;
}

std::string Commander::toString()
{
	return "Comm";
}

void Commander::writeObject(QJsonObject &json) const
{
	json["login"] = _login;
	json["password"] = _password;
	json["firstName"] = _firstName;
	json["lastName"] = _lastName;
	json["type"] = "commander";

}

Commander Commander::operator=(const Commander &c)
{
	if(this!=&c) {
		_lastName = c.getLastName();
		_firstName = c.getFirstName();
		_login = c.getLogin();
		_password = c.getPassword();
	}
	return *this;
}

//dtor
Commander::~Commander()
{
    //cout << "Destruction Commander" << endl;
}

#include "include/Admin.h"

Admin::Admin():User()
{
    //ctor
}

Admin::Admin(QString ln, QString fn, QString log, QString pwd)
	:User(ln, fn, log, pwd)
{

}

Admin::Admin(const Admin &a)
	:User(a)
{

}

Admin Admin::operator=(const Admin &a)
{
	_lastName = a.getLastName();
	_firstName = a.getFirstName();
	_login = a.getLogin();
	_password = a.getPassword();
	return *this;
}


void Admin::addUser()
{

}

void Admin::modifyUser()
{

}

void Admin::deleteUser()
{

}

void Admin::writeObject(QJsonObject &json) const
{
	json["login"] = _login;
	json["password"] = _password;
	json["firstName"] = _firstName;
	json["lastName"] = _lastName;
	json["type"] = "admin";

}

Admin::~Admin()
{
    //dtor
}

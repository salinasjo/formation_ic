#include "include/Operator.h"
#include "include/MissionProcess.h"

Operator::Operator() : User()
{
    //ctor
}

Operator::Operator(QString ln, QString fn, QString log, QString pwd)
	:User(ln, fn, log, pwd)
{

}

Operator::Operator(const Operator &op)
	: User(op)
{

}

void Operator::missionManagement()
{

}

void Operator::missionTypeManagement()
{

}

std::string Operator::toString()
{
	return "Op";
}

void Operator::writeObject(QJsonObject &json) const
{
	json["login"] = _login;
	json["password"] = _password;
	json["firstName"] = _firstName;
	json["lastName"] = _lastName;
	json["type"] = "operator";
}

Operator Operator::operator=(const Operator &op)
{
	_lastName = op.getLastName();
	_firstName = op.getFirstName();
	_login = op.getLogin();
	_password = op.getPassword();
	return *this;
}


//dtor
Operator::~Operator()
{
    //cout << "Destruction Operator" << endl;
}

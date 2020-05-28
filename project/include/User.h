#ifndef USER_H
#define USER_H
#include <iostream>
#include <QObject>
#include <QDebug>

#include <QFile>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

using namespace std;

static QStringList userType {"admin", "operator", "commander" };
class User
{
    public:
		explicit User();
		User(QString, QString, QString, QString);
		User(const User &);
		User& operator=(const User&);
        virtual ~User();

		QString getLastName() const { return _lastName; }
		void setLastName(QString val) { _lastName = val; }
		QString getFirstName() const { return _firstName; }
		void setFirstName(QString val) { _firstName = val; }
		QString getLogin() const { return _login; }
		void setLogin(QString val) { _login = val; }
		QString getPassword() const { return _password; }
		void setPassword(QString val) { _password = val; }

        //Temporary, just to check if everything is in place
        void infos();
		virtual std::string toString();

		//Read and write to JSON
		static void write(QMap<QString, User *> *map, QJsonObject &json);
		static void read(QMap<QString, User *> *map, const QJsonObject &json);
		static bool saveUsers(QMap<QString, User *> *map);
		static bool loadUsers(QMap<QString, User *> *map);
		void readObject(const QJsonObject &json);


    protected:
		QString _lastName;
		QString _firstName;
		QString _login;
		QString _password;
    private:

};

#endif // USER_H

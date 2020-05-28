#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"


class Admin : public User
{

    public:
		explicit Admin();
		Admin(QString, QString, QString, QString);
		Admin(const Admin &);
		Admin operator=(const Admin &);
        virtual ~Admin();

        void addUser();
        void modifyUser();
        void deleteUser();

		void writeObject(QJsonObject &json) const;


    protected:

    private:
};

#endif // ADMIN_H

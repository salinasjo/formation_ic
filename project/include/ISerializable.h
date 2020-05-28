#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

#include <QJsonObject>



class ISerializable
{
public:
	virtual ~ISerializable() {}
	virtual void readObject(const QJsonObject &json)=0;
	virtual void writeObject(QJsonObject &json) const=0;
    virtual int getid() const = 0;
};

#endif // ISERIALIZABLE_H

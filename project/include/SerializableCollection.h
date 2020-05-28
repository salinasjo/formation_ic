#ifndef SERIALIZABLECOLLECTION_H
#define SERIALIZABLECOLLECTION_H

#include "ISerializable.h"

#include <QByteArray>
#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMap>

template <class T>
class SerializableCollection
{
public:
	explicit SerializableCollection(QString fileName, QString content);
	explicit SerializableCollection(const SerializableCollection &other);
	~SerializableCollection();
	SerializableCollection& operator=(const SerializableCollection &other);


	QString getSrc() const {return _fileName;}
	void setSrc(const QString fileName) {_fileName = fileName;}
	QString getContent() const {return _content;}
	void setContent(const QString content) {_content = content;}
	QMap<int, T*>* getMap() const {return _map;}

	bool load();
	bool save();
	void read(const QJsonObject &json);
	void write(QJsonObject &json);

private:
	QMap<int, T*> *_map;
	QString _fileName;
	QString _content;
};

#endif // SERIALIZABLECOLLECTION_H

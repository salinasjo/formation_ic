#include "../include/SerializableCollection.h"

#include "../include/Drone.h"

#include "include/MissionProcess.h"

template <class T>
SerializableCollection<T>::SerializableCollection(QString fileName, QString content)
{
	_map = new QMap<int, T*>();
	_fileName = fileName;
	_content = content;
}
template <class T>
SerializableCollection<T>::SerializableCollection(const SerializableCollection &other)
{
	_map = other.getMap();
	_fileName = other.getSrc();
	_content = other.getContent();
}
template <class T>
SerializableCollection<T>::~SerializableCollection()
{
	for(auto *d : _map->values()) {
		delete d;
	}
	delete _map;
}
template <class T>
SerializableCollection<T>& SerializableCollection<T>::operator=(const SerializableCollection &other) {
	_map = other.getMap();
	_fileName = other.getSrc();
	_content = other.getContent();
	return *this;
}

//Reading and Writing to File
template <class T>
bool SerializableCollection<T>::load()
{
	QFile loadFile(_fileName);

	if(!loadFile.exists()) {
		qDebug() << "No such file : \"" << _fileName << "\"";
		return false;
	}
	if (!loadFile.open(QIODevice::ReadOnly)) {
		qDebug() << "Couldn't open load file \"" << _fileName << "\"";
		return false;
	}

	QByteArray saveData = loadFile.readAll();

	QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

	read(loadDoc.object());

	qDebug() << "Loaded save for " << _content << " using JSON..." << endl;

	loadFile.close();
	return true;
}

template <class T>
bool SerializableCollection<T>::save()
{
	QFile saveFile(_fileName);

	if (!saveFile.open(QIODevice::WriteOnly)) {
		qDebug() << "Couldn't open save file \"" << _fileName << "\"";
		return false;
	}

	QJsonObject dronesObject;
	write(dronesObject);
	QJsonDocument saveDoc(dronesObject);
	saveFile.write(saveDoc.toJson());

	qDebug() << "Saved " << _content << " using JSON..." << endl;

	saveFile.close();
	return true;
}

template <class T>
void SerializableCollection<T>::read(const QJsonObject &json)
{
	if (json.contains(_content) && json[_content].isArray()) {
		QJsonArray array = json[_content].toArray();
		_map->clear();
		for (int index = 0; index < array.size(); ++index) {
			QJsonObject serObject = array[index].toObject();
			T *d = new T();
			d->readObject(serObject);
			_map->insert(d->getid(), d);
		}
	}
}

template <class T>
void SerializableCollection<T>::write(QJsonObject &json)
{
	QJsonArray droneArray;
	for(T *d : _map->values()) {
		QJsonObject droneObject;
		d->writeObject(droneObject);
		droneArray.append(droneObject);
	}
	json[_content] = droneArray;
}

template class SerializableCollection<Drone>;
template class SerializableCollection<MissionProcess>;
